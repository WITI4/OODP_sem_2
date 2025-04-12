#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Vehicle {
protected:
    std::string vehicleType;
    int passengerCapacity;
    std::string licensePlate;
public:
    Vehicle();
    Vehicle(const Vehicle& other);
    Vehicle(const std::string vehicleType, int passengerCapacity, const std::string licensePlate);

    virtual ~Vehicle();

    std::string GetVehicleType() const;
    int GetPassengerCapacity() const;
    std::string GetLicensePlate() const;

    void SetVehicleType(const std::string& vehicleType);
    void SetPassengerCapacity(int passengerCapacity);
    void SetLicensePlate(const std::string& licensePlate);

    virtual void PrintInfo(std::ostream& os) const = 0;
};

class Driver : public Vehicle {
private:
    std::string fullName;
    int experienceYears;
    std::string licenseCategory;
    int age;
public:
    Driver();
    Driver(const Driver& other);
    Driver(const std::string fullName, int experienceYears, const std::string licenseCategory, int age);

    ~Driver() override;

    std::string GetFullName() const;
    int GetExperienceYears() const;
    std::string GetLicenseCategory() const;
    int GetAge() const;

    void SetFullName(const std::string& fullName);
    void SetExperienceYears(int experienceYears);
    void SetLicenseCategory(const std::string& licenseCategory);
    void SetAge(int age);

    void PrintInfo(std::ostream& os) const override;
};

class Truck : public Vehicle {
private:
    double maxLoadCapacity;
    bool hasTrailer;
public:
    Truck();
    Truck(const Truck& other);
    Truck(const std::string vehicleType, int passengerCapacity, const std::string licensePlate,
        double maxLoadCapacity, bool hasTrailer);

    ~Truck() override;

    double GetMaxLoadCapacity() const;
    bool GetHasTrailer() const;

    void SetMaxLoadCapacity(double maxLoadCapacity);
    void SetHasTrailer(bool hasTrailer);

    void PrintInfo(std::ostream& os) const override;
};

class Car : public Vehicle {
private:
    std::string carClass;
    bool isElectric;
public:
    Car();
    Car(const Car& other);
    Car(const std::string vehicleType, int passengerCapacity, const std::string licensePlate,
        const std::string carClass, bool isElectric);

    ~Car() override;

    std::string GetCarClass() const;
    bool GetIsElectric() const;

    void SetCarClass(const std::string& carClass);
    void SetIsElectric(bool isElectric);

    void PrintInfo(std::ostream& os) const override;
};

void printToFile(const std::vector<Vehicle*>& fleet, const std::string& filename);
