#include <stdio.h>
#include <sys/types.h>//open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>//close、read、write
#include <sys/mman.h>//mmap
#include <pthread.h>
#include <stdlib.h>
#include <linux/input.h>


int randnum;
int showBMP(const char *path)
{
	//打开LCD驱动设备
	int fd = open("/dev/fb0",O_RDWR);
	if(fd < 0)
	{
		perror("open lcd failed");
		return -1;
	}
	

	
	//对LCD屏幕进行映射
	int *lcd = mmap(NULL,1024*600*4,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
	
	
	
	
	
	
	//打开图片
	int bmpfd= open(path,O_RDONLY);
	
	
	
	if(bmpfd < 0)
	{
		perror("open bmp failed");
		return -1;
	}
	
	//读取图片的头54个字节信息
	unsigned char head[54]={0};
	read(bmpfd,head,54);
	
	//解析宽度和高度
	int kuan = *((int *)&head[18]);
	int gao = *((int *)&head[22]);
	
	//printf("kuan=%d\n",kuan);
	//printf("gao=%d\n",gao);
	
	//变长数组
	int buf[gao][kuan];//32位图的buf
	char tmp_buf[gao*kuan*3];//24位图的tmp_buf
	
	//读取图片像素点的值存到tmp_buf
	read(bmpfd,tmp_buf,sizeof(tmp_buf));
	
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	unsigned char *p = tmp_buf ;
	unsigned int color =0;
	unsigned int x=0, y=0;
	
	for(y=0;y<gao;y++)
		for(x=0;x<kuan;x++)
		{
			b = *p++;
			g = *p++;
			r = *p++;
			
			a = 0;
			color = a << 24 | r << 16 | g << 8 | b;
			buf[y][x] = color;
			
			*(lcd +(600-1-y)*1024 + x)= buf[y][x];
		}
	
	
	//关闭LCD驱动设备
	close(fd);
	close(bmpfd);
	munmap(lcd,1024*600*4);
	
	return 0;
}


int successclick(const char *path)
{
	//打开LCD驱动设备
	int fd = open("/dev/fb0",O_RDWR);
	if(fd < 0)
	{
		perror("open lcd failed");
		return -1;
	}
	

	
	//对LCD屏幕进行映射
	int *lcd = mmap(NULL,1024*600*4,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
	
	
	
	
	
	
	//打开图片
	int bmpfd= open(path,O_RDONLY);
	
	
	
	if(bmpfd < 0)
	{
		perror("open bmp failed");
		return -1;
	}
	
	//读取图片的头54个字节信息
	unsigned char head[54]={0};
	read(bmpfd,head,54);
	
	//解析宽度和高度
	int kuan = *((int *)&head[18]);
	int gao = *((int *)&head[22]);
	
	//printf("kuan=%d\n",kuan);
	//printf("gao=%d\n",gao);
	
	//变长数组
	int buf[gao][kuan];//32位图的buf
	char tmp_buf[gao*kuan*3];//24位图的tmp_buf
	
	//读取图片像素点的值存到tmp_buf
	read(bmpfd,tmp_buf,sizeof(tmp_buf));
	
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	unsigned char *p = tmp_buf ;
	unsigned int color =0;
	unsigned int x=0, y=0;
	
	for(y=0;y<gao;y++)
		for(x=0;x<kuan;x++)
		{
			b = *p++;
			g = *p++;
			r = *p++;
			
			a = 0;
			color = a << 24 | r << 16 | g << 8 | b;
			buf[y][x] = color;
			//*(lcd +(y)*1024 + (x))=buf[y][x];
			*(lcd +(gao-1-(y))*1024 + (x+(1024-kuan)/2))= buf[y][x];
		}
	
	
	//关闭LCD驱动设备
	close(fd);
	close(bmpfd);
	munmap(lcd,1024*600*4);
	//system("mplayer song.mp3   &");	
	
	
	
	
	
	
	
	return 0;
}

void ulock()
{
		int i,j,k=0;
	for(i=1;i<100;i++)
{
	for( j=1;j<1000;j++)
	{
	for( k=1;k<5000;k++)
	{

	}
	}
}
}

void *playgame(void *args)
{	
	
	/*char *imagePath="./pic";*/
	//初始化界面
	//showBMP("000.bmp");
	
	char *dishunumber[]={ "000.bmp","001.bmp","002.bmp","003.bmp","004.bmp","005.bmp","006.bmp","007.bmp","008.bmp","009.bmp"};
	int touch_fd=open("/dev/input/event2",O_RDONLY);
	if(touch_fd<0){
		perror("faild");
		
	}
	int clicknum;
	
	struct input_event ts_val;
	int x=0,y=0;
	while(1)
	{
		int j,i,k;
		//delay(3000);
		//delay(3000);
			//ulock();
sleep
		//clicknum=-1;
	 
		
		read(touch_fd,&ts_val,sizeof(ts_val));
		if(ts_val.type == EV_ABS)
		{
			if(ts_val.code == ABS_X)
			{
				x=ts_val.value;
				//printf("x=%d\n",x);
			}
				if(ts_val.code == ABS_Y)
			{
				y=ts_val.value;
				//printf("y=%d\n",y);
			}
		
		}
		
		if(ts_val.type ==EV_KEY)
			{
				if(ts_val.code == BTN_TOUCH)
				{
					printf("key=%d\n",ts_val.value);
					printf("x=%d\n",x);
					printf("=%d\n",y);
					if(ts_val.value==1)
					{	
						
						if(x>130 && x<320)
						{
							if(y>97 && y<175)
							{
								clicknum=1;
								if(randnum==1)
								{
									successclick("click.bmp");
										system("mplayer dishu.mp3  &");		
									 sleep(1);
										
								}
								printf("1");
							}
							if(y>260 && y<340)
							{
								clicknum=4;
								if(randnum==4)
								{
									
									successclick("click.bmp");
										system("mplayer dishu.mp3  &");		
									 sleep(1);
								
								}
								printf("4");
							}
							if(y>425 && y<503)
							{
								clicknum=7;
								if(randnum==7)
								{
									successclick("click.bmp");
										system("mplayer dishu.mp3  &");		
									
										 sleep(1);

								}
								printf("7");
							}
						}
						if(x>430 && x<600)
						{
							if(y>97 && y<175)
							{
								clicknum=2;
								if(clicknum==randnum)
								{
									successclick("click.bmp");
										system("mplayer dishu.mp3  &");		
										 sleep(1);
								}
								printf("2");
							}
							if(y>260 && y<340)
							{
								clicknum=5;
								if(randnum==5)
								{
									successclick("click.bmp");
										system("mplayer dishu.mp3  &");		
										 sleep(1);
								}
								printf("5");
							}
							if(y>425 && y<503)
							{
								clicknum=8;
								if(randnum==8)
								{
									successclick("click.bmp");
										system("mplayer dishu.mp3  &");		
										 sleep(1);	
								}
								printf("8");
							}
						}
						if(x>730 && x<900)
						{
							if(y>97 && y<175)
							{
								clicknum=3;
								if(randnum==3)
								{
									successclick("click.bmp");
										system("mplayer dishu.mp3  &");		
										 sleep(1);
								}
								printf("3");
							}
							if(y>260 && y<340)
							{
								clicknum=6;
								if(randnum==6)
								{
									successclick("click.bmp");
										system("mplayer dishu.mp3  &");		
									 sleep(1);
								}
								printf("6");
							}
							if(y>425 && y<503)
							{
								clicknum=9;
								if(randnum==9)
								{
									successclick("click.bmp");
										system("mplayer dishu.mp3  &");		
										 sleep(1);
								}
								printf("9");
							}
						}
					
						
					}
					
					//if(ts_val.value==0)
				//	{	
											
						//showBMP("000.bmp");						
						
					//}
					
						
						
						
						
					}
				
			}
			
	}
	close(touch_fd);	

}

void *autoswiper(void *args)
{
	printf("in swiper");
	
	char *dishunumber[]={ "000.bmp","001.bmp","002.bmp","003.bmp","004.bmp","005.bmp","006.bmp","007.bmp","008.bmp","009.bmp"};
	int touch_fd=open("/dev/input/event2",O_RDONLY);
	if(touch_fd<0){
		perror("faild");
	
	}
	struct input_event ts_val;
	int x=0,y=0;
	while(1)
	{printf("inging---");
		randnum=rand()%9+1;
		 showBMP(dishunumber[randnum]);
		 //ulock();
		 sleep(2);
	}
}
int main(){
 showBMP("000.bmp");
printf("foreard swiper");
	pthread_t t3;
	pthread_create(&t3, NULL, autoswiper, NULL);
		pthread_t t4;
	pthread_create(&t4, NULL, playgame, NULL);
 pthread_join(t3,NULL);
  pthread_join(t4,NULL);
 //pthread_join(t1,NULL);
return 0;
}