#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
 private:
  T* data;
  size_t length;

 public:
  Vector(size_t len) {
    if (len == 0) throw std::invalid_argument("Length must be greater than 0");
    if (len > 1024) throw std::invalid_argument("Length must not exceed 1024");

    length = len;
    data = new T[length];

    if (!data) throw std::bad_alloc();

    for (size_t i = 0; i < length; ++i) data[i] = T();
  }
  ~Vector() { delete[] data; }

  T& operator[](size_t index) {
    if (index < 0) throw std::out_of_range("Index must be greater than 0");
    if (index >= length) throw std::out_of_range("Index out of range");
    return data[index];
  }

  Vector<T> operator+(const Vector<T>& other) {
    if (length != other.length)
      throw std::invalid_argument("Vectors must be of the same length");

    Vector<T> result(length);
    for (size_t i = 0; i < length; ++i) result[i] = data[i] + other.data[i];
    return result;
  }

  bool operator==(const Vector<T>& other) const {
    if (length != other.length) return false;
    for (size_t i = 0; i < length; ++i)
      if (data[i] != other.data[i]) return false;
    return true;
  }

  friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.length; ++i) {
      os << vec.data[i];
      if (i < vec.length - 1) os << ", ";
    }
    os << "]";
    return os;
  }
};

int main() {
  Vector<int> v1(3), v2(3);
  for (int i = 0; i < 3; ++i) {
    v1[i] = i + 1;
    v2[i] = i + 4;
  }
  std::cout << "v1 + v2 = " << v1 << " + " << v2 << " = " << (v1 + v2)
            << std::endl;

  Vector<double> v3(2), v4(2);
  v3[0] = 1.5;
  v3[1] = 2.5;
  v4[0] = 1.5;
  v4[1] = 2.5;

  std::cout << v3 << (v3 == v4 ? " == " : " != ") << v4 << std::endl;
  return 0;
}