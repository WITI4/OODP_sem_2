#pragma once
#include <iostream>
#include <string>
#include <fstream>

enum Position {
    LABORANT, SECRETAR, MANAGER, OTHER
};

class Date {
private:
    int day;
    int month;
    int year;
public:
    Date();
    Date(const Date& other);
    Date(int day, int month, int year);
    void Printf() const;
    std::string ToString() const;
    ~Date();
};

class Employee {
private:
    int id;
    float salary;
    Date hireDate;
    Position empPosition;
public:
    Employee();
    Employee(const Employee& other);
    Employee(int id, float salary, const Date& hireDate, Position empPosition);
    void Printf();
    std::string GetempPosition();
    void WriteToFile(std::ofstream& outFile);
    ~Employee();
};

int isValidDate(int day, int month, int year);
