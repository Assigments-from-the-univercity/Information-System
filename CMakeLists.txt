cmake_minimum_required(VERSION 3.17)
project(Information_System)

set(CMAKE_CXX_STANDARD 20)

add_executable(Information_System main.cpp View.cpp View.h Controller.cpp Controller.h Header.h Manifest.cpp Manifest.h Table.cpp Table.h Node.cpp Node.h List.cpp List.h TableProperties.cpp TableProperties.h TypeOfNote.cpp TypeOfNote.h FileWorker.cpp FileWorker.h TablePropertiesWorker.cpp TablePropertiesWorker.h)