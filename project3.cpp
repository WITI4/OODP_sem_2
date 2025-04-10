#include<iostream>
#include<string>
//#define DEBUG

class String {
private:
	std::string str;
	//static int count;
public:
	String() : str("") {}
	String(const String &other) : str(other.str) {}
	String(std::string str) {
		this->str = str;
		//count++;
	}

	std::string GetStr() const {
		return str;
	}
	void SetStr(const std::string &str) {
		this->str = str;
	}

	bool inline operator!() const;
	char inline operator[](int index);
	std::string inline operator()(int iStart, int iEnd) const;

	~String() {
#ifdef DEBUG
		cout << "Деструктор String вызван" << endl;
#endif
	}
	friend inline std::ostream& operator<<(std::ostream& os, const String& s);
	friend inline std::istream& operator>>(std::istream& is, String& s);

};

//int String::count = 0;

bool String::operator!() const {
	return str.empty();
}
char String::operator[](int index) {
	return str[index];
}
std::string String::operator()(int iStart, int iEnd) const {
	return str.substr(iStart, iEnd - iStart + 1);
}

std::ostream& operator<<(std::ostream& os, const String& s) {
	os << s.str;
	return os;
}
std::istream& operator>>(std::istream& is, String& s) {
	is >> s.str;
	return is;
}