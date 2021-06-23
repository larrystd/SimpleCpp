/*
 * @Author: your name
 * @Date: 2021-02-28 19:03:31
 * @LastEditTime: 2021-02-28 19:56:34
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /socketTest/client/client.cpp
 */
#include <iostream>
#include <signal.h>
#include "TCPClient.h"

TCPClient tcp;

void sig_exit(int s)
{
	tcp.exit();
	exit(0);
}

int main(int argc, char *argv[])
{
	if(argc != 4) {
		cerr << "Usage: ./client ip port message" << endl;
		return 0;
	}
	signal(SIGINT, sig_exit);

	tcp.setup(argv[1],atoi(argv[2]));	// ip和端口
	while(1)
	{
		tcp.Send(argv[3]);
		string rec = tcp.receive();
		if( rec != "" )
		{
			cout << rec << endl;
		}
		sleep(1);
	}
	return 0;
}
