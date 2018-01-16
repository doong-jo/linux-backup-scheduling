/*

GPL 2.0

Fsarchiver + termbackup, logwriter 작성자 : 조성동, 정하민

sdong001@gmail.com, wjdgkals74@gmail.com


*/


#include <stdio.h>
#include <time.h>
#include <string.h>
#include "logwriter.h"


void dateWriteBuf(int _date, char* _IntToString, char* _buf, char* _catChar)
{
	sprintf(_IntToString, "%d", _date);
	strcat(_buf, _IntToString);

	strcat(_buf, _catChar);
}

void LogWrite(char ** argvStrs)
{
	char fileName[256] = '\0';
	char sIntToString[10] = '\0';
	char buf[2048] = '\0';

	time_t timer = time(NULL);

	struct tm *t;

	t = localtime(&timer);

	int year = t->tm_year + 1900;
	int month = t->tm_mon + 1;
	int day = t->tm_mday;
	int hour = t->tm_hour;
	int min = t->tm_min;
	int sec = t->tm_sec;


	strcat(fileName, "./LogSaveDir/LogWriter_");
	sprintf(sIntToString, "%d", year);
	strcat(fileName, sIntToString);
	strcat(fileName, "-");
	sprintf(sIntToString, "%d", month);
	strcat(fileName, sIntToString);
	strcat(fileName, "-");
	sprintf(sIntToString, "%d", day);
	strcat(fileName, sIntToString);
	strcat(fileName, ".txt");

	FILE* fp = fopen(fileName, "at");

	strcat(buf, "LogWriter -> ");
	
	dateWriteBuf(year, sIntToString, buf, "-");
	dateWriteBuf(month, sIntToString, buf, "-");
	dateWriteBuf(day, sIntToString, buf, " ");
	dateWriteBuf(hour, sIntToString, buf, ":");
	dateWriteBuf(min, sIntToString, buf, ":");
	dateWriteBuf(sec, sIntToString, buf, " : ");
	
	
	/*
	sprintf(sIntToString, "%d", year);
	strcat(buf, sIntToString);

	strcat(buf, "-");

	sprintf(sIntToString, "%d", month);
	strcat(buf, sIntToString);

	strcat(buf, "-");

	sprintf(sIntToString, "%d", day);
	strcat(buf, sIntToString);

	strcat(buf, " ");

	sprintf(sIntToString, "%d", hour);
	strcat(buf, sIntToString);

	strcat(buf, ":");

	sprintf(sIntToString, "%d", min);
	strcat(buf, sIntToString);

	strcat(buf, ":");

	sprintf(sIntToString, "%d", sec);
	strcat(buf, sIntToString);


	strcat(buf, " : ");
	*/

	int i = 0;

	//printf("%s\n", argvStrs[0]);
	//strcat(buf, argvStrs[0]);
	//printf("%s\n", argvStrs[1]);
	//strcat(buf, argvStrs[1]);


	while( argvStrs[i] != NULL )
	{
		strcat(buf, argvStrs[i]);
		strcat(buf, " ");
		i++;
	}
	strcat(buf, "\n");


	fwrite(buf, 1, strlen(buf)+1, fp);


	fclose(fp);
}
