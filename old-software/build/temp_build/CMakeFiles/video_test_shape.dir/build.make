# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/browse/Documents/summer_2019/RASM/rasm-software/build/temp_build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/browse/Documents/summer_2019/RASM/rasm-software/build/temp_build

# Include any dependencies generated for this target.
include CMakeFiles/video_test_shape.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/video_test_shape.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/video_test_shape.dir/flags.make

CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.o: CMakeFiles/video_test_shape.dir/flags.make
CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.o: /home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/browse/Documents/summer_2019/RASM/rasm-software/build/temp_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.o -c /home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp

CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp > CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.i

CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp -o CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.s

CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.o.requires:

.PHONY : CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.o.requires

CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.o.provides: CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.o.requires
	$(MAKE) -f CMakeFiles/video_test_shape.dir/build.make CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.o.provides.build
.PHONY : CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.o.provides

CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.o.provides.build: CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.o


# Object files for target video_test_shape
video_test_shape_OBJECTS = \
"CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.o"

# External object files for target video_test_shape
video_test_shape_EXTERNAL_OBJECTS =

video_test_shape: CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.o
video_test_shape: CMakeFiles/video_test_shape.dir/build.make
video_test_shape: dlib_build/libdlib.a
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_face.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_text.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libnsl.so
video_test_shape: /usr/lib/x86_64-linux-gnu/libSM.so
video_test_shape: /usr/lib/x86_64-linux-gnu/libICE.so
video_test_shape: /usr/lib/x86_64-linux-gnu/libX11.so
video_test_shape: /usr/lib/x86_64-linux-gnu/libXext.so
video_test_shape: /usr/lib/x86_64-linux-gnu/libgif.so
video_test_shape: /usr/lib/x86_64-linux-gnu/libpng.so
video_test_shape: /usr/lib/x86_64-linux-gnu/libz.so
video_test_shape: /usr/lib/x86_64-linux-gnu/libjpeg.so
video_test_shape: /usr/lib/x86_64-linux-gnu/libopenblas.so
video_test_shape: /usr/lib/x86_64-linux-gnu/libsqlite3.so
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_video.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.3.2.0
video_test_shape: /usr/lib/x86_64-linux-gnu/libopencv_core.so.3.2.0
video_test_shape: CMakeFiles/video_test_shape.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/browse/Documents/summer_2019/RASM/rasm-software/build/temp_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable video_test_shape"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/video_test_shape.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/video_test_shape.dir/build: video_test_shape

.PHONY : CMakeFiles/video_test_shape.dir/build

CMakeFiles/video_test_shape.dir/requires: CMakeFiles/video_test_shape.dir/home/browse/Documents/fall_2018/me4010/rasm-v2/include/vision/test_file.cpp.o.requires

.PHONY : CMakeFiles/video_test_shape.dir/requires

CMakeFiles/video_test_shape.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/video_test_shape.dir/cmake_clean.cmake
.PHONY : CMakeFiles/video_test_shape.dir/clean

CMakeFiles/video_test_shape.dir/depend:
	cd /home/browse/Documents/summer_2019/RASM/rasm-software/build/temp_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/browse/Documents/summer_2019/RASM/rasm-software/build/temp_build /home/browse/Documents/summer_2019/RASM/rasm-software/build/temp_build /home/browse/Documents/summer_2019/RASM/rasm-software/build/temp_build /home/browse/Documents/summer_2019/RASM/rasm-software/build/temp_build /home/browse/Documents/summer_2019/RASM/rasm-software/build/temp_build/CMakeFiles/video_test_shape.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/video_test_shape.dir/depend

