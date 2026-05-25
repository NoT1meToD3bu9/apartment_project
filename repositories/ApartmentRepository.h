#pragma once

#include <string>
#include <vector>

#include "../database/Database.h"
#include "../models/Apartment.h"

class ApartmentRepository {
private:
    Database& database;

public:
    explicit ApartmentRepository(Database& db) : database(db) {}

    void add(const Apartment& apartment);
    std::vector<Apartment> getAll();
    bool existsById(int id);
    void updateStatus(int id, const std::string& newStatus);
    void remove(int id);
};

