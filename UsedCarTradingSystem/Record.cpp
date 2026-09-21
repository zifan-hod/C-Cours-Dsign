#include "Record.h"
#include <cstdio>
#include <time.h>
using namespace std;
// ============================================================================
//  GetNowTime —— TODO 练习
//
//  目标：返回 "YYYY-MM-DD HH:MM:SS" 格式的当前时间字符串
//  思路（三步）：
//    1. 取得当前系统时间（秒数）
//    2. 把秒数转换为"本地时间"结构体（含年、月、日、时、分、秒）
//    3. 按目标格式拼接成字符串返回；月、日、时、分、秒不足两位时前面补 0
//
//  需要的头文件已在本文件顶部包含
// ============================================================================
std::string GetNowTime()
{
    // TODO:
    time_t now = time(0);
    tm tmnow;
    localtime_r(&now, &tmnow);
    char stime[20];
    snprintf(stime, sizeof(stime), "%04d-%02d-%02d %02d:%02d:%02d", tmnow.tm_year + 1900,
             tmnow.tm_mon + 1, tmnow.tm_mday, tmnow.tm_hour, tmnow.tm_min,
             tmnow.tm_sec);

    return string(stime);
    // 这里再返回的时候还是用string()这样的形式，因为，可以直接把char[]转化为string类型
    // 更符合C++写法方便
}
