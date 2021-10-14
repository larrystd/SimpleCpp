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
using delFunc = std::function<void(Connection*)>;

class ConnectionPool {
public:
    /// static 单例模式, 这样通过类名即可以调用getInstance获取对象
    static ConnectionPool* getInstance();
    // 获得一条连接, ->这里声明函数返回值为std::shared_ptr<Connection>
    auto getConnect() -> std::shared_ptr<Connection>;
    // 归还连接
    auto retConnect(std::shared_ptr<Connection>& ret) -> void;

    // get size
    auto getPoolSize() -> int;
    ~ConnectionPool();

private:
    /// 构造ConnectionPool
    ConnectionPool(std::string name, std::string pwd, std::string nurl, int maxSize);
    /// 初始化连接池
    auto initConnectPool(int initialSize) -> void;
    /// 销毁连接池
    auto destroyPool() -> void;
    /// 销毁一个连接
    auto destroyOneConn() -> void;
    /// 扩大数据库连接池
    auto expandPool(int size) -> void;
    auto reducePool(int size) -> void;
    /// 增加连接
    auto addConn(int size)-> void;

    std::string username;
    std::string password;
    std::string url;
    int poolSize;

    /// 存放连接, 用std::list链表
    std::list<std::shared_ptr<Connection>> conlist;
    /// static维护的自身对象
    static ConnectionPool* pool;    // 连接池对象
    
    std::mutex lock;
    Driver* driver; // mysql driver
}

#endifW