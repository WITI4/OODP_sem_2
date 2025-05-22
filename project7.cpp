#include "input_check.h"
#include <iostream>
#include <string>
#include <vector>

#define fastErrInfo \
std::cerr << "Некорректный ввод. Введите информацию еще раз:\n";

class Empl {
    int id;
    std::string name;
    double salary;
public:
    Empl() : Empl(0, "", 0.0) {}
    Empl(const Empl& other) : id(other.id), name(other.name), salary(other.salary) {}
    Empl(int id, const std::string& name, double salary) {
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

    virtual ~Empl() {
#ifdef DEBUG
        std::cout << "Деструктор Empl вызван" << std::endl;
#endif
    }

    virtual void printInfo(std::ostream& os) const = 0;
};

class Developer : public Empl {
    std::string language;
    std::string level;
public:
    Developer() : Developer(0, "", 0.0, "Unknown", "Unknown") {}
    Developer(const Developer& other) : Empl(other), language(other.language), level(other.level) {}
    Developer(int id, const std::string& name, double salary, const std::string& language, const std::string& level) : Empl(id, name, salary) {
        this->language = language;
        this->level = level;
    }

    std::string GetLanguage() const { return language; }
    std::string GetLevel() const { return level; }

    void SetLanguage(const std::string& language) { this->language = language; }
    void SetLevel(const std::string& level) { this->level = level; }

    ~Developer() override {
#ifdef DEBUG
        std::cout << "Деструктор Developer вызван" << std::endl;
#endif
    }

    static Developer createFromInput() {
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
            if (language == "c++" || language == "c" || language == "php" || language == "c#" || language == "js" || language == "go" || language == "java") {
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

        return Developer(id, name, salary, language, level);
    }

    void printInfo(std::ostream& os) const override {
        os << "Developer Info:\n"
            << "ID: " << GetId() << "\n"
            << "Name: " << GetName() << "\n"
            << "Salary: " << GetSalary() << "\n"
            << "Language: " << GetLanguage() << "\n"
            << "Level: " << GetLevel() << "\n";
    }
};

template<typename T>
class Manager : public Empl {
    int members;
    T averagesalary;
public:
    Manager() : Manager(0, "", 0.0, 0, T()) {}
    Manager(const Manager& other) : Empl(other), members(other.members), averagesalary(other.averagesalary) {}
    Manager(int id, const std::string& name, double salary, int members, T averagesalary) : Empl(id, name, salary) {
        this->members = members;
        this->averagesalary = averagesalary;
    }

    constexpr int GetMembers() const { return members; }
    constexpr T GetAverageSalary() const { return averagesalary; }

    void SetMembers(const int& members) { this->members = members; }
    void SetAverageSalary(const T& averageSalary) { this->averagesalary = averageSalary; }

    ~Manager() override {
#ifdef DEBUG
        std::cout << "Деструктор Manager<" << typeid(T).name() << "> вызван" << std::endl;
#endif
    }

    static Manager createFromInput() {
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

        return Manager(id, name, salary, members, averagesalary);
    }

    void printInfo(std::ostream& os) const override {
        os << "Manager<" << typeid(T).name() << "> Info:\n"
            << "ID: " << GetId() << "\n"
            << "Name: " << GetName() << "\n"
            << "Salary: " << GetSalary() << "\n"
            << "Team Members: " << GetMembers() << "\n"
            << "Average Salary: " << GetAverageSalary() << "\n";
    }
};

class Designer : public Empl {
    std::string designTool;
    bool isUX;
public:
    Designer() : Designer(0, "", 0.0, "Unknown", false) {}
    Designer(const Designer& other) : Empl(other), designTool(other.designTool), isUX(other.isUX) {}
    Designer(int id, const std::string& name, double salary, const std::string& designTool, bool isUX) : Empl(id, name, salary) {
        this->designTool = designTool;
        this->isUX = isUX;
    }

    std::string GetDesignTool() const { return designTool; }
    bool GetIsUX() const { return isUX; }

    void SetDesignTool(const std::string& designTool) { this->designTool = designTool; }
    void SetIsUX(bool isUX) { this->isUX = isUX; }

    ~Designer() override {
#ifdef DEBUG
        std::cout << "Деструктор Designer вызван" << std::endl;
#endif
    }

    static Designer createFromInput() {
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
        std::cout << "Инструмент (Figma/Photoshop/etc): "; std::getline(std::cin, designTool);
        std::cout << "UX дизайнер? (y/n): "; std::cin >> uxChoice;
        isUX = (uxChoice == 'y' || uxChoice == 'Y');

        return Designer(id, name, salary, designTool, isUX);
    }

    void printInfo(std::ostream& os) const override {
        os << "Designer Info:\n"
            << "ID: " << GetId() << "\n"
            << "Name: " << GetName() << "\n"
            << "Salary: " << GetSalary() << "\n"
            << "Design Tool: " << GetDesignTool() << "\n"
            << "Is UX: " << (GetIsUX() ? "Yes" : "No") << "\n";
    }
};

class QAEngineer : public Empl {
    std::string testingType;
    bool isAutomation;
public:
    QAEngineer() : QAEngineer(0, "", 0.0, "Unknown", false) {}
    QAEngineer(const QAEngineer& other) : Empl(other), testingType(other.testingType), isAutomation(other.isAutomation) {}
    QAEngineer(int id, const std::string& name, double salary, const std::string& testingType, bool isAutomation) : Empl(id, name, salary) {
        this->testingType = testingType;
        this->isAutomation = isAutomation;
    }

    std::string GetTestingType() const { return testingType; }
    bool GetIsAutomation() const { return isAutomation; }

    void SetTestingType(const std::string& testingType) { this->testingType = testingType; }
    void SetIsAutomation(bool isAutomation) { this->isAutomation = isAutomation; }

    ~QAEngineer() override {
#ifdef DEBUG
        std::cout << "Деструктор QAEngineer вызван" << std::endl;
#endif
    }

    static QAEngineer createFromInput() {
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
        std::cout << "Тип тестирования: "; std::getline(std::cin, testingType);
        std::cout << "Автоматизация? (y/n): "; std::cin >> autoChoice;
        isAutomation = (autoChoice == 'y' || autoChoice == 'Y');

        return QAEngineer(id, name, salary, testingType, isAutomation);
    }

    void printInfo(std::ostream& os) const override {
        os << "QA Engineer Info:\n"
            << "ID: " << GetId() << "\n"
            << "Name: " << GetName() << "\n"
            << "Salary: " << GetSalary() << "\n"
            << "Testing Type: " << GetTestingType() << "\n"
            << "Is Automation: " << (GetIsAutomation() ? "Yes" : "No") << "\n";
    }
};