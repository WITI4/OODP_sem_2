#include "project6_header.h"
//#define DEBUG

EmployeeData::EmployeeData() : EmployeeData("", { 0.0, 0.0, 0.0 }) {}
EmployeeData::EmployeeData(const EmployeeData& other) : lastName(other.lastName), quarterlySalaries(other.quarterlySalaries) {}
EmployeeData::EmployeeData(const std::string& lastName, const std::vector<double>& quarterlySalaries) : lastName(lastName), quarterlySalaries(quarterlySalaries) {}

EmployeeData::~EmployeeData() {
#ifdef DEBUG
    std::cout << "���������� EmployeeData ������" << std::endl;
#endif
}

std::string EmployeeData::GetLastName() const { return lastName; }
std::vector<double> EmployeeData::GetQuarterlySalaries() const { return quarterlySalaries; }

void EmployeeData::SetLastName(const std::string& lastName) { this->lastName = lastName; }
void EmployeeData::SetQuarterlySalaries(const std::vector<double>& quarterlySalaries) {
    this->quarterlySalaries = quarterlySalaries;
}

double EmployeeData::GetTotalSalary() const {
    double totalSalary = 0.0;
    for (size_t i = 0; i < quarterlySalaries.size(); i++) {
        totalSalary += quarterlySalaries[i];
    }
    return totalSalary;
}

TaxData::TaxData() : TaxData(0.0) {}
TaxData::TaxData(const TaxData& other) : incomeTaxRate(other.incomeTaxRate) {}
TaxData::TaxData(const double& incomeTaxRate) : incomeTaxRate(incomeTaxRate) {}

TaxData::~TaxData() {
#ifdef DEBUG
    std::cout << "���������� TaxData ������" << std::endl;
#endif
}

double TaxData::GetIncomeTaxRate() const { return incomeTaxRate; }
void TaxData::SetIncomeTaxRate(const double& incomeTaxRate) { this->incomeTaxRate = incomeTaxRate; }

double TaxData::CalculateTax(double amount) const {
    return amount * incomeTaxRate / 100;
}

PaymentForm::PaymentForm() : EmployeeData(), TaxData() {}
PaymentForm::PaymentForm(const std::string& lastName, const std::vector<double>& quarterlySalaries, const double& incomeTaxRate) : EmployeeData(lastName, quarterlySalaries), TaxData(incomeTaxRate) {}

void PaymentForm::ScanPaymentForm(std::ostream& os, std::istream& is) {
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
            os << "����� " << month + 1 << ": ";
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

void PaymentForm::PrintPaymentForm(std::ostream& os) const {
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

PaymentForm::~PaymentForm() {
#ifdef DEBUG
    std::cout << "���������� PaymentForm ������" << std::endl;
#endif
}

void printToFile(const std::vector<PaymentForm>& people, const std::string& filename) {
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