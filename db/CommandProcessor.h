#pragma once
#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <string>

class CommandProcessor {
public:
    CommandProcessor();
    std::string readDatabaseFilePath();
    std::string readUserQuery();
};

#endif // COMMANDPROCESSOR_H


