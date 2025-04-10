#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<cmath>
//#define DEBAG

static std::ostream& customFormat(std::ostream& os) {
    os << std::setw(10) << std::setfill('#') << std::fixed << std::setprecision(4);
    return os;
}
class QuadraticEquation {
private:
    double a, b, c;
    double root1, root2;
    int rootCount;
public:
    QuadraticEquation() : a(0.0), b(0.0), c(0.0), root1(0.0), root2(0.0), rootCount(0) {}
    QuadraticEquation(const QuadraticEquation& other) : a(other.a), b(other.b), c(other.c), root1(other.root1), root2(other.root2), rootCount(other.rootCount) {}
    void SetQuadraticEquation(double a = 0.0, double b = 0.0, double c = 0.0) {
        this->a = a;
        this->b = b;
        this->c = c;
        rootsCalculate();
    }
    void rootsCalculate() {
        double discriminant = pow(b, 2) - 4 * a * c;
        if (discriminant > 0) {
            rootCount = 2;
            root1 = (-b + sqrt(discriminant)) / (2 * a);
            root2 = (-b - sqrt(discriminant)) / (2 * a);
        }
        else if (discriminant == 0) {
            rootCount = 1;
            root1 = -b / (2 * a);
            root2 = root1;
        }
        else {
            rootCount = 0;
        }
    }
    void Printf() const {
        std::cout << "Коэффициенты: a = " << a << ", b = " << b << ", c = " << c << std::endl;
        std::cout << "Количество корней: " << rootCount << std::endl;
        if (rootCount == 1) {
            std::cout << "Корень: " << customFormat << root1 << std::endl;
        }
        else if (rootCount == 2) {
            std::cout << "Корни: " << customFormat << root1 << ", " << customFormat << root2 << std::endl;
        }
        else {
            std::cout << "Нет корней!" << std::endl;
        }
        std::cout << std::resetiosflags(std::ios::fixed) << std::setprecision(6) << std::setfill(' ');
    }
    void WriteToFile(std::ofstream& outFile2) const {
        outFile2 << "Коэффициенты: a = " << a << ", b = " << b << ", c = " << c << std::endl;
        outFile2 << "Количество корней: " << rootCount << std::endl;
        if (rootCount == 1) {
            outFile2 << "Корень: " << customFormat << root1 << std::endl;
        }
        else if (rootCount == 2) {
            outFile2 << "Корни: " << customFormat << root1 << ", " << customFormat << root2 << std::endl;
        }
        else {
            outFile2 << "Нет корней!" << std::endl;
        }
        outFile2 << std::resetiosflags(std::ios::fixed) << std::setprecision(6) << std::setfill(' ');
    }
    ~QuadraticEquation() {
#ifdef DEBAG
        cout << "Деструктор QuadraticEquation вызван" << endl;
#endif
    }
};
