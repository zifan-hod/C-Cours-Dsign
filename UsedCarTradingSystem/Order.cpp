#include "Order.h"

Order::Order() {}

Order::Order(const std::string &vin,
             const std::string &buyer,
             const std::string &seller)
    : carVin(vin), buyerId(buyer), sellerId(seller) {}

Order::~Order() {}

// TODO 练习：cout << "[Order] vin=" << carVin << " buyer=" << buyerId << " seller=" << sellerId
void Order::Print() const
{
    // TODO:
}

// TODO 练习：把三个字段用空格连起来，方便 fstream 读写
//   return carVin + " " + buyerId + " " + sellerId;
std::string Order::ToLine() const
{
    // TODO:
    return "";
}

// TODO 练习：用 istringstream 从 line 拆出三个字段
//   提示：#include <sstream>
//   istringstream iss(line); iss >> carVin >> buyerId >> sellerId;
Order Order::FromLine(const std::string &line)
{
    // TODO:
    return Order();
}
