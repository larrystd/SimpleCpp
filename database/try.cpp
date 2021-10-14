#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <mysql_connection.h>
#include <unistd.h>

/// getInstance()是static静态方法, 返回一个数据库连接池对象
ConnectionsPool* pool = ConectionPool::getInstance();

int main(int argc, char* argv[]) {
    std::shared_ptr<Connection> con;
    Statement* state;
    ResultSet* result;

    /// 获得一个数据库连接
    con = pool->getConnect();
    state = con->createStatement();
    // 使用数据库
    state->execute("use mydb");

    // 查询语句
    result = state->executeQuery("select * from user;");
    while(result->next()) {
        ///int id = result->getInt("uid");
        std::string name = result->getString("username");
        std::cout << " name:" << name << std::endl; 
    }
    sleep(2);
    pool->retConnect(conn); // 归还连接
    std::cout << pool->getPoolSize() << std::endl;
    sleep(2);

    return EXIT_SUCCESS;
}
