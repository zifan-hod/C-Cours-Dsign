#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "DoubleLinkList.h" // 复用 Status
#include "Record.h"         // 基类
using namespace std;
// ============================================================================
//  Car 车辆类（继承 Record）—— 双链表装的就是这个类的对象
//  字段说明：
//    vin        车架号（主键，唯一）→ 查找/删除/修改都靠它
//    brand      品牌
//    model      型号
//    year       上牌年份
//    mileage    里程
//    price      售价
//    sellerId   卖家 ID（关联 User.id）
//    status     待售 / 已预订 / 已售出 ← 交易流转靠它
//    store      门店（"巴南·龙洲湾"）← 题目特色
//    createTime 上架时间（GetNowTime 生成）
// ============================================================================
class Car : public Record
{
public:
    std::string vin;
    std::string brand;
    std::string model;
    int year;
    int mileage;
    double price;
    std::string sellerId;
    std::string status;
    std::string store;
    std::string createTime;

    Car();
    Car(const std::string &vin, const std::string &brand);
    ~Car();

    void Print() const override;                  // 重写基类纯虚函数
    std::string ToLine() const override;          // 重写：冒号分隔
    std::string GetKey() const override;          // 重写：返回 vin
    static Car FromLine(const std::string &line); // 静态：从一行还原

    // 重载 ==：按 vin 比较，供链表 LocateElem 使用
    //  函数体只有一行，直接写在头文件里（简单函数的惯例）
    bool operator==(const Car &other) const { return vin == other.vin; }
};
