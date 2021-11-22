#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "mysql_connection_sp.h"

/// 初始化 static对象 ConnectionPool::pool
/// ConnectionPool* 
///ConnectionPool::pool = nullptr;
ConnectionPool* ConnectionPool::pool = nullptr;

/// 构造函数, 直接在参数中就根据形参name, pwd等初始化了username, password
ConnectionPool::ConnectionPool(std::string name, std::string pwd, std::string nurl, int maxSize):
    username(name), password(pwd), url(nurl), poolCapacity(0)
{
    /// mysql驱动, 来自cppconn/driver.h, 获取实例Driver* driver
    driver = get_driver_instance();
    /// 初始化连接池, 预先加入poolSize的连接
    initConnectionPool(maxSize/2);
}

ConnectionPool::~ConnectionPool() {
    /// 析构线程池
    destroyPool();
}

/// 线程池大小
int ConnectionPool::getPoolSize() {
    return connList.size();
}

/// 向连接池中增加size的连接, 不会改变poolSize
void ConnectionPool::addConn(int size)
{
    for (int i = 0; i < size; i ++) {
        // 创建连接, 调用driver->connect(), 返回Connection
        Connection* conn = driver->connect(url, username, password);
        /// shared_ptr维护连接对象conn, 并加入析构函数。一般的,conn永远不会被析构, 用完了会归还给连接池
        /// 
        std::shared_ptr<Connection> spConn(conn, 
            [](Connection* conn) {
                delete conn;
            });
        /// 连接以右值形式加入到connList中
        connList.push_back(std::move(spConn));
        poolCapacity++;
    }
}

/// 初始化连接池, 预先加入指定大小的连接
void ConnectionPool::initConnectionPool(int initialSize) {
    /// 初始化连接池, 向里面增加initialSize的连接
    std::lock_guard<std::mutex> locker(lock);
    addConn(initialSize);
}

/// 销毁连接池front队头位置的连接
void ConnectionPool::destroyOneConn() {
    /// 拿出头部连接
    std::shared_ptr<Connection>& spConn = connList.front();
    spConn->close();    // Connection调用close()
    ///spConn.reset();
    --poolCapacity;
}

/// 只是销毁连接池的所有连接. 连接池没有销毁
void ConnectionPool::destroyPool() {
    /// 对conList连接池的所有连接, 从connList.front开始
    for (auto& conn : connList) {
        /// 拿出连接, 执行close()
        std::shared_ptr<Connection>& spConn = connList.front();
        spConn->close();    /// 关闭连接
        ///spConn.reset();    /// shared_ptr计数减一, 调用注册的析构函数析构Connection对象
        /// unique_ptr离开作用域自动释放
        --poolCapacity;
    }
}

/// 从连接池中移除大小为size的连接, 注意移除连接导致poolSize的变化因为不会还回来; 用户申请数据连接不会导致poolSize变化,因为会还回来
void ConnectionPool::reducePool(int size)
{
    std::lock_guard<std::mutex> locker(lock);
    if (size > poolCapacity)
        return; /// size有问题, 不进行任何操作
    for (int i = 0; i < size; i++) {
        destroyOneConn();
    }
    poolCapacity -= size;
}

/// 得到一个ConnectionPool连接池对象
/// 对象在堆上分配内存, 指针pool是static的(在静态区的指针)
ConnectionPool* ConnectionPool::getInstance() {
    if (pool == nullptr) {
        /// username(name), password(pwd), url(nurl), poolSize(maxSize)
        pool = new ConnectionPool("root", "root", "tcp://127.0.0.1:3306", 40);
    }
    return pool;
}

// 从conList中得到一个连接
std::shared_ptr<Connection>
ConnectionPool::getConn()
{
    std::lock_guard<std::mutex> locker(lock);
    if (connList.size() <= 0){
        addConn(poolCapacity/2);  /// 增加1/2的容量
    } /// 容量不够

    ///std::shared_ptr<Connection> spConn = connList.front();
    std::shared_ptr<Connection> spConn = std::move(connList.front());
    connList.pop_front();    /// 连接移出连接池
    return spConn;
}

// 归还连接到连接池, connList加入归还的连接
void ConnectionPool::retConn(std::shared_ptr<Connection>&& ret) {
    std::lock_guard<std::mutex> locker(lock);
    connList.push_back(std::move(ret));
}