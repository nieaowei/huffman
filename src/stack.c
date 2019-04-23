/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * File: stack.c                                                               *
 * Project: src                                                                *
 * Created Date: 2019-04-22 Monday 3:54:53 pm                                  *
 * Author: Nie Aowei at <nieaowei@qq.com>                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Last Modified: 2019-04-22 Monday 5:24:32 pm                                 *
 * Modified By: Nie Aowei at <nieaowei@qq.com>                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2019 Nie Aowei                                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * UPDATE HISTORY:                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "stack.h"

LinkStack CreateStack(){
    return NULL;
}

StackState PushStack(LinkStack *stack,StackType elem){
    StackNode *p;
    p=(StackNode *)malloc(sizeof(StackNode));
	if(p==NULL) return 0;
    p->data=elem;
    p->next=(*stack);
    (*stack)=p;
    return OK;
}

StackState PopStack(LinkStack *stack,StackType *elem){
    StackNode *temp;
    if(stack==NULL){
        return ERROR;
    }
    *elem=(*stack)->data;
	temp=(*stack);
    (*stack)=(*stack)->next;
    free(temp);
    return OK;
}