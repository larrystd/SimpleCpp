
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
 
using namespace sql;
using namespace std;
 
#define DBHOST "tcp://127.0.0.1:3306"
#define USER "root"
#define PASSWORD "root"
 
int main(){
 
  Driver *driver;
  Connection *conn;
  driver = get_driver_instance();
  conn = driver->connect(DBHOST, USER, PASSWORD);
  cout<<"DataBase connection autocommit mode = "<<conn->getAutoCommit()<<endl;
  delete conn;
  driver = NULL;
  conn = NULL;
  return 0;
}