#include "User.h"

User::User() {}

User::User(const std::string &id,
           const std::string &username,
           const std::string &role)
    : id(id), username(username), role(role) {}

User::~User() {}

// TODO 练习：cout 打印一个用户的所有字段（密码可打 * 号）
void User::Print() const
{
    // TODO:
}

// TODO 练习：把全部字段序列化成一行字符串，字段之间用冒号 ':' 分隔
std::string User::ToLine() const
{
    // TODO:
    return "";
}

// TODO 练习：按冒号把 line 拆回 5 个字段
User User::FromLine(const std::string &line)
{
    // TODO:
    return User();
}

// GetKey：返回唯一标识用户 ID
std::string User::GetKey() const
{
    return id;
}
