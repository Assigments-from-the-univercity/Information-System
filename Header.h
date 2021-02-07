//
// Created by mark on 07.02.21.
//

#ifndef INFORMATION_SYSTEM_HEADER_H
#define INFORMATION_SYSTEM_HEADER_H

#include <iostream>
#include <vector>
#include <cstring>
#include <filesystem>
#include <cstdio>


using namespace std;

static const int INT_SIZE = 4;
static const int NAME_SIZE = 20;
static const int DESCRIPTION_SIZE = 100;

char* makeNewCharArray(string begin, char message[], string end);{
    string messageString(message);
    messageString = begin + messageString + end;
    char newMessage[messageString.size()];
    strcpy(newMessage, messageString);
    newMessage[messageString.size() - 1] = '\0';
    return newMessage;
}

#endif //INFORMATION_SYSTEM_HEADER_H
