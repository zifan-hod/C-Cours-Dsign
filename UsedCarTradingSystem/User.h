#pragma once
#include <iostream>
#include <string>
#include "DoubleLinkList.h"   // 复用 Status
#include "Record.h"          // 基类

// ============================================================================
//  User 用户类（继承 Record）—— 双链表装的就是这个类的对象
//  字段：
//    id        用户 ID（主键）
//    username  用户名
//    password  密码（练习项目，明文存储即可）
//    phone     电话
//    role      角色：buyer / seller / admin
// ============================================================================
class User : public Record
{
public:
    std::string id;
    std::string username;
    std::string password;
    std::string phone;
    std::string role;   // buyer / seller / admin

    User();
    User(const std::string &id,
         const std::string &username,
         const std::string &role);
    ~User();

    void        Print() const override;                 // 重写基类纯虚函数
    std::string ToLine() const override;                // 重写：冒号分隔
    std::string GetKey() const override;                // 重写：返回 id
    static User FromLine(const std::string &line);      // 静态：从一行还原

    // 重载 ==：按 id 比较，供链表 LocateElem 使用
    bool operator==(const User &other) const { return id == other.id; }
};
