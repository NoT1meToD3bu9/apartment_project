#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "database/Database.h"
#include "repositories/ApartmentRepository.h"
#include "repositories/BillRepository.h"
#include "repositories/ResidentRepository.h"
#include "utils/Input.h"

// ========================= PRINT HEADERS =========================
void printApartmentHeader() {
    using std::cout;
    using std::left;
    using std::setw;

    cout << left
         << setw(5) << "ID"
         << setw(12) << "Ma can"
         << setw(8) << "Tang"
         << setw(12) << "Dien tich"
         << setw(22) << "Chu ho"
         << setw(15) << "Trang thai" << "\n";
    cout << std::string(74, '-') << "\n";
}

void printResidentHeader() {
    using std::cout;
    using std::left;
    using std::setw;

    cout << left
         << setw(5) << "ID"
         << setw(25) << "Ho ten"
         << setw(16) << "SDT"
         << setw(15) << "Vai tro"
         << setw(10) << "Can ho" << "\n";
    cout << std::string(71, '-') << "\n";
}

void printBillHeader() {
    using std::cout;
    using std::left;
    using std::setw;

    cout << left
         << setw(5) << "ID"
         << setw(12) << "Can ho"
         << setw(10) << "Thang"
         << setw(12) << "Tong tien"
         << setw(10) << "Trang thai" << "\n";
    cout << std::string(49, '-') << "\n";
}

// ========================= MENUS =========================
void apartmentMenu(ApartmentRepository& apartmentRepo) {
    while (true) {
        std::cout << "\n===== QUAN LY CAN HO =====\n";
        std::cout << "1. Them can ho\n";
        std::cout << "2. Xem danh sach can ho\n";
        std::cout << "3. Cap nhat trang thai can ho\n";
        std::cout << "4. Xoa can ho\n";
        std::cout << "0. Quay lai\n";

        int choice = Input::integer("Chon: ");

        try {
            if (choice == 1) {
                std::string code = Input::line("Ma can ho: ");
                int floor = Input::integer("Tang: ");
                double area = Input::realNumber("Dien tich: ");
                std::string owner = Input::line("Chu ho: ");
                std::string status = Input::line("Trang thai (Dang o/Trong/Bao tri): ");

                Apartment apartment(0, code, floor, area, owner, status);
                apartmentRepo.add(apartment);
                std::cout << "Them can ho thanh cong!\n";
            }
            else if (choice == 2) {
                std::vector<Apartment> apartments = apartmentRepo.getAll();
                if (apartments.empty()) {
                    std::cout << "Chua co du lieu can ho.\n";
                } else {
                    printApartmentHeader();
                    for (const auto& apartment : apartments) {
                        apartment.display();
                    }
                }
            }
            else if (choice == 3) {
                int id = Input::integer("Nhap ID can ho: ");
                std::string newStatus = Input::line("Nhap trang thai moi: ");
                apartmentRepo.updateStatus(id, newStatus);
                std::cout << "Cap nhat thanh cong!\n";
            }
            else if (choice == 4) {
                int id = Input::integer("Nhap ID can ho can xoa: ");
                apartmentRepo.remove(id);
                std::cout << "Xoa can ho thanh cong!\n";
            }
            else if (choice == 0) {
                return;
            }
            else {
                std::cout << "Lua chon khong hop le!\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Loi: " << e.what() << "\n";
        }
    }
}

void residentMenu(ResidentRepository& residentRepo, ApartmentRepository& apartmentRepo) {
    while (true) {
        std::cout << "\n===== QUAN LY CU DAN =====\n";
        std::cout << "1. Them cu dan\n";
        std::cout << "2. Xem danh sach cu dan\n";
        std::cout << "3. Cap nhat so dien thoai\n";
        std::cout << "4. Xoa cu dan\n";
        std::cout << "0. Quay lai\n";

        int choice = Input::integer("Chon: ");

        try {
            if (choice == 1) {
                std::string fullName = Input::line("Ho ten: ");
                std::string phone = Input::line("So dien thoai: ");
                std::string role = Input::line("Vai tro (Chu ho/Vo chong/Con/Khach thue...): ");
                int apartmentId = Input::integer("ID can ho: ");

                if (!apartmentRepo.existsById(apartmentId)) {
                    std::cout << "Khong ton tai can ho nay!\n";
                    continue;
                }

                Resident resident(0, fullName, phone, role, apartmentId);
                residentRepo.add(resident);
                std::cout << "Them cu dan thanh cong!\n";
            }
            else if (choice == 2) {
                std::vector<Resident> residents = residentRepo.getAll();
                if (residents.empty()) {
                    std::cout << "Chua co du lieu cu dan.\n";
                } else {
                    printResidentHeader();
                    for (const auto& resident : residents) {
                        resident.display();
                    }
                }
            }
            else if (choice == 3) {
                int id = Input::integer("Nhap ID cu dan: ");
                std::string newPhone = Input::line("Nhap so dien thoai moi: ");
                residentRepo.updatePhone(id, newPhone);
                std::cout << "Cap nhat thanh cong!\n";
            }
            else if (choice == 4) {
                int id = Input::integer("Nhap ID cu dan can xoa: ");
                residentRepo.remove(id);
                std::cout << "Xoa cu dan thanh cong!\n";
            }
            else if (choice == 0) {
                return;
            }
            else {
                std::cout << "Lua chon khong hop le!\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Loi: " << e.what() << "\n";
        }
    }
}

void billMenu(BillRepository& billRepo, ApartmentRepository& apartmentRepo) {
    while (true) {
        std::cout << "\n===== QUAN LY HOA DON =====\n";
        std::cout << "1. Tao hoa don\n";
        std::cout << "2. Xem danh sach hoa don\n";
        std::cout << "3. Danh dau da thanh toan\n";
        std::cout << "4. Xoa hoa don\n";
        std::cout << "5. Tong tien chua thanh toan\n";
        std::cout << "0. Quay lai\n";

        int choice = Input::integer("Chon: ");

        try {
            if (choice == 1) {
                int apartmentId = Input::integer("ID can ho: ");
                if (!apartmentRepo.existsById(apartmentId)) {
                    std::cout << "Khong ton tai can ho nay!\n";
                    continue;
                }

                std::string month = Input::line("Thang hoa don (YYYY-MM): ");
                double serviceFee = Input::realNumber("Phi dich vu: ");
                double electricityFee = Input::realNumber("Tien dien: ");
                double waterFee = Input::realNumber("Tien nuoc: ");
                double parkingFee = Input::realNumber("Phi gui xe: ");
                double otherFee = Input::realNumber("Phi khac: ");

                Bill bill(0, apartmentId, month, serviceFee, electricityFee,
                          waterFee, parkingFee, otherFee, 0, 0);

                billRepo.add(bill);
                std::cout << "Tao hoa don thanh cong!\n";
            }
            else if (choice == 2) {
                std::vector<Bill> bills = billRepo.getAll();
                if (bills.empty()) {
                    std::cout << "Chua co hoa don.\n";
                } else {
                    printBillHeader();
                    for (const auto& bill : bills) {
                        bill.display();
                    }
                }
            }
            else if (choice == 3) {
                int id = Input::integer("Nhap ID hoa don: ");
                billRepo.markAsPaid(id);
                std::cout << "Cap nhat thanh toan thanh cong!\n";
            }
            else if (choice == 4) {
                int id = Input::integer("Nhap ID hoa don can xoa: ");
                billRepo.remove(id);
                std::cout << "Xoa hoa don thanh cong!\n";
            }
            else if (choice == 5) {
                double total = billRepo.getTotalUnpaid();
                std::cout << "Tong tien chua thanh toan: " << std::fixed << std::setprecision(2)
                     << total << "\n";
            }
            else if (choice == 0) {
                return;
            }
            else {
                std::cout << "Lua chon khong hop le!\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Loi: " << e.what() << "\n";
        }
    }
}

// ========================= MAIN =========================
int main() {
    try {
        Database db("chungcu.db");
        db.initSchema();

        ApartmentRepository apartmentRepo(db);
        ResidentRepository residentRepo(db);
        BillRepository billRepo(db);

        while (true) {
            std::cout << "\n========== HE THONG QUAN LY CHUNG CU ==========\n";
            std::cout << "1. Quan ly can ho\n";
            std::cout << "2. Quan ly cu dan\n";
            std::cout << "3. Quan ly hoa don\n";
            std::cout << "0. Thoat\n";

            int choice = Input::integer("Chon chuc nang: ");

            if (choice == 1) {
                apartmentMenu(apartmentRepo);
            }
            else if (choice == 2) {
                residentMenu(residentRepo, apartmentRepo);
            }
            else if (choice == 3) {
                billMenu(billRepo, apartmentRepo);
            }
            else if (choice == 0) {
                std::cout << "Tam biet!\n";
                break;
            }
            else {
                std::cout << "Lua chon khong hop le!\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cout << "Loi he thong: " << e.what() << "\n";
    }

    return 0;
}