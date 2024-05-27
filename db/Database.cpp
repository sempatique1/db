#include "database.h"
#include <iostream>

Database::Database(const std::string& filePath) {
    if (sqlite3_open(filePath.c_str(), &db) == SQLITE_OK) {
        std::cout << "�������� ����������� � ���� ������.\n";
    }
    else {
        std::cerr << "������ ����������� � ���� ������: " << sqlite3_errmsg(db) << "\n";
        exit(1);
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
        std::cout << "���������� �� ���� ������ �������.\n";
    }
}

sqlite3* Database::getDb() const {
    return db;
}

void Database::createTestTable() {
    const char* sqlCreateTable = R"(
        CREATE TABLE IF NOT EXISTS people (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            birthdate TEXT
        );
    )";

    const char* sqlInsertData[] = {
        "INSERT INTO people (name, birthdate) VALUES ('John', '1990-01-01');",
        "INSERT INTO people (name, birthdate) VALUES ('Emma', '1985-05-15');",
        "INSERT INTO people (name, birthdate) VALUES ('Michael', '1978-11-22');"
    };

    char* errMsg = nullptr;

    if (sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "������ �������� �������: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
    else {
        std::cout << "������� 'people' ������� �������.\n";
    }

    for (const char* sql : sqlInsertData) {
        if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "������ ������� ������: " << errMsg << "\n";
            sqlite3_free(errMsg);
        }
    }

    std::cout << "������� 'people' ��������� �������.\n";
}

