#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Human {
protected:
    std::string fullName;
    int birthYear;
    std::string passportData;

public:
    Human();
    Human(const Human& other);
    Human(const std::string fullName, int birthYear, const std::string passportData);

    virtual ~Human();

    std::string GetFullName() const;
    int GetBirthYear() const;
    std::string GetPassportData() const;

    void SetFullName(const std::string& fullName);
    void SetBirthYear(const int& birthYear);
    void SetPassportData(const std::string& passportData);

    virtual void PrintInfo(std::ostream& os) const;
};

class Entrepreneur : public Human {
private:
    std::string licenseNumber;
    std::string registrationAddress;
    std::string unn;
    std::string taxPayments;

public:
    Entrepreneur();
    Entrepreneur(const Entrepreneur& other);
    Entrepreneur(const std::string& fullName, int birthYear, const std::string& passportData, const std::string& licenseNumber, const std::string& registrationAddress, const std::string& unn, const std::string& taxPayments);

    ~Entrepreneur() override;

    std::string GetLicenseNumber() const;
    std::string GetRegistrationAddress() const;
    std::string GetUNN() const;
    std::string GetTaxPayments() const;

    void SetLicenseNumber(const std::string& licenseNumber);
    void SetRegistrationAddress(const std::string& registrationAddress);
    void SetUNN(const std::string& unn);
    void SetTaxPayments(const std::string& taxPayments);

    void PrintInfo(std::ostream& os) const override;
};

class Tourist : public Human {
private:
    std::string borderCrossingData;

public:
    Tourist();
    Tourist(const Tourist& other);
    Tourist(const std::string& fullName, int birthYear, const std::string& passportData, const std::string& borderCrossingData);

    ~Tourist() override;

    std::string GetBorderCrossingData() const;

    void SetBorderCrossingData(const std::string& borderCrossingData);

    void PrintInfo(std::ostream& os) const override;
};

class Shuttle : public Human {
private:
    std::string purchaseAddresses;

public:
    Shuttle();
    Shuttle(const Shuttle& other);
    Shuttle(const std::string& fullName, int birthYear, const std::string& passportData,
        const std::string& purchaseAddresses);

    ~Shuttle() override;

    std::string GetPurchaseAddresses() const;

    void SetPurchaseAddresses(const std::string& purchaseAddresses);

    void PrintInfo(std::ostream& os) const override;
};

Human* findOldest(const std::vector<Human*>& people);
void printToFile(const std::vector<Human*>& people, const std::string& filename);