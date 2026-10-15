#pragma once

#include <iostream>
#include <string>
#include <clocale> // std::setlocale
#include <cwchar>  // std::mbrtowc, std::mbstate_t, ::wcwidth

// ============================================================================
//  终端对齐辅助函数
//  中文/全角字符在终端里占 2 列，ASCII 占 1 列。
//  setw() 按字符数填充会错位，所以用 wcwidth() 算"显示宽度"再补空格。
//  依赖：程序启动时调用 std::setlocale(LC_CTYPE, "") 让 mbrtowc 按当前
//        locale（UTF-8）解析多字节字符。
// ============================================================================
// 处理流程
// 先分析数据类型，是纯英文数字编码，还是除此以外还有别的类型
// （对了还要分析运行平台和使用的编程语言）
// 而今天我们遇到就中英问题，这里我们的编程语言是C++但是，我们需要知道的是
// 我们最开始使用的方法是用C++内置的setw()这个函数的本质，是设定字符长度
// 而我们在liunx的终端的呈现的方式是用的按列的方式来判断的，但是这里我们就涉及
// 到了ascll码，unicode码这些的区别了，在utf-8下一个中文字符占2字节这里我们
// 就出现问题了，假设我要表示“李媛媛”这个，在liunx下，显示的就是6个字节，也就是
// 它这里有6列，而我们的setw()这个函数，显示的只是3个宽度，然后这里明显就产生了
// 一个矛盾，而这样不具一个普适性，为了方便我们的可移植性，我决定写一个封装函数
// 主要是分成两个方向，一个是啥呢，先计算字符串在特定的编码模式下，显示的实际宽度
// 另一个就是通过你设置目标宽度来平衡，就是目标宽度减去实际宽度，以此来确定空格的数量
// 但是我们在实际操作的时候，发现一个问题，就是还是出现错位，经分析我们知道是终端宽度
// 的问题，通过tput cols来解决
// 计算字符串的显示宽度；遇到非法/不完整多字节字符返回 -1
inline int displayWidth(const std::string &str)
{
    std::mbstate_t state{};
    // 这里的
    const char *p = str.c_str();
    // 这里让string转换成char *
    // 使它指向字符串的刚开始，因为，每一个字符也有以存储的位置因为，计算机里面
    // 一个字符（ascll码里面）都是一个字节
    int width = 0;
    // 这里记录实际字符的宽度在终端中的
    while (*p != '\0')
    {
        wchar_t wc;
        size_t len = std::mbrtowc(&wc, p, MB_CUR_MAX, &state);
        // 求的是转换后的宽字符，len消耗的字节
        if (len == static_cast<size_t>(-1) || len == static_cast<size_t>(-2))
        //(-1)读取失败，-2不足以完成一个多字节字符的转换
        {
            return -1; // 非法或不完整的多字节字符
        }
        if (len == 0)
        {
            break;
        }

        int w = ::wcwidth(wc);
        // 用来判断一个宽字符通常占据多少个终端列
        if (w < 0)
        {
            return -1; // 不可打印字符
        }
        width += w;
        p += len;
    }
    return width;
}

// 左对齐打印：输出 str 后补空格到 targetWidth 个显示列
inline void printField(const std::string &str, int targetWidth)
{
    int width = displayWidth(str);
    if (width < 0)
    {
        std::cout << str; // 解析失败就原样输出，不补空格
        return;
    }
    std::cout << str;
    if (width < targetWidth)
    {
        std::cout << std::string(targetWidth - width, ' ');
    }
}

// ============================================================================
//  Record 记录 —— 抽象基类
//  Car / User / Order 都继承它，统一接口，练习虚函数与多态
//
//  学习要点：
//    1. virtual 关键字 + 末尾 = 0 表示"纯虚函数"：
//       基类不给实现，子类【必须】重写，否则子类也不能创建对象
//    2. 含有纯虚函数的类叫"抽象类"，不能直接 new Record，但可以定义
//       Record* 指针指向子类对象 —— 多态就靠它
//    3. 虚析构函数：基类 delete 子类对象时能正确调子类析构，防止内存泄漏
//    4. override 写在子类声明后，让编译器帮忙检查"是否真的重写了父类虚函数"
// ============================================================================
class Record
{
public:
    virtual ~Record() {} // 虚析构：基类必备

    virtual void Print() const = 0;         // 纯虚：打印自身
    virtual std::string ToLine() const = 0; // 纯虚：序列化为文件一行
    virtual std::string GetKey() const = 0; // 纯虚：返回唯一标识
};

// 时间工具函数：返回 "YYYY-MM-DD HH:MM:SS" 格式的当前时间
// Car 上架、Order 下单时调用
std::string GetNowTime();
