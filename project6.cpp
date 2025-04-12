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
        std::cout << "Деструктор EmployeeData вызван" << std::endl;
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
        std::cout << "Деструктор TaxData вызван" << std::endl;
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
        os << "Введите фамилию работника: ";
        is >> lastName;
        SetLastName(lastName);

        std::vector<double> salaries;
        double salary;
        os << "Введите зарплаты за 3 месяца:\n";
        for (int month = 0; month < 3; month++) {
            while (true) {
                os << "Месяц " << month+1 << ": ";
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
        os << "Введите процент налога (0-100): ";
        while (true) {
            if (is >> taxRate && taxRate >= 0 && taxRate <= 100) {
                SetIncomeTaxRate(taxRate);
                break;
            }
            else {
                fastErrInfo;
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                os << "Введите процент налога (0-100): ";
            }
        }
    }

    void PrintPaymentForm(std::ostream& os) const {
        os << "\nПлатежная ведомость:\n";
        os << "Фамилия: " << GetLastName() << "\n";
        os << "Зарплаты в квартал: \n";
        for (size_t i = 0; i < GetQuarterlySalaries().size(); i++) {
            os << GetQuarterlySalaries()[i] << "\n";
        }
        os << "Налоговая ставка: " << GetIncomeTaxRate() << "%" << "\n";
        os << "Общая сумма: " << GetTotalSalary() << std::endl;
        os << "Налог: " << CalculateTax(GetTotalSalary()) << std::endl;
        os << "К выплате: " << GetTotalSalary() - CalculateTax(GetTotalSalary()) << std::endl;
    }

    ~PaymentForm() override {
#ifdef DEBUG
        std::cout << "Деструктор PaymentForm вызван" << std::endl;
#endif
    }
};

static void printToFile(const std::vector<PaymentForm>& people, const std::string& filename) {
    std::ofstream output(filename);
    if (!output) {
        std::cerr << "Не удалось открыть файл для записи\n";
        return;
    }

    for (size_t i = 0; i < people.size(); i++) {
        people[i].PrintPaymentForm(output);
        output << std::string(20, '-') << std::endl;
    }
    output.close();
}