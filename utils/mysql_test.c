#include <stdlib.h>
#include <stdio.h>
 
#include "mysql.h"
 
int main(int argc, char *argv[]) {
   MYSQL *conn_ptr;
 
   conn_ptr = mysql_init(NULL);//初始化
   if (!conn_ptr) {
      fprintf(stderr, "mysql_init failed\n");
      return EXIT_FAILURE;
   }
   
   conn_ptr = mysql_real_connect(conn_ptr, "localhost", "root", "root","mydb", 0, NULL, 0);//连接数据库 1则success or failed
 
   if (conn_ptr) {
      printf("Connection success\n");
   } else {
      printf("Connection failed\n");
   }
 
   mysql_close(conn_ptr);
 
   return EXIT_SUCCESS;
}