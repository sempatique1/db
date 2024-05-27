#include "commandprocessor.h"
#include <iostream>
#include <algorithm>

CommandProcessor::CommandProcessor() {
    setlocale(LC_ALL, "ru");
}

std::string CommandProcessor::readDatabaseFilePath() {
    std::string dbFilePath;
    std::cout << "������� ���� � ����� ���� ������: ";
    std::getline(std::cin, dbFilePath);
    return dbFilePath;
}

std::string CommandProcessor::readUserQuery() {
    std::string userQuery;
    std::cout << "������� ��� SQL-������ (��� ������� 'close' ��� ����������): ";
    std::getline(std::cin, userQuery);
    std::transform(userQuery.begin(), userQuery.end(), userQuery.begin(), ::tolower);
    return userQuery;
}
