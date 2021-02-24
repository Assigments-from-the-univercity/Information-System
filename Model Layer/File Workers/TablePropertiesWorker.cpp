//
// Created by Mark on 23.02.2021.
//

#include "../../Header.h"
#include "TablePropertiesWorker.h"

void TablePropertiesWorker::setProperties(TableProperties tableProperties) {
    this->tableProperties = tableProperties;
}

TableProperties TablePropertiesWorker::getProperties() {
    return tableProperties;
}

TablePropertiesWorker::~TablePropertiesWorker() {
    tableProperties.safeProperties(fp);
}