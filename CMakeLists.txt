cmake_minimum_required(VERSION 2.8.3)
project(cut_circle)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)
#set( CMAKE_CXX_COMPILER "/usr/bin/clang++" )

find_package(catkin REQUIRED COMPONENTS
  image_transport
  roscpp
  rospy
  std_msgs
  geometry_msgs
)

set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#find_package(PCL REQUIRED)
#include_directories(${PCL_INCLUDE_DIRS})

#find_package(VTK REQUIRED)
#include_directories(${VTK_INCLUDE_DIRS})

#FIND_PACKAGE(OpenGL)
#IF(OPENGL_FOUND)
#MESSAGE("OpenGL found")
#INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
##TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OPENGL_LIBRARIES})
#ELSE(OPENGL_FOUND)
#MESSAGE(FATAL_ERROR "OpenGL not found")
#ENDIF(OPENGL_FOUND)

#FIND_PACKAGE(GLUT)
#IF(GLUT_FOUND)
#MESSAGE("GLUT found")
#INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIR})
##TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${GLUT_LIBRARIES})
#ELSE(GLUT_FOUND)
#MESSAGE(FATAL_ERROR "GLUT not found")
#ENDIF(GLUT_FOUND)

include_directories(
  /usr/include/eigen3
  ${catkin_INCLUDE_DIRS}
  include
)

# Describe catkin Project
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS image_transport roscpp rospy  std_msgs geometry_msgs
)

#ADD_LIBRARY(config STATIC src/config.cpp )

##-------------------------executables----------------------------- 
#cut_circle
add_executable(cut_circle src/cut_circle_exe.cpp src/cut_circle.cpp)
target_link_libraries(cut_circle ${OpenCV_LIBS} ${catkin_LIBRARIES})
#add_dependencies(cut_circle cut_circle_generate_message_cpp)
