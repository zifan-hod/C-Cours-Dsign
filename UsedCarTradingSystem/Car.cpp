#include "car.h"

Car::Car() : year(0), mileage(0), price(0.0) {}

Car::Car(const std::string &vin, const std::string &brand)
    : vin(vin), brand(brand), year(0), mileage(0), price(0.0) {}

Car::~Car() {}

// TODO 练习：cout 格式化打印一辆车的所有字段（含 createTime）
//
// 【批注】功能能跑通 ✓ 两个小问题：
//   1. 表头第 8 列写的是"待售/已预订/已售出"，这是该列的【取值举例】，
//      列名本身应该是"状态"，否则表头和下面的数据对不上
//   2. 连续多个 "     " 不统一，列会错位；课设级别够用，想对齐可以用
//      setw(12)（需要 #include <iomanip>）给每列固定宽度
//
// ── 简要笔记：iomanip 和 setw ─────────────────────────────────
//   流（stream）= 数据流动的管道
//     cout 是输出流：数据流向屏幕；cin 是输入流：数据从键盘流入
//   <iomanip> = I/O Manipulators（输入输出操纵符）头文件
//   setw(n) = 给【下一个】输出项分配 n 字符宽度，不够补空格
//     - 只对下一个输出项生效，用完失效（不粘）
//     - 默认右对齐，加 left 变左对齐
//     - 中文字符按字节算（setw(8) = 8 字节）
//   对比当前写法 "     " + vin + "     " + brand：
//     vin 长度不一会导致列错位；setw 每列固定宽度，永远对齐
//   示例：cout << setw(10) << vin << setw(10) << brand << setw(10) << model;
// ──────────────────────────────────────────────────────────────
void Car::Print() const
{
  // TODO:
  cout << "\t车架号     品牌     型号     上牌年份     里程     售价     "
          "卖家ID     待售/已预订/已售出     门店     上架时间"
       << endl;
  cout << "\t" << "     " << vin << "     " << "     " << brand << "     "
       << "     " << model << "     " << "     " << year << "     " << mileage
       << "     " << price << "     " << sellerId << "     " << status
       << "     " << store << "     " << createTime << endl;
}

// TODO 练习：把全部字段序列化成一行字符串，字段之间用冒号 ':' 分隔
//   思路：借助字符串输出流依次写入各字段，字段之间写冒号，最后返回拼成的串
//   约束：字段值本身不能含冒号
//
// 【批注】你这版逻辑【完全正确】，能正常序列化 ✓ 回答你的三个疑问：
//
//   疑问1："约束条件难道要写很多 if-else 检查？"
//     —— 不用写任何检查代码。这个"约束"是【格式约定】，不是函数功能：
//        我们在选分隔符时就知道品牌/门店等数据天然不含冒号，靠录入时
//        大家共同遵守即可。它是写给"读代码的人"看的提醒，不是要程序判断。
//        （真想防御，最多一句检查"拼好后冒号总数是否=9"，没必要。）
//
//   疑问2："感觉写法冗杂，可以怎么优化？"
//     —— 冗杂的根源：to_string 每次把数字变一个新字符串，'+' 每加一段
//        又产生一个临时字符串，10 段要创建十几个临时对象。
//        优化方向：用【字符串输出流 ostringstream】，把字段和冒号依次
//        "流入"同一个流，数字直接流入（不用 to_string），最后一次性
//        取出整串。这只是优化不是 bug，你现在的写法保留对照。
//
// ── 简要笔记：字符串流（sstream）─────────────────────────────
//   流（stream）= 数据流动的管道
//     cout 是输出流：数据流向屏幕
//     ostringstream 也是输出流，但数据流向【内部的字符串缓冲区】
//   ostringstream 用法（#include <sstream>）：
//     ostringstream oss;
//     oss << "VIN001" << ':' << "大众" << ':' << 2020;
//     string s = oss.str();   // s = "VIN001:大众:2020"
//   关键：<< 直接接受各种类型，数字不用 to_string，内部自动转字符
//   .str() 取出整段字符串
//   比用 + 拼接少创建十几个临时对象（性能好、代码简洁）
//
//   istringstream（反过来，FromLine 会用到）：
//     istringstream iss("VIN001 大众 朗逸 2020");
//     iss >> vin >> brand >> model >> year;
//     // >> 自动按空格切分、自动转类型（int 直接读成数字）
// ──────────────────────────────────────────────────────────────
//
//   疑问3【重要·约定冲突】：你在末尾拼了 "\n"。
//     SaveToFile 的计划是"ToLine() 取出一行后，由存盘代码补换行符"。
//        如果 ToLine 自己带 \n，存盘时就会出现两个换行，车辆之间空行。
//        两种风格二选一（推荐 ToLine 不带 \n，让 SaveToFile 统一补），
//        你当前写法先保留，到写 SaveToFile 时会真实看到这个问题。
//
//   另提醒：这里字段的【书写顺序】就是将来 FromLine 的【解析顺序】，
//        两边必须一一对应，错一个位置字段就全错位。
std::string Car::ToLine() const
{
  // TODO:
  // 难点是约束条件不可能很多个if_eles吧，而且感觉现在的写法也不会
  // string str = vin + ":" + brand + ":" + to_string(year) + ":" +
  //              to_string(mileage) + ":" + to_string(price) + ":" + sellerId +
  //              ":" + status + ":" + store + ":" + createTime + "\n";
  ostringstream oss;
  oss << vin << ':' << brand << ':' << model << ':' << year << ':' << mileage
      << ':' << price << ':' << sellerId << ':' << status << ':' << store << ':'
      << createTime;
  // 末尾【不】加 "\n"
  return oss.str();
}

// TODO 练习：按冒号把 line 拆回 10 个字段
//   提示：可以自己写循环找 ':' 的位置并 substr，也可以先把 ':' 全替换成空格
//         再用 istringstream 读取
//
// 【批注】这里是你卡住的地方，先讲清【方向性错误】，再给思路：
//
//   报错原因有两层：
//   1) char com[4096] = ToLine();
//        a. 字符数组不能直接用 std::string 赋值/初始化（两种不同类型，
//           数组只能逐个元素拷）
//        b. 更根本：FromLine 是 static 函数，【没有 this、没有任何对象】，
//           编译器报"没有对象无法调用非静态成员函数 ToLine()"——
//           ToLine 是"把【已存在的车】变成文字"，而 FromLine 的工作是
//           "从文字【造出一辆新车】"，此刻车还不存在，没法调 ToLine。
//   2) 你要解析的文字，就是这个函数的【参数 line】（LoadFromFile 从
//      文件切出来的一行传进来的），不需要、也不应该自己去 ToLine。
//
//  "为什么最后 return Car()？"
//      函数返回类型是 Car，必须交回一辆车。Car() 是当初占位用的【空车】，
//      等于交了张白卷。最终版本应该：造一辆本地新车 → 把解析出的字段
//      逐个填进去 → return 这辆填好的车。
//
// ── 简要笔记：return Car() 空占位 ────────────────────────────
//   函数签名 Car FromLine(...) 要求：无论走哪条分支，必须返回一辆 Car
//   Car() = 调用默认构造函数，造一辆所有字段为初始值的车
//     （vin="", brand="", year=0, ...）——白板车
//   return Car() = 先返回一辆白板车占位，让代码能编译过
//   类比：答应交作业但没写完，先交白纸占位置，等写完再换真作业
//   真正实现完应该是：
//     Car car;          // 造一辆本地新车（在函数内）
//     // ... 解析 line，填字段 ...
//     return car;       // 返回填好的车（不是空车 Car()）
// ──────────────────────────────────────────────────────────────
//
//  正确思路（5 步，代码你自己写）：
//    1. 先造一辆空车：Car car;
//    2. 在【参数 line】里把 10 个字段按 ':' 切成 10 段：
//         方向一：循环查找 ':' 的位置，每找到就把"上一个位置到这里"
//                 之间的子串切出来（查找位置 + 取子串两个操作）
//         方向二：把 line 里每个 ':' 都替换成空格，再用【字符串输入流】
//                 像 cin 一样依次读（注意：字符串字段含空格会被切断，
//                 品牌/门店无空格才适用）
//    3. 第 4、5 段是 int、第 6 段是 double：字符串转数字
//         （输入流读入数字天然就是数值类型；或用 stoi / stod）
//    4. 按 ToLine 的【同样顺序】把 10 段赋给 car 的 10 个字段
//         （字符串字段直接赋，数字字段用转换后的值）
//    5. return car;
//
//   你下面原来的写法保留不动，用来对照"切完的字串必须赋给车的字段，
//   光在 buf 里搬运不会产生 Car 对象"。
Car Car::FromLine(const std::string &line)
{
  // TODO:
  // char buf[4096];
  // char com[4096] = ToLine();
  // int i = 0;
  // int m = 0;
  // // 我的想法是把ToLine()的返回值拿到,然后循环，而且我没懂返回值
  // // 为啥是Car()
  // while (com[i] != '\n')
  // {
  //   buf[m] = com[m];
  //   if (com[i] == ':')
  //     buf[m + 1] = ' ';
  //   m++;
  //   i++;
  // }
  Car cars;
  ostringstream os;

  // start 必须声明在循环【外面】：上一次找到冒号后，下一次从冒号后继续找，
  // 不能每轮都重置为 0（否则永远找到第一个冒号，while(1) 变死循环）
  size_t start = 0;
  while (true)
  {
    size_t pos = line.find(':', start); // 从 start 找下一个冒号
    if (pos == string::npos)
      break;                                      // 找不到冒号了 → 剩下的是最后一个字段
    os << line.substr(start, pos - start) << ' '; // 取出这一字段，冒号换成空格
    start = pos + 1;                              // 下一字段从冒号后一位开始
  }
  os << line.substr(start); // 最后一个字段（后面没有冒号）

  // is 要用 os 拼好的字符串初始化，否则 is 是空流，什么都读不出来
  istringstream is(os.str());
  // >> 按空格切分并自动转类型：字符串直接读，int/double 直接变成数值
  is >> cars.vin >> cars.brand >> cars.model >> cars.year >> cars.mileage >>
      cars.price >> cars.sellerId >> cars.status >> cars.store;
  // 最后一个字段 createTime 内部含空格和冒号：冒号全被换成空格后，
  // "2026-09-20 01:27:37" 变成 4 个 token，拆成 4 段读出再拼回原格式
  // 这一步其实是可以少些的，把前面的Toline的分隔符改成别的，比如“，”这类的
  string datePart, hh, mm, ss;
  is >> datePart >> hh >> mm >> ss;
  cars.createTime = datePart + " " + hh + ":" + mm + ":" + ss;

  return cars;
}

// GetKey：返回唯一标识车架号
std::string Car::GetKey() const { return vin; }
