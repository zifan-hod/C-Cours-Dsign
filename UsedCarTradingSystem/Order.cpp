#include "Order.h"

Order::Order() {}

Order::Order(const std::string &vin, const std::string &buyer,
             const std::string &seller)
    : carVin(vin), buyerId(buyer), sellerId(seller) {}

Order::~Order() {}

// TODO 练习：cout 打印一笔订单的所有字段
void Order::Print() const {
  // TODO:
}

// TODO 练习：把全部字段序列化成一行字符串，字段之间用冒号 ':' 分隔
std::string Order::ToLine() const {
  // TODO:
  return "";
}

// TODO 练习：按冒号把 line 拆回 4 个字段
Order Order::FromLine(const std::string &line) {
  // TODO:
  return Order();
}

// GetKey：返回唯一标识车架号（一车一单）
std::string Order::GetKey() const { return carVin; }
