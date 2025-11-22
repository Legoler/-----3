#include <iostream>
#include <string>
#include <vector>
using namespace std;
// Базовый класс - Средство передвижения
class Vehicle {
protected:
    string brand;
    int year;

public:
    Vehicle(const string& b, int y) : brand(b), year(y) {}

    virtual ~Vehicle() = default;

    virtual void displayInfo() const {
        cout << "Марка: " << brand << ", Год: " << year;
    }

    string getBrand() const { return brand; }
    int getYear() const { return year; }
};

// Класс Велосипед
class Bicycle : public Vehicle {
private:
    int gears;

public:
    Bicycle(const string& b, int y, int g)
        : Vehicle(b, y), gears(g) {}

    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << ", Тип: Велосипед, Передачи: " << gears;
    }
};

// Класс Автомобиль
class Car : public Vehicle {
private:
    string fuelType;

public:
    Car(const string& b, int y, const string& fuel)
        : Vehicle(b, y), fuelType(fuel) {}

    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << ", Тип: Автомобиль, Топливо: " << fuelType;
    }
};

// Класс Грузовик
class Truck : public Vehicle {
private:
    double cargoCapacity;

public:
    Truck(const string& b, int y, double capacity): Vehicle(b, y), cargoCapacity(capacity) {}

    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << ", Тип: Грузовик, Грузоподъемность: " << cargoCapacity << " т";
    }
};

// Шаблонный класс для хранения массива указателей
template<typename T>
class VehicleArray {
private:
    vector<T*> pointers;

public:
    // Конструкторы
    VehicleArray() = default;

    VehicleArray(initializer_list<T*> list) : pointers(list) {}

    // Деструктор
    ~VehicleArray() {
        for (auto ptr : pointers) {
            delete ptr;
        }
    }

    // Добавление указателя
    void add(T* ptr) {
        pointers.push_back(ptr);
    }

    // Получение размера массива
    size_t getSize() const {
        return pointers.size();
    }

    // Перегрузка оператора []
    T* operator[](size_t index) {
        if (index >= pointers.size()) {
            throw out_of_range("Индекс выходит за границы массива");
        }
        return pointers[index];
    }

    // Удаление элемента по индексу
    void remove(size_t index) {
        if (index < pointers.size()) {
            delete pointers[index];
            pointers.erase(pointers.begin() + index);
        }
    }

    // Вывод информации обо всех объектах
    void displayAll() const {
        for (size_t i = 0; i < pointers.size(); ++i) {
            cout << "[" << i << "] ";
            if (pointers[i]) {
                pointers[i]->displayInfo();
                cout << endl;
            }
            else {
                cout << "Пустой указатель" << endl;
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    // Создаем массив транспортных средств  
    VehicleArray<Vehicle> vehicles;

    // Добавляем разные типы транспортных средств  
    vehicles.add(new Bicycle("Gorny", 2020, 21));
    vehicles.add(new Car("Toyota Camry", 2019, "Gasoline"));
    vehicles.add(new Truck("Kamaz", 2018, 20));

    // Демонстрируем работу оператора []  
    for (int i = 0; i < vehicles.getSize(); ++i) {
        vehicles[i]->displayInfo();
        cout << endl;
    }

    return 0;
}