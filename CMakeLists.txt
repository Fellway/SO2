cmake_minimum_required(VERSION 3.10)

# set the project name
project(SO2)
set(SOURCE_FILES app/main.cpp utils/Process.cpp utils/Process.h app/Calculator.cpp app/Calculator.h)
set(PROJECT_NAME SO2)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} app/RandomPicker.cpp)