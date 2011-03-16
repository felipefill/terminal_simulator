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
	char* t;
	time_t lt= time(NULL);
  	
	t = (char*) malloc( sizeof(char) * strlen(asctime(localtime(&lt))) + 1);

	strcpy(t, asctime(localtime(&lt)));

	return t;
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
		printf("%s ~ %s\n-------\n", cmd[i].date, cmd[i].line);
	}

	close_log(log_file);
}

void close_log(FILE* log_file)
{
	fclose(log_file);
}
