/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * File: main.c                                                                *
 * Project: src                                                                *
 * Created Date: 2019-04-21 Sunday 10:03:02 pm                                 *
 * Author: Nie Aowei at <nieaowei@qq.com>                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Last Modified: 2019-04-23 Tuesday 6:23:06 pm                                *
 * Modified By: Nie Aowei at <nieaowei@qq.com>                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2019 Nie Aowei                                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * UPDATE HISTORY:                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "huffman.h"

int main(int argc,char *argv[]){
	byte option;
	while(1){
		printf("请输入您的选择：");
		scanf("%d",&option);
		switch(option){
			case 1:
				Scanf_Value_Decode("./hfmTree.txt","./CodeFile.txt");
				break;
			case 2:
				Scanf_File_Decode("./ToBeTran.txt","./CodePrint.txt","./htmTree.txt","./CodeFile.txt");
				break;
		}
	}
	//LinkStack sp;
	//PushStack(&sp,'a');
	//printf("%c",sp->data);
}