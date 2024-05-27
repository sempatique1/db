#include "commandprocessor.h"
#include <iostream>
#include <algorithm>

CommandProcessor::CommandProcessor() {
    setlocale(LC_ALL, "ru");
}

std::string CommandProcessor::readDatabaseFilePath() {
    std::string dbFilePath;
    std::cout << "¬ведите путь к файлу базы данных: ";
    std::getline(std::cin, dbFilePath);
    return dbFilePath;
}

std::string CommandProcessor::readUserQuery() {
    std::string userQuery;
    std::cout << "¬ведите ваш SQL-запрос (или введите 'close' дл€ завершени€): ";
    std::getline(std::cin, userQuery);
    std::transform(userQuery.begin(), userQuery.end(), userQuery.begin(), ::tolower);
    return userQuery;
}
