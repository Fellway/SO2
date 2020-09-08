cmake_minimum_required(VERSION 3.10)

# set the project name
project(SO2)
set(SOURCE_FILES app/main.cpp app/utils/Process.cpp app/headers/Process.h app/core/Calculator.cpp app/headers/Calculator.h app/utils/Counter.cpp app/headers/Counter.h app/utils/FileText.cpp app/headers/FileText.h app/core/Monitor.cpp app/headers/Monitor.h Variables.h app/utils/Converter.cpp app/headers/Converter.h app/core/Writer.cpp app/headers/Writer.h)
set(PROJECT_NAME SO2)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} app/utils/RandomPicker.cpp)