/*
给你一支股票价格的数据流。数据流中每一条记录包含一个 时间戳 和该时间点股票对应的 价格 。

每一条记录包含一个时间戳和价格

不巧的是，由于股票市场内在的波动性，股票价格记录可能不是按时间顺序到来的。某些情况下，有的记录可能是错的。如果两个有相同时间戳的记录出现在数据流中，前一条记录视为错误记录，后出现的记录 更正 前一条错误的记录。

如果两个有相同时间戳的记录出现在数据流中，前一条记录视为错误记录，后出现的记录 更正 前一条错误的记录。

请你设计一个算法，实现：

更新 股票在某一时间戳的股票价格，如果有之前同一时间戳的价格，这一操作将 更正 之前的错误价格。
找到当前记录里 最新股票价格 。最新股票价格 定义为时间戳最晚的股票价格。
找到当前记录里股票的 最高价格 。
找到当前记录里股票的 最低价格 。
请你实现 StockPrice 类：

StockPrice() 初始化对象，当前无股票价格记录。
void update(int timestamp, int price) 在时间点 timestamp 更新股票价格为 price 。
int current() 返回股票 最新价格 。  
int maximum() 返回股票 最高价格 。
int minimum() 返回股票 最低价格 。

维护当前股票的最高最低价格
根时间戳返回股票价格, 用map

时间戳从小到达排序直接用map

用大顶堆, 小顶堆分别维护最大值和最小值。但出堆之后需要判定元素是否在map中(有可能已经被Update了堆存储的是之前的元素)
*/
#include <iostream>
#include <vector>
#include <queue>

#include 

using namespace std;

class StockPrice {
public:
    StockPrice() {
        minPrice = -1;
        maxPrice = -1;
    }
    
    void update(int timestamp, int price) {
        if (!stocks.count(timestamp)) { 
            currentPrice = price;
        }
        stocks.insert({timestamp, price});
        minHeap.push({price, timestamp});
        maxHeap.push({price, timestamp});
        
    }
    
    int current() {
        return currentPrice;
    }
    
    int maximum() {
        int p = maxHeap.top();
        while (!stocks.count(p.second)) {
            maxHeap.pop();
            p = maxHeap.top();
        }
        return p.first;
    }
    
    int minimum() {
        int p = minHeap.top();
        while (!stocks.count(p.second)) {
            minHeap.pop();
            p = minHeap.top();
        }
        return p.first;
    }
private:
    int currentPrice;

    int currentTime;

    size_t size;

    map<int, int> stocks;
    priority_queue<pair<int,int>, vector<pair<int, int>>, less<int>> maxHeap;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<int>> minHeap;

};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */