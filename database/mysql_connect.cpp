#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "mysql_connect.h"

/// 初始化 static ConnectionPool
ConnectionPool* ConnectionPool::pool = nullptr;

/// 构造函数, 直接在参数中就根据形参name, pwd等初始化了username, password
ConnectionPool::ConnectionPool(std::string name, std::string pwd, 
    username(name), password(pwd), url(nurl), poolSize(maxSize)) 
{
    /// mysql驱动, 来自cppconn/driver.h
    driver = get_driver_instance();
    initConnectionPool(poolSize/2);
}

ConnectionPool::~ConnectionPool() {
    /// 析构线程池
    destroyPool();
}

/// 线程池大小
Connection::getPoolSize() {
    return conlist.size();
}

/// 向连接池中增加size的连接
int
ConnectionPool::addConn(int size)
{
    /// 向
    for (int i = 0; i < size; i ++) {
        // 创建连接, 调用driver->connect
        Connection* conn = driver->connect(url, usrname, password);
        /// shared_ptr维护连接对象conn, 并加入析构函数
        std::shared_ptr<Connection> sp(conn, 
            [](Connection* conn) {
                delete conn;
            });
        /// 连接加入到connList中
        conList.push_back(std::move(sp));
    }
}

/// 初始化连接池
void 
ConnectionPool::initConnectionPool(int initialSize) {
    /// 初始化连接池, 向里面增加initialSize的连接
    std::lock_guard<std::mutex> locker(lock);
    addConn(initialSize);
}

/// 销毁连接池front位置的连接
void
ConnectionPool::destoryOneConn() {
    /// 拿出头部连接
    std::shared_ptr<Connection>&& sp = std::move(conList.front());
    sp->close();    // Connection调用close()
    --poolsize;
}

/// 只是销毁连接池的所有连接. 连接池没有销毁
void
ConnectionPool::destroyPool() {
    /// 对conList连接池的所有连接, 执行关闭
    for (auto& conn : conList) {
        /// 拿出连接, 执行close()
        std::shared_ptr<Connection>&& sp = std::move(conList.front());
        sp->close();
        --poolsize;
    }
}

/// 从连接池中移除大小为size的连接
void
ConnectionPool::reducePool(int size)
{
    std::lock_guard<std::mutex> locker(lock);
    if (size > poolsize)
        return ;
    for (int i = 0; i < size; i++) {
        destroyOneConn();
    }
    poolSize -= size;
}

/// 得到一个ConnectionPool连接池对象
/// 对象在堆上分配内存, 指针pool是static的(在静态区的指针)
ConnectionPool*
ConnectionPool::getInstance() {
    if (pool == nullptr) {
        /// username(name), password(pwd), url(nurl), poolSize(maxSize)
        pool = new ConnectionPool("root", "root", "tcp://127.0.0.1:3306", 40);
    }
    return pool;
}

// 从conList得到连接
std::shared_ptr<Connection>
ConnectionPool::getConnect()
{
    std::lock_guard<std::mutex> locker(lock);
    std::shared_ptr<Connection> sp = conList.front();
    conList.pop_front();    // 注意移出conList
    return sp;
}

// 归还连接, conList加入该连接
void
ConnectionPool::retConnect(std::shared_ptr<Connection>& ret) {
    std::lock_guard<std::mutex> locker(lock);
    conList.push_back(ret);
}