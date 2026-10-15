#include "User.h"
#include <iomanip>

User::User() {}

User::User(const string &id, const string &username, const string &role)
    : id(id), username(username), role(role) {}

User::~User() {}


void User::Print() const {
  // 列宽（按"显示宽度"算，中文占 2 列）
  const int W_ID    = 12;
  const int W_NAME  = 16;
  const int W_PWD   = 16;
  const int W_PHONE = 16;
  const int W_ROLE  = 10;

  // 表头
  printField("用户ID", W_ID);
  printField("用户名", W_NAME);
  printField("密码",   W_PWD);
  printField("电话",   W_PHONE);
  printField("角色",   W_ROLE);
  cout << "\n";

  // 分隔线
  cout << string(W_ID + W_NAME + W_PWD + W_PHONE + W_ROLE, '-') << "\n";

  // 密码打码
  string masked(password.size(), '*');

  // 数据行（列宽与表头完全一致）
  printField(id,       W_ID);
  printField(username, W_NAME);
  printField(masked,   W_PWD);
  printField(phone,    W_PHONE);
  printField(role,     W_ROLE);
  cout << "\n";
}


string User::ToLine() const {
  ostringstream os;
  os << id << ':' << username << ':' << password << ':' << phone << ':' << role;

  return os.str();
}


User User::FromLine(const string &line) {

  User user;
  size_t start = 0;
  size_t pos = line.find(':', start);
  user.id = line.substr(start, pos - start);
  start = pos + 1;

  pos = line.find(':', start);
  user.username = line.substr(start, pos - start);
  start = pos + 1;

  pos = line.find(':', start);
  user.password = line.substr(start, pos - start);
  start = pos + 1;

  pos = line.find(':', start);
  user.phone = line.substr(start, pos - start);
  start = pos + 1;

  user.role = line.substr(start);
  return user;
}


string User::GetKey() const { return id; }
