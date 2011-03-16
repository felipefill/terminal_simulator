#include "log.h"

FILE* open_log(int id)
{
/*
	id = 0 ~ append
	id = 1 ~ read
*/
	FILE* log_file;

	if( id == 0 )
	{

		if( (log_file = fopen("logData.dat", "at")) == NULL )
		{
			printf("Erro ao abrir o arquivo!");
			return NULL;
		}else
		{
			return log_file;
		}

	}else
	{
		if( (log_file = fopen("logData.dat", "r")) == NULL )
		{
			printf("Erro ao abrir o arquivo!");
			return NULL;
		}else
		{
			return log_file;
		}

	}
}

char* get_time()
{
	char t[40];
	char* ret;
	int i;
	time_t lt;

	ret = (char*) malloc(sizeof(char) * SIZE_TIME);

	lt= time(NULL);
	strcpy(t, asctime(localtime(&lt)));

	for( i = 0; i < SIZE_TIME - 1; i++ )
	{
		ret[i] = t[i+11]; //time starts at char 11
	}

	ret[SIZE_TIME - 1] = '\0';

	return ret;
}

char* get_date()
{
	char* ret = (char*) malloc(sizeof(char) * SIZE_DATE);
    time_t t;
    struct tm *tmp;

    t = time(NULL);
    tmp = localtime(&t);

    strftime(ret, SIZE_DATE, "%d%m%y", tmp);

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
	FILE* log_file = open_log(0);

	fwrite(cmd, sizeof(command), 1, log_file);

	close_log(log_file);
}

void read_log()
{
	command* cmd;
	long size;
	int i, count;
	FILE* log_file = open_log(1);

	fseek(log_file, 0, 2); //fim do arquivo

	size = ftell(log_file); //tamanho do arquivo

	count = (int) ( size / sizeof(command) );

	fseek(log_file, 0, 0); //começo do arquivo

	cmd = (command*) malloc(sizeof(command)*count);

	fread(cmd, sizeof(command)*count, count, log_file);

	for( i = 0; i < count; i++)
	{
		if( strcmp("quit", cmd[i].line ) != 0 )
		{
			printf("Data: %s, hora: %s ~ Comando %d: %s\n", cmd[i].date, cmd[i].time, cmd[i].count, cmd[i].line);
		}else
		{
			printf("******************************************************\n");
		}
	}

	close_log(log_file);
}

void close_log(FILE* log_file)
{
	fclose(log_file);
}
