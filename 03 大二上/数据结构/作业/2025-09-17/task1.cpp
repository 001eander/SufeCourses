#include <iostream>
#include <string>

class Employee {
 private:
  std::string name;

 public:
  Employee(const std::string& name_) : name(name_) {}
  std::string getName() const { return name; }
  virtual double calculateSalary() const = 0;
};

class FullTimeEmployee : public Employee {
 private:
  double monthlySalary;
  double bonus;

 public:
  FullTimeEmployee(const std::string& name_, double salary, double empBonus)
      : Employee(name_), monthlySalary(salary), bonus(empBonus) {}

  double calculateSalary() const override { return monthlySalary + bonus; }
};

class PartTimeEmployee : public Employee {
 private:
  double hourlyWage;
  double workHours;

 public:
  PartTimeEmployee(const std::string& name_, double wage, double hours)
      : Employee(name_), hourlyWage(wage), workHours(hours) {}

  double calculateSalary() const override {
    return hourlyWage * workHours +
           (workHours > 160 ? 0.5 * hourlyWage * (workHours - 160) : 0);
  }
};

int main() {
  Employee* employees[] = {
      new FullTimeEmployee("张三", 8000, 2000),
      new FullTimeEmployee("李四", 7500, 1500),
      new PartTimeEmployee("王五", 60, 180),
  };

  double totalSalary = 0;
  for (const auto& emp : employees) {
    auto salary = emp->calculateSalary();
    totalSalary += salary;
    std::cout << emp->getName() << "的薪资：" << salary << std::endl;
  }
  std::cout << "总薪资：" << totalSalary << std::endl;

  return 0;
}