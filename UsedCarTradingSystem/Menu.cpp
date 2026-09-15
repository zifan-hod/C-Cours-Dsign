#include "Menu.h"
#include <fstream>
#include <sstream>
#include <ctime>

Menu::Menu()
{
    users = new DoubleLinkList<User>;
    cars  = new DoubleLinkList<Car>;
    orders = new CirQueue<Order>;
    currentUser = nullptr;
}

Menu::~Menu()
{
    // TODO 练习：delete users / cars / orders
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
    std::cout << "再见，数据已写回 data/ 目录\n";
}

// ============================================================================
//  文件读写：用 std::fstream 落盘，文件放 data/ 子目录
//  数据格式：每行一个对象，字段用空格分隔
// ============================================================================
void Menu::LoadFromFile()
{
    // TODO 练习：
    //   std::ifstream fin("data/users.txt");
    //   if (!fin) return;   // 文件不存在，跳过
    //   string line;
    //   while (getline(fin, line))
    //       users->ListInsert(users->ListLength()+1, User::FromLine(line));
    //   同理处理 cars.txt
    //
    //   orders 是循环队列：读完后用 Push 入队
}

void Menu::SaveToFile()
{
    // TODO 练习：
    //   std::ofstream fout("data/users.txt");
    //   遍历 users，每行写 u.ToLine()
    //   同理处理 cars.txt 和 orders.txt
}

void Menu::InitDefaultAdmin()
{
    // TODO 练习：构造一个 User("U001", "admin", "admin")，密码 "123456"，role "admin"
    //   users->ListInsert(1, adminUser);
    //   也可以同时塞一两个假用户、几辆假车，方便演示
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
        case 1: Login(); break;
        case 2:
            // TODO 练习：注册一个 buyer，插到 users 链表
            break;
        case 0:
            SaveToFile();
            std::cout << "数据已写回，再见\n";
            exit(0);
        default: break;
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
            // TODO 练习：cars->ListTraverse([](const Car& c){ if (c.status=="待售") c.Print(); });
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
        case 0: currentUser = nullptr; break;
        default: break;
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
        case 0: currentUser = nullptr; break;
        default: break;
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
        case 0: currentUser = nullptr; break;
        default: break;
    }
}
