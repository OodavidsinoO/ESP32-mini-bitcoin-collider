CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic -g
LDFLAGS = -lm

all: rgb2bmp images ffmpegConvert

images: images
	$(CC) -o images images.cpp -Wall -Wextra -Werror -std=c++11 -pedantic -g -lstdc++ -lm

rgb2bmp: rgb2bmp.c
	$(CC) $(CFLAGS) -o rgb2bmp rgb2bmp.c $(LDFLAGS)

ffmpegConvert:
	./images.exe
	ffmpeg -vcodec rawvideo -f rawvideo -pix_fmt rgb565 -s 320x170 -i .\setupModeScreen.bin -f image2 -vcodec png setupModeScreen.png -y
	ffmpeg -vcodec rawvideo -f rawvideo -pix_fmt rgb565 -s 320x170 -i .\MinerScreen.bin -f image2 -vcodec png MinerScreen.png -y
	ffmpeg -vcodec rawvideo -f rawvideo -pix_fmt rgb565 -s 320x170 -i .\initScreen.bin -f image2 -vcodec png initScreen.png -y
	ffmpeg -vcodec rawvideo -f rawvideo -pix_fmt rgb565 -s 320x170 -i .\minerClockScreen.bin -f image2 -vcodec png minerClockScreen.png -y
	ffmpeg -vcodec rawvideo -f rawvideo -pix_fmt rgb565 -s 320x170 -i .\globalHashScreen.bin -f image2 -vcodec png globalHashScreen.png -y

clean:
	rm -f rgb2bmp images *.exe *.o *.bin *.bmp *.png