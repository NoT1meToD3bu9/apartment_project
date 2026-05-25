#pragma once

#include <sqlite3.h>

#include <string>

class Database {
private:
    sqlite3* db;

public:
    explicit Database(const std::string& filename);
    ~Database();

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    sqlite3* getConnection() const { return db; }

    void execute(const std::string& sql);
    void initSchema();
};

