#include <iostream>
#include <functional>
#include <string>
#include <vector>

class Rational {
private:
    int numerator {};
    int denominator {};

    /*
     * Finds the GCD recursively
     */
    int GCD(int a, int b) {
        if (a < 0)
            a = -a;
        if (b < 0)
            b = -b;

        if (a == 0) return b;
        if (b == 0) return a;
        if (a == b) return a;

        if (a > b)
            return GCD(a-b, b);
        return GCD(a, b-a);
    }
public:
    /*
     * Construct a zero rational number.
     * This constructor is fully implemented.
     */
    Rational() {
        Rational(0, 1);
    }

    /*
     * Copy the initial value of the numerator and denominator
     * If the denominator value is zero, throw std::runtime_error exception
     */
    Rational(int n, int d) {
        if (!d)
            throw std::runtime_error("denominator cannot be 0");
        numerator = n;
        denominator = d;
        reduce();
    };

    /*
     * Reduce the fraction by diving by GCD. Make sure to call this function
     * after each mathematical operation to make the fraction stored in the reduced form.
     */
    void reduce() {
        int gcd {GCD(numerator, denominator)};
        numerator /= gcd;
        denominator /= gcd;
    }

    /*
     * Adding two rational numbers.
     */
    Rational operator+(const Rational &a) const {
        Rational result {};
        if (denominator == a.denominator) {
            result.denominator = denominator;
            result.numerator = numerator + a.numerator;
        } else {
            result.denominator = denominator * a.denominator;
            result.numerator = (numerator * a.denominator) + (a.numerator * denominator);
        }
        result.reduce();
        return result;
    }

    /*
     * Adding integer to rational number.
     */
    Rational operator+(const int i) const {
        Rational a {i, 1};
        return operator+(a);
    }

    /*
     * Subtracting two rational numbers.
     */
    Rational operator-(const Rational &a) const {
        Rational result {};
        if (denominator == a.denominator) {
            result.denominator = denominator;
            result.numerator = numerator - a.numerator;
        } else {
            result.denominator = denominator * a.denominator;
            result.numerator = (numerator * a.denominator) - (a.numerator * denominator);
        }
        result.reduce();
        return result;
    }

    /*
     * Subtracting integer from rational number.
     */
    Rational operator-(const int i) const {
        Rational s {i, 1};
        return operator-(s);
    }

    /*
     * Multiplying two rational numbers.
     */
    Rational operator*(const Rational &a) const {
        Rational result {};
        result.numerator = numerator * a.numerator;
        result.denominator = denominator * a.denominator;
        result.reduce();
        return result;
    }

    /*
     * Multiplying integer by rational number.
     */
    Rational operator*(const int i) const {
        Rational a {i, 1};
        return operator*(a);
    }

    /*
     * Dividing two rational numbers.
     * If dividing by zero, throw a std::runtime_error exception.
     */
    Rational operator/(const Rational &a) const {
        if (!a.numerator)
            throw std::runtime_error("cannot divide by 0");
        Rational result {};
        result.numerator = numerator * a.denominator;
        result.denominator = denominator * a.numerator;
        result.reduce();
        return result;
    }

    /*
     * Dividing rational numbers by integer.
     * If dividing by zero, throw a std::runtime_error exception.
     */
    Rational operator/(const int i) const {
        Rational a {i, 1};
        return operator/(a);
    }

    void printRational() {
        std::cout << numerator << "/" << denominator << std::endl;
    }

    int getNumerator() const {
        return numerator;
    }

    int getDenominator() const {
        return denominator;
    }
};

void evaluate_exception(std::function<void()> test) {
    static std::string fail{"FAIL\n"};
    static std::string pass{"PASS\n"};

    try {
        test();
        std::cout << fail;
    } catch (std::runtime_error &e) {
        std::cout << pass;
    }
}

void evaluate_test(bool result) {
    static std::string fail{"FAIL\n"};
    static std::string pass{"PASS\n"};

    if (result) {
        std::cout << pass;
    } else {
        std::cout << fail;
    }
}

int main() {
    Rational default_rational{};
    Rational zero_rational{0, 1};
    Rational rational1{5, 7};
    Rational rational2{110, 30};

    std::cout << "Testing Exceptions\n";

    std::cout << "\tZero denominator: ";
    evaluate_exception([&]() { Rational{5, 0}; });

    std::cout << "\tDividing by zero fraction: ";
    evaluate_exception([&]() { rational1 / zero_rational; });

    std::cout << "\tDividing by zero integer: ";
    evaluate_exception([&]() { rational1 / 0; });

    std::cout << "\nTesting Functions\n";

    std::cout << "\tAdding 110/30 to 5/7: ";
    default_rational = rational1 + rational2;
    evaluate_test(default_rational.getNumerator() == 92 && default_rational.getDenominator() == 21);

    std::cout << "\tSubtracting 110/30 from 5/7: ";
    default_rational = rational1 - rational2;
    evaluate_test(default_rational.getNumerator() == -62 && default_rational.getDenominator() == 21);

    std::cout << "\tMultiplying 5/7 by 110/30: ";
    default_rational = rational1 * rational2;
    evaluate_test(default_rational.getNumerator() == 55 && default_rational.getDenominator() == 21);

    std::cout << "\tDividing 5/7 by 110/30: ";
    default_rational = rational1 / rational2;
    evaluate_test(default_rational.getNumerator() == 15 && default_rational.getDenominator() == 77);

    std::cout << "\tAdding 3 to 5/7: ";
    default_rational = rational1 + 3;
    evaluate_test(default_rational.getNumerator() == 26 && default_rational.getDenominator() == 7);

    std::cout << "\tSubtracting 3 from 5/7: ";
    default_rational = rational1 - 3;
    evaluate_test(default_rational.getNumerator() == -16 && default_rational.getDenominator() == 7);

    std::cout << "\tMultiplying 5/7 by 3: ";
    default_rational = rational1 * 3;
    evaluate_test(default_rational.getNumerator() == 15 && default_rational.getDenominator() == 7);

    std::cout << "\tDividing 5/7 by 3: ";
    default_rational = rational1 / 3;
    evaluate_test(default_rational.getNumerator() == 5 && default_rational.getDenominator() == 21);

    return 0;
}