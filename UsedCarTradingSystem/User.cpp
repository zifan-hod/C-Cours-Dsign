#include "User.h"

User::User() {}

User::User(const std::string &id,
           const std::string &username,
           const std::string &role)
    : id(id), username(username), role(role) {}

User::~User() {}

// TODO 练习：cout << "[User] id=" << id << " name=" << username << " role=" << role
void User::Print() const
{
    // TODO:
}

// TODO 练习：把 5 个字段用空格连起来
std::string User::ToLine() const
{
    // TODO:
    return "";
}

// TODO 练习：用 istringstream 拆出 5 个字段
User User::FromLine(const std::string &line)
{
    // TODO:
    return User();
}
