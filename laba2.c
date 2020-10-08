#include<stdio.h>
#include<TIME.H>
int main()
{
	int time2, hour, min, sec;
	time2 = time(NULL);
	hour = time2 % 3600;
	min = time2 % 60;
	sec = time2;
	
	printf(hour, time, sec, "%dhour, %dmin, %dsec");
}

