#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct
{
	char line[200];
	char date[50];
} command;

FILE* open_log(int id);

char* get_time();

void save_log(command* cmd);

void read_log();

void close_log(FILE* log_file);
