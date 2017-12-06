/*
 * fsarchiver+logwrter_termbackup: Filesystem Archiver add optional backup function
 *
 * Copyright (C) 2017 Jipuragi.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License v2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * Homepage: http://github.com/sdong001/oss_hw4/
 * Email : sdong001@gmail.com wjdgkals74@gmail.com

*/

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "logwriter.h"

void LogWrite(char ** argvStrs)
{
	char fileName[256] = { \0 };
	char sIntToString[10] = { \0 };
	char buf[2048] = { \0 };

	time_t timer = time(NULL);

	int year = t->tm_year + 1900;
	int month = t->tm_mon + 1;
	int day = t->tm_mday;
	int hour = t->tm_hour;
	int min = t->tm_min;
	int sec = t->tm_sec;

	struct tm *t;

	t = localtime(&timer);

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

	int i = 0;

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
