#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>

static std::ostream& customFormat(std::ostream& os);

class QuadraticEquation {
private:
    double a, b, c;
    double root1, root2;
    int rootCount;

public:
    QuadraticEquation();
    QuadraticEquation(const QuadraticEquation& other);
    void SetQuadraticEquation(double a = 0.0, double b = 0.0, double c = 0.0);
    void rootsCalculate();
    void Printf() const;
    void WriteToFile(std::ofstream& outFile2) const;
    ~QuadraticEquation();
};