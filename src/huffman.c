/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * File: huffman.c                                                             *
 * Project: src                                                                *
 * Created Date: 2019-04-21 Sunday 10:03:19 pm                                 *
 * Author: Nie Aowei at <nieaowei@qq.com>                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Last Modified: 2019-04-22 Monday 3:13:59 pm                                 *
 * Modified By: Nie Aowei at <nieaowei@qq.com>                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2019 Nie Aowei                                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * UPDATE HISTORY:                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "huffman.h"

//创建哈夫曼树
HuffMan *CreateHuffManTree(unsigned long ascii_dic[],short char_kind_num){//创建哈夫曼树
	unsigned short i,j;//计次变量
	unsigned short min1,min2;//最小值
	HuffMan *huffman;//声明哈夫曼树指针
	huffman=(HuffMan *)malloc(sizeof(HuffMan));//分配空间
	huffman->lenth=2*char_kind_num-1;//设置哈夫曼树的总结点树
	huffman->char_kind_num=char_kind_num;//设置哈夫曼树字符的种数
	huffman->node=(TreeNode *)malloc(sizeof(TreeNode)*huffman->lenth);//开辟总结数个树结点
	//初始化各结点各变量，并将ASCII数组中的下标转化 以及 权值赋值
	for ( i = 0, j=0; i <=__BYTE_MAX__; i++)
	{
		if(ascii_dic[i]!=0){
			huffman->node[j].flag=0;

			huffman->node[j].lchild=-1;
			huffman->node[j].rchild=-1;
			huffman->node[j].parent=-1;

			huffman->node[j].ch=(char)(i);//将ASCII数组对应下标转化成字符
			huffman->node[j].weight=ascii_dic[i];//对应权值赋值
			j++;
		}
		if(i==__BYTE_MAX__){//当最后一个字符统计完后，也就是最后一次循环结束前
			//初始化字符种数后的结点，以便于查找最小函数的使用
			for(;j<huffman->lenth;j++){
				huffman->node[j].flag=0;
				huffman->node[j].weight=0;
				huffman->node[j].lchild=-1;
				huffman->node[j].rchild=-1;
				huffman->node[j].parent=-1;
			}
		}
	}
	
	//将各个树结点链接起来，构建哈夫曼树
	for(i=huffman->char_kind_num;i<huffman->lenth;i++){
		min1=Find_Min_Weight(huffman);
		min2=Find_Min_Weight(huffman);
		huffman->node[i].weight=huffman->node[min1].weight+huffman->node[min2].weight;
		huffman->node[min1].parent=i;
		huffman->node[min2].parent=i;
		huffman->node[i].lchild=min1;
		huffman->node[i].rchild=min2;
	}
	//返回huffman指针
	return huffman;
}

unsigned short Find_Min_Weight(HuffMan *huffman){//查找最小权值结点位置
	unsigned short i;//计次变量
	unsigned long temp;//临时变量，存放最小值
	unsigned short locate;//位置变量，最放最小值的位置
	//扫描结点的权值，将第一个未被取出的权值赋值给temp，以及位置赋值给locate
	for(i=0;i<huffman->lenth;i++){
		if(huffman->node[i].flag==0 && huffman->node[i].weight!=0){
			temp=huffman->node[i].weight;
			locate=i;
			break;
		}
	}
	//扫描结点的权值，找到未被取出的权值中的最小权值
	for(i=0;i<huffman->lenth;i++){
		if(huffman->node[i].weight!=0 && huffman->node[i].flag==0 && temp>huffman->node[i].weight){
			temp=huffman->node[i].weight;
			locate=i;
		}
	}
	//设置已被取出标志
	huffman->node[locate].flag=1;
	return locate;

}

HuffMan_State CreateHF_File(HuffMan *huffman){
	unsigned short i;
	FILE *fp=fopen("./hfmTree","wt+");//创建文件
	if(fp==NULL){
		return Create_File_FAIL;//创建失败
	}
	for ( i = 0; i < huffman->lenth; i++)
	{
		fprintf(fp,"id:%d ch:%c weight:%ld ",i,huffman->node[i].ch,huffman->node[i].weight);
		fprintf(fp,"parent:%d lchild:%d rchild:%d\n",huffman->node[i].parent,huffman->node[i].lchild,huffman->node[i].rchild);
	}
	return Create_File_OK;//创建成功
}

void HuffMan_Decode(HuffMan *huffman){//根据哈夫曼树编码
	unsigned short i;//对应下标志，范围在0~510，所以用short类型
	for ( i = 0; i < huffman->char_kind_num; i++){
		
	}
	
}

DecodeType *TreeNode_Decode(HuffMan *huffman){
	DecodeType *code;
	unsigned char *tempcode;
	byte i;
	byte current;//当前节点位置
	byte p;
	byte start;
	tempcode=(unsigned char *)malloc(sizeof(unsigned char)*huffman->char_kind_num);
	code=(DecodeType *)malloc(sizeof(DecodeType)*huffman->char_kind_num);
	for(i=0;i<huffman->char_kind_num;i++){
		code[i].ch=huffman->node[i].ch;
		for(current=i,p=huffman->char_kind_num-1;\
			huffman->node[current].parent!=-1;\
			current=huffman->node[current].parent){
			if(huffman->node[huffman->node[current].parent].lchild==current){
				tempcode[p]='0';
				p--;
			}else{
				tempcode[p]='1';
				p--;	
			}
		}
		printf("%s\t",&tempcode[p+1]);
		strcpy(code[i].decode,&tempcode[p+1]);
	}
	return code;
}

void CodePrint(DecodeType *code){
	short i;
	for ( i = 0; i < 10; i++)
	{
		printf("char:%c,code:%s\n",code[i].ch,code[i].decode);
	}
}