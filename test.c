
//this program is for testing

#include "wave.h"
#include <stdio.h>
#include <math.h>

//this program will open a wave file and dplay wav header siinfo
int main(int argc, char*argv[])
{
	FILE*fp;
	WAVHDR myhdr;
	int answer;
	if(argc != 2)
	{
		printf("Usage : %s wave_file\n", argv[0]);
		return -1;
	}
	fp = fopen(argv[1], "r"); //try to open the wav file
	if(fp == NULL)
	{
		printf("Cannot find the file\n", argv[1]);
		return -1;
	}
	fread(&myhdr, sizeof(myhdr), 1, fp);
	displayWAVHDR(myhdr);
	fclose(fp);
	printf("Do you want to generate a test tone? (1:yes, 0:no)\n");
	scanf("%d", &answer);
	if(answer == 1)	testTone(1000, 5);
}

void testTone(int freq, double d)
{
	FILE*fp;
	int i;
	WAVHDR h;
	short int sample;
	fp = fopen("testtone.wav", "w");
	fillID("RIFF", h.ChunkID);
	//chunksizll be calculated later
	fillID("WAVE", h.Format);
	fillID("fmt ", h.Subchunk1ID);
	h.Subchunk1Size = 16;
	h.AudioFormat = 1;
	h.SampleRate = SAMPLE_RATE;
	h.BitsPerSample = 16;
	h.ByteRate = SAMPLE_RATE*h.NumChannels*(h.BitsPerSample/8);
	h.BlockAlign = h.NumChannels*(h.BitsPerSample/8);
	fillID("data", h.Subchunk2ID);
	h.Subchunk2Size = d*SAMPLE_RATE*(h.BitsPerSample/8);
	fillID("data", h.Subchunk2ID);
	h.Subchunk2Size = (int)h.ByteRate*d;
	h.ChunkSize = h.Subchunk2Size + 36;
	fwrite(&h, sizeof(h), 1, fp);
	for(i=0; i<d*SAMPLE_RATE; i++)
	{
		sample = 32768*sin(2*PI*freq*i/SAMPLE_RATE);
		fwrite(&sample, sizeof(sample), 1, fp);
	}
	fclose(fp); 
}

void displayWAVHDR(WAVHDR hdr)
{
	double duration;
        printf("ChunkID: ");    printID(hdr.ChunkID);
        printf("ChunkSize: %d\n", hdr.ChunkSize);
        printf("Format: ");     printID(hdr.Format);
        printf("Subchunk1 ID; ");       printID(hdr.Subchunk1ID);
        printf("Subchunk1 Size: %d\n", hdr.Subchunk1Size);
        printf("Audio Format: %d\n", hdr.AudioFormat);
        printf("Number of Channel: %d\n", hdr.NumChannels);
        printf("Sample Rate; %d\n", hdr.SampleRate);
        printf("Byte Rate: %d\n", hdr.ByteRate);
        printf("Block Align: %d\n", hdr.BlockAlign);
        printf("Bits per Sample: %d\n", hdr.BitsPerSample);
        printf("Subchunk2 ID; ");       printID(hdr.Subchunk2ID);
        printf("Subchunk2 Size: %d\n", hdr.Subchunk2Size);
	duration = (double)hdr.Subchunk2Size/hdr.ByteRate;
	printf("Duration of Audio %.3f sec\n", duration);
}

void printID(char id[])
{
	int i;
	for(i=0; i<4; i++) putchar(id[i]);
	printf("\n");
}

void fillID(const char*s, char d[])
{
	int i;
	for(i=0; i<4; i++)	d[i] = *s++;
}
