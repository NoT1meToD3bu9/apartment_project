#include "ResidentRepository.h"

#include <sqlite3.h>

#include <stdexcept>
#include <string>
#include <vector>

void ResidentRepository::add(const Resident& resident) {
    const char* sql =
        "INSERT INTO residents(full_name, phone, role, apartment_id) VALUES(?,?,?,?);";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(database.getConnection()));
    }

    sqlite3_bind_text(stmt, 1, resident.getFullName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, resident.getPhone().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, resident.getRole().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, resident.getApartmentId());

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::string msg = sqlite3_errmsg(database.getConnection());
        sqlite3_finalize(stmt);
        throw std::runtime_error(msg);
    }

    sqlite3_finalize(stmt);
}

std::vector<Resident> ResidentRepository::getAll() {
    std::vector<Resident> residents;
    const char* sql =
        "SELECT id, full_name, phone, role, apartment_id FROM residents ORDER BY id DESC;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(database.getConnection()));
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Resident resident(
            sqlite3_column_int(stmt, 0),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            sqlite3_column_int(stmt, 4)
        );
        residents.push_back(resident);
    }

    sqlite3_finalize(stmt);
    return residents;
}

void ResidentRepository::updatePhone(int id, const std::string& newPhone) {
    const char* sql = "UPDATE residents SET phone = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(database.getConnection()));
    }

    sqlite3_bind_text(stmt, 1, newPhone.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::string msg = sqlite3_errmsg(database.getConnection());
        sqlite3_finalize(stmt);
        throw std::runtime_error(msg);
    }

    sqlite3_finalize(stmt);
}

void ResidentRepository::remove(int id) {
    const char* sql = "DELETE FROM residents WHERE id = ?;";
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

