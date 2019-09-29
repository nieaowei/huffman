# C语言哈夫曼树编码压缩实践项目-huffman
1. 根据机器位数可以压缩理论值最大文件。  

2. 提供自主输入权值、字符进行编码的接口。  

3. 提供输入文件编码。  

4. 注释详细。

# 一、该项目理论上的优点  

1. 合理分配了所有变量，根据不同的使用场景分配合适大小的变量内存。  

2. 为了支持理论值上的压缩，合理采用了动态分配变量内存。  

# 二、该项目支持的功能展示

注：选项1为压缩接口，选项2为文件压缩。

## 1.压缩接口  
在主函数中调用了Scanf_Value_Decode("./hfmTree.txt","./CodeFile.txt")该函数，该函数会将用户输入的权值等数据进行处理编码后，将相应的哈夫曼树输出到当前运行目录下的hfmTree.txt文件，将编码输出到当前运行目录下的CodeFile.txt文件。  

![alt](https://s2.ax1x.com/2019/09/29/u8UHSO.jpg)

## 2.文件压缩  

在主函数中调用Scanf_File_Decode("./ToBeTran.txt","./CodePrint.txt","./htmTree.txt","./CodeFile.txt")函数，实现对当前目录下ToBeTran.txt生成哈夫曼树导出至htmTree.txt文件，将字符编码导出至CodeFile.txt文件，将相应编码好的文件导出至CodePrint.txt文件。  

![alt](https://s2.ax1x.com/2019/09/29/u8w8F1.jpg)
![alt](https://s2.ax1x.com/2019/09/29/u8wIkn.jpg)  
![alt](https://s2.ax1x.com/2019/09/29/u8wGJx.jpg)
![alt](https://s2.ax1x.com/2019/09/29/u8w1oR.jpg)
![alt](https://s2.ax1x.com/2019/09/29/u8wlw9.jpg)