#include "Menu.h"
#include <clocale>   // std::setlocale

int main()
{
    // 让 mbrtowc/wcwidth 按当前 locale（UTF-8）解析多字节字符，
    // 这样 printField 才能正确计算中文的显示宽度。
    std::setlocale(LC_CTYPE, "");

    Menu m;
    m.Run();
    return 0;
}
