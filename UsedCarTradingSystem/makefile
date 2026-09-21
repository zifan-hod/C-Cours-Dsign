# ============================================================================
#  makefile —— 按简单教学风格重写（不用 $@ $< 等自动化变量）
# ============================================================================

# 编译器与编译选项（把 g++ 命令里反复出现的选项提成变量）
CXX      = g++
CXXFLAGS = -std=c++11 -g -Wall

# 头文件目录，方便以后扩展（当前就是当前目录，可省略 -I.）
INCLUDEDIR = -I.

# all 是个伪目标：敲 make 时默认构建它，它会触发下面所有目标
all: used_car_system

# 一步直接编译可执行文件（单条命令搞定，不用先编 .o 再链接）
# 如果项目文件不多，这种写法最省事
used_car_system: main.cpp Menu.cpp Car.cpp User.cpp Order.cpp Record.cpp
	g++ -o used_car_system main.cpp Menu.cpp Car.cpp User.cpp Order.cpp Record.cpp $(CXXFLAGS) $(INCLUDEDIR)
#这样可以吗
#used_car_system: main.cpp Menu.cpp Car.cpp User.cpp Order.cpp
#	g++ -o $@ $^ $(CXXFLAGS) $(INCLUDEDIR)

# 如果只想单独编译某个 .o（调试用），可以保留这几条
# 但日常用上面那条就够
main.o: main.cpp
	g++ -c main.cpp $(CXXFLAGS) $(INCLUDEDIR)

Menu.o: Menu.cpp
	g++ -c Menu.cpp $(CXXFLAGS) $(INCLUDEDIR)

Car.o: Car.cpp
	g++ -c Car.cpp $(CXXFLAGS) $(INCLUDEDIR)

User.o: User.cpp
	g++ -c User.cpp $(CXXFLAGS) $(INCLUDEDIR)

Order.o: Order.cpp
	g++ -c Order.cpp $(CXXFLAGS) $(INCLUDEDIR)

# 链表测试程序：敲 make test_linklist 编译，./test_linklist 运行
test_linklist: test_linklist.cpp DoubleLinkList.h
	g++ -o test_linklist test_linklist.cpp $(CXXFLAGS) $(INCLUDEDIR)

clean:
	rm -f used_car_system test_linklist main.o Menu.o Car.o User.o Order.o

.PHONY: all clean
