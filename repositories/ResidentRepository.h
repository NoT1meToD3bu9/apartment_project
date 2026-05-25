#pragma once

#include <string>
#include <vector>

#include "../database/Database.h"
#include "../models/Resident.h"

class ResidentRepository {
private:
    Database& database;

public:
    explicit ResidentRepository(Database& db) : database(db) {}

    void add(const Resident& resident);
    std::vector<Resident> getAll();
    void updatePhone(int id, const std::string& newPhone);
    void remove(int id);
};

