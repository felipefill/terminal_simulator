/**
	Trabalho para a disciplina de Sistemas Operacionais II
	Simula um terminal e grava um log com os comandos digitados.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define SIZE_DATE 9		   //  dd/mm/yy
#define SIZE_TIME 9		   //  hh:mm:ss
#define SIZE_LINE 200

typedef struct
{ //struct for the command's info
	char line[SIZE_LINE];
	char date[SIZE_DATE];
	char time[SIZE_TIME];
	int  count;
} command;

char* get_time(); //returns current time
char* get_date(); //returns current date

FILE* open_log(const char* mode); //opens the log file using the given mode
void save_log(command* cmd); //inserts the command into the log file
void read_log(); //reads the log
void close_log(FILE* log_file); //closes the log file

