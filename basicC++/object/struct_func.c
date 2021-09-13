
#include<stdio.h>
#include<malloc.h>
struct Hello{
	void (*sayHello)(char* name); 
};
void sayHello(char* name){
	printf("你好，%s\n",name);
}
int main(){
	struct Hello* hello=(struct Hello *)malloc(sizeof(struct Hello));
	hello->sayHello=sayHello;//这个结构体有多少个函数，就要在这个有多少个结构体内，函数指针指向函数的声明。
	hello->sayHello("a");
	return 0;
}