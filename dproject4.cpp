#include<iostream>
#include<string>

class Animal {
    std::string name;
public:
    virtual void speak(std::ostream& os) const = 0;
};
class Dog :public Animal {
public:
    void speak(std::ostream& os) const override {
        os << "Gav!\n";
    }
};
class Cat :public Animal {
public:
    void speak(std::ostream& os) const override {
        os << "Meooooow!\n";
    }
};
class Parrot :public Animal {
public:
    void speak(std::ostream& os) const override {
        os << "Hrrr-Hrrrr!\n";
    }
};