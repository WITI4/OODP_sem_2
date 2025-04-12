#include "project5_header.h"
//#define DEBUG

Vehicle::Vehicle() : Vehicle("", 0, "") {}
Vehicle::Vehicle(const Vehicle& other) : vehicleType(other.vehicleType), passengerCapacity(other.passengerCapacity), licensePlate(other.licensePlate) {}
Vehicle::Vehicle(const std::string vehicleType, int passengerCapacity, const std::string licensePlate){
    this->vehicleType = vehicleType;
    this->passengerCapacity = passengerCapacity;
    this->licensePlate = licensePlate;
}

Vehicle::~Vehicle() {
#ifdef DEBUG
    std::cout << "Деструктор Vehicle вызван" << std::endl;
#endif
}

std::string Vehicle::GetVehicleType() const { return vehicleType; }
int Vehicle::GetPassengerCapacity() const { return passengerCapacity; }
std::string Vehicle::GetLicensePlate() const { return licensePlate; }

void Vehicle::SetVehicleType(const std::string& vehicleType) { this->vehicleType = vehicleType; }
void Vehicle::SetPassengerCapacity(int passengerCapacity) { this->passengerCapacity = passengerCapacity; }
void Vehicle::SetLicensePlate(const std::string& licensePlate) { this->licensePlate = licensePlate; }

Driver::Driver() : Driver("", 0, "", 0) {}
Driver::Driver(const Driver& other) : Vehicle(other), fullName(other.fullName), experienceYears(other.experienceYears), licenseCategory(other.licenseCategory), age(other.age) {}
Driver::Driver(const std::string fullName, int experienceYears, const std::string licenseCategory, int age) : Vehicle() {
    this->fullName = fullName;
    this->experienceYears = experienceYears;
    this->licenseCategory = licenseCategory;
    this->age = age;
}

Driver::~Driver() {
#ifdef DEBUG
    std::cout << "Деструктор Driver вызван" << std::endl;
#endif
}

std::string Driver::GetFullName() const { return fullName; }
int Driver::GetExperienceYears() const { return experienceYears; }
std::string Driver::GetLicenseCategory() const { return licenseCategory; }
int Driver::GetAge() const { return age; }

void Driver::SetFullName(const std::string& fullName) { this->fullName = fullName; }
void Driver::SetExperienceYears(int experienceYears) { this->experienceYears = experienceYears; }
void Driver::SetLicenseCategory(const std::string& licenseCategory) { this->licenseCategory = licenseCategory; }
void Driver::SetAge(int age) { this->age = age; }

void Driver::PrintInfo(std::ostream& os) const {
    os << "ФИО: " << fullName << "\n";
    os << "Стаж: " << experienceYears << " лет\n";
    os << "Категория прав: " << licenseCategory << "\n";
    os << "Возраст: " << age << "\n";
}

Truck::Truck() : Truck("", 0, "", 0.0, false) {}
Truck::Truck(const Truck& other) : Vehicle(other), maxLoadCapacity(other.maxLoadCapacity), hasTrailer(other.hasTrailer) {}
Truck::Truck(const std::string vehicleType, int passengerCapacity, const std::string licensePlate, double maxLoadCapacity, bool hasTrailer) : Vehicle(vehicleType, passengerCapacity, licensePlate) {
    this->maxLoadCapacity = maxLoadCapacity;
    this->hasTrailer = hasTrailer;
}

Truck::~Truck() {
#ifdef DEBUG
    std::cout << "Деструктор Truck вызван" << std::endl;
#endif
}

double Truck::GetMaxLoadCapacity() const { return maxLoadCapacity; }
bool Truck::GetHasTrailer() const { return hasTrailer; }

void Truck::SetMaxLoadCapacity(double maxLoadCapacity) { this->maxLoadCapacity = maxLoadCapacity; }
void Truck::SetHasTrailer(bool hasTrailer) { this->hasTrailer = hasTrailer; }

void Truck::PrintInfo(std::ostream& os) const {
    os << "Тип: " << GetVehicleType() << "\n";
    os << "Вместимость: " << GetPassengerCapacity() << "\n";
    os << "Госномер: " << GetLicensePlate() << "\n";
    os << "Грузоподъемность: " << maxLoadCapacity << " кг\n";
    os << "Прицеп: " << (hasTrailer ? "Да" : "Нет") << "\n";
}

Car::Car() : Car("", 0, "", "", false) {}
Car::Car(const Car& other) : Vehicle(other), carClass(other.carClass), isElectric(other.isElectric) {}
Car::Car(const std::string vehicleType, int passengerCapacity, const std::string licensePlate, const std::string carClass, bool isElectric) : Vehicle(vehicleType, passengerCapacity, licensePlate) {
    this->carClass = carClass;
    this->isElectric = isElectric;
}

Car::~Car() {
#ifdef DEBUG
    std::cout << "Деструктор Car вызван" << std::endl;
#endif
}

std::string Car::GetCarClass() const { return carClass; }
bool Car::GetIsElectric() const { return isElectric; }

void Car::SetCarClass(const std::string& carClass) { this->carClass = carClass; }
void Car::SetIsElectric(bool isElectric) { this->isElectric = isElectric; }

void Car::PrintInfo(std::ostream& os) const {
    os << "Тип: " << GetVehicleType() << "\n";
    os << "Вместимость: " << GetPassengerCapacity() << "\n";
    os << "Госномер: " << GetLicensePlate() << "\n";
    os << "Класс: " << carClass << "\n";
    os << "Электромобиль: " << (isElectric ? "Да" : "Нет") << "\n";
}

void printToFile(const std::vector<Vehicle*>& fleet, const std::string& filename) {
    std::ofstream output(filename);
    if (!output) {
        std::cerr << "Не удалось открыть файл для записи\n";
        return;
    }

    for (size_t i = 0; i < fleet.size(); i++) {
        fleet[i]->PrintInfo(output);
        output << std::string(20, '-') << std::endl;
    }
    output.close();
}