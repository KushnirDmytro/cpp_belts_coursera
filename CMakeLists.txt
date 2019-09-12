cmake_minimum_required(VERSION 3.14)
project(cpp_belts)

set(CMAKE_CXX_STANDARD 17)

#set(OpenCV DIR /usr/local/share/op)
#find_package( OpenCV REQUIRED )

#add_library(rational Rational.cpp)
#add_library(palindrome white_belt/w2/IsPalindrom.cpp)

# Add some multithreaded build support
MARK_AS_ADVANCED(MULTITHREADED_BUILD)
set(MULTITHREADED_BUILD 12 CACHE STRING "How many threads are used to build the project")
if(MULTITHREADED_BUILD)
    if(${CMAKE_GENERATOR} MATCHES "Unix Makefiles")
        message(STATUS ${CMAKE_BUILD_TOOL})
        set(CMAKE_MAKE_PROGRAM "${CMAKE_MAKE_PROGRAM} -j${MULTITHREADED_BUILD}")
        message(STATUS "Added arguments to CMAKE_BUILD_TOOL: ${CMAKE_MAKE_PROGRAM}")
    elseif(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
        message(STATUS "Added parallel build arguments to CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
    endif()
endif()


set(CMAKE_CXX_FLAGS "-O0 -Wall -Wextra")

add_executable(cpp_belts
        red_belt/w5/group_heavy_strings.cpp
       )

#add_executable(cpp_belts main.cpp)

target_link_libraries( cpp_belts ${OpenCV_LIBS} )