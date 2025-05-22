#include "input_check.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <memory>

#define fastErrInfo \
std::cerr << "Некорректный ввод. Введите информацию еще раз:\n";

class EmployeeState {
    int id;
    std::string name;
    double salary;
public:
    EmployeeState(int id, const std::string& name, double salary) : id(id), name(name), salary(salary) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    double getSalary() const { return salary; }
};

class TransactionManager {
    std::map<int, std::stack<EmployeeState>> employeeHistory;

public:
    void saveState(const std::shared_ptr<class Emp>& emp);
    bool restoreState(std::shared_ptr<class Emp>& emp);
    bool hasHistory(int id) const;
};

class Emp {
    int id;
    std::string name;
    double salary;
public:
    Emp() : Emp(0, "", 0.0) {}
    Emp(const Emp& other) : id(other.id), name(other.name), salary(other.salary) {}
    Emp(int id, const std::string& name, double salary) {
        this->id = id;
        this->name = name;
        this->salary = salary;
    }

    constexpr int GetId() const { return id; }
    std::string GetName() const { return name; }
    constexpr double GetSalary() const { return salary; }

    void SetId(const int& id) { this->id = id; }
    void SetName(const std::string& name) { this->name = name; }
    void SetSalary(const double& salary) { this->salary = salary; }

    virtual ~Emp() {
#ifdef DEBUG
        std::cout << "Деструктор Emp вызван" << std::endl;
#endif
    }

    virtual void printInfo(std::ostream& os) const = 0;
    virtual double calculateSalary() const { return salary; }
};
inline void TransactionManager::saveState(const std::shared_ptr<Emp>& emp) {
    employeeHistory[emp->GetId()].push( EmployeeState(emp->GetId(), emp->GetName(), emp->GetSalary()));
}
inline bool TransactionManager::restoreState(std::shared_ptr<Emp>& emp) {
    auto& history = employeeHistory[emp->GetId()];
    if (!history.empty()) {
        EmployeeState state = history.top();
        history.pop();
        emp->SetName(state.getName());
        emp->SetSalary(state.getSalary());
        return true;
    }
    return false;
}

inline bool TransactionManager::hasHistory(int id) const {
    auto it = employeeHistory.find(id);
    return it != employeeHistory.end() && !it->second.empty();
}

class Dev : public Emp {
    std::string language;
    std::string level;
public:
    Dev() : Dev(0, "", 0.0, "Unknown", "Unknown") {}
    Dev(const Dev& other) : Emp(other), language(other.language), level(other.level) {}
    Dev(int id, const std::string& name, double salary, const std::string& language, const std::string& level)
        : Emp(id, name, salary) {
        this->language = language;
        this->level = level;
    }

    std::string GetLanguage() const { return language; }
    std::string GetLevel() const { return level; }

    void SetLanguage(const std::string& language) { this->language = language; }
    void SetLevel(const std::string& level) { this->level = level; }

    ~Dev() override {
#ifdef DEBUG
        std::cout << "Деструктор Dev вызван" << std::endl;
#endif
    }

    static std::shared_ptr<Dev> createFromInput() {
        bool errflag = false;
        int id;
        std::string name;
        double salary;
        std::string language;
        std::string level;

        std::cout << "Создание разработчика:\n";

        std::cout << "ID: ";
        number_filteredInput<int>(id, 0, 1);
        std::cout << "Имя: ";
        letter_filteredInput<std::string>(name, 1);
        std::cout << "Зарплата: ";
        while (!errflag) {
            number_filteredInput<double>(salary, 0, 1);
            if (salary > 0) {
                errflag = true;
            }
            else {
                fastErrInfo;
            }
        }
        errflag = false;
        std::cout << "Язык программирования: ";
        while (!errflag) {
            letter_filteredInput<std::string>(language);
            if (language == "c++" || language == "c" || language == "php" ||
                language == "c#" || language == "js" || language == "go" || language == "java") {
                errflag = true;
            }
            else {
                fastErrInfo;
            }
        }
        errflag = false;
        std::cout << "Уровень (Junior/Middle/Senior): ";
        while (!errflag) {
            letter_filteredInput<std::string>(level, 1);
            if (level == "junior" || level == "middle" || level == "senior") {
                errflag = true;
            }
            else {
                fastErrInfo;
            }
        }

        return std::make_shared<Dev>(id, name, salary, language, level);
    }

    double calculateSalary() const override {
        double bonus = 0.0;
        if (level == "senior") bonus = GetSalary() * 0.2;
        else if (level == "middle") bonus = GetSalary() * 0.1;
        return GetSalary() + bonus;
    }

    void printInfo(std::ostream& os) const override {
        os << "Dev Info:\n"
            << "ID: " << GetId() << "\n"
            << "Name: " << GetName() << "\n"
            << "Base Salary: " << GetSalary() << "\n"
            << "Total Salary: " << calculateSalary() << "\n"
            << "Language: " << GetLanguage() << "\n"
            << "Level: " << GetLevel() << "\n";
    }
};

template<typename T>
class Mgr : public Emp {
    int members;
    T averagesalary;
public:
    Mgr() : Mgr(0, "", 0.0, 0, T()) {}
    Mgr(const Mgr& other) : Emp(other), members(other.members), averagesalary(other.averagesalary) {}
    Mgr(int id, const std::string& name, double salary, int members, T averagesalary)
        : Emp(id, name, salary) {
        this->members = members;
        this->averagesalary = averagesalary;
    }

    constexpr int GetMembers() const { return members; }
    constexpr T GetAverageSalary() const { return averagesalary; }

    void SetMembers(const int& members) { this->members = members; }
    void SetAverageSalary(const T& averageSalary) { this->averagesalary = averageSalary; }

    ~Mgr() override {
#ifdef DEBUG
        std::cout << "Деструктор Mgr<" << typeid(T).name() << "> вызван" << std::endl;
#endif
    }

    static std::shared_ptr<Mgr<T>> createFromInput() {
        bool errflag = false;
        int id, members;
        std::string name;
        double salary;
        T averagesalary;

        std::cout << "Создание менеджера:\n";

        std::cout << "ID: ";
        number_filteredInput<int>(id, 0, 1);
        std::cout << "Имя: ";
        letter_filteredInput<std::string>(name, 1);
        std::cout << "Зарплата: ";
        while (!errflag) {
            number_filteredInput<double>(salary, 0, 1);
            if (salary > 0) {
                errflag = true;
            }
            else {
                fastErrInfo;
            }
        }
        errflag = false;
        std::cout << "Число подчиненных: ";
        while (!errflag) {
            number_filteredInput<int>(members, 0, 1);
            if (members > 0) {
                errflag = true;
            }
            else {
                fastErrInfo;
            }
        }
        errflag = false;
        std::cout << "Средняя зарплата команды: ";
        while (!errflag) {
            number_filteredInput<T>(averagesalary, 0, 1);
            if (averagesalary > 0) {
                errflag = true;
            }
            else {
                fastErrInfo;
            }
        }

        return std::make_shared<Mgr<T>>(id, name, salary, members, averagesalary);
    }

    double calculateSalary() const override {
        double bonus = GetMembers() * static_cast<double>(GetAverageSalary()) * 0.01;
        return GetSalary() + bonus;
    }

    void printInfo(std::ostream& os) const override {
        os << "Mgr<" << typeid(T).name() << "> Info:\n"
            << "ID: " << GetId() << "\n"
            << "Name: " << GetName() << "\n"
            << "Base Salary: " << GetSalary() << "\n"
            << "Total Salary: " << calculateSalary() << "\n"
            << "Team Members: " << GetMembers() << "\n"
            << "Average Salary: " << GetAverageSalary() << "\n";
    }
};

class Dsgnr : public Emp {
    std::string designTool;
    bool isUX;
public:
    Dsgnr() : Dsgnr(0, "", 0.0, "Unknown", false) {}
    Dsgnr(const Dsgnr& other) : Emp(other), designTool(other.designTool), isUX(other.isUX) {}
    Dsgnr(int id, const std::string& name, double salary, const std::string& designTool, bool isUX)
        : Emp(id, name, salary) {
        this->designTool = designTool;
        this->isUX = isUX;
    }

    std::string GetDesignTool() const { return designTool; }
    bool GetIsUX() const { return isUX; }

    void SetDesignTool(const std::string& designTool) { this->designTool = designTool; }
    void SetIsUX(bool isUX) { this->isUX = isUX; }

    ~Dsgnr() override {
#ifdef DEBUG
        std::cout << "Деструктор Dsgnr вызван" << std::endl;
#endif
    }

    static std::shared_ptr<Dsgnr> createFromInput() {
        bool errflag = false;
        int id;
        std::string name, designTool;
        double salary;
        bool isUX;
        char uxChoice;

        std::cout << "Создание дизайнера:\n";

        std::cout << "ID: ";
        number_filteredInput<int>(id, 0, 1);
        std::cout << "Имя: ";
        letter_filteredInput<std::string>(name, 1);
        std::cout << "Зарплата: ";
        while (!errflag) {
            number_filteredInput<double>(salary, 0, 1);
            if (salary > 0) {
                errflag = true;
            }
            else {
                fastErrInfo;
            }
        }
        errflag = false;
        std::cout << "Инструмент (Figma/Photoshop/etc): ";
        std::cin.ignore();
        std::getline(std::cin, designTool);
        std::cout << "UX дизайнер? (y/n): ";
        std::cin >> uxChoice;
        isUX = (uxChoice == 'y' || uxChoice == 'Y');

        return std::make_shared<Dsgnr>(id, name, salary, designTool, isUX);
    }

    double calculateSalary() const override {
        double bonus = GetIsUX() ? GetSalary() * 0.15 : GetSalary() * 0.05;
        return GetSalary() + bonus;
    }

    void printInfo(std::ostream& os) const override {
        os << "Dsgnr Info:\n"
            << "ID: " << GetId() << "\n"
            << "Name: " << GetName() << "\n"
            << "Base Salary: " << GetSalary() << "\n"
            << "Total Salary: " << calculateSalary() << "\n"
            << "Design Tool: " << GetDesignTool() << "\n"
            << "Is UX: " << (GetIsUX() ? "Yes" : "No") << "\n";
    }
};

// Класс QA инженера
class QAEng : public Emp {
    std::string testingType;
    bool isAutomation;
public:
    QAEng() : QAEng(0, "", 0.0, "Unknown", false) {}
    QAEng(const QAEng& other) : Emp(other), testingType(other.testingType), isAutomation(other.isAutomation) {}
    QAEng(int id, const std::string& name, double salary, const std::string& testingType, bool isAutomation)
        : Emp(id, name, salary) {
        this->testingType = testingType;
        this->isAutomation = isAutomation;
    }

    std::string GetTestingType() const { return testingType; }
    bool GetIsAutomation() const { return isAutomation; }

    void SetTestingType(const std::string& testingType) { this->testingType = testingType; }
    void SetIsAutomation(bool isAutomation) { this->isAutomation = isAutomation; }

    ~QAEng() override {
#ifdef DEBUG
        std::cout << "Деструктор QAEng вызван" << std::endl;
#endif
    }

    static std::shared_ptr<QAEng> createFromInput() {
        bool errflag = false;
        int id;
        std::string name, testingType;
        double salary;
        bool isAutomation;
        char autoChoice;

        std::cout << "Создание QA инженера:\n";

        std::cout << "ID: ";
        number_filteredInput<int>(id, 0, 1);
        std::cout << "Имя: ";
        letter_filteredInput<std::string>(name, 1);
        std::cout << "Зарплата: ";
        while (!errflag) {
            number_filteredInput<double>(salary, 0, 1);
            if (salary > 0) {
                errflag = true;
            }
            else {
                fastErrInfo;
            }
        }
        errflag = false;
        std::cout << "Тип тестирования: ";
        std::cin.ignore();
        std::getline(std::cin, testingType);
        std::cout << "Автоматизация? (y/n): ";
        std::cin >> autoChoice;
        isAutomation = (autoChoice == 'y' || autoChoice == 'Y');

        return std::make_shared<QAEng>(id, name, salary, testingType, isAutomation);
    }

    double calculateSalary() const override {
        double bonus = GetIsAutomation() ? GetSalary() * 0.2 : GetSalary() * 0.1;
        return GetSalary() + bonus;
    }

    void printInfo(std::ostream& os) const override {
        os << "QAEng Info:\n"
            << "ID: " << GetId() << "\n"
            << "Name: " << GetName() << "\n"
            << "Base Salary: " << GetSalary() << "\n"
            << "Total Salary: " << calculateSalary() << "\n"
            << "Testing Type: " << GetTestingType() << "\n"
            << "Is Automation: " << (GetIsAutomation() ? "Yes" : "No") << "\n";
    }
};

class ITCompany {
    std::vector<std::shared_ptr<Emp>> teamMembers;
    TransactionManager transactionManager;

public:
    void addEmployee(const std::shared_ptr<Emp>& emp) {
        transactionManager.saveState(emp);
        teamMembers.push_back(emp);
    }

    inline bool updateEmployee(int id, const std::string& newName, double newSalary) {
        auto emp = findEmployee(id);
        if (emp) {
            transactionManager.saveState(emp);
            emp->SetName(newName);
            emp->SetSalary(newSalary);
            return true;
        }
        return false;
    }

    inline bool rollbackEmployee(int id) {
        auto emp = findEmployee(id);
        if (emp && transactionManager.hasHistory(id)) {
            return transactionManager.restoreState(emp);
        }
        return false;
    }

    std::shared_ptr<Emp> findEmployee(int id) {
        auto it = std::find_if(teamMembers.begin(), teamMembers.end(),
            [id](const std::shared_ptr<Emp>& emp) { return emp->GetId() == id; });
        return it != teamMembers.end() ? *it : nullptr;
    }

    void printAllEmployees() const {
        if (teamMembers.empty()) {
            std::cout << "Список сотрудников пуст!\n";
            return;
        }

        std::cout << "=== СПИСОК СОТРУДНИКОВ ===\n";
        std::cout << "Общее количество: " << teamMembers.size() << "\n";
        std::cout << "Общие расходы на зарплаты: " << calculateTotalSalary() << "\n\n";

        for (const auto& emp : teamMembers) {
            emp->printInfo(std::cout);
            std::cout << "------------------------\n";
        }
    }

    double calculateTotalSalary() const {
        double total = 0.0;
        for (const auto& emp : teamMembers) {
            total += emp->calculateSalary();
        }
        return total;
    }
};
//template<typename T>
//class SmartPointer {
//    T* ptr;
//public:
//    SmartPointer(T* ptr) { this->ptr = ptr; }
//    ~SmartPointer{ delete ptr; }
//
//    T& operator*() {
//    return *ptr;
//    }
//};
// 
// 
// 
//unique_ptr<int> p1(new int(5));
//unique_ptr<int> p2;
//p2 = move(p1);
//p2.swap(p1);
//get - получить
//reset - стереть 
//release - затереть

//class Transaction {
//    bool failed = false;
//public:
//    void begin() {}
//    void commit(!vailed){}
//    void rollback(vailed){}
//};