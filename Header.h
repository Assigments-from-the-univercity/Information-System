//
// Created by mark on 07.02.21.
//

#ifndef INFORMATION_SYSTEM_HEADER_H
#define INFORMATION_SYSTEM_HEADER_H

#include <iostream>
#include <vector>
#include <cstring>
//#include <filesystem> this library isn`t working on Windows
#include "direct.h"
#include <windows.h>
#include <cstdio>


using namespace std;

/*
 * Constants of sizes
 */
static const int INT_SIZE = 4;
static const int NAME_SIZE = 20;
static const int DESCRIPTION_SIZE = 100;

/*static char* makeNewCharArray(string begin, char message[], string end){
    string messageString(message);
    messageString = begin + messageString + end;
    char newMessage[messageString.size()+1];
    strcpy(newMessage, messageString.c_str());
    newMessage[messageString.size()] = '\0';
    return newMessage;
}*/

/**
 * STRING CONSTANTS
 */
static const string TABLES_FOLDER = "../../Data/Tables";
static const string MANIFEST_FOLDER = "../../Data";

static const string MANIFEST_NAME = "manifest.dat";

static const string REGIME_READEBLE = "r+b";
static const string REGIME_WRITEBLE = "w+b";

#endif //INFORMATION_SYSTEM_HEADER_H
