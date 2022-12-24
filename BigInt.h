#ifndef BIG_INT_H
#define BIG_INT_H

#include <iostream>
#include <vector>
#include <string>

class BigInt {
public:
    BigInt();
    BigInt(long long number);
    BigInt(std::string string);
    static std::string convert_to_string(const BigInt& number);
    friend std::ostream& operator <<(std::ostream& ostream, const BigInt& number);
    friend bool operator >(const BigInt& first_number, const BigInt& second_number);
    friend bool operator >=(const BigInt& first_number, const BigInt& second_number);
    friend bool operator <(const BigInt& first_number, const BigInt& second_number);
    friend bool operator <=(const BigInt& first_number, const BigInt& second_number);
    friend bool operator ==(const BigInt& first_number, const BigInt& second_number);
    friend bool operator !=(const BigInt& first_number, const BigInt& second_number);
    friend BigInt operator +(const BigInt& first_number, const BigInt& second_number);
    friend BigInt operator -(const BigInt& first_number, const BigInt& second_number);
    friend BigInt operator *(const BigInt& first_number, const BigInt& second_number);
    friend BigInt operator /(const BigInt& first_number, const BigInt& second_number);
    friend BigInt operator %(const BigInt& first_number, const BigInt& second_number);
    BigInt& operator =(const std::string& string);
    BigInt& operator +=(const BigInt& number);
    BigInt operator ++();
    BigInt operator ++(int);
    BigInt& operator -=(const BigInt& number);
    BigInt operator --();
    BigInt operator --(int);
    BigInt& operator *=(const BigInt& number);
    BigInt& operator /=(const BigInt& number);
    BigInt& operator %=(const BigInt& number);
private:
    std::vector<int> numbers;
    bool sign;
    static const int base = 1000000000;
    static std::vector<int> string_convert_to_vector(const std::string& string);
    static BigInt remove_leading_zeros(BigInt& number);
    static BigInt shift_right(BigInt& number, int shift_power);
    static char compare(BigInt first_number, BigInt second_number);
    static BigInt subtraction(BigInt first_number, BigInt second_number);
    static BigInt sum(BigInt first_number, BigInt second_number);
    static BigInt multiplication(const BigInt& first_number, const BigInt& second_number);
    static BigInt whole_of_division(BigInt first_number, BigInt second_number);
    static BigInt remainder_of_division(BigInt first_number, BigInt second_number);
    static BigInt get_gcd(BigInt first_number, BigInt second_number);
};

#endif
