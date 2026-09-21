#pragma once
#include <iostream>
#include "DoubleLinkList.h"
#include "CirQueue.h"
#include "car.h"
#include "User.h"
#include "Order.h"

// ============================================================================
//  Menu 菜单类 —— 整个系统的"调度中心"
//  持有三个数据结构：
//    DoubleLinkList<User>  users    所有用户
//    DoubleLinkList<Car>   cars     所有车辆
//    CirQueue<Order>       orders   待处理订单队列
//  Run() 是主循环：加载文件 → 登录 → 按角色分发子菜单 → 退出写回
// ============================================================================
class Menu
{
private:
    DoubleLinkList<User>  *users;
    DoubleLinkList<Car>   *cars;
    CirQueue<Order>       *orders;
    User                  *currentUser;   // 当前登录用户，未登录时为 nullptr

public:
    Menu();
    ~Menu();

    // 主流程
    void Run();
    void LoadFromFile();            // 启动时读当前目录的 users.txt / cars.txt / orders.txt
    void SaveToFile();             // 退出时写回三个文件（当前目录）
    void InitDefaultAdmin();        // 首次启动无 users.txt 时初始化 admin / 123456
    bool Login();                   // 登录流程，成功后 currentUser 设置好

    // 角色菜单
    void ShowLoginMenu();           // 未登录主菜单
    void ShowBuyerMenu();           // 买家菜单
    void ShowSellerMenu();          // 卖家菜单
    void ShowAdminMenu();           // 管理员菜单
};
