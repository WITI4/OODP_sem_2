#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>

#undef max
#define fastErrInfo \
SetConsoleTextAttribute(consoleColor, 4);\
std::cerr << "������������ ����. ������� ���������� ��� ���:\n";\
SetConsoleTextAttribute(consoleColor, 7); 

class EmployeeData {
    std::string lastName;
    std::vector<double> quarterlySalaries;
public:
    EmployeeData() : EmployeeData("", { 0.0, 0.0, 0.0 }) {}
    EmployeeData(const EmployeeData& other) : lastName(other.lastName), quarterlySalaries(other.quarterlySalaries) {}
    EmployeeData(const std::string& lastName, const std::vector<double>& quarterlySalaries) {
        this->lastName = lastName;
        this->quarterlySalaries = quarterlySalaries;
    }

    std::string GetLastName() const { return lastName; }
    std::vector<double> GetQuarterlySalaries() const { return quarterlySalaries; }

    void SetLastName(const std::string& lastName) { this->lastName = lastName; }
    void SetQuarterlySalaries(const std::vector<double>& quarterlySalaries) { this->quarterlySalaries = quarterlySalaries; }

    double GetTotalSalary() const {
        double totalSalary = 0.0;
        for (size_t i = 0; i < quarterlySalaries.size(); i++) {
            totalSalary += quarterlySalaries[i];
        }
        return totalSalary;
    }

    virtual ~EmployeeData() {
#ifdef DEBUG
        std::cout << "���������� EmployeeData ������" << std::endl;
#endif
    }
};

class TaxData {
    double incomeTaxRate;
public:
    TaxData() : TaxData(0.0) {}
    TaxData(const TaxData& other) : incomeTaxRate(other.incomeTaxRate) {}
    TaxData(const double& incomeTaxRate) {
        this->incomeTaxRate = incomeTaxRate;
    }

    double GetIncomeTaxRate() const { return incomeTaxRate; }
    void SetIncomeTaxRate(const double& incomeTaxRate) { this->incomeTaxRate = incomeTaxRate; }

    double CalculateTax(double amount) const {
        return amount * incomeTaxRate / 100;
    }

    virtual ~TaxData() {
#ifdef DEBUG
        std::cout << "���������� TaxData ������" << std::endl;
#endif
    }
};

class PaymentForm : public EmployeeData, public TaxData {
public:
    PaymentForm() : EmployeeData(), TaxData() {}
    PaymentForm(const std::string& lastName, const std::vector<double>& quarterlySalaries, const double& incomeTaxRate)
        : EmployeeData(lastName, quarterlySalaries), TaxData(incomeTaxRate) {
    }

    void CinPaymentForm(std::ostream& os, std::istream& is) {
        HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

        std::string lastName;
        os << "������� ������� ���������: ";
        is >> lastName;
        SetLastName(lastName);

        std::vector<double> salaries;
        double salary;
        os << "������� �������� �� 3 ������:\n";
        for (int month = 0; month < 3; month++) {
            while (true) {
                os << "����� " << month+1 << ": ";
                if (is >> salary && salary > 0) {
                    salaries.push_back(salary);
                    break;
                }
                else {
                    fastErrInfo;
                    is.clear();
                    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }
        SetQuarterlySalaries(salaries);

        double taxRate;
        os << "������� ������� ������ (0-100): ";
        while (true) {
            if (is >> taxRate && taxRate >= 0 && taxRate <= 100) {
                SetIncomeTaxRate(taxRate);
                break;
            }
            else {
                fastErrInfo;
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                os << "������� ������� ������ (0-100): ";
            }
        }
    }

    void PrintPaymentForm(std::ostream& os) const {
        os << "\n��������� ���������:\n";
        os << "�������: " << GetLastName() << "\n";
        os << "�������� � �������: \n";
        for (size_t i = 0; i < GetQuarterlySalaries().size(); i++) {
            os << GetQuarterlySalaries()[i] << "\n";
        }
        os << "��������� ������: " << GetIncomeTaxRate() << "%" << "\n";
        os << "����� �����: " << GetTotalSalary() << std::endl;
        os << "�����: " << CalculateTax(GetTotalSalary()) << std::endl;
        os << "� �������: " << GetTotalSalary() - CalculateTax(GetTotalSalary()) << std::endl;
    }

    ~PaymentForm() override {
#ifdef DEBUG
        std::cout << "���������� PaymentForm ������" << std::endl;
#endif
    }
};

static void printToFile(const std::vector<PaymentForm>& people, const std::string& filename) {
    std::ofstream output(filename);
    if (!output) {
        std::cerr << "�� ������� ������� ���� ��� ������\n";
        return;
    }

    for (size_t i = 0; i < people.size(); i++) {
        people[i].PrintPaymentForm(output);
        output << std::string(20, '-') << std::endl;
    }
    output.close();
}