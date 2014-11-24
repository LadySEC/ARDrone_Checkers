### CMakeLists to compile the embedded tictactoe program
###
### Author : Pierre-Louis TILAK
### Date   : 20 Nov 2014

cmake_minimum_required (VERSION 2.8.9)

project(tictactoe)

### Requierements
find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED )

include_directories(${OpenCV_INCLUDE_DIRS} ../Sources)

set(TICTACTOE_SRC  	../Sources/at_command.c
			../Sources/calcul_order.c
			../Sources/calcul_tag.c
			../Sources/communication.c
			../Sources/detect_tag_wrapper.cpp
			../Sources/detect_tag.cpp
			../Sources/keyboard.c
			../Sources/periodic.c
			../Sources/supervisor.c
		   )

ADD_EXECUTABLE(tictactoe  ${TICTACTOE_SRC} ../Sources/main.c)

TARGET_LINK_LIBRARIES(tictactoe rt  ${CMAKE_THREAD_LIBS_INIT} ${OpenCV_LIBS})

