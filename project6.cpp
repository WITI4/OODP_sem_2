#include "project6_header.h"
#include "input_check.h"
//#define DEBUG

EmployeeData::EmployeeData() : EmployeeData("", { 0.0, 0.0, 0.0 }) {}
EmployeeData::EmployeeData(const EmployeeData& other) : lastName(other.lastName), quarterlySalaries(other.quarterlySalaries) {}
EmployeeData::EmployeeData(const std::string& lastName, const std::vector<double>& quarterlySalaries) {
    this->lastName = lastName;
    this->quarterlySalaries = quarterlySalaries;
}

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
TaxData::TaxData(const double& incomeTaxRate) {
    this->incomeTaxRate = incomeTaxRate;
}

TaxData::~TaxData() {
#ifdef DEBUG
    std::cout << "���������� TaxData ������" << std::endl;
#endif
}

constexpr double TaxData::GetIncomeTaxRate() const { return incomeTaxRate; }
void TaxData::SetIncomeTaxRate(const double& incomeTaxRate) { this->incomeTaxRate = incomeTaxRate; }

double TaxData::CalculateTax(double amount) const {
    return amount * incomeTaxRate / 100;
}

PaymentForm::PaymentForm() : EmployeeData(), TaxData() {}
PaymentForm::PaymentForm(const std::string& lastName, const std::vector<double>& quarterlySalaries, const double& incomeTaxRate) : EmployeeData(lastName, quarterlySalaries), TaxData(incomeTaxRate) {}

void PaymentForm::ScanPaymentForm(std::vector<PaymentForm>& forms, std::ostream& os, std::istream& is) {
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    unsigned paymentFormCount = 0;

    os << "������� ���������� ���� ��� ����������: ";
    number_filteredInput<unsigned>(paymentFormCount);
    std::cout << "\n";

    forms.clear();

    for (int i = 0; i < paymentFormCount; i++) {
        PaymentForm form;

        std::string lastName;
        os << "������� ������� ��������� " << i + 1 << " : ";
        number_filteredInput<std::string>(lastName);
        form.SetLastName(lastName);
        std::cout << "\n";

        std::vector<double> salaries;
        double salary;
        os << "������� �������� �� 3 ������:\n";
        for (int month = 0; month < 3; month++) {
            while (true) {
                os << "����� " << month + 1 << ": ";
                number_filteredInput<double>(salary);
                std::cout << "\n";
                if (salary > 0) {
                    salaries.push_back(salary);
                    break;
                }
                else fastErrInfo;
            }
        }
        form.SetQuarterlySalaries(salaries);

        double taxRate;
        while (true) {
            os << "������� ������� ������ (0-100): ";
            number_filteredInput<double>(taxRate);
            std::cout << "\n";
            if (taxRate > 0 && taxRate <= 100) {
                form.SetIncomeTaxRate(taxRate);
                break;
            }
            else fastErrInfo;
        }

        forms.push_back(form);
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
void PaymentForm::PrintAllForms(const std::vector<PaymentForm>& forms, std::ostream& os) const {
    os << std::string(20, '-');
    os << "\n��� ��������� ���������:\n\n";
    for (size_t i = 0; i < forms.size(); i++) {
        os << "����� #" << i + 1 << "\n";
        forms[i].PrintPaymentForm(os);
        os << std::string(20, '-') << "\n\n";
    }
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