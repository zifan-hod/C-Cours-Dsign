









#include <iostream>
#include "DoubleLinkList.h"

using namespace std;



void PrintInt(const int &x)
{
    cout << "[visit] " << x << endl;
}


void Split(const string &title)
{
    cout << "\n========== " << title << " ==========" << endl;
}

int main()
{
    DoubleLinkList<int> L;


    Split("1. 空表测试");
    cout << "ListEmpty() 期望=1 实际=" << L.ListEmpty() << endl;
    cout << "ListLength() 期望=0 实际=" << L.ListLength() << endl;


    Split("2. 插入 10 20 30（尾插）");
    L.ListInsert(1, 10);
    L.ListInsert(2, 20);
    L.ListInsert(3, 30);
    cout << "ListLength() 期望=3 实际=" << L.ListLength() << endl;
    cout << "ListEmpty() 期望=0 实际=" << L.ListEmpty() << endl;
    cout << "遍历（期望依次看到 [visit] 10 20 30）：" << endl;
    L.ListTraverse(PrintInt);


    Split("3. 头插 5（位置1）、中间插 15（位置3）");
    L.ListInsert(1, 5);
    L.ListInsert(3, 15);
    cout << "现在链表期望: 5 10 15 20 30" << endl;
    L.ListTraverse(PrintInt);
    cout << "ListLength() 期望=5 实际=" << L.ListLength() << endl;


    Split("4. GetElem 测试");
    int e = -999;
    L.GetElem(1, e);
    cout << "GetElem(1) 期望=5  实际=" << e << endl;
    L.GetElem(3, e);
    cout << "GetElem(3) 期望=15 实际=" << e << endl;
    L.GetElem(5, e);
    cout << "GetElem(5) 期望=30 实际=" << e << endl;
    cout << "GetElem(0) 期望返回 ERROR(-1) 实际=" << L.GetElem(0, e) << endl;
    cout << "GetElem(99) 期望返回 ERROR(-1) 实际=" << L.GetElem(99, e) << endl;


    Split("5. LocateElem 测试");
    DoubleNode<int> *p = L.LocateElem(20);
    cout << "查找 20 期望=非空 实际=" << (p != nullptr ? "找到" : "没找到") << endl;
    p = L.LocateElem(999);
    cout << "查找 999 期望=没找到 实际=" << (p != nullptr ? "找到(错!)" : "没找到") << endl;


    Split("6. ListDelete 测试（当前链表: 5 10 15 20 30）");


    e = -999;
    int ret = L.ListDelete(3, e);
    cout << "删位置3: 返回值期望=1 实际=" << ret
         << " | e 期望=15 实际=" << e << endl;
    cout << "剩余链表期望: 5 10 20 30" << endl;
    L.ListTraverse(PrintInt);
    cout << "长度期望=4 实际=" << L.ListLength() << endl;


    e = -999;
    ret = L.ListDelete(1, e);
    cout << "\n删位置1: 返回值期望=1 实际=" << ret
         << " | e 期望=5 实际=" << e << endl;
    cout << "剩余链表期望: 10 20 30" << endl;
    L.ListTraverse(PrintInt);
    cout << "长度期望=3 实际=" << L.ListLength() << endl;


    e = -999;
    ret = L.ListDelete(3, e);
    cout << "\n删位置3(尾): 返回值期望=1 实际=" << ret
         << " | e 期望=30 实际=" << e << endl;
    cout << "剩余链表期望: 10 20" << endl;
    L.ListTraverse(PrintInt);
    cout << "长度期望=2 实际=" << L.ListLength() << endl;


    e = -999;
    L.ListDelete(1, e);
    L.ListDelete(1, e);
    cout << "\n连续删光后，ListEmpty() 期望=1 实际=" << L.ListEmpty() << endl;
    cout << "空表再删 期望返回 ERROR(-1) 实际=" << L.ListDelete(1, e) << endl;


    Split("7. Clear 测试");
    L.ListInsert(1, 100);
    L.ListInsert(2, 200);
    cout << "插入2个后长度 期望=2 实际=" << L.ListLength() << endl;
    L.Clear();
    cout << "Clear后 ListEmpty 期望=1 实际=" << L.ListEmpty() << endl;
    cout << "Clear后长度 期望=0 实际=" << L.ListLength() << endl;

    L.ListInsert(1, 777);
    cout << "Clear后再插入777，GetElem(1) 测试：";
    L.GetElem(1, e);
    cout << "期望=777 实际=" << e << endl;


    Split("8. 插入边界测试");
    L.Clear();
    cout << "空表插位置0  期望ERROR 实际=" << L.ListInsert(0, 1) << endl;
    cout << "空表插位置2  期望ERROR 实际=" << L.ListInsert(2, 1) << endl;
    cout << "空表插位置1  期望OK(1) 实际=" << L.ListInsert(1, 1) << endl;
    cout << "1个元素插位置3 期望ERROR 实际=" << L.ListInsert(3, 2) << endl;
    cout << "1个元素插位置2 期望OK(1) 实际=" << L.ListInsert(2, 2) << endl;

    cout << "\n========== 测试结束 ==========" << endl;
    return 0;
}
