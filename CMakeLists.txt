cmake_minimum_required(VERSION 3.10)
project(P2PStreaming)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(OpenCV_DIR "E:/opencv/build-debug")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(POCO_INCLUDE_DIR "E:/poco-install/include")
set(POCO_LIB_DIR "E:/poco-install/lib")

include_directories(${POCO_INCLUDE_DIR})
link_directories(${POCO_LIB_DIR})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(POCO_LIBS 
        PocoFoundationd
        PocoNetd
        PocoUtild
    )
else()
    set(POCO_LIBS 
        PocoFoundation
        PocoNet
        PocoUtil
    )
endif()

add_executable(P2PStreaming PranamPGowda_SahyadriCollege_C++_Task10.cpp)
target_link_libraries(P2PStreaming ${OpenCV_LIBS} ${POCO_LIBS})

add_executable(VideoSender video_sender.cpp)
target_link_libraries(VideoSender ${OpenCV_LIBS} ${POCO_LIBS})

add_executable(VideoReceiver video_receiver.cpp)
target_link_libraries(VideoReceiver ${OpenCV_LIBS} ${POCO_LIBS})
