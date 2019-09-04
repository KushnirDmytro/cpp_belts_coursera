cmake_minimum_required(VERSION 3.14)
project(cpp_belts)

set(CMAKE_CXX_STANDARD 14)

#set(OpenCV DIR /usr/local/share/op)
#find_package( OpenCV REQUIRED )

#add_library(rational Rational.cpp)
#add_library(palindrome white_belt/w2/IsPalindrom.cpp)

add_executable(cpp_belts
        yellow_belt/w6/main.cpp
        yellow_belt/w6/token.cpp
        yellow_belt/w6/condition_parser_test.cpp
        yellow_belt/w6/node.cpp
        yellow_belt/w6/node.h
        yellow_belt/w6/date.cpp
        yellow_belt/w6/database.cpp
        yellow_belt/w6/condition_parser_my.cpp
        yellow_belt/w6/test_runner.cpp yellow_belt/w6/state_execution_test.cpp
        yellow_belt/w6/event_parser.cpp
        yellow_belt/w6/event_parser.h
        yellow_belt/w6/condition_parser_my.cpp
#        yellow_belt/w6/condition_parser_how_it_should_be.cpp
        )

#add_executable(cpp_belts main.cpp)

target_link_libraries( cpp_belts ${OpenCV_LIBS} )