cmake_minimum_required(VERSION 3.17)
project(Information_System)

set(CMAKE_CXX_STANDARD 20)

add_executable(Information_System "main.cpp" "View Layer/View.cpp" "View Layer/View.h" "Controller Layer/Controller.cpp"
        "Controller Layer/Controller.h" "Header.h" "DEPRECATED/Manifest.cpp" "DEPRECATED/Manifest.h"
        "Model Layer/Table.cpp" "Model Layer/Table.h" "Basic Units/Node.cpp" "Basic Units/Node.h" "Basic Units/List.cpp"
        "Basic Units/List.h" "Basic Units/TypeOfNote.cpp" "Basic Units/TypeOfNote.h"
        "DEPRECATED/File Workers/FileWorker.cpp" "DEPRECATED/File Workers/FileWorker.h"
        "DEPRECATED/File Workers/TablePropertiesWorker.cpp" "DEPRECATED/File Workers/TablePropertiesWorker.h"
        "DEPRECATED/File Workers/TableDataWorker.cpp" "DEPRECATED/File Workers/TableDataWorker.h"
        "View Layer/Printer.cpp" "View Layer/Printer.h" "Basic Units/FilterRequest.h"
        "CSV Workers/CSVWorker.cpp"
        "CSV Workers/CSVWorker.h" "Controller Layer/Filter.cpp" "Controller Layer/Filter.h"
        "Basic Units/SortRequest.h" "CSV Workers/CSVReader.cpp" "CSV Workers/CSVReader.h"
        "CSV Workers/CSVWriter.cpp" "CSV Workers/CSVWriter.h" "Controller Layer/Sorter.cpp"
        "Controller Layer/Sorter.h" "DAT Workers/DATWriter.cpp" "DAT Workers/DATWriter.h" "DAT Workers/DATReader.cpp" "DAT Workers/DATReader.h")