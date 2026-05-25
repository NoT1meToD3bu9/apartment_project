#include "ApartmentRepository.h"

#include <sqlite3.h>

#include <stdexcept>
#include <string>
#include <vector>

void ApartmentRepository::add(const Apartment& apartment) {
    const char* sql =
        "INSERT INTO apartments(code, floor, area, owner_name, status) VALUES(?,?,?,?,?);";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(database.getConnection()));
    }

    sqlite3_bind_text(stmt, 1, apartment.getCode().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, apartment.getFloor());
    sqlite3_bind_double(stmt, 3, apartment.getArea());
    sqlite3_bind_text(stmt, 4, apartment.getOwnerName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, apartment.getStatus().c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::string msg = sqlite3_errmsg(database.getConnection());
        sqlite3_finalize(stmt);
        throw std::runtime_error(msg);
    }

    sqlite3_finalize(stmt);
}

std::vector<Apartment> ApartmentRepository::getAll() {
    std::vector<Apartment> apartments;
    const char* sql =
        "SELECT id, code, floor, area, owner_name, status FROM apartments ORDER BY floor, code;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(database.getConnection()));
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Apartment apartment(
            sqlite3_column_int(stmt, 0),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            sqlite3_column_int(stmt, 2),
            sqlite3_column_double(stmt, 3),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5))
        );
        apartments.push_back(apartment);
    }

    sqlite3_finalize(stmt);
    return apartments;
}

bool ApartmentRepository::existsById(int id) {
    const char* sql = "SELECT 1 FROM apartments WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(database.getConnection()));
    }

    sqlite3_bind_int(stmt, 1, id);
    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return exists;
}

void ApartmentRepository::updateStatus(int id, const std::string& newStatus) {
    const char* sql = "UPDATE apartments SET status = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(database.getConnection()));
    }

    sqlite3_bind_text(stmt, 1, newStatus.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::string msg = sqlite3_errmsg(database.getConnection());
        sqlite3_finalize(stmt);
        throw std::runtime_error(msg);
    }

    sqlite3_finalize(stmt);
}

void ApartmentRepository::remove(int id) {
    const char* sql = "DELETE FROM apartments WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(database.getConnection()));
    }

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::string msg = sqlite3_errmsg(database.getConnection());
        sqlite3_finalize(stmt);
        throw std::runtime_error(msg);
    }

    sqlite3_finalize(stmt);
}

