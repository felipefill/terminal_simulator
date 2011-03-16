#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define SIZE_DATE 9
#define SIZE_TIME 9
#define SIZE_LINE 200

typedef struct
{
	char line[SIZE_LINE];
	char date[SIZE_DATE];
	char time[SIZE_TIME];
	int  count;
} command;

FILE* open_log(int id);

char* get_time();

char* get_date();

void save_log(command* cmd);

void read_log();

void close_log(FILE* log_file);
