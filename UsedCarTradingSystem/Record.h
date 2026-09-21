#pragma once

#include <iostream>
#include <string>

// ============================================================================
//  Record 记录 —— 抽象基类
//  Car / User / Order 都继承它，统一接口，练习虚函数与多态
//
//  学习要点：
//    1. virtual 关键字 + 末尾 = 0 表示"纯虚函数"：
//       基类不给实现，子类【必须】重写，否则子类也不能创建对象
//    2. 含有纯虚函数的类叫"抽象类"，不能直接 new Record，但可以定义
//       Record* 指针指向子类对象 —— 多态就靠它
//    3. 虚析构函数：基类 delete 子类对象时能正确调子类析构，防止内存泄漏
//    4. override 写在子类声明后，让编译器帮忙检查"是否真的重写了父类虚函数"
// ============================================================================
class Record
{
public:
    virtual ~Record() {}                       // 虚析构：基类必备

    virtual void        Print() const = 0;     // 纯虚：打印自身
    virtual std::string ToLine() const = 0;    // 纯虚：序列化为文件一行
    virtual std::string GetKey() const = 0;    // 纯虚：返回唯一标识
};

// 时间工具函数：返回 "YYYY-MM-DD HH:MM:SS" 格式的当前时间
// Car 上架、Order 下单时调用
std::string GetNowTime();
