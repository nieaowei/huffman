/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * File: text.c                                                                *
 * Project: src                                                                *
 * Created Date: 2019-04-21 Sunday 10:03:15 pm                                 *
 * Author: Nie Aowei at <nieaowei@qq.com>                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Last Modified: 2019-04-23 Tuesday 6:23:50 pm                                *
 * Modified By: Nie Aowei at <nieaowei@qq.com>                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2019 Nie Aowei                                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * UPDATE HISTORY:                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "text.h"

Text *CreateText(unsigned long lenth){
	Text *text;//声明text指针
	short i;//计数变量
	text=(Text *)malloc(sizeof(Text));//分配空间
	text->lenth=lenth;//设置文本字符串长度
	text->data=(unsigned char *)malloc(sizeof(unsigned char)*text->lenth);//开辟文本字符串长度个字符数组
	text->char_kind_num=0;//种类初始化为0
	for(i=0;i<=__BYTE_MAX__;i++){//ASCII码表初始化
		text->char_ascii[i]=0;
	}
	return text;
}

void Text_Scan(Text *text,byte mode){
	Text_Max i;
	/**
	 * 扫描字符串，
	 * 得到ASCII码字符频率表
	 */
	if(mode==1){
		for(i=0;i<text->lenth;i++){
			text->char_ascii[(int)(text->data[i])]++;
		}
	}
	/**
	 * 扫描字ASCII码表
	 * 统计出现的字符种类数
	 */
	for(i=0;i<=__BYTE_MAX__;i++){
		if(text->char_ascii[i]!=0){
			text->char_kind_num++;
		}
	}
}

void PrintText(Text *text){
	short i;
	for(i=0;i<=__BYTE_MAX__;i++){
		printf("%ld ",text->char_ascii[i]);
		if(i%15==0 && i!=0) printf("\n");
		}
}