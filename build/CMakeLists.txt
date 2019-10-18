cmake_minimum_required(VERSION 2.8.12)
project(test_vision)
find_package( OpenCV REQUIRED )
find_package( PythonLibs 3 REQUIRED )
set(CMAKE_BUILD_TYPE RelWithDebInfo)
add_subdirectory(/home/browse/Documents/fall_2018/me4010/lib/lib/download/dlib-19.13/dlib dlib_build)
add_executable(video_test_shape
  /home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp)
add_executable(vision_func
  /home/browse/Documents/summer_2019/RASM/rasm-software/main.cpp)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(video_test_shape dlib::dlib)
target_link_libraries(vision_func dlib::dlib)
target_link_libraries( video_test_shape ${OpenCV_LIBS} )
target_link_libraries( vision_func ${OpenCV_LIBS} )
target_link_libraries( vision_func ${PYTHON_LIBRARIES})

