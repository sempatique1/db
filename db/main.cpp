#include <iostream>
#include "database.h"
#include "commandprocessor.h"
#include <sys/stat.h>

bool checkDatabaseFile(const std::string& filePath) {
    struct stat buffer;
    std::cout << "Проверка существования файла базы данных...\n";
    if (stat(filePath.c_str(), &buffer) == 0) {
        std::cout << "Файл базы данных найден.\n";
        return true;
    }
    else {
        std::cout << "Файл базы данных не найден. Будет создан новый файл базы данных.\n";
        return false;
    }
}

void sql_commands(sqlite3* db, const std::string& query) {
    char* errMsg = nullptr;
    sqlite3_exec(db, query.c_str(), [](void*, int argc, char** argv, char** colNames) -> int {
        for (int i = 0; i < argc; i++) {
            std::cout << (argv[i] ? argv[i] : "NULL") << "\t";
        }
        std::cout << "\n";
        return 0;
        }, nullptr, &errMsg);

    if (errMsg) {
        std::cerr << "Ошибка выполнения запроса: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
}

int main() {
    CommandProcessor commandProcessor;
    std::string dbFilePath = commandProcessor.readDatabaseFilePath();

    bool dbExists = checkDatabaseFile(dbFilePath);

    {
        Database dbHelper(dbFilePath);

        if (!dbExists) {
            dbHelper.createTestTable();
        }

        while (true) {
            std::string userQuery = commandProcessor.readUserQuery();
            if (userQuery == "close") {
                break;
            }
            sql_commands(dbHelper.getDb(), userQuery); // Используем функцию sql_commands
        }
    }

    return 0;
}
