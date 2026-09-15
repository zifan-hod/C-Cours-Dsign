#pragma once
#include <iostream>
#include <string>
#include "DoubleLinkList.h"   // 复用 Status
using namespace std;
// ============================================================================
//  Car 车辆类 —— 双链表装的就是这个类的对象
//  字段说明：
//    vin       车架号（主键，唯一）→ 查找/删除/修改都靠它
//    brand     品牌
//    model     型号
//    year      上牌年份
//    mileage   里程
//    price     售价
//    sellerId  卖家 ID（关联 User.id）
//    status    待售 / 已预订 / 已售出 ← 交易流转靠它
//    store     门店（"巴南·龙洲湾"）← 题目特色
// ============================================================================
class Car
{
public:
    std::string vin;
    std::string brand;
    std::string model;
    int         year;
    int         mileage;
    double      price;
    std::string sellerId;
    std::string status;
    std::string store;

    Car();
    Car(const std::string &vin, const std::string &brand);
    ~Car();

    void Print() const;                                  // 打印到 cout
    std::string ToLine() const;                          // 序列化为文件一行
    static Car FromLine(const std::string &line);        // 从文件一行反序列化
};
