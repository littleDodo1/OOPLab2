#ifndef BINARY_H
#define BINARY_H

#include <initializer_list>
#include <string>

class Binary {
    private:
        unsigned char* number;
        size_t size; 

    public:
        Binary();
        Binary(const size_t & n, unsigned char t = 0);
        Binary(const std::initializer_list< unsigned char > &t);
        Binary(const std::string &t);

        Binary(const Binary& other);
        Binary(Binary&& other) noexcept;
        virtual ~Binary() noexcept;

        Binary add(const Binary& other) const;
        Binary subtract(const Binary& other) const;
        Binary copy() const;

        bool equals(const Binary& other) const;
        bool lessThan(const Binary& other) const;
        bool greaterThan(const Binary& other) const;

        void print() const;
};

#endif