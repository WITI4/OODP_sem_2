#include <iostream>
#include <string>
#include <vector>

static void customTerminate() {
    std::cerr << "Вызвана пользовательская функция завершения. Необработанное исключение!" << std::endl;
    std::abort();
}

class HardwareException : public std::runtime_error {
public:
    HardwareException(const std::string& msg) : std::runtime_error(msg) {}
};

class Component {
protected:
    std::string model;
    std::string manufacturer;
    double price;
public:
    Component() : Component("", "", 0.0) {}
    Component(const Component& other) : model(other.model), manufacturer(other.manufacturer), price(other.price) {}
    Component(const std::string& model, const std::string& manufacturer, double price) {
        this->model = model;
        this->manufacturer = manufacturer;
        this->price = price;
    }

    virtual ~Component() {
        std::cout << "Уничтожен компонент: " << model << std::endl;
    }

    std::string GetModel() const { return model; }
    std::string GetManufacturer() const { return manufacturer; }
    constexpr double GetPrice() const { return price; }

    void SetModel(const std::string& model) { this->model = model; }
    void SetManufacturer(const std::string& manufacturer) { this->manufacturer = manufacturer; }
    void SetPrice(double price) {
        if (price < 0) throw HardwareException("Отрицательная цена компонента");
        this->price = price;
    }

    virtual void printInfo(std::ostream& os) const = 0;
    virtual void printInfo() const = 0;
};

class CPUException : public HardwareException {
public:
    CPUException(const std::string& msg) : HardwareException(msg) {}
};

class CPU : public Component {
    int cores;
    double clockSpeed;
public:
    CPU() : CPU("", "", 0.0, 0, 0.0) {}
    CPU(const CPU& other) : Component(other), cores(other.cores), clockSpeed(other.clockSpeed) {}
    CPU(const std::string& m, const std::string& manuf, double p, int c, double cs) : Component(m, manuf, p), cores(c), clockSpeed(cs) {}

    ~CPU() override {
        std::cout << "Уничтожен процессор: " << model << std::endl;
    }

    int GetCores() const { return cores; }
    double GetClockSpeed() const { return clockSpeed; }

    void SetCores(int c) {
        if (c <= 0) throw CPUException("Неверное количество ядер");
        cores = c;
    }
    void SetClockSpeed(double cs) {
        if (cs <= 0) throw CPUException("Неверная тактовая частота");
        clockSpeed = cs;
    }

    void printInfo(std::ostream& os) const override {
        os << "Процессор " << manufacturer << " " << model
            << ", ядер: " << cores << ", частота: " << clockSpeed << " GHz";
    }

    void printInfo() const override {
        printInfo(std::cout);
        std::cout << std::endl;
    }
};

class MemoryException : public HardwareException {
public:
    MemoryException(const std::string& msg) : HardwareException(msg) {}
};

class Memory : public Component {
    int sizeGB;
    std::string type;
public:
    Memory() : Memory("", "", 0.0, 0, "") {}
    Memory(const Memory& other) : Component(other), sizeGB(other.sizeGB), type(other.type) {}
    Memory(const std::string& m, const std::string& manuf, double p, int s, const std::string& t) : Component(m, manuf, p), sizeGB(s), type(t) {}

    ~Memory() override {
        std::cout << "Уничтожена память: " << model << std::endl;
    }

    int GetSizeGB() const { return sizeGB; }
    std::string GetType() const { return type; }

    void SetSizeGB(int s) {
        if (s <= 0) throw MemoryException("Неверный объем памяти");
        sizeGB = s;
    }
    void SetType(const std::string& t) { type = t; }

    void printInfo(std::ostream& os) const override {
        os << "Память " << manufacturer << " " << model
            << ", размер: " << sizeGB << "GB, тип: " << type;
    }

    void printInfo() const override {
        printInfo(std::cout);
        std::cout << std::endl;
    }
};

class StorageException : public HardwareException {
public:
    StorageException(const std::string& msg) : HardwareException(msg) {}
};

class Storage : public Component {
    int capacityGB;
    bool isSSD;
public:
    Storage() : Storage("", "", 0.0, 0, false) {}
    Storage(const Storage& other) : Component(other), capacityGB(other.capacityGB), isSSD(other.isSSD) {}
    Storage(const std::string& m, const std::string& manuf, double p, int c, bool ssd) : Component(m, manuf, p), capacityGB(c), isSSD(ssd) {}

    ~Storage() override {
        std::cout << "Уничтожено хранилище: " << model << std::endl;
    }

    int GetCapacityGB() const { return capacityGB; }
    bool IsSSD() const { return isSSD; }

    void SetCapacityGB(int c) {
        if (c <= 0) throw StorageException("Неверная емкость хранилища");
        capacityGB = c;
    }
    void SetIsSSD(bool ssd) { isSSD = ssd; }

    void printInfo(std::ostream& os) const override {
        os << "Хранилище " << manufacturer << " " << model
            << ", емкость: " << capacityGB << "GB, тип: " << (isSSD ? "SSD" : "HDD");
    }

    void printInfo() const override {
        printInfo(std::cout);
        std::cout << std::endl;
    }
};

class GPUException : public HardwareException {
public:
    GPUException(const std::string& msg) : HardwareException(msg) {}
};

class GPU : public Component {
    int vramGB;
public:
    GPU() : GPU("", "", 0.0, 0) {}
    GPU(const GPU& other) : Component(other), vramGB(other.vramGB) {}
    GPU(const std::string& m, const std::string& manuf, double p, int vram) : Component(m, manuf, p), vramGB(vram) {}

    ~GPU() override {
        std::cout << "Уничтожена видеокарта: " << model << std::endl;
    }

    int GetVRAMGB() const { return vramGB; }

    void SetVRAMGB(int vram) {
        if (vram <= 0) throw GPUException("Неверный объем видеопамяти");
        vramGB = vram;
    }

    void printInfo(std::ostream& os) const override {
        os << "Видеокарта " << manufacturer << " " << model
            << ", видеопамять: " << vramGB << "GB";
    }

    void printInfo() const override {
        printInfo(std::cout);
        std::cout << std::endl;
    }
};

class MotherboardException : public HardwareException {
public:
    MotherboardException(const std::string& msg) : HardwareException(msg) {}
};

class Motherboard : public Component {
    std::string socket;
    int ramSlots;
    std::vector<Component*> components;
public:
    Motherboard() : Motherboard("", "", 0.0, "", 0) {}
    Motherboard(const Motherboard& other) : Component(other), socket(other.socket), ramSlots(other.ramSlots) {
        for (auto c : other.components) {
            if (auto cpu = dynamic_cast<CPU*>(c)) {
                components.push_back(new CPU(*cpu));
            }
            else if (auto mem = dynamic_cast<Memory*>(c)) {
                components.push_back(new Memory(*mem));
            }
            else if (auto storage = dynamic_cast<Storage*>(c)) {
                components.push_back(new Storage(*storage));
            }
            else if (auto gpu = dynamic_cast<GPU*>(c)) {
                components.push_back(new GPU(*gpu));
            }
        }
    }
    Motherboard(const std::string& m, const std::string& manuf, double p, const std::string& s, int rs) : Component(m, manuf, p), socket(s), ramSlots(rs) {}

    ~Motherboard() override {
        for (auto c : components) {
            delete c;
        }
        std::cout << "Уничтожена материнская плата: " << model << std::endl;
    }

    std::string GetSocket() const { return socket; }
    int GetRamSlots() const { return ramSlots; }
    const std::vector<Component*>& GetComponents() const { return components; }

    void SetSocket(const std::string& s) { socket = s; }
    void SetRamSlots(int rs) {
        if (rs <= 0) throw MotherboardException("Неверное количество слотов памяти");
        ramSlots = rs;
    }

    void addComponent(Component* c) {
        components.push_back(c);
    }

    void printInfo(std::ostream& os) const override {
        os << "Материнская плата " << manufacturer << " " << model
            << ", сокет: " << socket << ", слотов памяти: " << ramSlots;
    }

    void printInfo() const override {
        printInfo(std::cout);
        std::cout << std::endl;
        std::cout << "Установленные компоненты:" << std::endl;
        for (const auto& c : components) {
            c->printInfo();
        }
    }

    double getTotalPrice() const {
        double total = price;
        for (const auto& c : components) {
            total += c->GetPrice();
        }
        return total;
    }
};

class Computer {
    std::string name;
    std::vector<Component*> components;
public:
    Computer() : Computer("") {}
    Computer(const Computer& other) : name(other.name) {
        for (auto c : other.components) {
            if (auto cpu = dynamic_cast<CPU*>(c)) {
                components.push_back(new CPU(*cpu));
            }
            else if (auto mem = dynamic_cast<Memory*>(c)) {
                components.push_back(new Memory(*mem));
            }
            else if (auto storage = dynamic_cast<Storage*>(c)) {
                components.push_back(new Storage(*storage));
            }
            else if (auto gpu = dynamic_cast<GPU*>(c)) {
                components.push_back(new GPU(*gpu));
            }
            else if (auto mb = dynamic_cast<Motherboard*>(c)) {
                components.push_back(new Motherboard(*mb));
            }
        }
    }
    Computer(const std::string& n) : name(n) {}

    ~Computer() {
        std::cout << "Компьютер " << name << " разобран" << std::endl;
    }

    std::string GetName() const { return name; }
    const std::vector<Component*>& GetComponents() const { return components; }

    void SetName(const std::string& n) { name = n; }

    void addComponent(Component* c) {
        components.push_back(c);
    }

    void printConfiguration() const {
        std::cout << "Конфигурация компьютера " << name << ":" << std::endl;
        for (const auto& c : components) {
            c->printInfo();
        }
    }

    double getTotalPrice() const {
        double total = 0;
        for (const auto& c : components) {
            total += c->GetPrice();
        }
        return total;
    }
};

static void demonstrateNewException() {
    try {
        long long hugeSize = std::numeric_limits<long long>::max();
        int* hugeArray = new int[hugeSize];
        delete[] hugeArray;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Ошибка выделения памяти: " << e.what() << std::endl;
        throw;
    }
}

//ifstream fin;
////для файлов
//fin.exceptions(ifstream::badbit | ifstream::failbit);
//
//try
//{
//    std::cout << "Попытка открыть файл\n";
//    fin.open();
//    std::cout << "файл открыт!\n";
//}
//catch (const std::exception& ex)
//{
//    std::cout << ex.what();
//    std::cout << "Ошибка открытия файла\n";
//}