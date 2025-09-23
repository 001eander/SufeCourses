#include <fstream>
#include <string>

void writeToFile(const std::string& filename, const int arr[], size_t size) {
  std::ofstream os(filename);
  if (!os) throw std::ios_base::failure("Failed to open file");
  for (size_t i = 0; i < size; ++i) os << arr[i] << (i < size - 1 ? " " : "");
  os << std::endl;
  os.close();
}

void writeToFile(const std::string& filename, const std::string& content) {
  std::ofstream os(filename);
  if (!os) throw std::ios_base::failure("Failed to open file");
  os << content << std::endl;
  os.close();
}

void writeToFile(const std::string& filename, const double arr[], size_t size) {
  std::ofstream os(filename);
  if (!os) throw std::ios_base::failure("Failed to open file");
  for (size_t i = 0; i < size; ++i) os << arr[i] << std::endl;
  os.close();
}

int main() {
  const int intArr[]{1, 2, 3, 4, 5};
  const std::string text = "Hello, File!";
  const double doubleArr[]{1.1, 2.2, 3.3};

  writeToFile("ints.txt", intArr, 5);
  writeToFile("string.txt", text);
  writeToFile("doubles.txt", doubleArr, 3);
  return 0;
}