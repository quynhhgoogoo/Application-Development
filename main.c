//this program is for testing

#include "wave.h"
#include <stdio.h>
#include <signal.h>
#include <math.h>
#include <sys/wait.h>
#include "screen.h"
#include <stdlib.h>	//eliminate the warning when -c99 standard is used

//this program will open a wave file and dplay wav header siinfo
int main(int argc, char*argv[])
{
        FILE*fp;
        WAVHDR myhdr;
	short int sa[SAMPLE_RATE];
        int answer, ret;
       /* if(argc != 2)
        {
                printf("Usage : %s wave_file\n", argv[0]);
                return -1;
        }
        fp = fopen(argv[1], "r"); //try to open the wav file

 if(fp == NULL)
        {
                printf("Cannot find the file\n", argv[1]);
                return -1;
        }*/
	while(1){
		ret = system("arecord -r16000 -c1 -d1 -f S16_LE -q data.wav");
		clearScreen();	//a fresh screen to dplay
		if(WIFSIGNALED(ret) && (WTERMSIG(ret)==SIGINT || WTERMSIG(ret)==SIGQUIT))break;
		fp = fopen("data.wav", "r");	//open file to read dara
	        fread(&myhdr, sizeof(myhdr), 1, fp);	//read wav samples
	        displayWAVHDR(myhdr);	//kculate RSM value and display them
		fread(&sa, sizeof(short int), SAMPLE_RATE, fp);
		displayWAVdata(sa);
        	fclose(fp);
	}
        printf("Do you want to generate a test tone? (1:yes, 0:no)\n");
        scanf("%d", &answer);

	if(answer == 1) testTone(440, 5);
}

