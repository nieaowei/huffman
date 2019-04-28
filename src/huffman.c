/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * File: huffman.c                                                             *
 * Project: src                                                                *
 * Created Date: 2019-04-21 Sunday 10:03:19 pm                                 *
 * Author: Nie Aowei at <nieaowei@qq.com>                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Last Modified: 2019-04-27 Saturday 6:23:36 pm                               *
 * Modified By: Nie Aowei at <nieaowei@qq.com>                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2019 Nie Aowei                                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * UPDATE HISTORY:                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "huffman.h"

//创建哈夫曼树
HuffMan *CreateHuffManTree(unsigned long *ascii_dic,//
						   short array_lenth,//
						   short char_kind_num){//创建哈夫曼树
	unsigned short i,j;//计次变量
	unsigned short min1,min2;//最小值
	HuffMan *huffman;//声明哈夫曼树指针
	huffman=(HuffMan *)malloc(sizeof(HuffMan));//分配空间
	huffman->lenth=2*char_kind_num-1;//设置哈夫曼树的总结点树
	huffman->char_kind_num=char_kind_num;//设置哈夫曼树字符的种数
	huffman->node=(TreeNode *)malloc(sizeof(TreeNode)*huffman->lenth);//开辟总结数个树结点
	//初始化各结点各变量，并将ASCII数组中的下标转化 以及 权值赋值
	for ( i = 0, j=0; i <array_lenth; i++)
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

HuffMan_State CreateHF_File(const char *str,HuffMan *huffman){
	unsigned short i;
	FILE *fp=fopen(str,"wt+");//创建文件
	if(fp==NULL){
		return Create_File_FAIL;//创建失败
	}
	for ( i = 0; i < huffman->lenth; i++)
	{
		fprintf(fp,"id:%d ch:%c weight:%ld ",i,huffman->node[i].ch,huffman->node[i].weight);
		fprintf(fp,"parent:%d lchild:%d rchild:%d\n",huffman->node[i].parent,huffman->node[i].lchild,huffman->node[i].rchild);
	}
	fclose(fp);
	return Create_File_OK;//创建成功
}

HuffMan_State HuffMan_Decode(HuffMan *huffman){
	LinkStack sq=NULL;//初始化栈
	unsigned short i;//对应下标志，范围在0~510，所以用short类型
	short current;//当前节点位置
	byte p;
	byte e;
	huffman->code=(DecodeType *)malloc(sizeof(DecodeType)*huffman->char_kind_num);
	for(i=0;i<huffman->char_kind_num;i++){

		for(current=i,p=0;\
			huffman->node[current].parent!=-1;\
			current=huffman->node[current].parent){
			if(huffman->node[huffman->node[current].parent].lchild==current){//满足条件就压栈
				PushStack(&sq,'0');
				p++;
			}else{
				PushStack(&sq,'1');
				p++;
			}
		}
		//给编码字符赋值
		huffman->code[i].ch=huffman->node[i].ch;
		//开辟相应个节点的空间大小
		huffman->code[i].lenth=p;
		huffman->code[i].decode=(byte *)malloc(sizeof(byte)*p);
		//所有元素出栈
		p=0;
		while(sq!=NULL){//当栈不空
			PopStack(&sq,&e);
			sprintf(&huffman->code[i].decode[p++],"%c",e);
		}
		//printf("%s\n",huffman->code[i].decode);
	}
	return Encode_FAIL;
}
//打印字符编码
void CodePrint(HuffMan *huffman){
	short i;
	for ( i = 0; i<huffman->char_kind_num ; i++)
	{
		printf("char_id:%d char:%c,code:%s\n",huffman->code[i].ch,huffman->code[i].ch,huffman->code[i].decode);
	}
}
//创建哈夫曼编码文件
HuffMan_State CreateHFCode_File(const char *str,HuffMan *huffman){
	FILE *fp=fopen(str,"wt+");//打开或创建可读可写文件
	short i;
	if(fp==NULL) return Create_File_FAIL;

	for(i=0;i<huffman->char_kind_num;i++){
		fprintf(fp,"%c:%s\n",huffman->code[i].ch,huffman->code[i].decode);
	}
	fclose(fp);
	return Create_File_OK;
}

void FreeHuffman(HuffMan *huffman){
	free(huffman->node);
	free(huffman->code);
	free(huffman);
}

//实现题目所给要求，即将所需函数用逻辑拼接起来

void Scanf_Value_Decode(const char *HFFile,const char *HfCode){
	unsigned short char_kind_num;//字符种类数
    unsigned short i;//计数
    unsigned long ascii[256];//ASCII对应表
    unsigned char *ascii_char;//ASCII字符对应表
	//FILE *out;//输出文件
	//char ch;//临时字符
	HuffMan *huffman;//哈夫曼树
	//out=fopen(outstr,"wt+");//打开out文件
	printf("请输入字符种类数：");
    scanf("%hd",&char_kind_num);//输入
    getchar();//吸收回车
    ascii_char=(unsigned char *)malloc(sizeof(unsigned char)*char_kind_num);//开辟字符类数字符数组
	printf("请输入字符（以空格为间隔）:");
    for(i=0;i<char_kind_num;i++){
        scanf("%c",&ascii_char[i]);
        getchar();//吸收回车
    }
	for(i=0;i<256;i++) ascii[i]=0;
	printf("请输入各字符权值（与上方对应）:");
    for(i=0;i<char_kind_num;i++){
        scanf("%ld",&ascii[(int)ascii_char[i]]);
    }
	huffman=CreateHuffManTree(ascii,256,char_kind_num);//创建哈夫曼树
	CreateHF_File(HFFile,huffman);//创建哈夫曼树文件
	HuffMan_Decode(huffman);//哈夫曼编码
	//CodePrint(huffman);
	CodePrint(huffman);
	PrintAverageWe(huffman);
	CreateHFCode_File(HfCode,huffman);//哈夫曼编码文件
	//i=0;
	//while(i<char_kind_num){
		//fscanf(fp,"%c",&ch);
	//	fprintf(out,"%s",huffman->code[Find_Code(huffman,ascii_char[i])].decode);
	//	i++;
	//}
	//fclose(out);
	FreeHuffman(huffman);
}

void Scanf_File_Decode(const char *instr,const char *outstr,const char *HFFile,const char *HfCode){
	FILE *fp;//输入文件
	FILE *out;//输出文件
	HuffMan *huffman;//
	Text *text;//声明文本
	unsigned char ch;
	text=CreateText(0);//创建文本
	fp=fopen(instr,"r");//只读方式打开输入文件
	out=fopen(outstr,"wt+");//可写创建或打开输出文件
	//开始统计文本长度已经字符频率
	while((ch=fgetc(fp))!=255){//文本未结束
		//fscanf(fp,"%c",&ch);
		text->char_ascii[(int)ch]++;
		text->lenth++;
	}
	//fclose(fp);//后面用不到，及时关闭，节省内存
	//统计字符种类
	Text_Scan(text,0);
	//创建哈夫曼树
	huffman=CreateHuffManTree(text->char_ascii,256,text->char_kind_num);
	//哈夫曼树写入文件hffile
	CreateHF_File(HFFile,huffman);
	//根据生成的哈夫曼树进行编码
	HuffMan_Decode(huffman);
	//打印编码文件
	CodePrint(huffman);
	//将编码写入文件hfcode
	CreateHFCode_File(HfCode,huffman);
	PrintAverageWe(huffman);
	//fp指向文件头
	rewind(fp);
	//对输入文件进行编码，写入输出文件
	while((ch=fgetc(fp))!=255){
		//fscanf(fp,"%c",&ch);
		fprintf(out,"%s",huffman->code[Find_Code(huffman,ch)].decode);
	}
	//关闭out文件流
	fclose(out);
	//释放huffman所有申请内存
	FreeHuffman(huffman);
}

short Find_Code(HuffMan *huffman,char ch){
	short i;
	for(i=0;i<huffman->char_kind_num;i++){
		if(ch==huffman->code[i].ch)
			return i;
	}
}

void PrintAverageWe(HuffMan *huffman){
	long sum=0;
	int i;
	long m=0;
	for ( i = 0; i < huffman->char_kind_num; i++)
	{
		/* code */
		m+=huffman->node[i].weight;
	}
	for ( i = 0; i < huffman->char_kind_num; i++)
	{
		//printf("(%d/%d)*%d",huffman->node[i].weight,m,huffman->code[i].lenth);
		sum+=huffman->node[i].weight*huffman->code[i].lenth;
	}
	printf("平均码长为：%lf",sum/1.0/m);
}