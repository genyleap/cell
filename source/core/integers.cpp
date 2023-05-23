#if __has_include("integers.hpp")
#   include "integers.hpp"
#else
#   error "Cell's "integers.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Types)

BigNumber::BigNumber(){
}

BigNumber::BigNumber(const std::string& number)
{
    digits.reserve(number.length());
    std::transform(number.rbegin(),
                   number.rend(),
                   std::back_inserter(digits), [](char c)
                   {
                       return c - '0';
                   });
}

BigNumber::BigNumber(long long int number)
{
    while (number > 0) {
        digits.push_back(number % 10);
        number /= 10;
    }
}

OptionalString BigNumber::toString() const
{
    std::string result;
    result.reserve(digits.size());

    if (digits.empty()) {
        result = "0";
    } else {
        if (digits.back() < 0) {
            result.push_back('-');
        }

        std::transform(digits.rbegin(),
                       digits.rend(),
                       std::back_inserter(result),
                       [](int digit) {
                           return std::abs(digit) + '0';
                       });
    }

    return result;
}

BigNumber BigNumber::operator+(const BigNumber& other) const
{
    BigNumber result;
    std::vector<long long int> temp(std::max(digits.size(), other.digits.size()) + 1, 0);

    size_t i = 0;
    int carry = 0;

    while (i < digits.size() || i < other.digits.size() || carry != 0)
    {
        long long int sum = carry;
        if (i < digits.size())
            sum += digits[i];
        if (i < other.digits.size())
            sum += other.digits[i];

        temp[i] = sum % 10;
        carry = sum / 10;

        i++;
    }

    while (!temp.empty() && temp.back() == 0) {
        temp.pop_back();
    }

    result.digits = std::move(temp);
    return result;
}

BigNumber BigNumber::operator-(const BigNumber& other) const
{
    BigNumber result;
    std::vector<long long int> temp(std::max(digits.size(), other.digits.size()), 0);

    size_t i = 0;
    int carry = 0;

    while (i < digits.size()) {
        long long int diff = digits[i] - carry;
        if (i < other.digits.size())
            diff -= other.digits[i];

        if (diff < 0) {
            diff += 10;
            carry = 1;
        } else {
            carry = 0;
        }

        temp[i] = diff;

        i++;
    }

    while (!temp.empty() && temp.back() == 0)
    {
        temp.pop_back();
    }

    result.digits = std::move(temp);
    return result;
}

BigNumber BigNumber::operator*(const BigNumber& other) const
{
    BigNumber result;
    std::vector<long long int> temp(digits.size() + other.digits.size(), 0);

    for (size_t i = 0; i < digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < other.digits.size() || carry != 0; ++j) {
            long long int product = temp[i + j] + digits[i] * (j < other.digits.size() ? other.digits[j] : 0) + carry;
            temp[i + j] = product % 10;
            carry = product / 10;
        }
    }

    while (!temp.empty() && temp.back() == 0) {
        temp.pop_back();
    }

    result.digits = std::move(temp);
    return result;
}


bool BigNumber::operator==(const BigNumber& other) const
{
    return digits == other.digits;
}

bool BigNumber::operator!=(const BigNumber& other) const
{
    return !(*this == other);
}

bool BigNumber::operator<(const BigNumber& other) const
{
    if (digits.size() < other.digits.size())
        return true;
    if (digits.size() > other.digits.size())
        return false;

    for (size_t i = digits.size(); i > 0; --i) {
        if (digits[i - 1] < other.digits[i - 1])
            return true;
        if (digits[i - 1] > other.digits[i - 1])
            return false;
    }

    return false;
}

bool BigNumber::operator<=(const BigNumber& other) const
{
    return (*this < other) || (*this == other);
}

bool BigNumber::operator>(const BigNumber& other) const
{
    return !(*this <= other);
}

bool BigNumber::operator>=(const BigNumber& other) const
{
    return !(*this < other);
}

BigNumber BigNumber::operator-() const {
    BigNumber negated = *this;
    if (!negated.digits.empty()) {
        negated.digits.back() = -negated.digits.back();
    }
    return negated;
}

BigNumber& BigNumber::operator+=(const BigNumber& other)
{
    *this = *this + other;
    return *this;
}

BigNumber& BigNumber::operator-=(const BigNumber& other)
{
    *this = *this - other;
    return *this;
}

BigNumber& BigNumber::operator*=(const BigNumber& other)
{
    *this = *this * other;
    return *this;
}

BigNumber64::BigNumber64()
{
}

BigNumber64::BigNumber64(const std::string& number)
{
    digits.reserve(number.length());
    std::transform(number.rbegin(), number.rend(), std::back_inserter(digits), [](char c) { return c - '0'; });
}

BigNumber64::BigNumber64(u64 number)
{
    while (number > 0) {
        digits.push_back(number % 10);
        number /= 10;
    }
}

OptionalString BigNumber64::toString() const
{
    std::string result;

    if (digits.empty()) {
        result = "0";
    } else {
        result.reserve(digits.size());

        // Convert each digit to a character and append it to the result string
        for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
            char digitChar = static_cast<char>(*it + '0');
            result.push_back(digitChar);
        }
    }

    // Remove leading zeros
    result.erase(0, result.find_first_not_of('0'));

    return result;
}

BigNumber64 BigNumber64::operator+(const BigNumber64& other) const
{
    BigNumber64 result;
    std::vector<u64> temp(digits.size() + other.digits.size(), 0);
    temp.reserve(digits.size() + other.digits.size());

    u64 carry = 0;
    for (size_t i = 0; i < digits.size() || i < other.digits.size() || carry != 0; ++i)
    {
        u64 sum = carry;
        if (i < digits.size())
            sum += digits[i];
        if (i < other.digits.size())
            sum += other.digits[i];

        temp[i] = sum % 10;
        carry = sum / 10;
    }

    result.digits = std::move(temp);
    return result;
}

BigNumber64 BigNumber64::operator-(const BigNumber64& other) const
{
    BigNumber64 result;
    std::vector<u64> temp(digits.size(), 0);
    temp.reserve(digits.size());

    int64_t carry = 0;
    for (size_t i = 0; i < digits.size() || i < other.digits.size(); ++i)
    {
        int64_t diff = carry;
        if (i < digits.size())
            diff += digits[i];
        if (i < other.digits.size())
            diff -= other.digits[i];

        if (diff < 0) {
            diff += 10;
            carry = -1;
        } else {
            carry = 0;
        }

        temp[i] = diff;
    }

    result.digits = std::move(temp);
    result.removeLeadingZeros();
    return result;
}

BigNumber64 BigNumber64::operator*(const BigNumber64& other) const
{
    BigNumber64 result;
    std::vector<u64> temp(digits.size() + other.digits.size(), 0);
    temp.reserve(digits.size() + other.digits.size());

    for (size_t i = 0; i < digits.size(); ++i) {
        u64 carry = 0;
        for (size_t j = 0; j < other.digits.size() || carry != 0; ++j)
        {
            u64 product = carry;
            if (j < other.digits.size())
                product += digits[i] * other.digits[j];

            size_t index = i + j;
            u64 sum = temp[index] + product;
            temp[index] = sum % 10;
            carry = sum / 10;
        }
    }

    result.digits = std::move(temp);
    result.removeLeadingZeros();
    return result;
}

bool BigNumber64::operator==(const BigNumber64& other) const
{
    return digits == other.digits;
}

bool BigNumber64::operator!=(const BigNumber64& other) const
{
    return !(*this == other);
}

bool BigNumber64::operator<(const BigNumber64& other) const
{
    if (digits.size() < other.digits.size())
        return true;
    if (digits.size() > other.digits.size())
        return false;

    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
        if (digits[i] < other.digits[i])
            return true;
        if (digits[i] > other.digits[i])
            return false;
    }

    return false;
}

bool BigNumber64::operator<=(const BigNumber64& other) const
{
    return (*this < other) || (*this == other);
}

bool BigNumber64::operator>(const BigNumber64& other) const
{
    return !(*this <= other);
}

bool BigNumber64::operator>=(const BigNumber64& other) const
{
    return (*this > other) || (*this == other);
}

BigNumber64 BigNumber64::operator-() const
{
    BigNumber64 result(*this);
    for (auto& digit : result.digits)
        digit = 9 - digit;
    ++result.digits[0];

    result.removeLeadingZeros();
    return result;
}

BigNumber64& BigNumber64::operator+=(const BigNumber64& other)
{
    *this = *this + other;
    return *this;
}

BigNumber64& BigNumber64::operator-=(const BigNumber64& other)
{
    *this = *this - other;
    return *this;
}

BigNumber64& BigNumber64::operator*=(const BigNumber64& other)
{
    *this = *this * other;
    return *this;
}

void BigNumber64::removeLeadingZeros()
{
    auto it = std::ranges::find_if_not(digits, [](const Types::u64& digit) {
        return digit == 0;
    });
    digits.erase(digits.begin(), it);
}

BigNumber128::BigNumber128()
{
}

BigNumber128::BigNumber128(const std::string& number)
{
    digits.reserve(number.length());
    std::transform(number.rbegin(), number.rend(), std::back_inserter(digits), [](char c) { return c - '0'; });
}

BigNumber128::BigNumber128(u128 number)
{
    while (number > 0) {
        digits.push_back(number % 10);
        number /= 10;
    }
}

OptionalString BigNumber128::toString() const
{
    std::string result;

    if (digits.empty()) {
        result = "0";
    } else {
        result.reserve(digits.size());

        // Convert each digit to a character and append it to the result string
        for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
            char digitChar = static_cast<char>(*it + '0');
            result.push_back(digitChar);
        }
    }

    // Remove leading zeros
    result.erase(0, result.find_first_not_of('0'));

    return result;
}

BigNumber128 BigNumber128::operator+(const BigNumber128& other) const
{
    BigNumber128 result;
    std::vector<u128> temp(digits.size() + other.digits.size(), 0);

    u128 carry = 0;
    for (size_t i = 0; i < digits.size() || i < other.digits.size() || carry != 0; ++i)
    {
        u128 sum = carry;
        if (i < digits.size())
            sum += digits[i];
        if (i < other.digits.size())
            sum += other.digits[i];

        temp[i] = sum % 10;
        carry = sum / 10;
    }

    result.digits = std::move(temp);
    result.removeLeadingZeros();
    return result;
}

BigNumber128 BigNumber128::operator-(const BigNumber128& other) const
{
    BigNumber128 result;
    std::vector<u128> temp(digits.size(), 0);

    u128 carry = 0;
    for (size_t i = 0; i < digits.size() || i < other.digits.size(); ++i)
    {
        u128 diff = carry;
        if (i < digits.size())
            diff += digits[i];
        if (i < other.digits.size())
            diff -= other.digits[i];

        if (diff < 0) {
            diff += 10;
            carry = -1;
        } else {
            carry = 0;
        }

        temp[i] = diff;
    }

    result.digits = std::move(temp);
    result.removeLeadingZeros();
    return result;
}

BigNumber128 BigNumber128::operator*(const BigNumber128& other) const
{
    BigNumber128 result;
    std::vector<u128> temp(digits.size() + other.digits.size(), 0);

    for (size_t i = 0; i < digits.size(); ++i) {
        u128 carry = 0;
        for (size_t j = 0; j < other.digits.size() || carry != 0; ++j)
        {
            u128 product = carry;
            if (j < other.digits.size())
                product += digits[i] * other.digits[j];

            size_t index = i + j;
            u128 sum = temp[index] + product;
            temp[index] = sum % 10;
            carry = sum / 10;
        }
    }

    result.digits = std::move(temp);
    result.removeLeadingZeros();
    return result;
}

bool BigNumber128::operator==(const BigNumber128& other) const
{
    return digits == other.digits;
}

bool BigNumber128::operator!=(const BigNumber128& other) const
{
    return !(*this == other);
}

bool BigNumber128::operator<(const BigNumber128& other) const
{
    if (digits.size() < other.digits.size())
        return true;
    if (digits.size() > other.digits.size())
        return false;

    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i)
    {
        if (digits[i] < other.digits[i])
            return true;
        if (digits[i] > other.digits[i])
            return false;
    }

    return false;
}

bool BigNumber128::operator<=(const BigNumber128& other) const
{
    return (*this < other) || (*this == other);
}

bool BigNumber128::operator>(const BigNumber128& other) const
{
    return !(*this <= other);
}

bool BigNumber128::operator>=(const BigNumber128& other) const
{
    return (*this > other) || (*this == other);
}

BigNumber128 BigNumber128::operator-() const
{
    BigNumber128 result(*this);
    for (auto& digit : result.digits)
        digit = 9 - digit;
    ++result.digits[0];

    result.removeLeadingZeros();
    return result;
}

BigNumber128& BigNumber128::operator+=(const BigNumber128& other)
{
    *this = *this + other;
    return *this;
}

BigNumber128& BigNumber128::operator-=(const BigNumber128& other)
{
    *this = *this - other;
    return *this;
}

BigNumber128& BigNumber128::operator*=(const BigNumber128& other)
{
    *this = *this * other;
    return *this;
}

void BigNumber128::removeLeadingZeros() {
    auto it = std::ranges::find_if_not(digits, [](const Types::u128& digit) {
        return digit == 0;
    });
    digits.erase(digits.begin(), it);
}

CELL_NAMESPACE_END
