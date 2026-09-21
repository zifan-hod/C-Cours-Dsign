#include "Menu.h"
#include <ctime>
#include <fcntl.h> // open + O_WRONLY/O_CREAT/O_TRUNC/O_RDONLY
#include <fstream>
#include <sstream>
#include <unistd.h> // read / write / close

Menu::Menu()
{
  users = new DoubleLinkList<User>;
  cars = new DoubleLinkList<Car>;
  orders = new CirQueue<Order>;
  currentUser = nullptr;
}

Menu::~Menu()
{
  // TODO 练习：释放构造函数中 new 出的三个数据结构（自己 new 的自己 delete）
  //   注意 currentUser 不是 new 出来的，不要在这里释放
  delete users;
  delete cars;
  delete orders;
}

// ============================================================================
//  主流程：加载 → 默认 admin → 登录循环 → 分发 → 写回
// ============================================================================
void Menu::Run()
{
  LoadFromFile();
  if (users->ListEmpty())
    InitDefaultAdmin();

  while (true)
  {
    if (currentUser == nullptr)
    {
      ShowLoginMenu();
    }
    else if (currentUser->role == "buyer")
    {
      ShowBuyerMenu();
    }
    else if (currentUser->role == "seller")
    {
      ShowSellerMenu();
    }
    else if (currentUser->role == "admin")
    {
      ShowAdminMenu();
    }
    else
    {
      // 未知角色，退出
      break;
    }
  }

  SaveToFile();
  std::cout << "再见，数据已写回当前目录\n";
}

// ============================================================================
//  文件读写：Linux 系统调用 open/read/write，文件放【当前目录】
//  数据格式：每行一个对象，字段用冒号 ':' 分隔
// ============================================================================
void Menu::LoadFromFile()
{
  // TODO 练习：从当前目录读取 users.txt / cars.txt / orders.txt
  //
  //  users.txt 思路：
  //    1. 以只读方式打开；打不开（文件不存在，第一次运行）直接结束
  //    2. 准备一块缓冲区，循环 read，每批处理新读到的字节
  //    3. 逐字节扫描本批内容：
  //         遇到换行符 → 一行结束，把这行交给 User::FromLine 还原，
  //                      追加到 users 链表末尾，然后清空行暂存
  //         否则       → 追加到当前行
  //    4. 全部读完后，行暂存若还有内容（最后一行可能没换行）同样处理
  //    5. close
  //  cars.txt 同样流程，追加到 cars；orders.txt 还原后用 Push 入队
  int fd = open("users.txt", 0644);
  int fd_1 = open("cars.txt", 0644);
  int fd_2 = open("orders.txt", 0644);
  
}

void Menu::SaveToFile()
{
  // TODO 练习：把三个数据结构写回当前目录
  //
  //  users.txt 思路：
  //    1. 只写方式打开：不存在就创建、已存在就清空
  //    2. 从第 1 个遍历到最后一个，逐个取出用户
  //    3. 每个用户 ToLine 后补一个换行符，write 进文件
  //    4. close
  //  cars.txt 同样写法；orders.txt 需自行把队列完整"转一圈"遍历
  //  （提示：队列只能从队头取，想保留队列可以"出队一个、写回、再入队"）
}

void Menu::InitDefaultAdmin()
{
  // TODO 练习：首次启动没有用户数据时，准备一个管理员账号
  //   思路：确定管理员的编号、用户名、密码、角色，构造好后加入 users
  //   也可以顺便准备一两个演示用的账号或车辆
}

// ============================================================================
//  登录：输入 id + 密码，校验通过则 currentUser 指向该用户
// ============================================================================
bool Menu::Login()
{
  // TODO 练习：
  //   string id, pwd;
  //   cin >> id >> pwd;
  //   用 LocateElem 在 users 里找 id；
  //   找到后比较 password，匹配则 currentUser = ...，return true；
  //   否则提示失败，return false
  return false;
}

// ============================================================================
//  菜单打印 —— 这里把菜单结构打全，业务分支留 TODO
// ============================================================================

void Menu::ShowLoginMenu()
{
  std::cout << "\n========== 巴南二手车交易系统 ==========\n";
  std::cout << " 1. 登录\n";
  std::cout << " 2. 注册（买家）\n";
  std::cout << " 0. 退出\n";
  std::cout << "========================================\n";
  std::cout << "选择: ";
  int op = 0;
  std::cin >> op;
  switch (op)
  {
  case 1:
    Login();
    break;
  case 2:
    // TODO 练习：注册一个 buyer，插到 users 链表
    break;
  case 0:
    SaveToFile();
    std::cout << "数据已写回，再见\n";
    exit(0);
  default:
    break;
  }
}

void Menu::ShowBuyerMenu()
{
  std::cout << "\n---- 买家菜单 [" << currentUser->username << "] ----\n";
  std::cout << " 1. 浏览所有待售车\n";
  std::cout << " 2. 按品牌搜索\n";
  std::cout << " 3. 下预订单（入队）\n";
  std::cout << " 4. 查看我的订单\n";
  std::cout << " 0. 注销\n";
  std::cout << "------------------------\n";
  std::cout << "选择: ";
  int op = 0;
  std::cin >> op;
  switch (op)
  {
  case 1:
    // TODO 练习：cars->ListTraverse([](const Car& c){ if (c.status=="待售")
    // c.Print(); });
    break;
  case 2:
    // TODO 练习：输入品牌，遍历 cars 找 brand 匹配
    break;
  case 3:
    // TODO 练习：输入 vin，找到对应 Car，构造 Order 入队
    //   注意：要把 Car.status 改成"已预订"
    break;
  case 4:
    // TODO 练习：遍历 orders 队列，找 buyerId == currentUser->id 的订单
    break;
  case 0:
    currentUser = nullptr;
    break;
  default:
    break;
  }
}

void Menu::ShowSellerMenu()
{
  std::cout << "\n---- 卖家菜单 [" << currentUser->username << "] ----\n";
  std::cout << " 1. 上架车\n";
  std::cout << " 2. 下架车\n";
  std::cout << " 3. 查看我的车\n";
  std::cout << " 4. 查看我的订单\n";
  std::cout << " 0. 注销\n";
  std::cout << "------------------------\n";
  std::cout << "选择: ";
  int op = 0;
  std::cin >> op;
  switch (op)
  {
  case 1:
    // TODO 练习：录入 Car 信息，sellerId = currentUser->id，ListInsert 进 cars
    break;
  case 2:
    // TODO 练习：输入 vin，LocateElem 找节点，ListDelete 删除
    break;
  case 3:
    // TODO 练习：遍历 cars，sellerId 匹配
    break;
  case 4:
    // TODO 练习：遍历 orders，sellerId 匹配
    break;
  case 0:
    currentUser = nullptr;
    break;
  default:
    break;
  }
}

void Menu::ShowAdminMenu()
{
  std::cout << "\n---- 管理员菜单 [admin] ----\n";
  std::cout << " 1. 查看所有用户\n";
  std::cout << " 2. 查看所有车辆\n";
  std::cout << " 3. 处理订单（出队成交）\n";
  std::cout << " 4. 查看订单队列\n";
  std::cout << " 0. 注销\n";
  std::cout << "------------------------\n";
  std::cout << "选择: ";
  int op = 0;
  std::cin >> op;
  switch (op)
  {
  case 1:
    // TODO 练习：users->ListTraverse([](const User& u){ u.Print(); });
    break;
  case 2:
    // TODO 练习：cars->ListTraverse([](const Car& c){ c.Print(); });
    break;
  case 3:
    // TODO 练习：orders->Pop(order)，把对应 Car.status 改成"已售出"
    break;
  case 4:
    // TODO 练习：orders->Traverse([](const Order& o){ o.Print(); });
    break;
  case 0:
    currentUser = nullptr;
    break;
  default:
    break;
  }
}
