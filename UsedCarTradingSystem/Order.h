#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "DoubleLinkList.h" // 复用 Status
#include "Record.h"         // 基类

// ============================================================================
//  Order 订单类（继承 Record）
//  循环队列里装的就是这个类的对象
//  字段：
//    carVin     车架号（关联 Car.vin，一车一单，兼作订单唯一标识）
//    buyerId    买家 ID
//    sellerId   卖家 ID
//    createTime 下单时间
//  TODO 练习扩展：成交价 price / 订单状态 status / 备注 remark
// ============================================================================
class Order : public Record
{
public:
    string carVin;
    string buyerId;
    string sellerId;
    string createTime;

    Order();
    Order(const string &vin,
          const string &buyer,
          const string &seller);
    ~Order();

    void Print() const override;                    // 重写基类纯虚函数
    std::string ToLine() const override;            // 重写：冒号分隔
    std::string GetKey() const override;            // 重写：返回 carVin
    static Order FromLine(const std::string &line); // 静态：从一行还原
};
