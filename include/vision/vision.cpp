#include <Python.h>
#include <iostream>
#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <fstream>
#include <unistd.h>
#include <cmath>
#include <stdio.h>
#include <time.h>

//Intrisics can be calculated using opencv sample code under opencv/sources/samples/cpp/tutorial_code/calib3d
//Normally, you can also apprximate fx and fy by image width, cx by half image width, cy by half image height instead
double K[9] = {7.3530833553043510e+02, 0.0, 320.0, 0.0, 7.3530833553043510e+02, 240.0, 0.0, 0.0, 1.0};
double D[5] = {-2.3528667558034226e-02, 1.3301431879108856e+00, 0.0, 0.0,
    -6.0786673300480434e+00};
const int debounce_camera_time_delay = 1;

int main(int argc, char *argv[]){

    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    Py_SetProgramName(program);  /* optional but recommended */
    Py_Initialize();
    PyRun_SimpleString("import serial\n");
    PyRun_SimpleString("ser = serial.Serial('/dev/ttyACM0', 9600, timeout=5)");
    cv::VideoCapture cap(1);
    if (!cap.isOpened())
        {
        std::cout << "Unable to connect to camera" << std::endl;
        return EXIT_FAILURE;
        }
    //Load face detection and pose estimation models (dlib).
    dlib::frontal_face_detector detector;
    dlib::shape_predictor predictor;
    detector = dlib::get_frontal_face_detector();
    dlib::deserialize("/home/browse/Documents/fall_2018/me4010/rasm-v2/test/filesysroot/rasm_2_1/data/vision/prediction/face_model_68_points.dat") >> predictor;
     //fill in cam intrinsics and distortion coefficients
    cv::Mat cam_matrix = cv::Mat(3, 3, CV_64FC1, K);
    cv::Mat dist_coeffs = cv::Mat(5, 1, CV_64FC1, D);
    //fill in 3D ref points(world coordinates), model referenced from http://aifi.isr.uc.pt/Downloads/OpenGL/glAnthropometric3DModel.cpp
    std::vector<cv::Point3d> object_pts;
 
    object_pts.push_back(cv::Point3d(6.825897, 6.760612, 4.402142));     //#33 left brow left corner
    object_pts.push_back(cv::Point3d(1.330353, 7.122144, 6.903745));     //#29 left brow right corner
    object_pts.push_back(cv::Point3d(-1.330353, 7.122144, 6.903745));    //#34 right brow left corner
    object_pts.push_back(cv::Point3d(-6.825897, 6.760612, 4.402142));    //#38 right brow right corner
    object_pts.push_back(cv::Point3d(5.311432, 5.485328, 3.987654));     //#13 left eye left corner
    object_pts.push_back(cv::Point3d(1.789930, 5.393625, 4.413414));     //#17 left eye right corner
    object_pts.push_back(cv::Point3d(-1.789930, 5.393625, 4.413414));    //#25 right eye left corner
    object_pts.push_back(cv::Point3d(-5.311432, 5.485328, 3.987654));    //#21 right eye right corner
    object_pts.push_back(cv::Point3d(2.005628, 1.409845, 6.165652));     //#55 nose left corner
    object_pts.push_back(cv::Point3d(-2.005628, 1.409845, 6.165652));    //#49 nose right corner
    object_pts.push_back(cv::Point3d(2.774015, -2.080775, 5.048531));    //#43 mouth left corner
    object_pts.push_back(cv::Point3d(-2.774015, -2.080775, 5.048531));   //#39 mouth right corner
    object_pts.push_back(cv::Point3d(0.000000, -3.116408, 6.097667));    //#45 mouth central bottom corner
    object_pts.push_back(cv::Point3d(0.000000, -7.415691, 4.070434));    //#6 chin corner

    //2D ref points(image coordinates), referenced from detected facial feature
    std::vector<cv::Point2d> image_pts;

    //result
    cv::Mat rotation_vec;                           //3 x 1
    cv::Mat rotation_mat;                           //3 x 3 R
    cv::Mat translation_vec;                        //3 x 1 T
    cv::Mat pose_mat = cv::Mat(3, 4, CV_64FC1);     //3 x 4 R | T
    cv::Mat euler_angle = cv::Mat(3, 1, CV_64FC1);

    //reproject 3D points world coordinate axis to verify result pose
    std::vector<cv::Point3d> reprojectsrc;
    reprojectsrc.push_back(cv::Point3d(10.0, 10.0, 10.0));
    reprojectsrc.push_back(cv::Point3d(10.0, 10.0, -10.0));
    reprojectsrc.push_back(cv::Point3d(10.0, -10.0, -10.0));
    reprojectsrc.push_back(cv::Point3d(10.0, -10.0, 10.0));
    reprojectsrc.push_back(cv::Point3d(-10.0, 10.0, 10.0));
    reprojectsrc.push_back(cv::Point3d(-10.0, 10.0, -10.0));
    reprojectsrc.push_back(cv::Point3d(-10.0, -10.0, -10.0));
    reprojectsrc.push_back(cv::Point3d(-10.0, -10.0, 10.0));

    //reprojected 2D points
    std::vector<cv::Point2d> reprojectdst;
    reprojectdst.resize(8);

    //temp buf for decomposeProjectionMatrix()
    cv::Mat out_intrinsics = cv::Mat(3, 3, CV_64FC1);
    cv::Mat out_rotation = cv::Mat(3, 3, CV_64FC1);
    cv::Mat out_translation = cv::Mat(3, 1, CV_64FC1);

    //text on screen
    std::ostringstream outtext;
    bool still_roll = false;
    bool still_y = false;
    time_t time_since_still_roll = 0;
    time_t time_since_still_y = 0;
    while (1)
    {
      //usleep(500000);
        // Grab a frame
        cv::Mat temp;
        cap >> temp;

        dlib::cv_image<dlib::bgr_pixel> cimg(temp);

        // Detect faces
        std::vector<dlib::rectangle> faces = detector(cimg);

        // Find the pose of each face
        if (faces.size() > 0)
            {
            //std::cout << "DETECTED " << faces.size() << std::endl << std::endl;
            //track features
            dlib::full_object_detection shape = predictor(cimg, faces[0]);

            //draw features
            for (unsigned int i = 0; i < 68; ++i)
                {
                cv::circle(temp, cv::Point(shape.part(i).x(), shape.part(i).y()), 2, cv::Scalar(0, 0, 255), -1);
                }

            //fill in 2D ref points, annotations follow https://ibug.doc.ic.ac.uk/resources/300-W/

            image_pts.push_back(cv::Point2d(shape.part(17).x(), shape.part(17).y())); //#17 left brow left corner
            image_pts.push_back(cv::Point2d(shape.part(21).x(), shape.part(21).y())); //#21 left brow right corner
            image_pts.push_back(cv::Point2d(shape.part(22).x(), shape.part(22).y())); //#22 right brow left corner
            image_pts.push_back(cv::Point2d(shape.part(26).x(), shape.part(26).y())); //#26 right brow right corner
            image_pts.push_back(cv::Point2d(shape.part(36).x(), shape.part(36).y())); //#36 left eye left corner
            image_pts.push_back(cv::Point2d(shape.part(39).x(), shape.part(39).y())); //#39 left eye right corner
            image_pts.push_back(cv::Point2d(shape.part(42).x(), shape.part(42).y())); //#42 right eye left corner
            image_pts.push_back(cv::Point2d(shape.part(45).x(), shape.part(45).y())); //#45 right eye right corner
            image_pts.push_back(cv::Point2d(shape.part(31).x(), shape.part(31).y())); //#31 nose left corner
            image_pts.push_back(cv::Point2d(shape.part(35).x(), shape.part(35).y())); //#35 nose right corner
            image_pts.push_back(cv::Point2d(shape.part(48).x(), shape.part(48).y())); //#48 mouth left corner
            image_pts.push_back(cv::Point2d(shape.part(54).x(), shape.part(54).y())); //#54 mouth right corner
            image_pts.push_back(cv::Point2d(shape.part(57).x(), shape.part(57).y())); //#57 mouth central bottom corner
            image_pts.push_back(cv::Point2d(shape.part(8).x(), shape.part(8).y()));   //#8 chin corner

            //calc pose
            cv::solvePnP(object_pts, image_pts, cam_matrix, dist_coeffs, rotation_vec, translation_vec);

            //reproject
            cv::projectPoints(reprojectsrc, rotation_vec, translation_vec, cam_matrix, dist_coeffs, reprojectdst);

            //draw axis
            cv::line(temp, reprojectdst[0], reprojectdst[1], cv::Scalar(0, 0, 255));
            cv::line(temp, reprojectdst[1], reprojectdst[2], cv::Scalar(0, 0, 255));
            cv::line(temp, reprojectdst[2], reprojectdst[3], cv::Scalar(0, 0, 255));
            cv::line(temp, reprojectdst[3], reprojectdst[0], cv::Scalar(0, 0, 255));
            cv::line(temp, reprojectdst[4], reprojectdst[5], cv::Scalar(0, 0, 255));
            cv::line(temp, reprojectdst[5], reprojectdst[6], cv::Scalar(0, 0, 255));
            cv::line(temp, reprojectdst[6], reprojectdst[7], cv::Scalar(0, 0, 255));
            cv::line(temp, reprojectdst[7], reprojectdst[4], cv::Scalar(0, 0, 255));
            cv::line(temp, reprojectdst[0], reprojectdst[4], cv::Scalar(0, 0, 255));
            cv::line(temp, reprojectdst[1], reprojectdst[5], cv::Scalar(0, 0, 255));
            cv::line(temp, reprojectdst[2], reprojectdst[6], cv::Scalar(0, 0, 255));
            cv::line(temp, reprojectdst[3], reprojectdst[7], cv::Scalar(0, 0, 255));
            cv::Point2d my_point = ((reprojectdst[0] + reprojectdst[1] + reprojectdst[2] + reprojectdst[3] + reprojectdst[4] + reprojectdst[5] + reprojectdst[6] + reprojectdst[7])/8);
            double my_x = my_point.x;
            double my_y = my_point.y;
            double x_for_pose = my_x/temp.cols;
            double y_for_pose = my_y/temp.rows;
            //std::cout << x_for_pose << std::endl;
            //std::cout << y_for_pose << std::endl;
            x_for_pose = x_for_pose -0.5;
            y_for_pose = y_for_pose -0.5;
            double x_distance = -translation_vec.at<double>(1,1)*atan(27.6*3.14159265/180)*x_for_pose/0.5;
            double y_distance = translation_vec.at<double>(1,1)*atan(20*3.14159265/180)*y_for_pose/0.5;

            //calc euler angle
            cv::Rodrigues(rotation_vec, rotation_mat);
            cv::hconcat(rotation_mat, translation_vec, pose_mat);
            cv::decomposeProjectionMatrix(pose_mat, out_intrinsics, out_rotation, out_translation, cv::noArray(), cv::noArray(), cv::noArray(), euler_angle);

                          //show angle result
            //outtext << "X: " << std::setprecision(3) << euler_angle.at<double>(0);
            double z_pos = -translation_vec.at<double>(1, 1)/2.54;
            outtext << "Distance from camera [in]: " << std::setprecision(3) << z_pos;
            cv::putText(temp, outtext.str(), cv::Point(50, 40), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 0, 0));
            outtext.str("");
            double x_pos = x_distance/2.54;
            outtext << "x position [in]: " << std::setprecision(3) << x_pos;
            //outtext << "Y: " << std::setprecision(3) << euler_angle.at<double>(1);
            cv::putText(temp, outtext.str(), cv::Point(50, 60), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 0, 0));
            outtext.str("");
            //outtext << "Z: " << std::setprecision(3) << euler_angle.at<double>(2);
            double y_pos = y_distance/2.54;
            outtext << "y position [in]: " << std::setprecision(3) << y_pos;
            cv::putText(temp, outtext.str(), cv::Point(50, 80), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 0, 0));
            outtext.str("");
            //outtext << "rot_vec 1: " << std::setprecision(3) << rotation_vec.at<double>(1, 1);
            double pitch = euler_angle.at<double>(0);
            outtext << "Pitch in degrees: " << std::setprecision(3) << pitch;
            cv::putText(temp, outtext.str(), cv::Point(50, 100), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 0, 0));
            outtext.str("");
            //outtext << "rot_vec 2: " << std::setprecision(3) << rotation_vec.at<double>(2, 1);
            double yaw = euler_angle.at<double>(1);
            outtext << "Yaw in degrees: " << std::setprecision(3) << yaw;
            cv::putText(temp, outtext.str(), cv::Point(50, 120), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 0, 0));
            outtext.str("");
            //outtext << "rot_vec 3: " << std::setprecision(3) << rotation_vec.at<double>(3, 1);
            double roll = euler_angle.at<double>(2);
            outtext << "Roll in degrees: " << std::setprecision(3) << roll;
            cv::putText(temp, outtext.str(), cv::Point(50, 140), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 0, 0));
            outtext.str("");
            char buffer[100];
            if(still_roll)
            {
              time_since_still_roll = time(NULL);
            }
            if(abs(roll) < 5)
            {
              roll = 0.0;
              still_roll = true;
            }
            else
            {
              still_roll = false;
            }
            if(time(NULL) < time_since_still_roll + debounce_camera_time_delay)
            {
              roll = 0.0;
            }
            sprintf(buffer,"ser.write('#%+03d\\x00'.encode())", (int)(roll*-2));
            PyRun_SimpleString(buffer);
            if(still_y)
            {
              time_since_still_y = time(NULL);
            }
            if(abs(y_pos) <= 3)
            {
              y_pos = 0;
              still_y = true;
            }
            else
            {
              still_y = false;
            }
            if(time(NULL) < time_since_still_y + debounce_camera_time_delay)
            {
              y_pos = 0.0;
            }
            sprintf(buffer,"ser.write('$%+03d\\x00'.encode())", (int)(y_pos*-2));
            PyRun_SimpleString(buffer);
            image_pts.clear();
            }
 //press esc to end
        cv::namedWindow( "demo", cv::WINDOW_NORMAL);
        cv::imshow("demo", temp);
        unsigned char key = cv::waitKey(1);
        if (key == 27)
            {
            break;
            }
    }
    PyMem_RawFree(program);
    return 0;
}

