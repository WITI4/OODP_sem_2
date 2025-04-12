#pragma once
#include <iostream>
#include <string>

class String {
private:
    std::string str;
    //static int count;

public:
    String();
    String(const String& other);
    String(std::string str);

    std::string GetStr() const;
    void SetStr(const std::string& str);

    bool operator!() const;
    char operator[](int index);
    std::string operator()(int iStart, int iEnd) const;

    ~String();

    friend std::ostream& operator<<(std::ostream& os, const String& s);
    friend std::istream& operator>>(std::istream& is, String& s);
};

// extern int String::count;