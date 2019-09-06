cmake_minimum_required(VERSION 3.14)
project(cpp_belts)

set(CMAKE_CXX_STANDARD 17)

#set(OpenCV DIR /usr/local/share/op)
#find_package( OpenCV REQUIRED )

#add_library(rational Rational.cpp)
#add_library(palindrome white_belt/w2/IsPalindrom.cpp)

add_executable(cpp_belts
        red_belt/w1/paginator.cpp
        )

#add_executable(cpp_belts main.cpp)

target_link_libraries( cpp_belts ${OpenCV_LIBS} )