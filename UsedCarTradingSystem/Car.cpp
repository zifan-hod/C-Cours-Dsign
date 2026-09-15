#include "car.h"

Car::Car()
    : year(0), mileage(0), price(0.0) {}

Car::Car(const std::string &vin, const std::string &brand)
    : vin(vin), brand(brand), year(0), mileage(0), price(0.0) {}

Car::~Car() {}

// TODO 练习：cout 格式化打印一辆车的所有字段
void Car::Print() const
{
    // TODO:
}

// TODO 练习：把所有字段用空格连起来，方便 fstream 读写
//   return vin + " " + brand + " " + model + " " + to_string(year) + ...
std::string Car::ToLine() const
{
    // TODO:
    return "";
}

// TODO 练习：用 istringstream 从 line 拆出各字段
//   提示：#include <sstream>
Car Car::FromLine(const std::string &line)
{
    // TODO:
    return Car();
}
