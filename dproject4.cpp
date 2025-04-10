#include<iostream>
#include<string>
#include <fstream>

class Animal {
    std::string name;
public:
    virtual void speak(std::ostream& out) const = 0;
};

class Dog : public Animal {
    std::string name;
public:
    Dog(const std::string& n) : name(n) {}
    void speak(std::ostream& os) const override {
        os << "name: " << name << "speak: " << "Woof!\n";
    }
};

class Cat : public Animal {
    std::string name;
public:
    Cat(const std::string& n) : name(n) {}
    void speak(std::ostream& os) const override {
        os << "name: " << name << "speak: " << "Meeeeeeow!\n";
    }
    class Parrot : public Animal {
        std::string name;
    public:
        Parrot(const std::string& n) : name(n) {}
        void speak(std::ostream& os) const override {
            os << "name: " << name << "speak: " << "Hrrrrrr!\n";
        }
    };
};
