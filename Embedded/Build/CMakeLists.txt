### CMakeLists to compile the embedded tictactoe program
###
### Author : Pierre-Louis TILAK
### Date : 20 Nov 2014

cmake_minimum_required (VERSION 2.8.9)
SET(CMAKE_SYSTEM_NAME Linux)


# specify the cross compiler and the target environment
IF(WIN32)
  SET(CMAKE_C_COMPILER   arm-none-linux-gnueabi-gcc)
  SET(CMAKE_CXX_COMPILER arm-none-linux-gnueabi-g++)
  SET(CMAKE_SYSROOT        "C:/CodeBench")
  SET(CMAKE_FIND_ROOT_PATH "C:/CodeBench")
ELSE()
  SET(CMAKE_C_COMPILER   arm-linux-gnueabi-gcc)
  SET(CMAKE_CXX_COMPILER arm-linux-gnueabi-g++)
  SET(CMAKE_SYSROOT        /usr/arm-linux-gnueabi/)
  SET(CMAKE_FIND_ROOT_PATH /usr/arm-linux-gnueabi/)
ENDIF()


# compiler options
SET(CMAKE_C_FLAGS   "" CACHE STRING "" FORCE)
SET(CMAKE_CXX_FLAGS "-std=c++11" CACHE STRING "" FORCE)


# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

project(tictactoe)

### Requirements
find_package(Threads REQUIRED)
find_package(OpenCV  REQUIRED)


include_directories(${OpenCV_INCLUDE_DIRS} ../Sources)
include_directories(${OpenCV_INCLUDE_DIRS} ../../Common)

SET(TICTACTOE_SRC
  ../../Common/log.c
  ../Sources/at_command.c
  ../Sources/calcul_order.c
  ../Sources/communication.c
  ../Sources/detect_tag.cpp
  ../Sources/keyboard.c
  ../Sources/periodic.c
  ../Sources/supervisor.c
)

ADD_EXECUTABLE(tictactoe ${TICTACTOE_SRC} ../Sources/main.c)

TARGET_LINK_LIBRARIES(tictactoe rt ${CMAKE_THREAD_LIBS_INIT} ${OpenCV_LIBS})