#pragma once
#include "DoubleLinkList.h"   // 复用 Status / OK / ERROR
#include <iostream>

// ============================================================================
//  循环队列（模板类）—— 装待处理订单
//  存储结构：固定容量数组 + front/rear 两个下标
//  判空：rear == front
//  判满：(rear + 1) % MAX == front  ← 牺牲一个单元区分空满
//  长度：(rear - front + MAX) % MAX
// ============================================================================
const int MAX_QUEUE_SIZE = 100;

template <typename T>
class CirQueue
{
private:
    T   *base;
    int  front;
    int  rear;

public:
    CirQueue();
    ~CirQueue();

    bool Empty() const;
    bool Full()  const;
    int  Length() const;

    Status Push(const T &e);   // 入队
    Status Pop(T &e);           // 出队
    T      Front() const;       // 取队头（不出队）

    void   Traverse(void (*visit)(const T &)) const;
};

// ============================================================================
//  模板成员函数实现
// ============================================================================
template <typename T>
CirQueue<T>::CirQueue()
{
    base  = new T[MAX_QUEUE_SIZE];
    front = 0;
    rear  = 0;
}

template <typename T>
CirQueue<T>::~CirQueue()
{
    delete[] base;
    base = nullptr;
}

template <typename T>
bool CirQueue<T>::Empty() const
{
    return rear == front;
}

template <typename T>
bool CirQueue<T>::Full() const
{
    return (rear + 1) % MAX_QUEUE_SIZE == front;
}

template <typename T>
int CirQueue<T>::Length() const
{
    return (rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

template <typename T>
Status CirQueue<T>::Push(const T &e)
{
    if (Full()) return ERROR;
    base[rear] = e;
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    return OK;
}

// TODO 练习：先判空，取 base[front]，front = (front+1) % MAX，e 带回值
template <typename T>
Status CirQueue<T>::Pop(T &e)
{
    // TODO:
    
    return ERROR;
}

// TODO 练习：判空后返回 base[front]
template <typename T>
T CirQueue<T>::Front() const
{
    // TODO:
    return T();
}

// TODO 练习：从 front 走 Length() 步，每步调 visit，下标取模
template <typename T>
void CirQueue<T>::Traverse(void (*visit)(const T &)) const
{
    // TODO:
}
