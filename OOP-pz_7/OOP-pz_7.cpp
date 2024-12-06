#include <iostream>
#include <Windows.h>
#include <stdexcept>
#include <string>

using namespace std;

class EmptyException {};

class ParameterException {
public:
    string message;
    ParameterException(const string& msg) : message(msg) {}
};

class DerivedException : public exception {
    string message;
public:
    DerivedException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

int TimeToSeconds(int hours, int minutes) {
    if (hours < 0 || minutes < 0 || minutes >= 60) {
        throw invalid_argument("Невірний формат");
    }
    return hours * 3600 + minutes * 60;
}

int TimeToSecondsThrow(int hours, int minutes) throw() {
    if (hours < 0 || minutes < 0 || minutes >= 60) {
        throw EmptyException();
    }
    return hours * 3600 + minutes * 60;
}

int TimeToSecondsWithStandardException(int hours, int minutes) throw(invalid_argument) {
    if (hours < 0 || minutes < 0 || minutes >= 60) {
        throw invalid_argument("Невірний формат");
    }
    return hours * 3600 + minutes * 60;
}

int TimeToSecondsWithCustomException(int hours, int minutes) throw(ParameterException) {
    if (hours < 0 || minutes < 0 || minutes >= 60) {
        throw ParameterException("Неправильний формат часу: " + to_string(hours) + " годин, " + to_string(minutes) + " хвилин");
    }
    return hours * 3600 + minutes * 60;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try {
        cout << "Час у секундах 1: " << TimeToSeconds(1, 30) << endl;
        cout << "Час у секундах 2: " << TimeToSecondsThrow(2, 61) << endl;
    }
    catch (const EmptyException&) {
        cerr << "Помилка!\n";
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }

    try {
        cout << "Час у секундах: " << TimeToSecondsWithStandardException(-3, 20) << endl;
    }
    catch (const invalid_argument& e) {
        cerr << "Звичайна помилка: " << e.what() << endl;
    }

    try {
        cout << "Час у секундах: " << TimeToSecondsWithCustomException(5, -10) << endl;
    }
    catch (const ParameterException& e) {
        cerr << "Помилка: " << e.message << endl;
    }
}
