/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * File: huffman.h                                                             *
 * Project: include                                                            *
 * Created Date: 2019-04-21 Sunday 10:03:28 pm                                 *
 * Author: Nie Aowei at <nieaowei@qq.com>                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Last Modified: 2019-04-22 Monday 4:55:58 pm                                 *
 * Modified By: Nie Aowei at <nieaowei@qq.com>                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2019 Nie Aowei                                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * UPDATE HISTORY:                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef _HUFFMAN_H
#define _HUFFMAN_H

//头文件引入
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "union_H.h"
//树结构定义
//树结点定义
/**
 * 由于总结点数不会超过256*2-1，所以采用short型，两个字节十六位够用
 * 权值足够大，采用long型,八个字节
 */ 
typedef struct{

	unsigned char ch;//字符 0~255
	Weight_Type weight;//权值 
	short lchild,rchild,parent;//左孩子，右孩子，父节点下标值
	byte flag;//最小值被取标志

}TreeNode;

//数定义
typedef struct{
	TreeNode *node;//树节点数组，数组下标范围0~510
	unsigned short lenth;//树节点总数，即树节点数组的大小，数组下标范围0~510
	unsigned short char_kind_num;//字符种数，范围0~256
}HuffMan;

//编码类型定义
typedef struct{
	unsigned char ch;
	byte decode[8];
}DecodeType;

//函数运行状态声明
typedef enum{
	Create_File_OK,
	Create_File_FAIL,
	Node_FAIL,
	Encode_OK,
	Encode_FAIL,
	Decode_OK,
	Decode_FAIL,

}HuffMan_State;
//全局变量声明


//函数声明
void HuffMan_Decode(HuffMan *huffman);//根据哈夫曼树编码

void Encode();//解码
HuffMan *CreateHuffManTree(unsigned long ascii_dic[],//ascii字典对应表
	short char_kind_num//数量
	);//创建哈夫曼树
unsigned short Find_Min_Weight(HuffMan *huffman);//查找最小权值结点
HuffMan_State CreateHF_File(HuffMan *huffman);//创建哈夫曼文件
void CodePrint(DecodeType *code);//编码类型打印

DecodeType *TreeNode_Decode(HuffMan *huffman);//通过Huffman树生成编码，返回编码类型

#endif