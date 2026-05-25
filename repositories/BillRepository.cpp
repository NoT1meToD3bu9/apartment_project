#include "BillRepository.h"

#include <sqlite3.h>

#include <stdexcept>
#include <string>
#include <vector>

void BillRepository::add(Bill bill) {
    bill.setTotalAmount(bill.calculateTotal());

    const char* sql = R"(
            INSERT INTO bills(
                apartment_id, bill_month, service_fee,
                electricity_fee, water_fee, parking_fee,
                other_fee, total_amount, paid_status
            ) VALUES(?,?,?,?,?,?,?,?,?);
        )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(database.getConnection()));
    }

    sqlite3_bind_int(stmt, 1, bill.getApartmentId());
    sqlite3_bind_text(stmt, 2, bill.getBillMonth().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 3, bill.getServiceFee());
    sqlite3_bind_double(stmt, 4, bill.getElectricityFee());
    sqlite3_bind_double(stmt, 5, bill.getWaterFee());
    sqlite3_bind_double(stmt, 6, bill.getParkingFee());
    sqlite3_bind_double(stmt, 7, bill.getOtherFee());
    sqlite3_bind_double(stmt, 8, bill.getTotalAmount());
    sqlite3_bind_int(stmt, 9, bill.getPaidStatus());

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::string msg = sqlite3_errmsg(database.getConnection());
        sqlite3_finalize(stmt);
        throw std::runtime_error(msg);
    }

    sqlite3_finalize(stmt);
}

std::vector<Bill> BillRepository::getAll() {
    std::vector<Bill> bills;
    const char* sql = R"(
            SELECT id, apartment_id, bill_month, service_fee,
                   electricity_fee, water_fee, parking_fee,
                   other_fee, total_amount, paid_status
            FROM bills
            ORDER BY bill_month DESC;
        )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(database.getConnection()));
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Bill bill(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_int(stmt, 1),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            sqlite3_column_double(stmt, 3),
            sqlite3_column_double(stmt, 4),
            sqlite3_column_double(stmt, 5),
            sqlite3_column_double(stmt, 6),
            sqlite3_column_double(stmt, 7),
            sqlite3_column_double(stmt, 8),
            sqlite3_column_int(stmt, 9)
        );
        bills.push_back(bill);
    }

    sqlite3_finalize(stmt);
    return bills;
}

void BillRepository::markAsPaid(int id) {
    const char* sql = "UPDATE bills SET paid_status = 1 WHERE id = ?;";
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

void BillRepository::remove(int id) {
    const char* sql = "DELETE FROM bills WHERE id = ?;";
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

double BillRepository::getTotalUnpaid() {
    const char* sql = "SELECT IFNULL(SUM(total_amount), 0) FROM bills WHERE paid_status = 0;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(database.getConnection()));
    }

    double total = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        total = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return total;
}

