#include "Menu.h"
#include <ctime>
#include <fcntl.h>
#include <fstream>
#include <sstream>
#include <unistd.h>

Menu::Menu() {
  users = new DoubleLinkList<User>;
  cars = new DoubleLinkList<Car>;
  orders = new CirQueue<Order>;
  currentUser = nullptr;
}

Menu::~Menu() {


  delete users;
  delete cars;
  delete orders;
}




void Menu::Run() {
  LoadFromFile();
  if (users->ListEmpty())
    InitDefaultAdmin();

  while (true) {
    if (currentUser == nullptr) {
      ShowLoginMenu();
    } else if (currentUser->role == "buyer") {
      ShowBuyerMenu();
    } else if (currentUser->role == "seller") {
      ShowSellerMenu();
    } else if (currentUser->role == "admin") {
      ShowAdminMenu();
    } else {

      break;
    }
  }

  SaveToFile();
  cout << "再见，数据已写回当前目录\n";
}







string Menu::ReadWholeFile(const char *path) {
  int fd = open(path, O_RDONLY);
  if (fd < 0)
    return "";

  char buf[4096];
  string result;
  ssize_t n = 0;

  while ((n = read(fd, buf, sizeof(buf))) > 0)
    result.append(buf,
                  static_cast<size_t>(n));



  close(fd);
  return result;
}

void Menu::LoadFromFile() {

  string content = ReadWholeFile("users.txt");
  size_t start = 0;
  while (true) {
    size_t pos = content.find('\n', start);
    if (pos == string::npos)
      break;
    string oneLine = content.substr(start, pos - start);
    if (!oneLine.empty())


      users->ListInsert(users->ListLength() + 1, User::FromLine(oneLine));
    start = pos + 1;
  }
  string tail = content.substr(start);
  if (!tail.empty())
    users->ListInsert(users->ListLength() + 1, User::FromLine(tail));


  content = ReadWholeFile("cars.txt");
  start = 0;
  while (true) {
    size_t pos = content.find('\n', start);
    if (pos == string::npos)
      break;
    string oneLine = content.substr(start, pos - start);
    if (!oneLine.empty())
      cars->ListInsert(cars->ListLength() + 1, Car::FromLine(oneLine));
    start = pos + 1;
  }
  tail = content.substr(start);
  if (!tail.empty())
    cars->ListInsert(cars->ListLength() + 1, Car::FromLine(tail));



  content = ReadWholeFile("orders.txt");
  start = 0;
  while (true) {
    size_t pos = content.find('\n', start);
    if (pos == string::npos)
      break;
    string oneLine = content.substr(start, pos - start);
    if (!oneLine.empty())
      orders->Push(Order::FromLine(oneLine));
    start = pos + 1;
  }
  tail = content.substr(start);
  if (!tail.empty())
    orders->Push(Order::FromLine(tail));
}

void Menu::SaveToFile() {


  int fd = open("users.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd >= 0) {
    for (int i = 1; i <= users->ListLength(); ++i) {
      User u;
      users->GetElem(i, u);
      string s = u.ToLine() + "\n";
      write(fd, s.c_str(), s.size());
    }
    close(fd);
  }


  fd = open("cars.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd >= 0) {
    for (int i = 1; i <= cars->ListLength(); ++i) {
      Car c;
      cars->GetElem(i, c);
      string s = c.ToLine() + "\n";
      write(fd, s.c_str(), s.size());
    }
    close(fd);
  }




  fd = open("orders.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd >= 0) {
    int cnt = orders->Length();
    for (int i = 0; i < cnt; ++i) {
      Order o;
      orders->Pop(o);
      string s = o.ToLine() + "\n";
      write(fd, s.c_str(), s.size());
      orders->Push(o);
    }
    close(fd);
  }
}

void Menu::InitDefaultAdmin() {



  User user;
  user.id = "A0001";
  user.username = "admin";
  user.password = "914sx2026";
  user.phone = "19123456789";
  user.role = "admin";
  users->ListInsert(users->ListLength() + 1, user);
}




bool Menu::Login() {
  string id, pwd;
  cout << "\n===== 登录 =====\n";
  cout << "请输入用户ID: " << flush;
  cin >> id;
  cout << "请输入密码: " << flush;
  cin >> pwd;

  User userkey;
  userkey.id = id;

  DoubleNode<User> *P = users->LocateElem(userkey);

  if (P != nullptr && P->data.password == pwd) {
    currentUser = &(P->data);
    cout << "登录成功，欢迎 " << currentUser->username << "\n";
    return true;
  }

  cout << "ID 或密码错误，请重试\n";
  return false;
}





void Menu::ShowLoginMenu() {
  cout << "\n========== 巴南二手车交易系统 ==========\n";
  cout << " 1. 登录\n";
  cout << " 2. 注册（买家）\n";
  cout << " 0. 退出\n";
  cout << "========================================\n";
  cout << "选择: ";
  int op = 0;
  cin >> op;
  if (cin.fail()) {
    cin.clear();
    cin.ignore(1024, '\n');
    op = -1;
  }
  switch (op) {
  case 1:
    Login();
    break;
  case 2: {

    string id, username, password, phone;
    cout << "输入用户ID: ";
    cin >> id;
    User key;
    key.id = id;
    if (users->LocateElem(key) != nullptr) {
      cout << "该 ID 已存在，注册失败\n";
      break;
    }
    cout << "用户名: ";
    cin >> username;
    cout << "密码: ";
    cin >> password;
    cout << "电话: ";
    cin >> phone;
    User u(id, username, "buyer");
    u.password = password;
    u.phone = phone;
    users->ListInsert(users->ListLength() + 1, u);
    cout << "注册成功，请登录\n";
    break;
  }
  case 0:
    SaveToFile();
    cout << "数据已写回，再见\n";
    exit(0);
  default:
    cout << "无效选择，请输入 0 / 1 / 2\n";
    break;
  }
}

void Menu::ShowBuyerMenu() {
  cout << "\n---- 买家菜单 [" << currentUser->username << "] ----\n";
  cout << " 1. 浏览所有待售车\n";
  cout << " 2. 按品牌搜索\n";
  cout << " 3. 下预订单（入队）\n";
  cout << " 4. 查看我的订单\n";
  cout << " 0. 注销\n";
  cout << "------------------------\n";
  cout << "选择: ";
  int op = 0;
  cin >> op;
  if (cin.fail()) {
    cin.clear();
    cin.ignore(1024, '\n');
    op = -1;
  }
  switch (op) {
  case 1: {

    int len = cars->ListLength();
    bool found = false;
    for (int i = 1; i <= len; ++i) {
      Car c;
      cars->GetElem(i, c);
      if (c.status == "待售") {
        c.Print();
        found = true;
      }
    }
    if (!found)
      cout << "暂无待售车辆\n";
    break;
  }
  case 2: {

    string brand;
    cout << "输入品牌: ";
    cin >> brand;
    bool found = false;
    int len = cars->ListLength();
    for (int i = 1; i <= len; ++i) {
      Car c;
      cars->GetElem(i, c);
      if (c.brand == brand) {
        c.Print();
        found = true;
      }
    }
    if (!found)
      cout << "没有该品牌的车辆\n";
    break;
  }
  case 3: {

    string vin;
    cout << "输入车架号(VIN): ";
    cin >> vin;
    Car key;
    key.vin = vin;
    DoubleNode<Car> *p = cars->LocateElem(key);
    if (p == nullptr) {
      cout << "车辆不存在\n";
    } else if (p->data.status != "待售") {
      cout << "该车当前状态: " << p->data.status << "，不可预订\n";
    } else {
      Order order(vin, currentUser->id, p->data.sellerId);
      order.createTime = GetNowTime();
      if (orders->Push(order) == OK) {
        p->data.status = "已预订";
        cout << "预订单已提交，等待卖家处理\n";
      } else {
        cout << "订单队列已满，提交失败\n";
      }
    }
    break;
  }
  case 4:

    {
      int cnt = orders->Length();
      bool found = false;
      for (int i = 0; i < cnt; ++i) {
        Order o;
        orders->Pop(o);
        if (o.buyerId == currentUser->id) {
          o.Print();
          found = true;
        }
        orders->Push(o);
      }
      if (!found)
        cout << "暂无订单\n";
    }
    break;
  case 0:
    currentUser = nullptr;
    break;
  default:
    cout << "无效选择，请输入 0 ~ 4\n";
    break;
  }
}

void Menu::ShowSellerMenu() {
  cout << "\n---- 卖家菜单 [" << currentUser->username << "] ----\n";
  cout << " 1. 上架车\n";
  cout << " 2. 下架车\n";
  cout << " 3. 查看我的车\n";
  cout << " 4. 查看我的订单\n";
  cout << " 0. 注销\n";
  cout << "------------------------\n";
  cout << "选择: ";
  int op = 0;
  cin >> op;
  if (cin.fail()) {
    cin.clear();
    cin.ignore(1024, '\n');
    op = -1;
  }
  switch (op) {
  case 1: {

    Car car;
    cout << "车架号(VIN): ";
    cin >> car.vin;
    Car key;
    key.vin = car.vin;
    if (cars->LocateElem(key) != nullptr) {
      cout << "该车架号已存在\n";
      break;
    }
    cout << "品牌: ";
    cin >> car.brand;
    cout << "型号: ";
    cin >> car.model;
    cout << "上牌年份: ";
    cin >> car.year;
    cout << "里程(km): ";
    cin >> car.mileage;
    cout << "售价: ";
    cin >> car.price;
    cout << "门店: ";
    cin >> car.store;
    car.sellerId = currentUser->id;
    car.status = "待售";
    car.createTime = GetNowTime();
    cars->ListInsert(cars->ListLength() + 1, car);
    cout << "上架成功\n";
    break;
  }
  case 2: {

    string vin;
    cout << "输入车架号(VIN): ";
    cin >> vin;
    int len = cars->ListLength();
    bool found = false;
    for (int i = 1; i <= len; ++i) {
      Car c;
      cars->GetElem(i, c);
      if (c.vin == vin) {
        if (c.sellerId != currentUser->id) {
          cout << "这不是你的车，不能下架\n";
        } else {
          Car del;
          cars->ListDelete(i, del);
          cout << "已下架\n";
        }
        found = true;
        break;
      }
    }
    if (!found)
      cout << "未找到该车\n";
    break;
  }
  case 3:

    {
      int len = cars->ListLength();
      bool found = false;
      for (int i = 1; i <= len; ++i) {
        Car c;
        cars->GetElem(i, c);
        if (c.sellerId == currentUser->id) {
          c.Print();
          found = true;
        }
      }
      if (!found)
        cout << "暂无车辆\n";
    }
    break;
  case 4:

    {
      int cnt = orders->Length();
      bool found = false;
      for (int i = 0; i < cnt; ++i) {
        Order o;
        orders->Pop(o);
        if (o.sellerId == currentUser->id) {
          o.Print();
          found = true;
        }
        orders->Push(o);
      }
      if (!found)
        cout << "暂无订单\n";
    }
    break;
  case 0:
    currentUser = nullptr;
    break;
  default:
    cout << "无效选择，请输入 0 ~ 4\n";
    break;
  }
}

void Menu::ShowAdminMenu() {
  cout << "\n---- 管理员菜单 [admin] ----\n";
  cout << " 1. 查看所有用户\n";
  cout << " 2. 查看所有车辆\n";
  cout << " 3. 处理订单（出队成交）\n";
  cout << " 4. 查看订单队列\n";
  cout << " 0. 注销\n";
  cout << "------------------------\n";
  cout << "选择: ";
  int op = 0;
  cin >> op;
  if (cin.fail()) {
    cin.clear();
    cin.ignore(1024, '\n');
    op = -1;
  }
  switch (op) {
  case 1:
    if (users->ListEmpty())
      cout << "暂无用户\n";
    else
      users->ListTraverse([](const User &u) { u.Print(); });
    break;
  case 2:
    if (cars->ListEmpty())
      cout << "暂无车辆\n";
    else
      cars->ListTraverse([](const Car &c) { c.Print(); });
    break;
  case 3: {

    Order order;
    if (orders->Pop(order) == ERROR) {
      cout << "订单队列为空\n";
    } else {
      Car key;
      key.vin = order.carVin;
      DoubleNode<Car> *p = cars->LocateElem(key);
      if (p != nullptr) {
        p->data.status = "已售出";
        cout << "已成交: VIN=" << order.carVin << " 买家=" << order.buyerId
             << "\n";
      } else {
        cout << "订单对应车辆不存在，跳过\n";
      }
    }
    break;
  }
  case 4:
    if (orders->Empty())
      cout << "订单队列为空\n";
    else
      orders->Traverse([](const Order &o) { o.Print(); });
    break;
  case 0:
    currentUser = nullptr;
    break;
  default:
    cout << "无效选择，请输入 0 ~ 4\n";
    break;
  }
}
