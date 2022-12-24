#include "BigInt.h"

std::vector<int> BigInt::string_convert_to_vector(const std::string& string) {
    std::vector<int> result;
    for (auto digit : string) result.push_back(digit - '0');
    return result;
}

std::string BigInt::convert_to_string(const BigInt& number) {
    std::string result;
    if (number.sign == false) result.append("-");
    result.reserve(number.numbers.size());
    char tmp;
    for (int i = 0; i < number.numbers.size(); i++) {
        tmp = number.numbers[i] + '0';
        result.push_back(tmp);
    }
    return result;
}

BigInt BigInt::remove_leading_zeros(BigInt& number) {
    while (number.numbers.size() != 1 && number.numbers[0] == 0)
        number.numbers.erase(number.numbers.begin() + 0);
    return number;
}

BigInt BigInt::shift_right(BigInt& number, int shift_power) {
    number.numbers.reserve(shift_power);
    for (int i = 0; i < shift_power; i++)
        number.numbers.insert(number.numbers.begin() + 0, 0);
    return number;
}

BigInt::BigInt() {
    numbers.resize(1);
    numbers[0] = 0;
    sign = true;
}

BigInt::BigInt(long long number) {
    sign = (number < 0 ? (number = number * (-1), sign = false) : sign = true);
    numbers = BigInt::string_convert_to_vector(std::to_string(number));
}

BigInt::BigInt(std::string string) {
    if (string.size() == 0 || (string.size() == 1 && string[0] == '-')) {
        throw "Error: String does not contain number";
    }
    if (string[0] == '-') {
        string.erase(string.begin() + 0);
        sign = false;
    }
    else sign = true;

    for (int i = 0; i < string.size(); i++) {
        if (string[i] < 48 || string[i] > 57) {
            throw "Error: String contain unknown characters";
        }
    }
    while (string.size() != 1 && string[0] == '0') {
        string.erase(string.begin() + 0);
    }
    numbers = BigInt::string_convert_to_vector(string);
}

char BigInt::compare(BigInt first_number, BigInt second_number) {
    if (first_number.sign == true && second_number.sign == false)
        return '>';
    if (first_number.sign == false && second_number.sign == true)
        return '<';
    if (first_number.sign == false && second_number.sign == false) {
        first_number.sign = true;
        second_number.sign = true;
        char tmp = BigInt::compare(first_number, second_number);
        if (tmp == '>') return '<';
        if (tmp == '<') return '>';
        return '=';
    }

    if (first_number.numbers.size() > second_number.numbers.size())
        return '>';
    if (first_number.numbers.size() < second_number.numbers.size())
        return '<';
    for (int pos = 0; pos < first_number.numbers.size(); pos++) {
        if (first_number.numbers[pos] > second_number.numbers[pos])
            return '>';
        if (first_number.numbers[pos] < second_number.numbers[pos])
            return '<';
    }
    return '=';
}

BigInt BigInt::subtraction(BigInt first_number, BigInt second_number) {
    if (first_number.sign == true && second_number.sign == false) {
        second_number.sign = true;
        return first_number + second_number;
    }
    if (first_number.sign == false && second_number.sign == true) {
        first_number.sign = true;
        BigInt tmp = first_number + second_number;
        tmp.sign = false;
        return tmp;
    }
    if (first_number.sign == false && second_number.sign == false) {
        first_number.sign = true;
        second_number.sign = true;
        BigInt tmp;
        tmp = first_number;
        first_number = second_number;
        second_number = tmp;
    }
    if (first_number < second_number) {
        BigInt tmp = first_number;
        first_number = second_number;
        second_number = tmp;
        first_number.sign = false;
    }
    second_number = BigInt::shift_right(second_number, first_number.numbers.size() - second_number.numbers.size());

    int difference = 0;
    for (long long indexes_of_first = first_number.numbers.size() - 1; indexes_of_first >= 0; indexes_of_first--) {
        difference = first_number.numbers[indexes_of_first] - second_number.numbers[indexes_of_first];
        if (difference >= 0) {
            first_number.numbers[indexes_of_first] = difference;
            continue;
        }
        first_number.numbers[indexes_of_first] = difference + 10;
        for (int pos = indexes_of_first - 1; ; pos--) {
            if (first_number.numbers[pos] == 0)
                first_number.numbers[pos] = 9;
            else {
                first_number.numbers[pos]--;
                break;
            }
        }
    }
    return remove_leading_zeros(first_number);
}

BigInt BigInt::sum(BigInt first_number, BigInt second_number) {
    if (first_number.sign == true && second_number.sign == false) {
        second_number.sign = true;
        return first_number - second_number;
    }
    if (second_number.sign == true && first_number.sign == false) {
        first_number.sign = true;
        return second_number - first_number;
    }
    if (first_number.sign == false && second_number.sign == false)
        second_number.sign = true;
    if (first_number.numbers.size() > second_number.numbers.size())
        second_number = BigInt::shift_right(second_number, first_number.numbers.size() - second_number.numbers.size());
    else
        first_number = BigInt::shift_right(first_number, second_number.numbers.size() - first_number.numbers.size());

    int sum = 0;
    int carry = 0;
    for (int numbers_position = first_number.numbers.size() - 1; numbers_position >= 0; numbers_position--) {
        sum = first_number.numbers[numbers_position] + second_number.numbers[numbers_position] + carry;
        carry = sum / 10;
        first_number.numbers[numbers_position] = sum % 10;
    }
    if (carry != 0) first_number.numbers.insert(first_number.numbers.begin() + 0, carry);
    return first_number;
}

BigInt BigInt::multiplication(const BigInt& first_number, const BigInt& second_number) {
    if (first_number == 0 || second_number == 0) return 0;
    BigInt result;
    result.numbers.resize(first_number.numbers.size() + second_number.numbers.size());
    int comp = 0;
    for (int index_of_first = first_number.numbers.size() - 1; index_of_first >= 0; --index_of_first) {
        for (int index_of_second = second_number.numbers.size() - 1; index_of_second >= 0; --index_of_second) {
            comp = first_number.numbers[index_of_first] * second_number.numbers[index_of_second];
            result.numbers[index_of_first + index_of_second + 1] = result.numbers[index_of_first + index_of_second + 1] + comp;
        }
    }
    int extra = 0;
    for (int index_of_result = result.numbers.size() - 1; index_of_result >= 0; --index_of_result) {
        extra = result.numbers[index_of_result] / 10;
        result.numbers[index_of_result] = result.numbers[index_of_result] - (extra * 10);
        result.numbers[index_of_result - 1] = result.numbers[index_of_result - 1] + extra;
    }
    result.sign = (first_number.sign == second_number.sign);
    return remove_leading_zeros(result);
}

BigInt BigInt::whole_of_division(BigInt first_number, BigInt second_number) {
    if (second_number == 0) {
        throw "Error: Division by zero is not possible";
    }

    BigInt result;
    result.sign = (first_number.sign == second_number.sign);
    BigInt part_of_first;
    first_number.sign = true;
    second_number.sign = true;
    if (first_number < second_number) return 0;

    result.numbers.resize(0);
    part_of_first.numbers.resize(0);
    BigInt tmp;

    for (long long index_of_first = 0; index_of_first < first_number.numbers.size(); index_of_first++) {
        part_of_first.numbers.push_back(first_number.numbers[index_of_first]);
        int quotient = 0, left = 0, middle = 0, right = BigInt::base;
        while (left <= right) {
            middle = (left + right) / 2;
            tmp = second_number * middle;
            if (tmp <= part_of_first) {
                quotient = middle;
                left = middle + 1;
            }
            else right = middle - 1;
        }
        part_of_first = part_of_first - (second_number * quotient);
        if (!result.numbers.empty() || quotient != 0) result.numbers.push_back(quotient);
        if (part_of_first == 0) part_of_first.numbers.resize(0);
    }
    return result;
}

BigInt BigInt::remainder_of_division(BigInt first_number, BigInt second_number) {
    if (second_number == 0) {
        throw "Error: Division by zero is not possible";
    }
    BigInt part_of_first;
    first_number.sign = true;
    second_number.sign = true;
    if (first_number < second_number) return first_number;
    part_of_first.numbers.resize(0);
    BigInt tmp;

    for (long long index_of_first = 0; index_of_first < first_number.numbers.size(); index_of_first++) {
        part_of_first.numbers.push_back(first_number.numbers[index_of_first]);
        int quotient = 0, left = 0, middle = 0, right = BigInt::base;
        while (left <= right) {
            middle = (left + right) / 2;
            tmp = second_number * middle;
            if (tmp <= part_of_first) {
                quotient = middle;
                left = middle + 1;
            }
            else right = middle - 1;
        }
        part_of_first = part_of_first - (second_number * quotient);
        if (part_of_first == 0) part_of_first.numbers.resize(0);
    }
    if (part_of_first.numbers.empty()) return 0;
    return part_of_first;
}

BigInt BigInt::get_gcd(BigInt first_number, BigInt second_number) {
    if (first_number == 0 and second_number == 0) {
        throw "Error : Counting the greatest common divisor is not possible. Both numbers are zero.";
    }
    first_number.sign = true;
    second_number.sign = true;
    if (first_number == 0) return second_number;
    if (second_number == 0) return first_number;
    while (first_number != 0 and second_number != 0) {
        if (first_number > second_number) first_number = first_number % second_number;
        else second_number = second_number % first_number;
    }
    return first_number + second_number;
}

std::ostream& operator <<(std::ostream& ostream, const BigInt& number) {
    std::string string = BigInt::convert_to_string(number);
    for (int i = 0; i < number.numbers.size(); i++)  ostream.put(string[i]);
    return ostream;
}

bool operator >(const BigInt& first_number, const BigInt& second_number) {
    return (BigInt::compare(first_number, second_number) == '>' ? true : false);
}
bool operator >=(const BigInt& first_number, const BigInt& second_number) {
    return (BigInt::compare(first_number, second_number) != '<' ? true : false);
}
bool operator <(const BigInt& first_number, const BigInt& second_number) {
    return (BigInt::compare(first_number, second_number) == '<' ? true : false);
}
bool operator <=(const BigInt& first_number, const BigInt& second_number) {
    return (BigInt::compare(first_number, second_number) != '>' ? true : false);
}
bool operator ==(const BigInt& first_number, const BigInt& second_number) {
    return (BigInt::compare(first_number, second_number) == '=' ? true : false);
}
bool operator !=(const BigInt& first_number, const BigInt& second_number) {
    return (BigInt::compare(first_number, second_number) != '=' ? true : false);
}

BigInt operator +(const BigInt& first_number, const BigInt& second_number) {
    return BigInt::sum(first_number, second_number);
}
BigInt operator -(const BigInt& first_number, const BigInt& second_number) {
    return BigInt::subtraction(first_number, second_number);
}
BigInt operator *(const BigInt& first_number, const BigInt& second_number) {
    return BigInt::multiplication(first_number, second_number);
}
BigInt operator /(const BigInt& first_number, const BigInt& second_number) {
    return BigInt::whole_of_division(first_number, second_number);
}
BigInt operator %(const BigInt& first_number, const BigInt& second_number) {
    return BigInt::remainder_of_division(first_number, second_number);
}

BigInt& BigInt::operator =(const std::string& string) {
    BigInt tmp(string);
    numbers = tmp.numbers;
    sign = tmp.sign;
    return *this;
}
BigInt& BigInt::operator +=(const BigInt& number) {
    return *this = *this + number;
}
BigInt BigInt::operator ++() {
    return *this = *this + 1;
}
BigInt BigInt::operator ++(int) {
    *this = *this + 1;
    return *this = (*this - 1);
}
BigInt& BigInt::operator -=(const BigInt& number) {
    return *this = *this - number;
}
BigInt BigInt::operator --() {
    return *this = (*this - 1);
}
BigInt BigInt::operator --(int) {
    *this = *this - 1;
    return *this = *this + 1;
}
BigInt& BigInt::operator *=(const BigInt& number) {
    return *this = *this * number;
}
BigInt& BigInt::operator /=(const BigInt& number) {
    return *this = *this / number;
}
BigInt& BigInt::operator %=(const BigInt& number) {
    return *this = *this % number;
}
