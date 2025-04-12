#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>

#undef max
#define fastErrInfo \
SetConsoleTextAttribute(consoleColor, 4);\
std::cerr << "Некорректный ввод. Введите информацию еще раз:\n";\
SetConsoleTextAttribute(consoleColor, 7);

class EmployeeData {
protected:
    std::string lastName;
    std::vector<double> quarterlySalaries;
public:
    EmployeeData();
    EmployeeData(const EmployeeData& other);
    EmployeeData(const std::string& lastName, const std::vector<double>& quarterlySalaries);

    virtual ~EmployeeData();

    std::string GetLastName() const;
    std::vector<double> GetQuarterlySalaries() const;

    void SetLastName(const std::string& lastName);
    void SetQuarterlySalaries(const std::vector<double>& quarterlySalaries);

    double GetTotalSalary() const;
};

class TaxData {
protected:
    double incomeTaxRate;
public:
    TaxData();
    TaxData(const TaxData& other);
    TaxData(const double& incomeTaxRate);

    virtual ~TaxData();

    double GetIncomeTaxRate() const;

    void SetIncomeTaxRate(const double& incomeTaxRate);

    double CalculateTax(double amount) const;
};

class PaymentForm : public EmployeeData, public TaxData {
public:
    PaymentForm();
    PaymentForm(const std::string& lastName, const std::vector<double>& quarterlySalaries, const double& incomeTaxRate);

    void ScanPaymentForm(std::ostream& os, std::istream& is);
    void PrintPaymentForm(std::ostream& os) const;

    ~PaymentForm() override;
};

void printToFile(const std::vector<PaymentForm>& people, const std::string& filename);