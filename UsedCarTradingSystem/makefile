# ============================================================================
#  makefile —— V1 规范化版本
#  目标：
#    make            → 默认编 debug 版（带 -g，方便 gdb）
#    make debug      → 同上
#    make release    → 编优化版（-O2，无调试信息）
#    make clean      → 删可执行文件和 .o
#    make test       → 编链表测试程序
# ============================================================================

# ---------- 基础变量 ----------
CXX        = g++                       # 编译器
INCLUDES   = -I.                       # 头文件搜索路径

# 所有目标共用的编译选项
#   -std=c++11    C++ 标准
#   -Wall         开常规警告
#   -Wextra       开更多警告（比 -Wall 更严，比如未用参数、有符号无符号比较）
CXXFLAGS_COMMON = -std=c++11 -Wall -Wextra $(INCLUDES)

# debug 版：-g 生成调试信息，-O0 不优化（gdb 单步最准）
CXXFLAGS_DEBUG   = $(CXXFLAGS_COMMON) -g -O0

# release 版：-O2 优化，去掉 -g 体积小、跑得快
CXXFLAGS_RELEASE = $(CXXFLAGS_COMMON) -O2

# ---------- 源文件清单 ----------
SRCS = main.cpp Menu.cpp Car.cpp User.cpp Order.cpp Record.cpp

# 头文件清单（任何一个 .h 改了，所有 .cpp 都要重编，因为模板在头文件里）
HEADERS = DoubleLinkList.h CirQueue.h Record.h car.h User.h Order.h Menu.h

# 目标可执行文件名
TARGET = used_car_system

# ---------- 伪目标声明 ----------
# .PHONY 告诉 make：这些名字不是文件，只是动作名，避免和同名文件冲突
.PHONY: all debug release clean test

# ---------- 默认目标 ----------
# 敲 make 不带参数时执行第一个目标，这里默认 debug
all: debug

# ---------- debug 版（默认） ----------
debug: $(SRCS) $(HEADERS)
	$(CXX) -o $(TARGET) $(SRCS) $(CXXFLAGS_DEBUG)

# ---------- release 版 ----------
release: $(SRCS) $(HEADERS)
	$(CXX) -o $(TARGET) $(SRCS) $(CXXFLAGS_RELEASE)

# ---------- 链表测试程序 ----------
test: test_linklist.cpp DoubleLinkList.h
	$(CXX) -o test_linklist test_linklist.cpp $(CXXFLAGS_DEBUG)

# ---------- 清理 ----------
# rm -f 不报错（文件不存在也不报错）
clean:
	rm -f $(TARGET) test_linklist *.o
