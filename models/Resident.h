#pragma once

#include <iomanip>
#include <iostream>
#include <string>

#include "Entity.h"

class Resident : public Entity {
private:
    std::string fullName;
    std::string phone;
    std::string role;
    int apartmentId;

public:
    Resident(
        int id = 0,
        std::string fullName = "",
        std::string phone = "",
        std::string role = "",
        int apartmentId = 0
    )
        : Entity(id),
          fullName(std::move(fullName)),
          phone(std::move(phone)),
          role(std::move(role)),
          apartmentId(apartmentId) {}

    std::string getFullName() const { return fullName; }
    std::string getPhone() const { return phone; }
    std::string getRole() const { return role; }
    int getApartmentId() const { return apartmentId; }

    void setFullName(const std::string& value) { fullName = value; }
    void setPhone(const std::string& value) { phone = value; }
    void setRole(const std::string& value) { role = value; }
    void setApartmentId(int value) { apartmentId = value; }

    void display() const override {
        using std::cout;
        using std::left;
        using std::setw;

        cout << left
             << setw(5) << id
             << setw(25) << fullName
             << setw(16) << phone
             << setw(15) << role
             << setw(10) << apartmentId << "\n";
    }
};

