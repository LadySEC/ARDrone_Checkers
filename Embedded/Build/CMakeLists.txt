### CMakeLists to compile the embedded tictactoe program
###
### Author : Pierre-Louis TILAK
### Date   : 20 Nov 2014

cmake_minimum_required (VERSION 2.8.9)

project(tictactoe )

### Requierements
#find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})


### Subdirectories where the sources are

#add_executable(tictactoe ../Sources/main.c ../Sources/communication.c ../Sources/supervisor.c ../Sources/keyboard.c ../Sources/at_command.c)

FILE(GLOB MyCSources "../Sources/*.c")

ADD_EXECUTABLE(tictactoe  ${MyCSources} ../Sources/detect_tag.cpp ../Sources/detect_tag.h)

TARGET_LINK_LIBRARIES(tictactoe rt ${CMAKE_THREAD_LIBS_INIT} ${OpenCV_LIBS})
