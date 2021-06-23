/**
* @file  uthread.cpp
* @author chenxueyou
* @version 0.1
* @brief   :A asymmetric coroutine library for C++
* History
*      1. Date: 2014-12-12 
*          Author: chenxueyou
*          Modification: this file was created 
*/

#ifndef MY_UTHREAD_CPP
#define MY_UTHREAD_CPP


#include "uthread.h"
//#include <stdio.h>

void uthread_resume(schedule_t &schedule , int id)
{
    if(id < 0 || id >= schedule.max_index){
        return;
    }

    uthread_t *t = &(schedule.threads[id]);

    if (t->state == SUSPEND) {
        swapcontext(&(schedule.main),&(t->ctx));    // 切换上下文从main到线程id ctx
    }
}

void uthread_yield(schedule_t &schedule)
{
    if(schedule.running_thread != -1 ){
        uthread_t *t = &(schedule.threads[schedule.running_thread]);
        t->state = SUSPEND;
        schedule.running_thread = -1;

        swapcontext(&(t->ctx),&(schedule.main));    // 切换回main
    }
}

void uthread_body(schedule_t *ps)
{
    int id = ps->running_thread;

    if(id != -1){
        uthread_t *t = &(ps->threads[id]);

        t->func(t->arg);    // 初始化协程的状态

        t->state = FREE;
        
        ps->running_thread = -1;
    }
}

int uthread_create(schedule_t &schedule,Fun func,void *arg)
{
    int id = 0;
    
    for(id = 0; id < schedule.max_index; ++id ){
        if(schedule.threads[id].state == FREE){     // 找到第一个空闲的协程
            break;
        }
    }
    
    if (id == schedule.max_index) {
        schedule.max_index++;
    }

    uthread_t *t = &(schedule.threads[id]);

    t->state = RUNNABLE;
    t->func = func;
    t->arg = arg;

    getcontext(&(t->ctx));  // 创建一个上下文
    
    t->ctx.uc_stack.ss_sp = t->stack;
    t->ctx.uc_stack.ss_size = DEFAULT_STACK_SZIE;
    t->ctx.uc_stack.ss_flags = 0;
    t->ctx.uc_link = &(schedule.main);  // 协程执行后的下文
    schedule.running_thread = id;
    
    makecontext(&(t->ctx),(void (*)(void))(uthread_body),1,&schedule);  // 协程执行uthread_body
    swapcontext(&(schedule.main), &(t->ctx));   // 切换到协程下文，也就是fun，进行执行
    
    return id;
}

int schedule_finished(const schedule_t &schedule)
{
    if (schedule.running_thread != -1){
        return 0;
    }else{
        for(int i = 0; i < schedule.max_index; ++i){
            if(schedule.threads[i].state != FREE){  // 状态不是free说明没有结束
                return 0;
            }
        }
    }

    return 1;
}

#endif
