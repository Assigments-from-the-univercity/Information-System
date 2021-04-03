cmake_minimum_required(VERSION 3.17)
project(Information_System)

set(CMAKE_CXX_STANDARD 20)

add_executable(Information_System "main.cpp" "View Layer/View.cpp" "View Layer/View.h" "Controller Layer/Controller.cpp"
        "Controller Layer/Controller.h"
        "Model Layer/Table.cpp" "Model Layer/Table.h" "Basic Units/List/Node.cpp" "Basic Units/List/Node.h" "Basic Units/List/List.cpp"
        "Basic Units/List/List.h" "Basic Units/TypeOfNote.cpp" "Basic Units/TypeOfNote.h"
        "View Layer/Printer.cpp" "View Layer/Printer.h" "Basic Units/Filter Request/FilterRequest.h"
        "CSV Workers/CSVWorker.cpp"
        "CSV Workers/CSVWorker.h" "Controller Layer/Filter.cpp" "Controller Layer/Filter.h"
        "Basic Units/Sort Request/SortRequest.h" "CSV Workers/CSVReader.cpp" "CSV Workers/CSVReader.h"
        "CSV Workers/CSVWriter.cpp" "CSV Workers/CSVWriter.h" "Controller Layer/Sorters/Sorter.cpp"
        "Controller Layer/Sorters/Sorter.h" "DAT Workers/DATWriter.cpp" "DAT Workers/DATWriter.h" "DAT Workers/DATReader.cpp" "DAT Workers/DATReader.h" "Basic Units/Action.cpp" "Basic Units/Action.h" "Basic Units/Sort Request/PreSortRequest.h" "Basic Units/Filter Request/UserRequest.cpp" "Basic Units/Filter Request/UserRequest.h" "View Layer/Parser.cpp" "View Layer/Parser.h" "Controller Layer/Sorters/Trie/TrieNode.cpp" "Controller Layer/Sorters/Trie/TrieNode.h" "Controller Layer/Sorters/Trie/Trie.cpp" "Controller Layer/Sorters/Trie/Trie.h" "Controller Layer/Sorters/RB Tree/RBTNode.cpp" "Controller Layer/Sorters/RB Tree/RBTNode.h" "Controller Layer/Sorters/RB Tree/RBTree.cpp" "Controller Layer/Sorters/RB Tree/RBTree.h")