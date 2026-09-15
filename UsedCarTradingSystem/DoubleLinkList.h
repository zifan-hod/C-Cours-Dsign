#pragma once

#include <iostream>
#include <string>
using namespace std;
// ============================================================================
//  循环双链表（带头节点）模板类 —— 严蔚敏《数据结构》风格
//  练习要点：
//    1. 状态码不要用 #define OK 1;  尾分号会让 return OK; 变成 return 1;;
//       改用 const int，是真正的常量而非文本替换
//    2. 模板类的成员函数实现必须放在头文件里（编译器要看到完整模板才能实例化）
//    3. 循环链表判空：head->next == head（而不是 head->next == nullptr）
//       遍历终止：p != head（而不是 p != nullptr）
//    4. C++ 中 new 出来的对象必须用 delete 释放，不能用 C 的 free
//    5. struct 里写构造函数 + 初始化列表 : 成员(值)
//       好处：new 出来的节点指针默认是 nullptr，避免野指针（未初始化的指针
//       指向随机内存，调试时容易段错误）
//    6. 查找 LocateElem 用 == 运算符，要求 T 类型重载 operator==
//       （例如 Car 按 vin 比较、User 按 id 比较等）
// ============================================================================
const int OK = 1;
const int ERROR = -1;
typedef int Status;

// 双链表节点
//  C++ 里 struct 也能有构造函数，默认成员 public，方便外部访问字段
template <typename T> struct DoubleNode {
  T data;
  DoubleNode<T> *pre;
  DoubleNode<T> *next;

  // 构造函数 + 初始化列表：: 成员(值), 成员(值) {}
  //  不写的话 new 出来的节点 pre/next 是随机值（野指针），调试时容易段错误
  DoubleNode() : pre(nullptr), next(nullptr) {}
  DoubleNode(const T &e) : data(e), pre(nullptr), next(nullptr) {}
};

// 循环双链表（带头节点）
//  空表：head->next == head->pre == head
//  非空：head->next 指向第一个数据节点；尾节点 next 指回 head
template <typename T> class DoubleLinkList {
private:
  DoubleNode<T> *head;

public:
  DoubleLinkList();
  ~DoubleLinkList();

  Status Init();
  Status Destroy();
  Status Clear();

  bool ListEmpty() const;
  int ListLength() const;

  Status GetElem(int i, T &e) const;

  // 查找：用 == 运算符判断相等（T 需要重载 operator==）
  DoubleNode<T> *LocateElem(const T &key) const;

  Status ListInsert(int i, const T &e); // 在第 i 个位置之前插入
  Status ListDelete(int i, T &e);       // 删除第 i 个节点，e 带回值

  void ListTraverse(void (*visit)(const T &)) const;
};

// ============================================================================
//  模板成员函数实现
// ============================================================================

template <typename T> DoubleLinkList<T>::DoubleLinkList() {
  head = new DoubleNode<T>;
  head->next = head;
  head->pre = head;
}

template <typename T> DoubleLinkList<T>::~DoubleLinkList() { Destroy(); }

template <typename T> Status DoubleLinkList<T>::Init() {
  if (head == nullptr)
    head = new DoubleNode<T>;
  head->next = head;
  head->pre = head;
  return OK;
}

template <typename T> Status DoubleLinkList<T>::Destroy() {
  // 循环链表终止条件是回到 head，不是 nullptr
  DoubleNode<T> *p = head->next;
  while (p != head) {
    DoubleNode<T> *q = p; // 先存住当前节点
    p = p->next;          // 再前进
    delete q;             // C++ 用 delete
  }
  delete head;
  head = nullptr;
  return OK;
}

// TODO 练习：照 Destroy 思路写，但最后保留 head，把 head->next / head->pre
// 都指回 head
//
// 【当前写法评价】Destroy()+Init() 逻辑上能跑通：
//   Destroy 删掉所有节点（含 head）并把 head=nullptr；Init 发现 nullptr 又 new
//   一个 head 缺点：head 刚 delete 又 new，等于把地基刨了重浇，多一次内存分配
// 【更优写法（只删数据节点，head 不动）】：
//   DoubleNode<T> *p = head->next;
//   while (p != head) {
//       DoubleNode<T> *q = p;
//       p = p->next;
//       delete q;
//   }
//   head->next = head;
//   head->pre  = head;
//   return OK;
template <typename T> Status DoubleLinkList<T>::Clear() {
  // TODO:
  Destroy();
  Init();
  return OK;
}

// TODO 练习：head->next == head 即空
template <typename T> bool DoubleLinkList<T>::ListEmpty() const {
  // TODO:
  if (head->next == head)
    return true;
  return false;
}

// TODO 练习：从 head->next 数到 head
//
// 【当前写法评价】逻辑能数对（靠 && 的短路求值），但有两个隐患：
//   1. while 条件里塞赋值 p = p->next 很难读，-Wall
//   会警告，建议加括号或干脆不这么写
//   2. return number; 的缩进看着像在 while 里，实际因为循环体没加大括号，
//      它在循环【外面】—— 歪打正着，但容易把自己绕晕
// 【建议标准写法】
//   int number = 0;
//   DoubleNode<T> *p = head->next;       // 直接从第一个数据节点起步
//   while (p != head) {
//       ++number;
//       p = p->next;
//   }
//   return number;
template <typename T> int DoubleLinkList<T>::ListLength() const {
  int number = 0;
  DoubleNode<T> *p = head;

  while (p->next != head &&p = p->next)
    number++;
  // TODO:
  return number;
}

// TODO 练习：定位第 i 个节点 p（从 head->next 走 i-1 步），e = p->data
//   越界（i < 1 或走完到 head 还没到 i）返回 ERROR
//
// 【当前写法评价】正确 ✓
//   q 从 head 出发走 i 步：i=1 落在第 1 个数据节点，i=len 落在尾节点，位置准确
//   i<=0、空表（len=0 时 i>len 拦截）、超长都拦住了
//   小冗余：i<=0 就是 i<1；ListEmpty() 时 len=0，i>len 也会拦截，不影响正确性
template <typename T> Status DoubleLinkList<T>::GetElem(int i, T &e) const {
  // TODO:
  int len = ListLength();
  if (i > len || ListEmpty() || i <= 0)
    return ERROR;
  DoubleNode<T> *q = head;
  for (int m = 0; m < i; m++)
    q = q->next;
  e = q->data;
  return OK;
}

// TODO 练习：从 head->next 遍历到 head，用 p->data == key 比较
//   找到返回节点指针 p，找不到返回 nullptr
//
// 【当前写法评价】正确 ✓
//   空表时 p=head、p->next==head，直接跳过循环返回 nullptr；
//   找到时返回的是节点指针，业务层可以直接改 p->data.xxx，
//   这也是之前删掉 ListUpdate 的原因——拿到指针后修改不需要专门函数
//   提醒：用的时候 T 必须支持 ==，Car/User 里要写 operator==
template <typename T>
DoubleNode<T> *DoubleLinkList<T>::LocateElem(const T &key) const {
  // TODO:
  DoubleNode<T> *p = head;
  while (p->next != head) {
    p = p->next;
    if (p->data == key)
      return p;
  }
  return nullptr;
}

// TODO 练习：定位到第 i-1 个节点 p（即插入位置的前驱）
//   i == 1 时前驱就是 head；否则从 head->next 走 i-2 步
//   越界（i < 1 或前驱走不到）返回 ERROR
//   定位好后改 4 个指针：
//   s->next = p->next;  s->pre = p;
//   p->next->pre = s;   p->next = s;
//
// 【当前写法有 3 个必须修的问题】
//   问题1【边界错误】if (i > ListLength()) 把"表尾追加"也拒绝了：
//     表里有 n 个节点时，合法插入位置是 1..n+1，应改为：
//     if (i < 1 || i > ListLength() + 1) return ERROR;
//   问题2【死循环】while (number < i) { s = s->next; } 里 number 永远是 1：
//     循环体里漏了 ++number;（或 number++;）
//   问题3【语法错误 + 数据丢失】new DoubleNode<T> *p; 不合法：
//     new 的结果必须赋给指针，正确写法是一行：
//     DoubleNode<T> *p = new DoubleNode<T>(e);
//     注意括号里的 e 必须传进去，否则新节点 data 是默认空值，插入了个寂寞
//   下面 4 行指针改接顺序是对的 ✓（p->next 先存住了旧后继），p 修好后不用动
template <typename T> Status DoubleLinkList<T>::ListInsert(int i, const T &e) {
  // TODO:
  if (i > ListLength() + 1 || i < 1)
    return ERROR;
  DoubleNode<T> *s = head;
  int number = 1;
  while (number < i) {
    s = s->next;
    number++;
  }
  // 记住把数据装进去
  DoubleNode<T> *p = new DoubleNode<T>(e);
  // there need't assign nullptr
  p->next = s->next;
  s->next = p;
  p->pre = s;
  p->next->pre = p;
  return OK;
}

// TODO 练习：删除第 i 个节点
//   通用思路 5 步：
//   1) 边界检查：i < 1 || i > ListLength() → return ERROR（空表时
//   len=0，一并拦住） 2) 定位被删节点 p：从 head->next 出发，循环走 i-1 步
//      （i=1 时一步不走，p 就是第一个数据节点）
//   3) 先存数据：e = p->data;        ← 必须在 delete 之前，否则数据跟着内存没了
//   4) 双向摘链（顺序无所谓，两句都在 delete 前即可）：
//        p->pre->next = p->next;
//        p->next->pre = p->pre;
//   5) delete p; return OK;
//   画图提示：pre 链和 next 链都要改，只改一条会断链
//
// 【当前写法有 2 个必须修的逻辑 bug】
//   bug1【e 从头到尾没赋值】函数签名 ListDelete(int i, T &e) 的本意是
//      "删除前把数据拷给 e 带回给调用者"。你的代码全程没写 e = ...，
//      调用者拿到的 e 还是进函数前的旧值，等于白调一次
//      修法：在 delete 之前加 e = (被删节点)->data;
//   bug2【delete s->next 删的是错节点】s 全程 = head 没动过，
//      所以 s->next 永远是 head 的下一个。但你在 delete 前已经改了指针
//      （p->next = p->next->next），这时 head->next 已指向新第一节点，
//      你 delete 掉的反而是新第一节点，被删节点漏在网上 → 内存泄漏 + 链表损坏
//      修法：被删节点还连在链上时，先用临时指针存下来：
//        DoubleNode<T> *del = p->next;   // 先存住要删的节点
//        e = del->data;                   // 先取数据
//        p->next = del->next;             // 改 next 链
//        del->next->pre = p;              // 改 pre 链
//        delete del;                      // 最后 delete 临时指针
//   【设计建议】i == 1 的特殊分支其实多余：通用分支里 p 从 head 走 i-1 步，
//      i=1 时一步不走 p 就是 head，天然处理。两套逻辑反而增加维护负担
template <typename T> Status DoubleLinkList<T>::ListDelete(int i, T &e) {
  // TODO:
  if (i < 1 || i > ListLength())
    return ERROR;
  DoubleNode<T> *p = head;
  DoubleNode<T> *s = head;
  if (i == 1) {
    p->next->next->pre = p;
    p->next = p->next->next;
    delete s->next;
    return OK;
  }
  int step = 1;
  while (step < i) {
    p = p->next;
    step++;
  }
  p->next->next->pre = p;
  p->next = p->next->next;
  delete s->next;
  return OK;
}

// TODO 练习：从 head->next 走到 head，每个节点调 visit(p->data)
//
// 【当前写法有 2 个必须修的问题】
//   问题1【语法错】cout / endl 没加 std:: 前缀，编译报"尚未声明"
//      这个头文件里没有 using namespace std;，必须写全 std::cout / std::endl
//      修法：要么 cout 前加 std::，要么文件顶部加 using namespace std;
//            （教学项目里二选一即可，加 using 更省事）
//   问题2【设计错】直接写死 cout << p->data，把函数参数 visit 晾在一边不用
//      带来三个问题：
//        a) 模板装 Car 时编不过——Car 没有 operator<<，cout 不知道怎么打印
//        b) 失去"通用遍历"意义：以后想存盘/统计时不能复用这个函数
//        c) visit 参数白拿
//      修法：函数体只写 visit(p->data); 把"做什么"的决定权交给调用者
//      调用方示例（Menu 里）：
//        cars->ListTraverse([](const Car& c){ if (c.status=="待售") c.Print();
//        });
template <typename T>
void DoubleLinkList<T>::ListTraverse(void (*visit)(const T &)) const {
  // TODO:
  DoubleNode<T> *p = head;
  while (p->next != head) {
    p = p->next;
    cout << p->data << endl;
  }
}
