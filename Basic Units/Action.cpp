//
// Created by Mark on 28.03.2021.
//

#include "Action.h"

void Action::getAction(string stringAction) {
    if (stringAction == "SELECT") {
        actionType = Action::SELECT;
    } else if (stringAction == "FROM") {
        actionType = Action::FROM;
    } else if (stringAction == "WHERE") {
        actionType = Action::WHERE;
    } else if (stringAction == "SORT") {
        actionType = Action::SORT;
    } else {
        actionType = Action::STOP;
    }
}
