#ifndef _MYSQL_CONNECTION_
#define _MYSQL_CONNECTION_

// STL
#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <functional>

/// mysql driver
#include <mysql_driver.h>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <exception>

#include <mutex>

using namespace sql;

/// 作为删除器的参数, std::function<void<Connection*>>
using delFunc = std::function<void(Connection*)>;

/// Connection析构器
//auto delInvmt = [](Connection* conn) {
//    delete conn;
//};

/// 约定, 函数中Conn表示connection连接
/// ConnectionPool表示连接池

class ConnectionPool {
public:
    /// static 单例模式, 这样通过类名即可以调用getInstance获取对象, 也就是ConnectionPool::getInstance
    static ConnectionPool* getInstance();
    /// 从连接池中得到一个连接
    auto getConn() -> std::unique_ptr<Connection,delFunc>;
    /// 将ret连接归还到连接池中
    auto retConn(std::unique_ptr<Connection, delFunc>&& ret) -> void;

    /// 连接池的大小
    auto getPoolSize() -> int;
    ~ConnectionPool();

private:
    /// 构造ConnectionPool
    ConnectionPool(std::string name, std::string pwd, std::string nurl, int maxSize);
    /// 初始化连接池
    auto initConnectionPool(int initialSize) -> void;
    /// 销毁连接池
    auto destroyPool() -> void;
    /// 销毁一个连接
    auto destroyOneConn() -> void;
    /// 扩大数据库连接池
    auto expandPool(int size) -> void;
    auto reducePool(int size) -> void;
    /// 增加连接
    auto addConn(int size)-> void;

private:
    std::string username;
    std::string password;
    std::string url;
    int poolCapacity;

    /// 存放连接, 用std::list链表, 使用相当于队列, 队头出, 队尾进入
    /// std::list<std::shared_ptr<Connection>> connList;

    /// 或许unique_ptr更好些
    std::list<std::unique_ptr<Connection, delFunc>> connList;
    /// static维护的自身对象
    static ConnectionPool* pool;    // 连接池对象, static
    
    std::mutex lock;
    Driver* driver; // mysql driver, 来自<cppconn/driver.h>
};

#endif