# apartment_project

QuanLyChungCu_Professional/
├── application/
│   └── services/
│       ├── BillingService.h
│       └── BillingService.cpp
├── domain/
│   ├── entities/
│   │   ├── Entity.h
│   │   ├── Building.h
│   │   ├── Apartment.h
│   │   ├── Resident.h
│   │   ├── Occupancy.h
│   │   ├── LeaseContract.h
│   │   ├── ApartmentOwner.h
│   │   ├── Meter.h
│   │   ├── MeterReading.h
│   │   ├── ServiceRate.h
│   │   ├── Invoice.h
│   │   ├── InvoiceLine.h
│   │   └── Payment.h
│   └── enums/
│       └── StatusEnums.h
├── infrastructure/
│   ├── database/
│   │   ├── Database.h
│   │   └── Database.cpp
│   └── repositories/
│       ├── MasterDataRepository.h
│       ├── MasterDataRepository.cpp
│       ├── ResidentRepository.h
│       ├── ResidentRepository.cpp
│       ├── BillingRepository.h
│       └── BillingRepository.cpp
├── presentation/
│   └── cli/
│       ├── Input.h
│       └── ConsoleFormatter.h
├── shared/
│   ├── Constants.h
│   ├── TimeUtils.h
│   └── DbUtils.h
├── main.cpp
├── build.sh
├── chungcu.db
└── README.md
