/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * File: stack.h                                                               *
 * Project: include                                                            *
 * Created Date: 2019-04-22 Monday 3:54:47 pm                                  *
 * Author: Nie Aowei at <nieaowei@qq.com>                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Last Modified: 2019-04-22 Monday 5:24:39 pm                                 *
 * Modified By: Nie Aowei at <nieaowei@qq.com>                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2019 Nie Aowei                                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * UPDATE HISTORY:                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _STACK_H
#define _STACK_H

#include <stdlib.h>

typedef unsigned char StackType;

typedef struct StackNode
{
    StackType data;
    struct StackNode *next;
    
}StackNode,*LinkStack;

typedef enum{
    ERROR=-1,
    OK,
}StackState;

LinkStack CreateStack(void);
StackState PushStack(LinkStack *stack,StackType elem);
StackState PopStack(LinkStack *stack,StackType *elem);
#endif
