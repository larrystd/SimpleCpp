#include "test.pb.h"		//解析出来的.h文件
#include "stdio.h"

void sendHeart();
void receHeart(TopMessage* topMessage);
void receHeartResp(TopMessage* topMessage);

void sendHeart(){   // 执行
	
	TopMessage message;
	message.set_message_type(REQUEST_HEARTBEAT_SIGNAL); // 消息
	printf("sendHeart %d\n",message.message_type());    
	receHeart(&message);
    printf("recvHeart %d\n",message.message_type());   
}

void receHeart(TopMessage* topMessage){

	if (topMessage->message_type() == REQUEST_HEARTBEAT_SIGNAL)
	{
		
		printf("request_heartbeat_signal\n");
		TopMessage topMessageResp;

		MsgResult mesResult;    // 设置MsgResultesult
		mesResult.set_result(true);
	
		mesResult.set_error_code("error");
		
		topMessageResp.set_message_type(RESPONSE_HEARTBEAT_RESULT); // 修改了top
		
		*topMessageResp.mutable_msg_result() = mesResult;   // MsgResult放入topMessageResp中

		receHeartResp(&topMessageResp);
	}
	
}

void receHeartResp(TopMessage* topMessage){

	if (topMessage->message_type() == RESPONSE_HEARTBEAT_RESULT)    // 读取topMessage
	{
		printf("response_heartbeat_result\n");
		
		printf("%s\n",topMessage->msg_result().error_code().c_str());

	}
}

int main()
{
	sendHeart();
	google::protobuf::ShutdownProtobufLibrary();
}