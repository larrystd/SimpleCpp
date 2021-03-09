/*
 * @Author: your name
 * @Date: 2021-03-09 19:56:38
 * @LastEditTime: 2021-03-09 20:43:30
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /SimpleCode/C++/uthread/uthread.h
 */
/**
* @file  thread.h
* @author chenxueyou
* @version 0.1
* @brief   :A asymmetric coroutine library for C++
* History
*      1. Date: 2014-12-12 
*          Author: chenxueyou
*          Modification: this file was created 
*/

#ifndef MY_UTHREAD_H
#define MY_UTHREAD_H

#ifdef __APPLE__
#define _XOPEN_SOURCE
#endif 

#include <ucontext.h>
#include <vector>

#define DEFAULT_STACK_SZIE (1024*128)
#define MAX_UTHREAD_SIZE   1024

enum ThreadState{FREE,RUNNABLE,RUNNING,SUSPEND};    // FREE,RUNNABLE,RUNING,SUSPEND,分别表示空闲，就绪，正在执行和挂起四种状态 

struct schedule_t;

typedef void (*Fun)(void *arg);

typedef struct uthread_t
{
    ucontext_t ctx;     // 当前上下文
    Fun func;   // 协程执行的用户函数
    void *arg;  // 参数
    enum ThreadState state; //协程的状态
    char stack[DEFAULT_STACK_SZIE]; // 协程的栈
}uthread_t;

typedef struct schedule_t   // 调度器
{
    ucontext_t main;
    int running_thread;
    uthread_t *threads;
    int max_index; // 曾经使用到的最大的index + 1

    schedule_t():running_thread(-1), max_index(0) {
        threads = new uthread_t[MAX_UTHREAD_SIZE];  // 创建多个协程
        for (int i = 0; i < MAX_UTHREAD_SIZE; i++) {
            threads[i].state = FREE;    // 设置协程状态
        }
    }
    
    ~schedule_t() {
        delete [] threads;
    }
}schedule_t;

/*help the thread running in the schedule*/
static void uthread_body(schedule_t *ps);

/*Create a user's thread , join in schedule sequence
*    @param[in]:
*        schedule_t &schedule 
*        Fun func: user's function
*        void *arg: the arg of user's function
*    @param[out]:
*    @return:
*        return the index of the created thread in schedule
*/
int  uthread_create(schedule_t &schedule,Fun func,void *arg);

/* Hang the currently running thread, switch to main thread
 挂起调度器schedule中当前正在执行的协程，切换到主函数。 */
void uthread_yield(schedule_t &schedule);

/* resume the thread which index equal id*/
void uthread_resume(schedule_t &schedule,int id);

/* 判断schedule中所有的协程是否都执行完毕，是返回1，否则返回0.注意：如果有协程处于挂起状态时算作未全部执行完毕，返回0.
*/
int  schedule_finished(const schedule_t &schedule);

#endif
