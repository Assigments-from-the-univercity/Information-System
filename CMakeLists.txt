cmake_minimum_required(VERSION 3.17)
project(Information_System)

set(CMAKE_CXX_STANDARD 20)

add_executable(Information_System "main.cpp" "View Layer/View.cpp" "View Layer/View.h" "Controller Layer/Controller.cpp" "Controller Layer/Controller.h" "Model Layer/Header.h" "Model Layer/Manifest.cpp" "Model Layer/Manifest.h" "Model Layer/Table.cpp" "Model Layer/Table.h" "Basic Units/Node.cpp" "Basic Units/Node.h" "Basic Units/List.cpp" "Basic Units/List.h" "Model Layer/TableProperties.cpp" "Model Layer/TableProperties.h" "Basic Units/TypeOfNote.cpp" "Basic Units/TypeOfNote.h" "Model Layer/FileWorker.cpp" "Model Layer/FileWorker.h" "Model Layer/TablePropertiesWorker.cpp" "Model Layer/TablePropertiesWorker.h")