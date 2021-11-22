#include <cstdio>
#include <cstdlib>
#include <cassert>

// #include "mysql_connection_up.h"
#include "mysql_connection_sp.h"
#include <unistd.h>
#include <memory>

/// getInstance()是static静态方法, 返回一个数据库连接池对象指针
/// g++ -o test mysql_test.cpp mysql_connect.cpp  -I . -lmysqlcppconn
ConnectionPool* pool = ConnectionPool::getInstance();

int main(int argc, char* argv[]) {
    ///std::unique_ptr<Connection> conn;
    Statement* state;
    ResultSet* result;

    /// 获得一个数据库连接

    ///std::unique_ptr<Connection, delFunc> conn = pool->getConn();
    std::shared_ptr<Connection> conn = pool->getConn();

    state = conn->createStatement();
    // 使用数据库
    state->execute("use mydb");
    std::cout << pool->getPoolSize() << std::endl;

    // 查询语句
    result = state->executeQuery("select * from user;");
    while(result->next()) {
        ///int id = result->getInt("uid");
        std::string name = result->getString("username");
        std::cout << " name:" << name << std::endl; 
    }
    sleep(2);
    pool->retConn(std::move(conn)); // 归还连接
    std::cout << pool->getPoolSize() << std::endl;
    sleep(2);


    return 0;
}