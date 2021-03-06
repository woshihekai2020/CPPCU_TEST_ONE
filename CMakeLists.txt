cmake_minimum_required(VERSION 3.10)
project(CPPCU_TEST_ONE)

find_package(PythonInterp REQUIRED) #ADD HEKAI , must be first place
#or cause error:Failed to compute shorthash for libnvrtc.so

#set(CMAKE_CXX_STANDARD 14)

#add_executable(CPPCU_TEST_ONE main.cpp)

#cmake_minimum_required(VERSION 2.8.4)  #版本最小为2.8.4

#PROJECT(dlib_facedetector)   #设置工程名

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -DDLIB_JPEG_SUPPORT ")

IF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
ENDIF()



# #INCLUDE OPENCV
# include_directories(/home/local/include/opencv/)
# include_directories(/home/local/include/opencv2/)
# include_directories(/home/local/include/)
# link_libraries(opencv_core)
# link_libraries(opencv_highgui)
# link_libraries(opencv_imgproc)
#INCLUDE OPENCV
FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
message(STATUS "Opencv include dir found at ${OpenCV_INCLUDE_DIRS}")


find_package( realsense2 REQUIRED )
include_directories( ${realsense2_INCLUDE_DIRS} )


#INCLUDE LIBTORCH
include_directories(/usr/local/include)
include_directories(~/.virtualenvs/Vyolo5/lib/python3.6/site-packages/torch/include/torch/csrc/api/include)
include_directories(~/.virtualenvs/Vyolo5/lib/python3.6/dist-packages/torch/include)
link_directories(/usr/local/lib)
link_directories(~/.virtualenvs/Vyolo5/lib/python3.6/site-packages/torch/lib)
set(CMAKE_PREFIX_PATH ~/.virtualenvs/Vyolo5/lib/python3.6/site-packages/torch)
set(Boost_USE_MULTITHREADED ON)
set(Torch_DIR ~/.virtualenvs/Vyolo5/lib/python3.6/site-packages/torch)
find_package(Torch REQUIRED)


#包含头文件DLIB, 19.22 USE CUDA
#INCLUDE_DIRECTORIES(~/dep/3_Face/dlib) #dlib根目录地址
#LINK_DIRECTORIES(~/dep/3_Face/dlib/build/dlib/) #dlib编译后bulid下dlib地址


find_package( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS})
find_package( Eigen3 REQUIRED )
add_definitions( ${EIGEN3_DEFINITIONS} )
include_directories( ${EIGEN3_INCLLUDE_DIRS} )
find_package( Ceres REQUIRED )
include_directories( ${CERES_INCLUDE_DIRS} )
#list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )
set( G2O_ROOT /usr/local/include/g2o )
include_directories( ${G2O_INCLUDE_DIRS} )



#生产类似于.exe的可执行文件
ADD_EXECUTABLE(CPPCU_TEST_ONE 9_thread.cpp)

#链接库
#TARGET_LINK_LIBRARIES(CPPCU_TEST_ONE dlib ${OpenCV_LIBS} ${realsense2_LIBRARY} )
TARGET_LINK_LIBRARIES(CPPCU_TEST_ONE  {OpenCV_LIBS} ${realsense2_LIBRARY} )
target_link_libraries(CPPCU_TEST_ONE ${TORCH_LIBRARIES})
#TARGET_LINK_LIBRARIES(dlib_detector libjpeg.so)
target_link_libraries(CPPCU_TEST_ONE
        ${OpenCV_LIBS}
        ${EIGEN3_LIBS}
        ${CERES_LIBRARIES}
        ${G2O_CORE_LIBRARY} ${G2O_STUFF_LIBRARY}
        g2o_types_slam3d g2o_core g2o_stuff g2o_types_sba g2o_solver_csparse
        g2o_csparse_extension cholmod g2o_solver_cholmod
        )


set_property(TARGET CPPCU_TEST_ONE PROPERTY CXX_STANDARD 14)
