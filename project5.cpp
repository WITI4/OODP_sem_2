#include<iostream>
#include<string>
#include <fstream>
#include<vector>

class Vehicle {
	std::string vehicleType;
	int passengerCapacity;
	std::string licensePlate;
public:
	Vehicle() : Vehicle("", 0, "") {}
	Vehicle(const Vehicle& other) : vehicleType(other.vehicleType), passengerCapacity(other.passengerCapacity), licensePlate(other.licensePlate) {}
	Vehicle(const std::string vehicleType, int passengerCapacity, const std::string licensePlate) {
		this->vehicleType = vehicleType;
		this->passengerCapacity = passengerCapacity;
		this->licensePlate = licensePlate;
	}

	std::string GetVehicleType() const { return vehicleType; }
	int GetPassengerCapacity() const { return passengerCapacity; }
	std::string GetLicensePlate() const { return licensePlate; }

	void SetVehicleType(const std::string& vehicleType) { this->vehicleType = vehicleType; }
	void SetPassengerCapacity(int passengerCapacity) { this->passengerCapacity = passengerCapacity; }
	void SetLicensePlate(const std::string& licensePlate) { this->licensePlate = licensePlate; }

	virtual void PrintInfo(std::ostream& os) const = 0;

	virtual ~Vehicle() {
#ifdef DEBUG
		std::cout << "Деструктор Vehicle вызван" << endl;
#endif
	}
};
class Driver :public Vehicle {
	std::string fullName;
	int experienceYears;
	std::string licenseCategory;
	int age;
public:
	Driver() : Driver("", 0, "", 0) {}
	Driver(const Driver& other) : Vehicle(other), fullName(other.fullName), experienceYears(other.experienceYears), licenseCategory(other.licenseCategory), age(other.age) {}
	Driver(const std::string fullName, int experienceYears, const std::string licenseCategory, int age) : Vehicle() {
		this->fullName = fullName;
		this->experienceYears = experienceYears;
		this->licenseCategory = licenseCategory;
		this->age = age;
	}

	std::string GetFullName() const { return fullName; }
	int GetExperienceYears() const { return experienceYears; }
	std::string GetLicenseCategory() const { return licenseCategory; }
	int GetAge() const { return age; }

	void SetFullName(const std::string& fullName) { this->fullName = fullName; }
	void SetExperienceYears(int experienceYears) { this->experienceYears = experienceYears; }
	void SetLicenseCategory(const std::string& licenseCategory) { this->licenseCategory = licenseCategory; }
	void SetAge(int age) { this->age = age; }

	void PrintInfo(std::ostream& os) const override {
		os << "ФИО: " << fullName << "\n";
		os << "Стаж: " << experienceYears << " лет\n";
		os << "Категория прав: " << licenseCategory << "\n";
		os << "Возраст: " << age << "\n";
	}
	~Driver() override {
#ifdef DEBUG
		std::cout << "Деструктор Driver вызван" << endl;
#endif
	}
};
class Truck :public Vehicle {
	double maxLoadCapacity;
	bool hasTrailer;
public:
	Truck() : Truck("", 0, "", 0.0, 0) {}
	Truck(const Truck& other) : Vehicle(other), maxLoadCapacity(other.maxLoadCapacity), hasTrailer(other.hasTrailer) {
	}
	Truck(const std::string vehicleType, int passengerCapacity, const std::string licensePlate, double maxLoadCapacity, bool hasTrailer) : Vehicle(vehicleType, passengerCapacity, licensePlate) {
		this->maxLoadCapacity = maxLoadCapacity;
		this->hasTrailer = hasTrailer;
	}

	double GetMaxLoadCapacity() const { return maxLoadCapacity; }
	bool GetHasTrailer() const { return hasTrailer; }

	void SetMaxLoadCapacity(double maxLoadCapacity) { this->maxLoadCapacity = maxLoadCapacity; }
	void SetHasTrailer(bool hasTrailer) { this->hasTrailer = hasTrailer; }

	void PrintInfo(std::ostream& os) const override {
		os << "Тип: " << GetVehicleType() << "\n";
		os << "Вместимость: " << GetPassengerCapacity() << "\n";
		os << "Госномер: " << GetLicensePlate() << "\n";
		os << "Грузоподъемность: " << maxLoadCapacity << " кг\n";
		os << "Прицеп: " << (hasTrailer ? "Да" : "Нет") << "\n";
	}

	~Truck() override {
#ifdef DEBUG
		std::cout << "Деструктор Truck вызван" << endl;
#endif
	}
};
class Car :public Vehicle {
	std::string carClass;
	bool isElectric;
public:
	Car() : Car("", 0, "", "", 0) {}
	Car(const Car& other) : Vehicle(other), carClass(other.carClass), isElectric(other.isElectric) {}
	Car(const std::string vehicleType, int passengerCapacity, const std::string licensePlate, const std::string carClass, bool isElectric) : Vehicle(vehicleType, passengerCapacity, licensePlate) {
		this->carClass = carClass;
		this->isElectric = isElectric;
	}

	std::string GetCarClass() const { return carClass; }
	bool GetIsElectric() const { return isElectric; }

	void SetCarClass(const std::string& carClass) { this->carClass = carClass; }
	void SetIsElectric(bool isElectric) { this->isElectric = isElectric; }

	void PrintInfo(std::ostream& os) const override {
		os << "Тип: " << GetVehicleType() << "\n";
		os << "Вместимость: " << GetPassengerCapacity() << "\n";
		os << "Госномер: " << GetLicensePlate() << "\n";
		os << "Класс: " << carClass << "\n";
		os << "Электромобиль: " << (isElectric ? "Да" : "Нет") << "\n";
	}

	~Car() override {
#ifdef DEBUG
		std::cout << "Деструктор Car вызван" << endl;
#endif
	}
};
static void printToFile(const std::vector<Vehicle*>& fleet, const std::string& filename) {
	std::ofstream output(filename);
	if (!output) {
		std::cerr << "Не удалось открыть файл для записи\n";
		return;
	}

	for (int i = 0; i < fleet.size(); i++) {
		fleet[i]->PrintInfo(output);
		output << std::string(20, '-') << std::endl;
	}
	output.close();
}