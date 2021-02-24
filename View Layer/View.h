//
// Created by mark on 07.02.21.
//

#ifndef INFORMATION_SYSTEM_VIEW_H
#define INFORMATION_SYSTEM_VIEW_H


#include "../Controller Layer/Controller.h"
#include "../Model Layer/Header.h"

/**
 * This class represent the view layer.
 * This class is used for working with console
 * and than giving commands to controller layer.
 */
class View {
private:
    Controller controller;
    vector<string> userDirectory;

    /**
     * This method print the path where user is.
     * Ut gives user a hint where he is and what he can do.
     */
    void printPath();

    /**
     * Main method in this class that receive users command
     * and call an appropriate method from controller layer.
     *
     * @param command A command from user.
     */
    void userCommand(string command);

public:
    /**
     * Public constructor
     */
    View();

    /**
     * The method that start working with user using console.
     */
    void startWork();
};


#endif //INFORMATION_SYSTEM_VIEW_H
