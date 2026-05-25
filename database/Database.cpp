#include "Database.h"

#include <stdexcept>
#include <string>

Database::Database(const std::string& filename) : db(nullptr) {
    if (sqlite3_open(filename.c_str(), &db) != SQLITE_OK) {
        std::string msg = sqlite3_errmsg(db);
        sqlite3_close(db);
        throw std::runtime_error("Khong mo duoc DB: " + msg);
    }
    execute("PRAGMA foreign_keys = ON;");
}

Database::~Database() {
    if (db) sqlite3_close(db);
}

void Database::execute(const std::string& sql) {
    char* errorMessage = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage);
    if (rc != SQLITE_OK) {
        std::string msg = errorMessage ? errorMessage : "SQL error";
        sqlite3_free(errorMessage);
        throw std::runtime_error(msg);
    }
}

void Database::initSchema() {
    std::string sql = R"(
            CREATE TABLE IF NOT EXISTS apartments (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                code TEXT NOT NULL UNIQUE,
                floor INTEGER NOT NULL,
                area REAL NOT NULL,
                owner_name TEXT NOT NULL,
                status TEXT NOT NULL
            );

            CREATE TABLE IF NOT EXISTS residents (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                full_name TEXT NOT NULL,
                phone TEXT NOT NULL,
                role TEXT NOT NULL,
                apartment_id INTEGER NOT NULL,
                FOREIGN KEY(apartment_id) REFERENCES apartments(id) ON DELETE CASCADE
            );

            CREATE TABLE IF NOT EXISTS bills (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                apartment_id INTEGER NOT NULL,
                bill_month TEXT NOT NULL,
                service_fee REAL NOT NULL,
                electricity_fee REAL NOT NULL,
                water_fee REAL NOT NULL,
                parking_fee REAL NOT NULL,
                other_fee REAL NOT NULL,
                total_amount REAL NOT NULL,
                paid_status INTEGER NOT NULL DEFAULT 0,
                UNIQUE(apartment_id, bill_month),
                FOREIGN KEY(apartment_id) REFERENCES apartments(id) ON DELETE CASCADE
            );
        )";
    execute(sql);
}

