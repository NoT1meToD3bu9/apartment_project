#pragma once

#include <iomanip>
#include <iostream>
#include <string>

#include "Entity.h"

class Bill : public Entity {
private:
    int apartmentId;
    std::string billMonth;
    double serviceFee;
    double electricityFee;
    double waterFee;
    double parkingFee;
    double otherFee;
    double totalAmount;
    int paidStatus;

public:
    Bill(
        int id = 0,
        int apartmentId = 0,
        std::string billMonth = "",
        double serviceFee = 0,
        double electricityFee = 0,
        double waterFee = 0,
        double parkingFee = 0,
        double otherFee = 0,
        double totalAmount = 0,
        int paidStatus = 0
    )
        : Entity(id),
          apartmentId(apartmentId),
          billMonth(std::move(billMonth)),
          serviceFee(serviceFee),
          electricityFee(electricityFee),
          waterFee(waterFee),
          parkingFee(parkingFee),
          otherFee(otherFee),
          totalAmount(totalAmount),
          paidStatus(paidStatus) {}

    int getApartmentId() const { return apartmentId; }
    std::string getBillMonth() const { return billMonth; }
    double getServiceFee() const { return serviceFee; }
    double getElectricityFee() const { return electricityFee; }
    double getWaterFee() const { return waterFee; }
    double getParkingFee() const { return parkingFee; }
    double getOtherFee() const { return otherFee; }
    double getTotalAmount() const { return totalAmount; }
    int getPaidStatus() const { return paidStatus; }

    void setApartmentId(int value) { apartmentId = value; }
    void setBillMonth(const std::string& value) { billMonth = value; }
    void setServiceFee(double value) { serviceFee = value; }
    void setElectricityFee(double value) { electricityFee = value; }
    void setWaterFee(double value) { waterFee = value; }
    void setParkingFee(double value) { parkingFee = value; }
    void setOtherFee(double value) { otherFee = value; }
    void setPaidStatus(int value) { paidStatus = value; }
    void setTotalAmount(double value) { totalAmount = value; }

    double calculateTotal() const {
        return serviceFee + electricityFee + waterFee + parkingFee + otherFee;
    }

    void display() const override {
        using std::cout;
        using std::left;
        using std::setw;

        cout << left
             << setw(5) << id
             << setw(12) << apartmentId
             << setw(10) << billMonth
             << setw(12) << totalAmount
             << setw(10) << (paidStatus ? "Da tra" : "Chua tra") << "\n";
    }
};

