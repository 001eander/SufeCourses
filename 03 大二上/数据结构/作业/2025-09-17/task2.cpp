#include <iostream>
#include <ostream>

class Complex {
 private:
  double real;
  double imag;

 public:
  Complex(double r = 0, double i = 0) : real(r), imag(i) {}
  ~Complex() = default;

  Complex operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
  }
  Complex operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
  }
  Complex operator*(const Complex& other) const {
    return Complex(real * other.real - imag * other.imag,
                   real * other.imag + imag * other.real);
  }

  friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real << (c.imag >= 0 ? "+" : "") << c.imag << "i";
    return os;
  }
};

int main() {
  Complex c1(3, 4);
  Complex c2(1, -2);

  std::cout << "c1 = " << c1 << std::endl;
  std::cout << "c2 = " << c2 << std::endl;

  std::cout << "c1 + c2 = " << c1 + c2 << std::endl;
  std::cout << "c1 - c2 = " << c1 - c2 << std::endl;
  std::cout << "c1 * c2 = " << c1 * c2 << std::endl;
  return 0;
}