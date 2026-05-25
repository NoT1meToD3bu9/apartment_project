#pragma once

#include <vector>

#include "../database/Database.h"
#include "../models/Bill.h"

class BillRepository {
private:
    Database& database;

public:
    explicit BillRepository(Database& db) : database(db) {}

    void add(Bill bill);
    std::vector<Bill> getAll();
    void markAsPaid(int id);
    void remove(int id);
    double getTotalUnpaid();
};

