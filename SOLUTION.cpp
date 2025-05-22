#include "cursor_visibility.h"
#include "cursor_menu.h"
#include "console_inactivity_timer.h"
#include "input_check.h"
#include "smoothWink.h"
#include "project1_header.h"
#include "project2_header.h"
#include "project3_header.h"
#include "project4_header.h"
#include "dproject4.cpp"
#include "project5_header.h"
#include "project6_header.h"
#include "project7.cpp"
#include "project8.cpp"
#include "project9.cpp"
#include <iostream>
#include <windows.h>
#include <vector>

#define fastErrInfo \
SetConsoleTextAttribute(consoleColor, 4);\
std::cerr << "Некорректный ввод. Введите информацию еще раз:\n";\
SetConsoleTextAttribute(consoleColor, 7); 
//#define DEBUG

enum For_SecondaryMenu_Switch { lab_showTask, lab_showTaskAndCopmplete, lab_returnToMainMenu, lab_endOfProgram };
enum For_ladNumberSwitch { lab_1_Encapsulation, lab_2_Dynamic_memory_allocation, lab_3_Friend_functions, lab_4_Inheritance, lab_5_Polymorphism, lab_6_Multiple_inheritance, lab_7_Templates, lab_8_SmartPointers, lab_9_Exeptions, endOfProgram };
enum MainMenuOption { add_developer, add_manager, add_designer, add_qa_engineer, show_all_employees, returnToMainMenu };

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    std::thread timer(inactivity_timer, 100);
    timer.detach();

    const std::string mainMenu[]{
        "Лабораторная работа №1 'Encapsulation'",
        "Лабораторная работа №2 'Dynamic memory allocation'",
        "Лабораторная работа №3 'Friend functions'",
        "Лабораторная работа №4 'Inheritance'",
        "Лабораторная работа №5 'Polymorphism'",
        "Лабораторная работа №6 'Multiple inheritance'",
        "Лабораторная работа №7 'Templates'",
        "Лабораторная работа №8 'Smart Pointers'",
        "Лабораторная работа №9 'Exeptions'",
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
        int choice = main_showMenu(".../mainMenu/", mainMenu, mainMenuCount, 1);
        switch (choice) {
        case lab_1_Encapsulation: {
            bool shouldReturnToMainMenu = false;
            while (!shouldReturnToMainMenu) {
                int secondaryChoice = main_showMenu(".../mainMenu/secondaryMenu/encapsulation", secondaryMenu, secondaryMenuCount);

                switch (secondaryChoice) {
                case lab_showTask: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО:\n\n1. создать программу на языке С / С++, которая позволяет выбрать номер лабораторной работы семестра(1, 2, 3, 4…),\n2. создать массив объектов указанных классов,\n3. считать данные объектов с клавиатуры\n4. вывести данные объектов на экран и в файл\n5. создать методы установки значений полей класса.Методы должны проверять корректность задаваемых параметров\n6. создать конструктор с параметрами, конструктор без параметров, конструктор копирования, деструктор.\n\n3. Создать класс Employee(сотрудник).Класс должен включать поле int для хранения идентификационного номера сотрудника и поле float для хранения величины его оклада.В классе Employee должно быть поле типа класса Date(дата) и перечисления Position(должность).Поле типа Date необходимо использовать для хранения даты приема сотрудника на работу. Поле типа Position использовать для хранения статуса сотрудника : лаборант, секретарь, менеджер и т.д.\n" << std::endl;
                    system("pause");
                    break;
                }
                case lab_showTaskAndCopmplete: {
                    unsigned empCount = 0;
                    int day, month, year, id, empPosition;
                    float salary;

                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО:\n\n1. создать программу на языке С / С++, которая позволяет выбрать номер лабораторной работы семестра(1, 2, 3, 4…),\n2. создать массив объектов указанных классов,\n3. считать данные объектов с клавиатуры\n4. вывести данные объектов на экран и в файл\n5. создать методы установки значений полей класса.Методы должны проверять корректность задаваемых параметров\n6. создать конструктор с параметрами, конструктор без параметров, конструктор копирования, деструктор.\n\n3. Создать класс Employee(сотрудник).Класс должен включать поле int для хранения идентификационного номера сотрудника и поле float для хранения величины его оклада.В классе Employee должно быть поле типа класса Date(дата) и перечисления Position(должность).Поле типа Date необходимо использовать для хранения даты приема сотрудника на работу. Поле типа Position использовать для хранения статуса сотрудника : лаборант, секретарь, менеджер и т.д.\n" << std::endl;
                    showCursor();

                    std::cout << "Введите количество сотрудников: ";;
                    number_filteredInput<unsigned>(empCount);
                    std::cout << "\n";

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
                    shouldReturnToMainMenu = true;
                    break;
                }
                case lab_endOfProgram: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    return 0;
                }
                }
            }
            break;
        }
        case lab_2_Dynamic_memory_allocation: {
            bool shouldReturnToMainMenu = false;
            while (!shouldReturnToMainMenu) {
                int secondaryChoice = main_showMenu(".../mainMenu/secondaryMenu/dynamic_memory_allocation", secondaryMenu, secondaryMenuCount);

                switch (secondaryChoice) {
                case lab_showTask: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО:\n\n 1. создать программу на языке С / С++, которая позволяет выбрать номер лабораторной работы семестра(1, 2, 3, 4…),\n2. создать массив объектов указанных классов,\n3. считать данные объектов с клавиатуры\n4. вывести данные объектов на экран и в файл\n5. создать методы установки значений полей класса.Методы должны проверять корректность задаваемых параметров\n6. создать конструктор с параметрами, конструктор без параметров, конструктор копирования, деструктор.\n\n3. Создать класс QuadraticEquation для решения квадратного уравнения.Установить ширину поля в 10 символов, точность 4 цифры, заполнить пробелы символом «#».Обязательно предусмотреть варианты двух, одного и отсутствия корней.Написать собственный манипулятор.\n" << std::endl;
                    system("pause");
                    break;
                }
                case lab_showTaskAndCopmplete: {
                    unsigned rootsIterCount;
                    double a, b, c;

                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО:\n\n 1. создать программу на языке С / С++, которая позволяет выбрать номер лабораторной работы семестра(1, 2, 3, 4…),\n2. создать массив объектов указанных классов,\n3. считать данные объектов с клавиатуры\n4. вывести данные объектов на экран и в файл\n5. создать методы установки значений полей класса.Методы должны проверять корректность задаваемых параметров\n6. создать конструктор с параметрами, конструктор без параметров, конструктор копирования, деструктор.\n\n3. Создать класс QuadraticEquation для решения квадратного уравнения.Установить ширину поля в 10 символов, точность 4 цифры, заполнить пробелы символом «#».Обязательно предусмотреть варианты двух, одного и отсутствия корней.Написать собственный манипулятор.\n" << std::endl;
                    showCursor();

                    while (true) {
                        std::cout << "Введите количество квадратных уравнений: ";

                        number_filteredInput<unsigned>(rootsIterCount);
                        std::cout << std::endl;
                        if (rootsIterCount != 0) {
                            QuadraticEquation* quadraticEquations = new QuadraticEquation[rootsIterCount];

                            for (int i = 0; i < rootsIterCount; i++) {
                                std::cout << "Введите коэффициенты a, b, c для уравнения:  " << i + 1 << std::endl;

                                number_filteredInput<double>(a);
                                std::cout << std::endl;
                                number_filteredInput<double>(b);
                                std::cout << std::endl;
                                number_filteredInput<double>(c);
                                std::cout << std::endl;

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
                    shouldReturnToMainMenu = true;
                    break;
                }
                case lab_endOfProgram: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    return 0;
                }
                }
            }
            break;
        }
        case lab_3_Friend_functions: {
            bool shouldReturnToMainMenu = false;
            while (!shouldReturnToMainMenu) {
                int secondaryChoice = main_showMenu(".../mainMenu/secondaryMenu/friend_functions", secondaryMenu, secondaryMenuCount);

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
                    shouldReturnToMainMenu = true;
                    break;
                }
                case lab_endOfProgram: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    return 0;
                }
                }
            }
            break;
        }
        case lab_4_Inheritance: {
            bool shouldReturnToMainMenu = false;
            while (!shouldReturnToMainMenu) {
                int secondaryChoice = main_showMenu(".../mainMenu/secondaryMenu/inheritance", secondaryMenu, secondaryMenuCount);

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

                    animals.clear();

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
                    shouldReturnToMainMenu = true;
                    break;
                }
                case lab_endOfProgram: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    return 0;
                }
                }
            }
            break;
        }
        case lab_5_Polymorphism: {
            bool shouldReturnToMainMenu = false;
            while (!shouldReturnToMainMenu) {
                int secondaryChoice = main_showMenu(".../mainMenu/secondaryMenu/polymorphism", secondaryMenu, secondaryMenuCount);

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
                    shouldReturnToMainMenu = true;
                    break;
                }
                case lab_endOfProgram: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    return 0;
                }
                }
            }
            break;
        }
        case lab_6_Multiple_inheritance: {
            bool shouldReturnToMainMenu = false;
            while (!shouldReturnToMainMenu) {
                int secondaryChoice = main_showMenu(".../mainMenu/secondaryMenu/multiple_inheritance", secondaryMenu, secondaryMenuCount);

                switch (secondaryChoice) {
                case lab_showTask: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;

                    std::cout << "\nНЕОБХОДИМО ВЫПОЛНИТЬ:\n\n3. Имеется два класса: «Данные о работнике» (поля класса: фамилия, массив зарплат за квартал), «Налоговые данные»(поля класса : процент подоходного налога).Разработать класс «Платежная форма» для вывода итоговых данных(данных о работке и о его налоговых вычетах). \n" << std::endl;
                    system("pause");
                    break;
                }
                case lab_showTaskAndCopmplete: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО ВЫПОЛНИТЬ:\n\n3. Имеется два класса: «Данные о работнике» (поля класса: фамилия, массив зарплат за квартал), «Налоговые данные»(поля класса : процент подоходного налога).Разработать класс «Платежная форма» для вывода итоговых данных(данных о работке и о его налоговых вычетах). \n" << std::endl;

                    showCursor();

                    std::vector<PaymentForm> forms;
                    PaymentForm pf;

                    pf.ScanPaymentForm(forms, std::cout, std::cin);
                    pf.PrintAllForms(forms, std::cout);
                    printToFile(forms, "payments.txt");

                    hideCursor();

                    system("pause");
                    break;
                }
                case lab_returnToMainMenu: {
                    shouldReturnToMainMenu = true;
                    break;
                }
                case lab_endOfProgram: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    return 0;
                }
                }
            }
            break;
        }
        case lab_7_Templates: {

            const std::string postsecondaryMenu[]{
               "Добавить разработчика",
               "Добавить менеджера",
               "Добавить дизайнера",
               "Добавить QA инженера",
               "Вывести всех сотрудников",
               "Выход в в главное меню"
            };
            int postsecondaryMenuCount = sizeof(postsecondaryMenu) / sizeof(postsecondaryMenu[0]);

            bool shouldReturnToMainMenu = false;
            while (!shouldReturnToMainMenu) {
                int secondaryChoice = main_showMenu(".../mainMenu/secondaryMenu/templates", secondaryMenu, secondaryMenuCount);

                switch (secondaryChoice) {
                case lab_showTask: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО ВЫПОЛНИТЬ:\n\n3. Разработать набор классов (минимум 5) по теме «учет сотрудников ИТ - компании».Корректно реализовать связи между классами.В разработанном наборе классов должен быть хотя бы один шаблонный класс.Все классы должны иметь методы получения и установки значений полей.Использовать конструктор с параметрами, конструктор без параметров, конструктор копирования, деструктор. \n" << std::endl;
                    system("pause");
                    break;
                }
                case lab_showTaskAndCopmplete: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО ВЫПОЛНИТЬ:\n\n3. Разработать набор классов (минимум 5) по теме «учет сотрудников ИТ - компании».Корректно реализовать связи между классами.В разработанном наборе классов должен быть хотя бы один шаблонный класс.Все классы должны иметь методы получения и установки значений полей.Использовать конструктор с параметрами, конструктор без параметров, конструктор копирования, деструктор. \n" << std::endl;
                    system("pause");

                    showCursor();

                    bool shouldReturnToMainMenu = false;
                    while (!shouldReturnToMainMenu) {
                        int postsecondaryChoice = main_showMenu(".../mainMenu/secondaryMenu/templates/postsecondaryMenu", postsecondaryMenu, postsecondaryMenuCount);

                        static std::vector<Empl*> employees;

                        switch (postsecondaryChoice) {
                        case add_developer: {
                            showCursor();
                            try {
                                employees.push_back(new Developer(Developer::createFromInput()));
                                std::cout << "Разработчик успешно добавлен!\n";
                            }
                            catch (...) {
                                std::cout << "Ошибка при добавлении разработчика!\n";
                            }
                            hideCursor();
                            system("pause");
                            break;
                        }
                        case add_manager: {
                            showCursor();
                            try {
                                std::cout << "Выберите тип для средней зарплаты (1 - int, 2 - double): ";
                                int typeChoice;
                                while (!(std::cin >> typeChoice) || (typeChoice != 1 && typeChoice != 2)) {
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    std::cout << "Некорректный ввод. Введите 1 или 2: ";
                                }

                                if (typeChoice == 1) {
                                    employees.push_back(new Manager<int>(Manager<int>::createFromInput()));
                                }
                                else {
                                    employees.push_back(new Manager<double>(Manager<double>::createFromInput()));
                                }
                                std::cout << "Менеджер успешно добавлен!\n";
                            }
                            catch (...) {
                                std::cout << "Ошибка при добавлении менеджера!\n";
                            }
                            hideCursor();
                            system("pause");
                            break;
                        }
                        case add_designer: {
                            showCursor();
                            try {
                                employees.push_back(new Designer(Designer::createFromInput()));
                                std::cout << "Дизайнер успешно добавлен!\n";
                            }
                            catch (...) {
                                std::cout << "Ошибка при добавлении дизайнера!\n";
                            }
                            hideCursor();
                            system("pause");
                            break;
                        }
                        case add_qa_engineer: {
                            showCursor();
                            try {
                                employees.push_back(new QAEngineer(QAEngineer::createFromInput()));
                                std::cout << "QA инженер успешно добавлен!\n";
                            }
                            catch (...) {
                                std::cout << "Ошибка при добавлении QA инженера!\n";
                            }
                            hideCursor();
                            system("pause");
                            break;
                        }
                        case show_all_employees: {
                            if (employees.empty()) {
                                std::cout << "Список сотрудников пуст!\n";
                            }
                            else {
                                std::cout << "=== СПИСОК СОТРУДНИКОВ ===\n\n";
                                for (size_t i = 0; i < employees.size(); ++i) {
                                    std::cout << "Сотрудник #" << i + 1 << "\n";
                                    employees[i]->printInfo(std::cout);
                                    std::cout << "------------------------\n";
                                }
                            }
                            system("pause");
                            break;
                        }
                        case returnToMainMenu: {
                            for (auto& emp : employees) {
                                delete emp;
                            }
                            employees.clear();
                            shouldReturnToMainMenu = true;
                            break;
                        }
                        default: {
                            std::cout << "Неизвестная команда!\n";
                            system("pause");
                            break;
                        }
                    }
                        }

                    hideCursor();

                    break;
                }
                case lab_returnToMainMenu: {
                    shouldReturnToMainMenu = true;
                    break;
                }
                case lab_endOfProgram: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    return 0;
                }
                }
            }
            break;
        }
        case lab_8_SmartPointers: {
            const std::string postsecondaryMenu[]{
               "Добавить разработчика",
               "Добавить менеджера",
               "Добавить дизайнера",
               "Добавить QA инженера",
               "Вывести всех сотрудников",
               "Выход в в главное меню"
            };
            int postsecondaryMenuCount = sizeof(postsecondaryMenu) / sizeof(postsecondaryMenu[0]);

            bool shouldReturnToMainMenu = false;
            while (!shouldReturnToMainMenu) {
                int secondaryChoice = main_showMenu(".../mainMenu/secondaryMenu/smartPointers", secondaryMenu, secondaryMenuCount);

                switch (secondaryChoice) {
                case lab_showTask: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО ВЫПОЛНИТЬ:\n\n3. Разработать набор классов (минимум 5) по теме «учет  сотрудников ИТ - компании».Корректно реализовать связи между классами.Использовать smart - указатели для создания программы учета сведений о сотрудниках и расчета для них заработной платы.В разработанном наборе классов должен быть хотя бы один шаблонный класс.Все классы должны иметь методы получения и установки значений поле.Использовать конструктор с параметрами, конструктор без параметров, конструктор копирования, деструктор. \n" << std::endl;
                    system("pause");
                    break;
                }
                case lab_showTaskAndCopmplete: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО ВЫПОЛНИТЬ:\n\n3. Разработать набор классов (минимум 5) по теме «учет  сотрудников ИТ - компании».Корректно реализовать связи между классами.Использовать smart - указатели для создания программы учета сведений о сотрудниках и расчета для них заработной платы.В разработанном наборе классов должен быть хотя бы один шаблонный класс.Все классы должны иметь методы получения и установки значений поле.Использовать конструктор с параметрами, конструктор без параметров, конструктор копирования, деструктор. \n" << std::endl;
                    system("pause");

                    showCursor();

                    ITCompany company;
                    int choice;

                    do {
                        std::cout << "\n=== Система учета сотрудников ИТ-компании ===\n";
                        std::cout << "1. Добавить разработчика\n";
                        std::cout << "2. Добавить менеджера\n";
                        std::cout << "3. Добавить дизайнера\n";
                        std::cout << "4. Добавить QA инженера\n";
                        std::cout << "5. Показать всех сотрудников\n";
                        std::cout << "6. Изменить данные сотрудника\n";
                        std::cout << "7. Откатить изменения сотрудника\n";
                        std::cout << "0. Выход\n";
                        std::cout << "Выберите действие: ";
                        std::cin >> choice;

                        try {
                            switch (choice) {
                            case 1: {
                                auto dev = Dev::createFromInput();
                                company.addEmployee(dev);
                                std::cout << "Разработчик успешно добавлен!\n";
                                break;
                            }
                            case 2: {
                                std::cout << "Выберите тип для средней зарплаты (1 - int, 2 - double): ";
                                int typeChoice;
                                std::cin >> typeChoice;

                                if (typeChoice == 1) {
                                    auto mgr = Mgr<int>::createFromInput();
                                    company.addEmployee(mgr);
                                }
                                else {
                                    auto mgr = Mgr<double>::createFromInput();
                                    company.addEmployee(mgr);
                                }
                                std::cout << "Менеджер успешно добавлен!\n";
                                break;
                            }
                            case 3: {
                                auto dsgnr = Dsgnr::createFromInput();
                                company.addEmployee(dsgnr);
                                std::cout << "Дизайнер успешно добавлен!\n";
                                break;
                            }
                            case 4: {
                                auto qa = QAEng::createFromInput();
                                company.addEmployee(qa);
                                std::cout << "QA инженер успешно добавлен!\n";
                                break;
                            }
                            case 5: {
                                company.printAllEmployees();
                                break;
                            }
                            case 6: {
                                int id;
                                std::string name;
                                double salary;

                                std::cout << "Введите ID сотрудника: ";
                                std::cin >> id;
                                std::cout << "Введите новое имя: ";
                                std::cin.ignore();
                                std::getline(std::cin, name);
                                std::cout << "Введите новую зарплату: ";
                                std::cin >> salary;

                                if (company.updateEmployee(id, name, salary)) {
                                    std::cout << "Данные обновлены\n";
                                }
                                else {
                                    std::cout << "Сотрудник не найден\n";
                                }
                                break;
                            }
                            case 7: {
                                int id;
                                std::cout << "Введите ID сотрудника: ";
                                std::cin >> id;

                                if (company.rollbackEmployee(id)) {
                                    std::cout << "Изменения откачены\n";
                                }
                                else {
                                    std::cout << "Не удалось откатить изменения\n";
                                }
                                break;
                            }
                            case 0: {
                                std::cout << "Выход из программы...\n";
                                break;
                            }
                            default: {
                                std::cout << "Неверный выбор. Попробуйте снова.\n";
                                break;
                            }
                            }
                        }
                        catch (const std::exception& e) {
                            std::cerr << "Ошибка: " << e.what() << "\n";
                        }
                    } while (choice != 0);

                    hideCursor();

                    break;
                }
                case lab_returnToMainMenu: {
                    shouldReturnToMainMenu = true;
                    break;
                }
                case lab_endOfProgram: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    return 0;
                }
                }
            }
            break;
        }
        case lab_9_Exeptions: {
            bool shouldReturnToMainMenu = false;
            while (!shouldReturnToMainMenu) {
                int secondaryChoice = main_showMenu(".../mainMenu/secondaryMenu/exeptions", secondaryMenu, secondaryMenuCount);

                switch (secondaryChoice) {
                case lab_showTask: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО ВЫПОЛНИТЬ:\n\n3.3. Разработать набор классов (минимум 5 классов, связи между  классами: агрегация, композиция, наследование) по предметной области «Аппаратное обеспечение компьютера».Функционал программы должен позволить собрать компьютер. \n" << std::endl;
                    system("pause");
                    break;
                }
                case lab_showTaskAndCopmplete: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    std::cout << "\nНЕОБХОДИМО ВЫПОЛНИТЬ:\n\n3.3. Разработать набор классов (минимум 5 классов, связи между  классами: агрегация, композиция, наследование) по предметной области «Аппаратное обеспечение компьютера».Функционал программы должен позволить собрать компьютер. \n" << std::endl;
                    system("pause");

                    showCursor();

                    set_terminate(customTerminate);

                    try {
                        try {
                            CPU invalidCPU("CPU", "AMD", 200, 4, -3.4);
                            std::cout << "Параметр добавлен!";
                        }
                        catch (const CPUException& ex) {
                            std::cerr << "Поймано исключение CPU: " << ex.what() << std::endl;
                        }

                        try {
                            Memory invalidMemory("Memory", "Kingston", 100, -16, "DDR4");
                            std::cout << "Параметр добавлен!";
                        }
                        catch (const MemoryException& ex) {
                            std::cerr << "Поймано исключение Memory: " << ex.what() << std::endl;
                        }

                        try {
                            Storage invalidStorage("Storage", "Seagate", 50, 0, false);
                            std::cout << "Параметр добавлен!";
                        }
                        catch (const StorageException& ex) {
                            std::cerr << "Поймано исключение Storage: " << ex.what() << std::endl;
                        }

                        try {
                            GPU invalidGPU("GPU", "NVIDIA", 300, -4);
                            std::cout << "Параметр добавлен!";
                        }
                        catch (const GPUException& ex) {
                            std::cerr << "Поймано исключение GPU: " << ex.what() << std::endl;
                        }

                        try {
                            Motherboard invalidMB("Motherboard", "ASUS", 150, "AM4", 0);
                            std::cout << "Параметр добавлен!";
                        }
                        catch (const MotherboardException& ex) {
                            std::cerr << "Поймано исключение Motherboard: " << ex.what() << std::endl;
                        }

                        try {
                            demonstrateNewException();
                        }
                        catch (...) {
                            std::cerr << "Перенаправленное исключение bad_alloc поймано в main" << std::endl;
                        }

                        CPU cpu("Ryzen 5 3600", "AMD", 200, 6, 3.6);
                        Memory memory("HyperX", "Kingston", 80, 16, "DDR4");
                        Storage storage("Barracuda", "Seagate", 60, 1000, false);
                        GPU gpu("RTX 3060", "NVIDIA", 400, 12);

                        Motherboard mb("B450", "ASUS", 120, "AM4", 4);
                        mb.addComponent(new Memory("HyperX", "Kingston", 80, 16, "DDR4"));
                        mb.addComponent(new CPU("Ryzen 5 3600", "AMD", 200, 6, 3.6));

                        Computer myPC("Мой ПК");
                        myPC.addComponent(&mb);
                        myPC.addComponent(&storage);
                        myPC.addComponent(&gpu);

                        myPC.printConfiguration();
                        std::cout << "Общая стоимость: $" << myPC.getTotalPrice() << std::endl;

                        try {
                            throw HardwareException("Тестовое пользовательское исключение");
                        }
                        catch (const HardwareException& e) {
                            std::cerr << "Поймано пользовательское исключение: " << e.what() << std::endl;
                        }


                    }
                    catch (...) {
                        std::cerr << "Поймано неизвестное исключение в main" << std::   endl;
                    }

                    system("pause");
                    hideCursor();

                    break;
                }
                case lab_returnToMainMenu: {
                    shouldReturnToMainMenu = true;
                    break;
                }
                case lab_endOfProgram: {
                    std::cout << "\nВы выбрали: " << secondaryMenu[secondaryChoice] << std::endl;
                    return 0;
                }
                }
            }
            break;
        }
        case endOfProgram: {// Выход из программы
            std::cout << "\nВы выбрали: " << mainMenu[choice] << " ";
            smoothWink();
            return 0;
        }
              break;
        }
    }
}