/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * File: main.c                                                                *
 * Project: src                                                                *
 * Created Date: 2019-04-21 Sunday 10:03:02 pm                                 *
 * Author: Nie Aowei at <nieaowei@qq.com>                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Last Modified: 2019-04-22 Monday 2:15:42 pm                                 *
 * Modified By: Nie Aowei at <nieaowei@qq.com>                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2019 Nie Aowei                                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * UPDATE HISTORY:                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "huffman.h"
#include "text.h"

int main(int argc,char *argv[]){
	
	unsigned long i;
	Text *text;
	HuffMan *huffman;
	DecodeType *code;
	//FILE *fp;
	scanf("%ld",&i);
	text=CreateText(i);
	scanf("%s",text->data);
	//sprintf(text->data,"%s",argv[1]);
	Text_Scan(text);
	huffman=CreateHuffManTree(text->char_ascii,text->char_kind_num);
	CreateHF_File(huffman);
	code=TreeNode_Decode(huffman);
	CodePrint(code);
	//printf("%d",sizeof(long));
	//test("\nmain finished...");
	/*printf("%d %d %d %d",sizeof(short),sizeof(long),sizeof(int),sizeof(unsigned char));
	for ( i = 0; i < 255; i++)
	{

		printf("%d:%c ",i,i);
	}*/
}