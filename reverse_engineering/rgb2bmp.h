//rgb2bmp.h文件
#include <stdio.h>
typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef int DWORD;

// BMP图像各部分说明如下
/***********
    第一部分    位图文件头
该结构的长度是固定的，为14个字节，各个域的依次如下：
    2byte   ：文件类型，必须是0x4d42，即字符串"BM"。
    4byte   ：整个文件大小
    4byte   ：保留字，为0
    4byte   ：从文件头到实际的位图图像数据的偏移字节数。
***********/

typedef struct
{   
    DWORD imageSize;
    DWORD blank;
    DWORD startPosition;
} BmpHead;

/***********
第二部分    位图信息头
该结构的长度也是固定的，为40个字节，各个域的依次说明如下：
    4byte   ：本结构的长度，值为40
    4byte   ：图像的宽度是多少象素。
    4byte   ：图像的高度是多少象素。
    2Byte   ：必须是1。
    2Byte   ：表示颜色时用到的位数，
				常用的值为1(黑白二色图)、4(16色图)、8(256色图)、24(真彩色图)。
    4byte   ：指定位图是否压缩，
				有效值为BI_RGB，BI_RLE8，BI_RLE4，BI_BITFIELDS。
				Windows位图可采用RLE4和RLE8的压缩格式，BI_RGB表示不压缩。
    4byte   ：指定实际的位图图像数据占用的字节数，可用以下的公式计算出来：
     图像数据 = Width' * Height * 表示每个象素颜色占用的byte数(即颜色位数/8,24bit图为3，256色为1）
     要注意的是：上述公式中的biWidth'必须是4的整数倍
	 (不是biWidth，而是大于或等于biWidth的最小4的整数倍)。
     如果biCompression为BI_RGB，则该项可能为0。
    4byte   ：目标设备的水平分辨率。
    4byte   ：目标设备的垂直分辨率。
    4byte   ：本图像实际用到的颜色数，
				如果该值为0，则用到的颜色数为2的(颜色位数)次幂,
				如颜色位数为8，2^8=256,即256色的位图
    4byte   ：指定本图像中重要的颜色数，如果该值为0，则认为所有的颜色都是重要的。
***********/

typedef struct
{
    DWORD    Length;
    DWORD    width;
    DWORD    height;
    WORD    colorPlane;
    WORD    bitColor;
    DWORD    zipFormat;
    DWORD    realSize;
    DWORD    xPels;
    DWORD    yPels;
    DWORD    colorUse;
    DWORD    colorImportant;
  /*  void show()
 
    {     
        printf("infoHead Length:%dn",Length);
        printf("width&height:%d*%dn",width,height); 
        printf("colorPlane:%dn",colorPlane);
        printf("bitColor:%dn",bitColor);
        printf("Compression Format:%dn",zipFormat);
        printf("Image Real Size:%dn",realSize);
        printf("Pels(X,Y):(%d,%d)n",xPels,yPels);
        printf("colorUse:%dn",colorUse);     
        printf("Important Color:%dn",colorImportant);
    }*/
} InfoHead;

/***********
    第三部分    调色盘结构  颜色表
    对于256色BMP位图，颜色位数为8，需要2^8 = 256个调色盘；
    对于24bitBMP位图，各象素RGB值直接保存在图像数据区，不需要调色盘，不存在调色盘区
    rgbBlue：   该颜色的蓝色分量。
    rgbGreen：  该颜色的绿色分量。
    rgbRed：    该颜色的红色分量。
    rgbReserved：保留值。
***********/

typedef struct
{
    BYTE   rgbBlue;
    BYTE   rgbGreen;
    BYTE   rgbRed;
    BYTE   rgbReserved;
/*  void show(void)
    {
        printf("Mix Plate B,G,R:%d %d %dn",rgbBlue,rgbGreen,rgbRed);
    }*/
} RGBMixPlate;

/***********
      RGB加上头部信息转换成BMP
      参数說明：
      rgb_buffer        :RGB数据文件中的信息
      nData             :RGB数据的长度
      nWidth            :图像宽度的像素数
      nHeight           :图像高度的像素数
      fp1               :所存放的文件
***********/

int RGB2BMP(unsigned char *rgb_buffer, int nWidth, int nHeight, FILE*fp1)
{
     BmpHead m_BMPHeader;        
     char bfType[2]={'B','M'};
     m_BMPHeader.imageSize=3*nWidth*nHeight+54;
     m_BMPHeader.blank=0;
     m_BMPHeader.startPosition=54;
 
     fwrite(bfType,1,sizeof(bfType),fp1);
     fwrite(&m_BMPHeader.imageSize,1,sizeof(m_BMPHeader.imageSize),fp1);
     fwrite(&m_BMPHeader.blank,1,sizeof(m_BMPHeader.blank),fp1);
     fwrite(&m_BMPHeader.startPosition,1,sizeof(m_BMPHeader.startPosition),fp1);
        
     InfoHead  m_BMPInfoHeader;
	 printf("40 == sizeof(InfoHead)=%lld\n", sizeof(InfoHead));
     m_BMPInfoHeader.Length=40; 
     m_BMPInfoHeader.width=nWidth;
     m_BMPInfoHeader.height=nHeight;
     m_BMPInfoHeader.colorPlane=1;
     m_BMPInfoHeader.bitColor=24;
     m_BMPInfoHeader.zipFormat=0;
     m_BMPInfoHeader.realSize=3*nWidth*nHeight;
     m_BMPInfoHeader.xPels=0;
     m_BMPInfoHeader.yPels=0;
     m_BMPInfoHeader.colorUse=0;
     m_BMPInfoHeader.colorImportant=0;
 
     fwrite(&m_BMPInfoHeader.Length,1,sizeof(m_BMPInfoHeader.Length),fp1);
     fwrite(&m_BMPInfoHeader.width,1,sizeof(m_BMPInfoHeader.width),fp1);
     fwrite(&m_BMPInfoHeader.height,1,sizeof(m_BMPInfoHeader.height),fp1);
     fwrite(&m_BMPInfoHeader.colorPlane,1,sizeof(m_BMPInfoHeader.colorPlane),fp1);
     fwrite(&m_BMPInfoHeader.bitColor,1,sizeof(m_BMPInfoHeader.bitColor),fp1);
     fwrite(&m_BMPInfoHeader.zipFormat,1,sizeof(m_BMPInfoHeader.zipFormat),fp1);
     fwrite(&m_BMPInfoHeader.realSize,1,sizeof(m_BMPInfoHeader.realSize),fp1);
     fwrite(&m_BMPInfoHeader.xPels,1,sizeof(m_BMPInfoHeader.xPels),fp1);
     fwrite(&m_BMPInfoHeader.yPels,1,sizeof(m_BMPInfoHeader.yPels),fp1);
     fwrite(&m_BMPInfoHeader.colorUse,1,sizeof(m_BMPInfoHeader.colorUse),fp1);
     fwrite(&m_BMPInfoHeader.colorImportant,1,sizeof(m_BMPInfoHeader.colorImportant),fp1);
     fwrite(rgb_buffer,3*nWidth*nHeight,1,fp1);
     return 0;
}
