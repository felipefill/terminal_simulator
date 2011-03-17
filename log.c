#include "log.h"

FILE* open_log(const char* mode)
{
/*
	Tries to open the log_file in the given mode.
	If it fails returns NULL
*/
	FILE* log_file;

	if( (log_file = fopen("logData.dat", mode)) == NULL ) //tries to open the file, if it's null then it failed
	{
		printf("Erro ao abrir o arquivo!\n");
		return NULL;
	}else
	{
		return log_file;
	}
}

char* get_time()
{
/*
	Returns the localtime
	hh:mm:ss format
*/
	char t[40]; //stores current time, unformatted
	char* ret;  //return var
	int i;		
	time_t lt;

	ret = (char*) malloc(sizeof(char) * SIZE_TIME); //allocating memory

	lt= time(NULL);
	strcpy(t, asctime(localtime(&lt))); //copying the time to t (currently unformatted)

	for( i = 0; i < SIZE_TIME - 1; i++ ) //let's format( hh:mm:ss starts at char 11 )
	{
		ret[i] = t[i+11]; //time starts at char 11
	}

	ret[SIZE_TIME - 1] = '\0';

	return ret;
}

char* get_date()
{
/*
	Returns the local date
	dd/mm/yy format
*/
	char* ret = (char*) malloc(sizeof(char) * SIZE_DATE); //allocating memory
    time_t t;
    struct tm *tmp;

    t = time(NULL);
    tmp = localtime(&t);

    strftime(ret, SIZE_DATE, "%d%m%y", tmp); //copies into ret the date in ddmmyy format

	//its ddmmyy let's make it dd/mm/yy

	ret[8] = '\0'; //end of string
	ret[7] = ret[5]; ret[6] = ret[4]; //year
	ret[5] = '/';
	ret[4] = ret[3]; ret[3] = ret[2]; //month
	ret[2] = '/';
	//day is ok already

	return ret;
}

void save_log(command* cmd)
{
/*
	Adds the cmd command to the log_file
*/
	FILE* log_file = open_log("at"); //opens the file to append

	fwrite(cmd, sizeof(command), 1, log_file); //writes the struct in

	close_log(log_file); //closes the file
}

void read_log()
{
/*
	Reads the log file and print its content on the screen.
*/
	command* cmd;
	long size;
	int i, count;
	FILE* log_file = open_log("r"); //opens the file to read

	if( log_file == NULL ) //if the pointer is null then there's no log!
	{
		printf("nao existe log\n");
		return;
	}

	fseek(log_file, 0, 2); //goes to end of file

	size = ftell(log_file); //gets the file's size in bytes (ps: it has to be in the end of the file to be accurate)

	count = (int) ( size / sizeof(command) ); // total size / size of one = number of structs in the file

	fseek(log_file, 0, 0); //begin of file :)

	cmd = (command*) malloc(sizeof(command)*count); //aux command

	fread(cmd, sizeof(command)*count, count, log_file);

	printf("******************************************************\n");

	for( i = 0; i < count; i++)
	{
		if( strcmp("fim", cmd[i].line ) != 0 )
		{
			printf("Data: %s, hora: %s ~ Comando %d: %s\n", cmd[i].date, cmd[i].time, cmd[i].count, cmd[i].line);
		}else
		{
			//if the command was quit then a user's session was over.
			printf("******************************************************\n");
		}
	}

	free(cmd); //deallocate memory

	close_log(log_file); //closes the log file
}

void close_log(FILE* log_file)
{
/*
	Closes the given file;
*/
	fclose(log_file);
}
