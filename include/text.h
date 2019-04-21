/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * File: text.h                                                                *
 * Project: include                                                            *
 * Created Date: 2019-04-21 Sunday 10:03:26 pm                                 *
 * Author: Nie Aowei at <nieaowei@qq.com>                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Last Modified: 2019-04-21 Sunday 10:03:26 pm                                *
 * Modified By: Nie Aowei at <nieaowei@qq.com>                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2019 Nie Aowei                                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * UPDATE HISTORY:                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
#include "union_H.h"

typedef unsigned long Text_Max;//文本字符串最大长度

//文本字符串结构定义
typedef struct{

	 char *data;//文本字符串
	Text_Max lenth;//字符串长度
	unsigned short char_kind_num;//字符种数0~256
	Weight_Type char_ascii[__BYTE_MAX__+1];//ASCII码字符频率对应表,频率long型

}Text;

Text *CreateText(Text_Max lenth);//创建lenth长度的字符串文本
void Text_Scan(Text *text);//扫描文本字符串，得到字符种数和ASCII吗字符频率