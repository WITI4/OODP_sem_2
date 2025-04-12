#include "project1.cpp"
#include "project2.cpp"
#include "project3.cpp"
#include "project4.cpp"
#include "dproject4.cpp"
#include "project5.cpp"
#include "cursor_visibility.h"
#include "cursor_menu.h"
#include <iostream>
#include<windows.h>
#include <conio.h>
#include <stdio.h>
#include <vector>
#include<cctype>

#undef max
#define fastErrInfo \
SetConsoleTextAttribute(consoleColor, 4);\
std::cerr << "Некорректный ввод. Введите информацию еще раз:\n";\
SetConsoleTextAttribute(consoleColor, 7); 
//#define DEBUG

enum For_SecondaryMenu_Switch {
    lab_showTask = 0,
    lab_showTaskAndCopmplete = 1,
    lab_returnToMainMenu = 2,
    lab_endOfProgram = 3
};

int main() {
    setlocale(0, "ru");
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    const std::string mainMenu[]{
        "Лабораторная работа №1",
        "Лабораторная работа №2",
        "Лабораторная работа №3",
        "Лабораторная работа №4",
        "Лабораторная работа №5",
        "Лабораторная работа №6",
        "Выход из программы"
    };
    int mainMenuCount = sizeof(mainMenu) / sizeof(mainMenu[0]);

    const std::string secondaryMenu[]{
        "Посмотреть задание",
        "Посмотреть задание и выполнить работу",
        "Вернуться в выбор лабораторной работы",
        "Выход из программы"
    };
    int secondaryMenuCount = sizeof(secondaryMenu) / sizeof(secondaryMenu[0]);

    while (true) {
        hideCursor();
        int choice = showMenu(".../mainMenu/", mainMenu, mainMenuCount);
        switch (choice) {
        case 0: { // Лабораторная работа №1
            while (true) {
                int secondaryChoice = showMenu(".../mainMenu/secondaryMenu/", secondaryMenu, secondaryMenuCount);

                switch (secondaryChoice) {
                case lab_showTask: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО:\n\n1. создать программу на языке С / С++, которая позволяет выбрать номер лабораторной работы семестра(1, 2, 3, 4…),\n2. создать массив объектов указанных классов,\n3. считать данные объектов с клавиатуры\n4. вывести данные объектов на экран и в файл\n5. создать методы установки значений полей класса.Методы должны проверять корректность задаваемых параметров\n6. создать конструктор с параметрами, конструктор без параметров, конструктор копирования, деструктор.\n\n3. Создать класс Employee(сотрудник).Класс должен включать поле int для хранения идентификационного номера сотрудника и поле float для хранения величины его оклада.В классе Employee должно быть поле типа класса Date(дата) и перечисления Position(должность).Поле типа Date необходимо использовать для хранения даты приема сотрудника на работу. Поле типа Position использовать для хранения статуса сотрудника : лаборант, секретарь, менеджер и т.д.\n" << std::endl;
                    system("pause");
                    break;
                }
                case lab_showTaskAndCopmplete: {
                    int day, month, year, id, empPosition, empCount = 0;
                    float salary;

                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО:\n\n1. создать программу на языке С / С++, которая позволяет выбрать номер лабораторной работы семестра(1, 2, 3, 4…),\n2. создать массив объектов указанных классов,\n3. считать данные объектов с клавиатуры\n4. вывести данные объектов на экран и в файл\n5. создать методы установки значений полей класса.Методы должны проверять корректность задаваемых параметров\n6. создать конструктор с параметрами, конструктор без параметров, конструктор копирования, деструктор.\n\n3. Создать класс Employee(сотрудник).Класс должен включать поле int для хранения идентификационного номера сотрудника и поле float для хранения величины его оклада.В классе Employee должно быть поле типа класса Date(дата) и перечисления Position(должность).Поле типа Date необходимо использовать для хранения даты приема сотрудника на работу. Поле типа Position использовать для хранения статуса сотрудника : лаборант, секретарь, менеджер и т.д.\n" << std::endl;
                    showCursor();

                    std::cout << "Введите количество сотрудников: ";
                    while (!(std::cin >> empCount) || std::cin.peek() != '\n') {
                        fastErrInfo
                            std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                    if (empCount > 0) {
                        Employee* employees = new Employee[empCount];

                        for (int i = 0; i < empCount; i++) {
                            std::cout << "Сотрудник под номером: " << i + 1 << std::endl;
                            std::cout << "Введите идентификационный номер сотрудника: ";
                            while (!(std::cin >> id) || id < 0 || std::cin.peek() != '\n') {
                                fastErrInfo
                                    std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            }
                            std::cout << "Введите величину оклада сотрудника: ";
                            while (!(std::cin >> salary) || salary < 0 || std::cin.peek() != '\n') {
                                fastErrInfo
                                    std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            }

                            std::cout << "Введите день, месяц и год приема на работу:\n";
                            while (true) {
                                if (!(std::cin >> day >> month >> year) || std::cin.peek() != '\n') {
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    fastErrInfo
                                        continue;
                                }
                                if (isValidDate(day, month, year)) break;
                                else {
                                    fastErrInfo
                                }
                            }
                            Date hireDate(day, month, year);

                            std::cout << "Введите позицию сотрудника (1 - LABORANT, 2 - SECRETAR, 3 - MANAGER): ";
                            while (!(std::cin >> empPosition) || empPosition < 1 || std::cin.peek() != '\n') {
                                fastErrInfo
                                    std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            }

                            employees[i] = Employee(id, salary, hireDate, static_cast<Position>(empPosition - 1));
                        }

                        std::cout << "\nИнформация о сотрудниках:\n";
                        for (int i = 0; i < empCount; i++) {
                            employees[i].Printf();
                            std::cout << std::endl;
                        }

                        std::ofstream outFile("employees.txt");
                        if (outFile.is_open()) {
                            for (int i = 0; i < empCount; i++) {
                                employees[i].WriteToFile(outFile);
                            }
                            outFile.close();
                            std::cout << "\nИнформация о сотрудниках успешно записана в файл employees.txt" << std::endl;
                        }
                        else {
                            std::cout << "Ошибка открытия файла для записи!" << std::endl;
                        }

                        delete[] employees;
                    }
                    hideCursor();

                    system("pause");
                    break;
                }
                case lab_returnToMainMenu: {
                    goto mainMenu;
                }
                case lab_endOfProgram: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    return 0;
                }
                }
            }
        }
        case 1: { // Лабораторная работа №2
            while (true) {
                int secondaryChoice = showMenu(".../mainMenu/secondaryMenu/", secondaryMenu, secondaryMenuCount);

                switch (secondaryChoice) {
                case lab_showTask: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО:\n\n 1. создать программу на языке С / С++, которая позволяет выбрать номер лабораторной работы семестра(1, 2, 3, 4…),\n2. создать массив объектов указанных классов,\n3. считать данные объектов с клавиатуры\n4. вывести данные объектов на экран и в файл\n5. создать методы установки значений полей класса.Методы должны проверять корректность задаваемых параметров\n6. создать конструктор с параметрами, конструктор без параметров, конструктор копирования, деструктор.\n\n3. Создать класс QuadraticEquation для решения квадратного уравнения.Установить ширину поля в 10 символов, точность 4 цифры, заполнить пробелы символом «#».Обязательно предусмотреть варианты двух, одного и отсутствия корней.Написать собственный манипулятор.\n" << std::endl;
                    system("pause");
                    break;
                }
                case lab_showTaskAndCopmplete: {
                    int rootsIterCount = 0;
                    double a, b, c;

                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО:\n\n 1. создать программу на языке С / С++, которая позволяет выбрать номер лабораторной работы семестра(1, 2, 3, 4…),\n2. создать массив объектов указанных классов,\n3. считать данные объектов с клавиатуры\n4. вывести данные объектов на экран и в файл\n5. создать методы установки значений полей класса.Методы должны проверять корректность задаваемых параметров\n6. создать конструктор с параметрами, конструктор без параметров, конструктор копирования, деструктор.\n\n3. Создать класс QuadraticEquation для решения квадратного уравнения.Установить ширину поля в 10 символов, точность 4 цифры, заполнить пробелы символом «#».Обязательно предусмотреть варианты двух, одного и отсутствия корней.Написать собственный манипулятор.\n" << std::endl;
                    showCursor();

                    while (true) {
                        std::cout << "Введите количество квадратных уравнений: ";
                        while (!(std::cin >> rootsIterCount) || std::cin.peek() != '\n') {
                            fastErrInfo
                                std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                        if (rootsIterCount > 0) {
                            QuadraticEquation* quadraticEquations = new QuadraticEquation[rootsIterCount];

                            for (int i = 0; i < rootsIterCount; i++) {
                                std::cout << "Введите коэффициенты a, b, c для уравнения:  " << i + 1 << std::endl;
                                while (!(std::cin >> a >> b >> c) || std::cin.peek() != '\n') {
                                    fastErrInfo
                                        std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }
                                quadraticEquations[i].SetQuadraticEquation(a, b, c);
                            }

                            std::cout << "\nИнформация о корнях:\n";
                            for (int i = 0; i < rootsIterCount; i++) {
                                quadraticEquations[i].Printf();
                                std::cout << std::endl;
                            }

                            std::ofstream outFile2("quadraticEquations.txt");
                            if (outFile2.is_open()) {
                                for (int i = 0; i < rootsIterCount; i++) {
                                    quadraticEquations[i].WriteToFile(outFile2);
                                }
                                outFile2.close();
                                std::cout << "\nИнформация об уранениях успешно записана в файл quadraticEquations.txt" << std::endl;
                            }
                            else {
                                std::cout << "Ошибка открытия файла для записи!" << std::endl;
                            }

                            delete[] quadraticEquations;
                            break;
                        }
                        else {
                            fastErrInfo
                        }
                    }
                    hideCursor();

                    system("pause");
                    break;
                }
                case lab_returnToMainMenu: {
                    goto mainMenu;
                }
                case lab_endOfProgram: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    return 0;
                }
                }
            }
        }
        case 2: { // Лабораторная работа №3
            while (true) {
                int secondaryChoice = showMenu(".../mainMenu/secondaryMenu/", secondaryMenu, secondaryMenuCount);

                switch (secondaryChoice) {
                case lab_showTask: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО:\n\n3. Реализовать класс String для работы со строками. Создать методы доступа к полям класса.Перегрузить для объектов класса String операторы «!»(пуст ли объект класса), «()(int, int)»(возвращение подстроки объекта), «[]»(возвращение некоторого символа строки).Реализовать конструкторы (по умолчанию, с параметрами, копирования), деструктор.Реализовать friend - функции для операторов ввода / вывода в поток для созданного класса\n" << std::endl;
                    system("pause");
                    break;
                }
                case lab_showTaskAndCopmplete: {
                    int iStart, iEnd, index;
                    std::string str;
                    String s1;

                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО:\n\n3. Реализовать класс String для работы со строками. Создать методы доступа к полям класса.Перегрузить для объектов класса String операторы «!»(пуст ли объект класса), «()(int, int)»(возвращение подстроки объекта), «[]»(возвращение некоторого символа строки).Реализовать конструкторы (по умолчанию, с параметрами, копирования), деструктор.Реализовать friend - функции для операторов ввода / вывода в поток для созданного класса\n" << std::endl;

                    showCursor();
                    while (true) {
                        std::cout << "Введите строку: ";
                        std::getline(std::cin, str);
                        s1.SetStr(str);
                        if (!s1) {
                            std::cout << "Строка пустая" << std::endl;
                            break;
                        }
                        else {
                            std::cout << "Строка не пустая" << std::endl;

                            std::cout << "-----------------------------------------\n\nВведите номер символа в строке, который хотите получить: ";
                            while (!(std::cin >> index) || index < 1 || index > str.length() || std::cin.peek() != '\n') {
                                fastErrInfo
                                    std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            }
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            char ch = s1[index - 1];
                            std::cout << "Символ по индексу " << index << ": " << ch << std::endl;

                            std::cout << "-----------------------------------------\n\nВведите начальный и конечный индекс в строке (для получения подстроки):" << std::endl;
                            while (!(std::cin >> iStart >> iEnd) || iStart < 1 || iEnd > str.length() || iEnd < iStart || std::cin.peek() != '\n') {
                                fastErrInfo
                                    std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            }
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::string subString = s1(iStart - 1, iEnd - 1);
                            std::cout << "Подстрока: " << subString << std::endl;
                            break;
                        }
                    }
                    hideCursor();

                    system("pause");
                    break;
                }
                case lab_returnToMainMenu: {
                    goto mainMenu;
                }
                case lab_endOfProgram: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    return 0;
                }
                }
            }
        }
        case 3: { // Лабораторная работа №4
            while (true) {
                int secondaryChoice = showMenu(".../mainMenu/secondaryMenu/", secondaryMenu, secondaryMenuCount);

                switch (secondaryChoice) {
                case lab_showTask: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО:\n\n3.Создать класс «Человек», включающий в себя ФИО, год рождения, паспортные данные.Создать классы «Предприниматель» с полями «номер лицензии», «адрес регистрации», «УНН», «данные о налоговых платежах»; «Турист» с полями «данные о пересечении границы»; «Челнок» с полем «список адресов, по которым покупался товар».Создать массив объектов базового класса и заполнить этот массив объектами базового и производных классов.Написать программу, которая определяет самого старшего из созданных объектов и выводит данные о созданных объектах в файл.Классы должны содержать методы получения и изменения значений всех полей.Все поля классов должны быть объявлены с атрибутами private или protected\n" << std::endl;
                    system("pause");
                    break;
                }
                case lab_showTaskAndCopmplete: {


                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО:\n\n3.Создать класс «Человек», включающий в себя ФИО, год рождения, паспортные данные.Создать классы «Предприниматель» с полями «номер лицензии», «адрес регистрации», «УНН», «данные о налоговых платежах»; «Турист» с полями «данные о пересечении границы»; «Челнок» с полем «список адресов, по которым покупался товар».Создать массив объектов базового класса и заполнить этот массив объектами базового и производных классов.Написать программу, которая определяет самого старшего из созданных объектов и выводит данные о созданных объектах в файл.Классы должны содержать методы получения и изменения значений всех полей.Все поля классов должны быть объявлены с атрибутами private или protected\n" << std::endl;

                    showCursor();

                    std::vector<Animal*> animals;
                    Dog dog;
                    Cat cat;
                    Parrot parrot;

                    std::string type;

                    for (int i = 0; i < 5; i++) {
                        std::cout << "Введите тип животного " << i + 1 << " : ";
                        std::cin >> type;

                        if (type == "dog") {
                            animals.push_back(&dog);
                            animals.back()->speak(std::cout);
                        }
                        else if (type == "cat") {
                            animals.push_back(&cat);
                            animals.back()->speak(std::cout);
                        }
                        else if (type == "parrot") {
                            animals.push_back(&parrot);
                            animals.back()->speak(std::cout);
                        }
                        else {
                            fastErrInfo;
                            i--;
                        }
                    }

                    /*std::vector<Human*> people;

                    people.push_back(new Entrepreneur("Иванов Иван Иванович", 1980, "AB1234567", "LIC123", "ул. Ленина, 1", "123456789", "Налог 2022: 1000$"));
                    people.push_back(new Entrepreneur("Смирнова Анна Владимировна", 1965, "GH3456789", "LIC456", "ул. Мира, 5", "987654321", "Налог 2022: 1500$"));
                    people.push_back(new Shuttle("Сидоров Сидор Сидорович", 1990, "EF5678912", "Турция, Китай"));
                    people.push_back(new Tourist("Петров Петр Петрович", 1975, "CD9876543", "2023-01-15: въезд"));

                    for (int i = 0; i < people.size(); i++) {
                        people[i]->PrintInfo(std::cout);
                        std::cout << std::string(20, '-') << std::endl;
                    }

                    Human* oldest = findOldest(people);
                    if (oldest) {
                        std::cout << "Самый старший человек:\n";
                        oldest->PrintInfo(std::cout);
                        std::cout << std::string(20, '-') << std::endl;
                    }

                    printToFile(people, "people_data.txt");
                    std::cout << "Данные сохранены в файл 'people_data.txt'\n";

                    people.clear();*/

                    hideCursor();

                    system("pause");
                    break;
                }
                case lab_returnToMainMenu: {
                    goto mainMenu;
                }
                case lab_endOfProgram: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    return 0;
                }
                }
            }
        }
        case 4: { // Лабораторная работа №5
            while (true) {
                int secondaryChoice = showMenu(".../mainMenu/secondaryMenu/", secondaryMenu, secondaryMenuCount);

                switch (secondaryChoice) {
                case lab_showTask: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nРАБОТЕ ОБЯЗАТЕЛЬНО РЕАЛИЗОВАТЬ:\n\n1. ДИНАМИЧЕСКИЙ ПОЛИМОРФИЗМ,\n2. СВЯЗЬ «НАСЛЕДОВАНИЕ»,\n3. СОЗДАТЬ АБСТРАКТНЫЙ КЛАСС,\n4. ПЕРЕОПРЕДЕЛЕНИЕ МЕТОДОВ КЛАССА.\n\n3. Написать программу учета наличия различных транспортных средств в автопарке.Разработать абстрактный базовый класс и набор дочерних классов содержащий поля с информацией о транспортных средствах.Классы должны содержать следующие поля : тип транспортного средства, количество мест для пассажиров и данные о водителе.По запросу выдавать необходимую информацию о транспортных средствах. Использовать конструктор с параметрами, конструктор без параметров, конструктор копирования.В класс добавить необходимый набор полей и методов(минимум два поля и два метода) на свое усмотрение. Предусмотреть метод для записи полученных данных в файл.\n" << std::endl;
                    system("pause");
                    break;
                }
                case lab_showTaskAndCopmplete: {


                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nРАБОТЕ ОБЯЗАТЕЛЬНО РЕАЛИЗОВАТЬ:\n\n1. ДИНАМИЧЕСКИЙ ПОЛИМОРФИЗМ,\n2. СВЯЗЬ «НАСЛЕДОВАНИЕ»,\n3. СОЗДАТЬ АБСТРАКТНЫЙ КЛАСС,\n4. ПЕРЕОПРЕДЕЛЕНИЕ МЕТОДОВ КЛАССА.\n\n3. Написать программу учета наличия различных транспортных средств в автопарке.Разработать абстрактный базовый класс и набор дочерних классов содержащий поля с информацией о транспортных средствах.Классы должны содержать следующие поля : тип транспортного средства, количество мест для пассажиров и данные о водителе.По запросу выдавать необходимую информацию о транспортных средствах. Использовать конструктор с параметрами, конструктор без параметров, конструктор копирования.В класс добавить необходимый набор полей и методов(минимум два поля и два метода) на свое усмотрение. Предусмотреть метод для записи полученных данных в файл.\n" << std::endl;

                    showCursor();

                    std::vector<Vehicle*> fleet;

                    Driver* driver1 = new Driver("Иванов Иван Иванович", 5, "C", 35);
                    Driver* driver2 = new Driver("Петров Петр Петрович", 10, "CE", 42);
                    Driver* driver3 = new Driver("Сидорова Анна Михайловна", 3, "B", 28);
                    fleet.push_back(new Truck("Грузовик-рефрижератор", 2, "А123БВ", 5000.0, true));
                    fleet.push_back(new Truck("Самосвал", 3, "В456ГД", 10000.0, false));
                    fleet.push_back(new Truck("Тягач с прицепом", 2, "Е789ЖЗ", 15000.0, true));
                    fleet.push_back(new Car("Седан бизнес-класса", 5, "О777ОО", "Премиум", false));
                    fleet.push_back(new Car("Хэтчбек", 5, "У123УУ", "Стандарт", true));
                    fleet.push_back(new Car("Внедорожник", 7, "Т456ТТ", "SUV", false));
                    fleet.push_back(new Truck("Микроавтобус", 12, "М789ММ", 2500.0, false));
                    fleet.push_back(new Truck("Минивэн", 7, "Н123НН", 1800.0, false));
                    fleet.push_back(driver1);
                    fleet.push_back(driver2);
                    fleet.push_back(driver3);

                    for (int i = 0; i < fleet.size(); i++) {
                        fleet[i]->PrintInfo(std::cout);
                        std::cout << std::string(20, '-') << std::endl;
                    }

                    printToFile(fleet, "people_data.txt");
                    std::cout << "Данные сохранены в файл 'people_data.txt'\n";

                    fleet.clear();

                    hideCursor();

                    system("pause");
                    break;
                }
                case lab_returnToMainMenu: {
                    goto mainMenu;
                }
                case lab_endOfProgram: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    return 0;
                }
                }
            }
        }
        case 5: { // Лабораторная работа №6
            while (true) {
                int secondaryChoice = showMenu(".../mainMenu/secondaryMenu/", secondaryMenu, secondaryMenuCount);

                switch (secondaryChoice) {
                case lab_showTask: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nРАБОТЕ ОБЯЗАТЕЛЬНО РЕАЛИЗОВАТЬ:\n\n1. ДИНАМИЧЕСКИЙ ПОЛИМОРФИЗМ,\n2. СВЯЗЬ «НАСЛЕДОВАНИЕ»,\n3. СОЗДАТЬ АБСТРАКТНЫЙ КЛАСС,\n4. ПЕРЕОПРЕДЕЛЕНИЕ МЕТОДОВ КЛАССА.\n\n3. Написать программу учета наличия различных транспортных средств в автопарке.Разработать абстрактный базовый класс и набор дочерних классов содержащий поля с информацией о транспортных средствах.Классы должны содержать следующие поля : тип транспортного средства, количество мест для пассажиров и данные о водителе.По запросу выдавать необходимую информацию о транспортных средствах. Использовать конструктор с параметрами, конструктор без параметров, конструктор копирования.В класс добавить необходимый набор полей и методов(минимум два поля и два метода) на свое усмотрение. Предусмотреть метод для записи полученных данных в файл.\n" << std::endl;
                    system("pause");
                    break;
                }
                case lab_showTaskAndCopmplete: {


                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nРАБОТЕ ОБЯЗАТЕЛЬНО РЕАЛИЗОВАТЬ:\n\n1. ДИНАМИЧЕСКИЙ ПОЛИМОРФИЗМ,\n2. СВЯЗЬ «НАСЛЕДОВАНИЕ»,\n3. СОЗДАТЬ АБСТРАКТНЫЙ КЛАСС,\n4. ПЕРЕОПРЕДЕЛЕНИЕ МЕТОДОВ КЛАССА.\n\n3. Написать программу учета наличия различных транспортных средств в автопарке.Разработать абстрактный базовый класс и набор дочерних классов содержащий поля с информацией о транспортных средствах.Классы должны содержать следующие поля : тип транспортного средства, количество мест для пассажиров и данные о водителе.По запросу выдавать необходимую информацию о транспортных средствах. Использовать конструктор с параметрами, конструктор без параметров, конструктор копирования.В класс добавить необходимый набор полей и методов(минимум два поля и два метода) на свое усмотрение. Предусмотреть метод для записи полученных данных в файл.\n" << std::endl;

                    showCursor();



                    hideCursor();

                    system("pause");
                    break;
                }
                case lab_returnToMainMenu: {
                    goto mainMenu;
                }
                case lab_endOfProgram: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    return 0;
                }
                }
            }
        }
        case 6: {// Выход из программы
            std::cout << "\nВы выбрали: " << mainMenu[choice] << std::endl;
            return 0;
        }
          mainMenu:;
        }
    }
}