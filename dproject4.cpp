#include<iostream>
#include<string>

class Animal {
    std::string name;
public:
    Animal() : name(""){}
    Animal(std::string& name) {
        this->name = name;
    }

    std::string GetName() const { return name; }

    virtual void speak(std::ostream& os, const Animal& name) const = 0;
};
class Dog :public Animal {
public:
    Dog(std::string& name) : Animal(name){}

    void speak(std::ostream& os, const Animal& name) const override {
        os << "name: " << name.GetName() << " speak: " << "Gav-gav!\n";
    }
};
class Cat :public Animal {
public:
    Cat(std::string& name) : Animal(name) {}

    void speak(std::ostream& os, const Animal& name) const override {
        os << "name: " << name.GetName() << "speak:" << "Meoooooow!\n";
    }
};
class Parrot :public Animal{
public:
    Parrot(std::string& name) : Animal(name) {}

    void speak(std::ostream& os, const Animal& name) const override {
        os << "name: " << name.GetName() << "speak:" << "Hrrrrrrr!\n";
    }
};