//
// Created by Administrator on 25-5-11.
//

#pragma once
#include <cstdint>

template <typename T, uint32_t Size>
class StaticQueue {
private:
    T buffer[Size];          // 静态数组存储队列元素
    uint32_t front;          // 队列头部索引
    uint32_t rear;           // 队列尾部索引
    uint32_t count;          // 当前元素数量
    const uint32_t maxSize;  // 队列最大容量

public:
    StaticQueue() : front(0), rear(0), count(0), maxSize(Size) {}

    // 入队操作
    bool enqueue(const T& item) {
        if (isFull()) {
            return false;  // 队列满
        }
        buffer[rear] = item;
        rear = (rear + 1) % maxSize;  // 循环队列
        count++;
        return true;
    }

    // 出队操作
    bool dequeue(T& item) {
        if (isEmpty()) {
            return false;  // 队列空
        }
        item = buffer[front];
        front = (front + 1) % maxSize;  // 循环队列
        count--;
        return true;
    }

    // 获取队列头部元素（不移除）
    bool peek(T& item) const {
        if (isEmpty()) {
            return false;  // 队列空
        }
        item = buffer[front];
        return true;
    }

    // 检查队列是否为空
    bool isEmpty() const {
        return count == 0;
    }

    // 检查队列是否已满
    bool isFull() const {
        return count == maxSize;
    }

    // 获取当前元素数量
    uint32_t size() const {
        return count;
    }

    // 获取队列最大容量
    uint32_t capacity() const {
        return maxSize;
    }
};

extern StaticQueue<uint8_t, 50> pump_queue;
extern StaticQueue<uint8_t, 50> valve_queue;