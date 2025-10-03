#include "../include/Binary.h"
#include <stdexcept>
#include <iostream>

Binary::Binary() {
    number = nullptr;
    size = 0;
}

Binary::Binary(const size_t& n, unsigned char t) {
    if (n <= 0) throw std::invalid_argument("Размер должен быть положительным");
    if (t != 0 && t != 1) throw std::invalid_argument("Некорректное значение");

    size = n;

    try {
        number = new unsigned char[size];
    } catch (const std::bad_alloc& e) {
        std::cout << "Ошибка выделения памяти" << std::endl;
    }

    for (size_t i = 0; i < size; i++) {
        number[i] = t;
    }
}

Binary::Binary(const std::initializer_list< unsigned char > &t) {
    size = t.size();

    try {
        number = new unsigned char[size];
    } catch (const std::bad_alloc& e) {
        std::cout << "Ошибка выделения памяти" << std::endl;
    }

    size_t i = size - 1;

    for(unsigned char value : t) {
        if (value != 1 && value != 0) {
            delete[] number;
            throw std::invalid_argument("Некорректное значение");
        }

        number[i--] = value;
    }
}

Binary::Binary(const std::string &t) {
    if (t.empty()) {
        throw std::invalid_argument("Пустая строка");
    }

    size = t.length();

    try {
        number = new unsigned char[size];
    } catch (const std::bad_alloc& e) {
        std::cout << "Ошибка выделения памяти" << std::endl;
    }

    size_t i = size - 1;

    for (char ch : t) {
        if (ch != '0' && ch != '1') {
            delete[] number;
            throw std::invalid_argument("Некорректное значение");
        }

        number[i--] = ch - '0';
    }
}

Binary::Binary(const Binary& other) {
    size = other.size;
        
    try {
        number = new unsigned char[size];
    } catch (const std::bad_alloc& e) {
        std::cout << "Ошибка выделения памяти" << std::endl;
    }

    for (size_t i = 0; i < size; i++) {
        number[i] = other.number[i];
    }
}

Binary::Binary(Binary&& other) noexcept {
    size = other.size;
    number = other.number;

    other.number = nullptr;
    other.size = 0;
}

Binary::~Binary() noexcept {
    delete[] number;
    number = nullptr;
}

bool Binary::equals(const Binary& other) const {
    size_t size1 = size;
    size_t size2 = other.size;

    while (size1 > 0 && number[size1 - 1] == 0) { // Исключаем ведущие 0
        size1 -= 1;
    }

    while (size2 > 0 && other.number[size2 - 1] == 0) { // Исключаем ведущие 0
        size2 -= 1;
    }

    if (size1 != size2) return false;

    for (int i = size1 - 1; 0 <= i; i--) {
        if (number[i] != other.number[i]) {
            return false;
        }
    }

    return true;
}

bool Binary::lessThan(const Binary& other) const {
    size_t size1 = size;
    size_t size2 = other.size;

    while (size1 > 0 && number[size1 - 1] == 0) { // Исключаем ведущие 0
        size1 -= 1;
    }

    while (size2 > 0 && other.number[size2 - 1] == 0) { // Исключаем ведущие 0
        size2 -= 1;
    }

    if (size1 > size2) return false;
    if (size1 < size2) return true;

    for (int i = size1 - 1; 0 <= i; i--) {
        if (number[i] > other.number[i]) {
            return false;
        }
        
        if (number[i] < other.number[i]) {
            return true;
        }
    }

    return false;
}

bool Binary::greaterThan(const Binary& other) const {
    return !lessThan(other) && !equals(other);
}

Binary Binary::add(const Binary& other) const {
    size_t max_size = std::max(size, other.size);

    Binary res(max_size + 1, 0);
    unsigned char carry = 0;

    for (size_t i = 0; i <= max_size; i++) {
        unsigned char bit1 = (i < size) ? number[i] : 0;
        unsigned char bit2 = (i < other.size) ? other.number[i] : 0;

        unsigned char sum = bit1 + bit2 + carry;
        res.number[i] = sum % 2;
        carry = sum / 2;
    }

    return res;
}

Binary Binary::subtract(const Binary& other) const {
    if (lessThan(other)) {
        throw std::invalid_argument("Может выйти отрицательное число");
    }

    Binary res(size, 0);
    unsigned char bor = 0;

    for (size_t i = 0; i < size; i++) {
        unsigned char bit1 = number[i];
        unsigned char bit2 = (i < other.size) ? other.number[i] : 0;

        int diff = bit1 - bit2 - bor;

        if (diff < 0) {
            diff += 2;
            bor = 1;
        } else {
            bor = 0;
        }

        res.number[i] = diff;
    }

    return res;
}

Binary Binary::copy() const {
    return Binary(*this);
}

void Binary::print() const {
    std::cout << size;
    for(size_t i = 0; i < size; i++) {
        std::cout << static_cast<int>(number[i]);
    }

    std::cout << std::endl;
}