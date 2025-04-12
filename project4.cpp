#include "project4_header.h"
//#define DEBUG

Human::Human() : Human("", 0, "") {}
Human::Human(const Human& other) : fullName(other.fullName), birthYear(other.birthYear), passportData(other.passportData) {}
Human::Human(const std::string fullName, int birthYear, const std::string passportData) :
    fullName(fullName),
    birthYear(birthYear),
    passportData(passportData) {
}

Human::~Human() {
#ifdef DEBUG
    std::cout << "���������� Human ������" << std::endl;
#endif
}

std::string Human::GetFullName() const { return fullName; }
int Human::GetBirthYear() const { return birthYear; }
std::string Human::GetPassportData() const { return passportData; }

void Human::SetFullName(const std::string& fullName) { this->fullName = fullName; }
void Human::SetBirthYear(const int& birthYear) { this->birthYear = birthYear; }
void Human::SetPassportData(const std::string& passportData) { this->passportData = passportData; }

void Human::PrintInfo(std::ostream& os) const {
    os << "���: " << fullName << "\n";
    os << "��� ��������: " << birthYear << "\n";
    os << "���������� ������: " << passportData << "\n";
}

Entrepreneur::Entrepreneur() : Entrepreneur("", 0, "", "", "", "", "") {}
Entrepreneur::Entrepreneur(const Entrepreneur& other) : Human(other), licenseNumber(other.licenseNumber), registrationAddress(other.registrationAddress), unn(other.unn), taxPayments(other.taxPayments) {}
Entrepreneur::Entrepreneur(const std::string& fullName, int birthYear, const std::string& passportData, const std::string& licenseNumber, const std::string& registrationAddress, const std::string& unn, const std::string& taxPayments) : Human(fullName, birthYear, passportData), licenseNumber(licenseNumber), registrationAddress(registrationAddress), unn(unn), taxPayments(taxPayments) {}

Entrepreneur::~Entrepreneur() {
#ifdef DEBUG
    std::cout << "���������� Entrepreneur ������" << std::endl;
#endif
}

std::string Entrepreneur::GetLicenseNumber() const { return licenseNumber; }
std::string Entrepreneur::GetRegistrationAddress() const { return registrationAddress; }
std::string Entrepreneur::GetUNN() const { return unn; }
std::string Entrepreneur::GetTaxPayments() const { return taxPayments; }

void Entrepreneur::SetLicenseNumber(const std::string& licenseNumber) { this->licenseNumber = licenseNumber; }
void Entrepreneur::SetRegistrationAddress(const std::string& registrationAddress) { this->registrationAddress = registrationAddress; }
void Entrepreneur::SetUNN(const std::string& unn) { this->unn = unn; }
void Entrepreneur::SetTaxPayments(const std::string& taxPayments) { this->taxPayments = taxPayments; }

void Entrepreneur::PrintInfo(std::ostream& os) const {
    Human::PrintInfo(os);
    os << "���: ���������������\n";
    os << "����� ��������: " << licenseNumber << "\n";
    os << "����� �����������: " << registrationAddress << "\n";
    os << "���: " << unn << "\n";
    os << "������ � ��������� ��������: " << taxPayments << "\n";
}

Tourist::Tourist() : Tourist("", 0, "", "") {}
Tourist::Tourist(const Tourist& other) : Human(other), borderCrossingData(other.borderCrossingData) {}
Tourist::Tourist(const std::string& fullName, int birthYear, const std::string& passportData, const std::string& borderCrossingData) : Human(fullName, birthYear, passportData), borderCrossingData(borderCrossingData) {}

Tourist::~Tourist() {
#ifdef DEBUG
    std::cout << "���������� Tourist ������" << std::endl;
#endif
}

std::string Tourist::GetBorderCrossingData() const { return borderCrossingData; }
void Tourist::SetBorderCrossingData(const std::string& borderCrossingData) { this->borderCrossingData = borderCrossingData; }

void Tourist::PrintInfo(std::ostream& os) const {
    Human::PrintInfo(os);
    os << "���: ������\n";
    os << "������ � ����������� �������: " << borderCrossingData << "\n";
}

Shuttle::Shuttle() : Shuttle("", 0, "", "") {}
Shuttle::Shuttle(const Shuttle& other) : Human(other), purchaseAddresses(other.purchaseAddresses) {}
Shuttle::Shuttle(const std::string& fullName, int birthYear, const std::string& passportData, const std::string& purchaseAddresses) : Human(fullName, birthYear, passportData), purchaseAddresses(purchaseAddresses) {}

Shuttle::~Shuttle() {
#ifdef DEBUG
    std::cout << "���������� Shuttle ������" << std::endl;
#endif
}

std::string Shuttle::GetPurchaseAddresses() const { return purchaseAddresses; }
void Shuttle::SetPurchaseAddresses(const std::string& purchaseAddresses) { this->purchaseAddresses = purchaseAddresses; }

void Shuttle::PrintInfo(std::ostream& os) const {
    Human::PrintInfo(os);
    os << "���: ������\n";
    os << "������ ������� ������� ������: " << purchaseAddresses << "\n";
}

Human* findOldest(const std::vector<Human*>& people) {
    if (people.empty()) return nullptr;

    Human* oldest = people[0];
    for (size_t i = 1; i < people.size(); i++) {
        if (people[i]->GetBirthYear() < oldest->GetBirthYear()) {
            oldest = people[i];
        }
    }
    return oldest;
}

void printToFile(const std::vector<Human*>& people, const std::string& filename) {
    std::ofstream output(filename);
    if (!output) {
        std::cerr << "�� ������� ������� ���� ��� ������\n";
        return;
    }

    for (size_t i = 0; i < people.size(); i++) {
        people[i]->PrintInfo(output);
        output << std::string(20, '-') << std::endl;
    }
    output.close();
}