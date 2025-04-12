#include<iostream>
#include<string>
#include <fstream>
#include<vector>

class Human {
	std::string fullName;
	int birthYear;
	std::string passportData;
public:
	Human() : Human("", 0, "") {}
	Human(const Human& other) : fullName(other.fullName), birthYear(other.birthYear), passportData(other.passportData) {}
	Human(const std::string fullName, int birthYear, const std::string passportData) {
		this->fullName = fullName;
		this->birthYear = birthYear;
		this->passportData = passportData;
	}

	std::string GetFullName() const { return fullName; }
	int GetBirthYear() const { return birthYear; }
	std::string GetPassportData() const { return passportData; }

	void SetFullName(const std::string& fullName) { this->fullName = fullName; }
	void SetBirthYear(const int& birthYear) { this->birthYear = birthYear; }
	void SetPassportData(const std::string& passportData) { this->passportData = passportData; }

	virtual void PrintInfo(std::ostream &os) const {
		os << "ФИО: " << fullName << "\n";
		os << "Год рождения: " << birthYear << "\n";
		os << "Паспортные данные: " << passportData << "\n";
	}
	virtual ~Human() {
#ifdef DEBUG
		std::cout << "Деструктор Human вызван" << endl;
#endif
	}
};
class Entrepreneur :public Human {
	std::string licenseNumber;
	std::string registrationAddress;
	std::string unn;
	std::string taxPayments;
public:
	Entrepreneur() : Entrepreneur("", 0, "", "", "", "", "") {}
	Entrepreneur(const Entrepreneur& other) : Human(other), licenseNumber(other.licenseNumber), registrationAddress(other.registrationAddress), unn(other.unn), taxPayments(other.taxPayments) {}
	Entrepreneur(const std::string& fullName, int birthYear, const std::string& passportData, const std::string& licenseNumber, const std::string& registrationAddress, const std::string& unn, const std::string& taxPayments) : Human(fullName, birthYear, passportData) {
		this->licenseNumber = licenseNumber;
		this->registrationAddress = registrationAddress;
		this->unn = unn;
		this->taxPayments = taxPayments;
	}

	std::string GetLicenseNumber() const { return licenseNumber; }
	std::string GetRegistrationAddress() const { return registrationAddress; }
	std::string GetUNN() const { return unn; }
	std::string GetTaxPayments() const { return taxPayments; }

	void SetLicenseNumber(const std::string& licenseNumber) { this->licenseNumber = licenseNumber; }
	void SetRegistrationAddress(const std::string& registrationAddress) { this->registrationAddress = registrationAddress; }
	void SetUNN(const std::string& unn) { this->unn = unn; }
	void SetTaxPayments(const std::string& taxPayments) { this->taxPayments = taxPayments; }

	void PrintInfo(std::ostream& os) const override {
		Human::PrintInfo(os);
		os << "Тип: Предприниматель\n";
		os << "Номер лицензии: " << licenseNumber << "\n";
		os << "Адрес регистрации: " << registrationAddress << "\n";
		os << "УНН: " << unn << "\n";
		os << "Данные о налоговых платежах: " << taxPayments << "\n";
	}
	~Entrepreneur() override {
#ifdef DEBUG
		std::cout << "Деструктор Entrepreneur вызван" << endl;
#endif
	}
};
class Tourist :public Human{
	std::string borderCrossingData;
public:
	Tourist() : Tourist("", 0, "", "") {}
	Tourist(const Tourist& other) : Human(other), borderCrossingData(other.borderCrossingData) {}
	Tourist(const std::string& fullName, int birthYear, const std::string& passportData, const std::string& borderCrossingData) : Human(fullName, birthYear, passportData) {
		this->borderCrossingData = borderCrossingData;
	}

	std::string GetBorderCrossingData() const { return borderCrossingData; }

	void SetBorderCrossingData(const std::string& borderCrossingData) { this->borderCrossingData = borderCrossingData; }

	void PrintInfo(std::ostream& os) const override {
		Human::PrintInfo(os);
		os << "Тип: Турист\n";
		os << "Данные о пересечении границы: " << borderCrossingData << "\n";
	}
	~Tourist() override {
#ifdef DEBUG
		std::cout << "Деструктор Tourist вызван" << endl;
#endif
	}
};
class Shuttle :public Human {
	std::string purchaseAddresses;
public:
	Shuttle() : Shuttle("", 0, "", "") {}
	Shuttle(const Shuttle& other) : Human(other), purchaseAddresses(other.purchaseAddresses) {}
	Shuttle(const std::string& fullName, int birthYear, const std::string& passportData, const std::string& purchaseAddresses) : Human(fullName, birthYear, passportData) {
		this->purchaseAddresses = purchaseAddresses;
	}

	std::string GetPurchaseAddresses() const { return purchaseAddresses; }

	void SetPurchaseAddresses(const std::string& purchaseAddresses) { this->purchaseAddresses = purchaseAddresses; }

	void PrintInfo(std::ostream& os) const override {
		Human::PrintInfo(os);
		os << "Тип: Челнок\n";
		os << "Список адресов покупки товара:\n";
	}
	~Shuttle() override {
#ifdef DEBUG
		std::cout << "Деструктор Shuttle вызван" << endl;
#endif
	}
};

static Human* findOldest(const std::vector<Human*>& people) {
	if (people.empty()) return nullptr;

	Human* oldest = people[0];
	for (int i = 1; i < people.size(); i++) {
		if (people[i]->GetBirthYear() < oldest->GetBirthYear()) {
			oldest = people[i];
		}
	}
	return oldest;
}

static void printToFile(const std::vector<Human*>& people, const std::string& filename) {
	std::ofstream output(filename);
	if (!output) {
		std::cerr << "Не удалось открыть файл для записи\n";
		return;
	}

	for (int i = 0; i < people.size(); i++) {
		people[i]->PrintInfo(output);
		output << std::string(20, '-') << std::endl;
	}
	output.close();
}
