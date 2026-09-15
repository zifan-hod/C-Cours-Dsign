#pragma once
#include <iostream>
#include <string>
#include "DoubleLinkList.h"   // 复用 Status

// ============================================================================
//  Order 订单类
//  循环队列里装的就是这个类的对象
//  字段（最小集）：carVin / buyerId / sellerId —— 关联 Car 和 User
//  TODO 练习扩展：
//    string orderId;     // 订单号，如 O20260914001
//    string createTime;   // 下单时间
//    double price;        // 成交价（可能 ≠ car.price）
//    string status;       // 待处理 / 已成交 / 已取消
//    string remark;       // 备注
// ============================================================================
class Order
{
public:
    std::string carVin;
    std::string buyerId;
    std::string sellerId;

    Order();
    Order(const std::string &vin,
          const std::string &buyer,
          const std::string &seller);
    ~Order();

    void Print() const;                                  // 打印到 cout
    std::string ToLine() const;                          // 序列化为文件一行（用空格分隔）
    static Order FromLine(const std::string &line);      // 从文件一行反序列化
};
