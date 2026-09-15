#pragma once
#include <iostream>
#include <string>
#include "DoubleLinkList.h"   // 复用 Status

// ============================================================================
//  User 用户类 —— 双链表装的就是这个类的对象
//  字段：
//    id        用户 ID（主键）
//    username  用户名
//    password  密码（练习项目，明文存储即可）
//    phone     电话
//    role      角色：buyer / seller / admin
// ============================================================================
class User
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

    void Print() const;
    std::string ToLine() const;
    static User FromLine(const std::string &line);
};
