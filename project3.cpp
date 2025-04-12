#include "project3_header.h"
//#define DEBUG

// int String::count = 0;

String::String() : str("") {}
String::String(const String& other) : str(other.str) {}
String::String(std::string str) : str(str) {}

std::string String::GetStr() const { return str; }

void String::SetStr(const std::string& str) { this->str = str; }

bool String::operator!() const {
    return str.empty();
}

char String::operator[](int index) {
    return str[index];
}

std::string String::operator()(int iStart, int iEnd) const {
    return str.substr(iStart, iEnd - iStart + 1);
}

String::~String() {
#ifdef DEBUG
    std::cout << "Деструктор String вызван" << std::endl;
#endif
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    os << s.str;
    return os;
}

std::istream& operator>>(std::istream& is, String& s) {
    is >> s.str;
    return is;
}