#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "rgb2bmp.h"

int main()
{
/***********  input data  ***********
    filename      :RGB数据文件名称
    nWidth        :所生成文件的水平像素
    nHeight       :所生成文件的垂直像素
    newFile       :最终生成文件的名称
***********/
    FILE* p;
    char* filename = "minerClockScreen.bin";
    int nWidth = 320;
    int nHeight = 170;
    char* newFile = "minerClockScreen.bmp";
    p = fopen(filename, "rb");
    if (p == NULL)
    {
        printf("!!!file %s open failed\n", filename);
        return 0;
    }
    printf("file %s open success\n",filename);

/***********  read Image Data  ***********/     
    long nData = nWidth*nHeight;
    unsigned short* rgb_buffer = malloc(nData*sizeof(short));    
    fread(rgb_buffer, 2, nData, p);
    long total = nWidth*nHeight*3;
    unsigned char* pVisit =  malloc(total*sizeof(char));
    unsigned char* tmp = pVisit;
    long i =0;
    unsigned char R,G,B;
    while(i<nData)
    {
       R = *rgb_buffer&0x1f;
    G = (*rgb_buffer>>5)&0x3f;
    B = (*rgb_buffer>>11)&0x1f;
    B = B<<3;
    G = G<<2;
    R = R<<3;
      *pVisit=R;pVisit++;
      *pVisit=G;pVisit++;
      *pVisit=B;pVisit++;
      rgb_buffer++;
      i++;  
     }
	 printf("read file over\n");
    printf("Data=%ld\n", nData);

/***********  write file ***********/
    FILE *result = fopen(newFile, "wb");
    if (result == NULL)
    {
       printf("open new file failed\n");
       return -1;
    }
    RGB2BMP(tmp, nWidth, nHeight, result);
    fclose(result);
    return 0;
}
