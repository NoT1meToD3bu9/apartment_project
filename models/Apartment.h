#pragma once
#include <iomanip>
#include <iostream>
#include <string>
#include "Entity.h"

class Apartment : public Entity {
private:
    std::string code;
    int floor;
    double area;
    std::string ownerName;
    std::string status;

public:
    Apartment(
        int id = 0,
        std::string code = "",
        int floor = 0,
        double area = 0,
        std::string ownerName = "",
        std::string status = "Trong"
    )
        : Entity(id),
          code(std::move(code)),
          floor(floor),
          area(area),
          ownerName(std::move(ownerName)),
          status(std::move(status)) {}

    std::string getCode() const { return code; }
    int getFloor() const { return floor; }
    double getArea() const { return area; }
    std::string getOwnerName() const { return ownerName; }
    std::string getStatus() const { return status; }

    void setCode(const std::string& value) { code = value; }
    void setFloor(int value) { floor = value; }
    void setArea(double value) { area = value; }
    void setOwnerName(const std::string& value) { ownerName = value; }
    void setStatus(const std::string& value) { status = value; }

    void display() const override {
        using std::cout;
        using std::left;
        using std::setw;

        cout << left
             << setw(5) << id
             << setw(12) << code
             << setw(8) << floor
             << setw(12) << area
             << setw(22) << ownerName
             << setw(15) << status << "\n";
    }
};

