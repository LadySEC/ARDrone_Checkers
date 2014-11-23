### CMakeLists to compile the embedded tictactoe program
###
### Author : Pierre-Louis TILAK
### Date   : 20 Nov 2014

cmake_minimum_required (VERSION 2.8.9)

project(tictactoe)

### Requierements
#find_package(Threads REQUIRED)
    find_package(OpenCV REQUIRED )
    include_directories(../Sources)
include_directories(${OpenCV_INCLUDE_DIRS})
    include(CheckIncludeFiles)
include(CheckIncludeFileCXX)
### Subdirectories where the sources are

#add_executable(tictactoe ../Sources/main.c ../Sources/communication.c ../Sources/supervisor.c ../Sources/keyboard.c ../Sources/at_command.c)
    FILE(GLOB MyCSources "../Sources/*.c")
ADD_LIBRARY(detect_tag ../Sources/detect_tag.cpp ../Sources/detect_tag.hpp)
    set_target_properties(detect_tag 
            PROPERTIES
            LINK_INTERFACE_LIBRARIES ""
            )
ADD_EXECUTABLE(tictactoe  ${MyCSources} ../Sources/detect_tag.cpp ../Sources/detect_tag.hpp)

TARGET_LINK_LIBRARIES(tictactoe rt  ${CMAKE_THREAD_LIBS_INIT} ${OpenCV_LIBS})
