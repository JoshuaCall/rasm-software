import dlib
import cv2
import numpy

if __name__ == "__main__":
    print("hello world")
    cap = cv2.VideoCapture(1)
    #cap = cv2.VideoCapture(0)
    if(not cap.isOpened()):
        print("Unable to connect to camera")
        exit() 
    print(dlib.__version__)
    detector = dlib.get_frontal_face_detector()
    predictor = dlib.shape_predictor("/home/browse/Documents/fall_2018/me4010/rasm-v2/test/filesysroot/rasm_2_1/data/vision/prediction/face_model_68_points.dat")
    #TODO     //fill in cam intrinsics and distortion coefficients
    object_pts = numpy.array([
        [6.825897, 6.760612, 4.402142],
        [2.330353, 7.122144, 6.903745],
        [-1.330353, 7.122144, 6.903745],
        [-6.825897, 6.760612, 4.402142],
        [5.311432, 5.485328, 3.987654],
        [1.789930, 5.393625, 4.413414],
        [-1.789930, 5.393625, 4.413414],
        [-5.311432, 5.485328, 3.987654],
        [2.005628, 1.409845, 6.165652],
        [-2.005628, 1.409845, 6.165652],
        [2.774015, -2.080775, 5.048531],
        [-2.774015, -2.080775, 5.048531],
        [0.000000, -3.116408, 6.097667],
        [0.000000, -7.415691, 4.070434]
        ],
        dtype=numpy.float64)
    image_pts = numpy.array([
