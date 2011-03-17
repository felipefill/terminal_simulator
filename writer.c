#include "log.h"

int main()
{
	char line[SIZE_LINE]; //string that'll store the command
	int count = 0; //command's number
	command cmd; //command itself (view log.h)

	do
	{
		printf(">"); //waiting for the command
		gets(line); //getting the command

		count++; //increasing the counter

		strcpy( cmd.line, line ); //copying the command to struct
		strcpy( cmd.time, get_time() ); //getting the time
		strcpy( cmd.date, get_date() ); //getting the date
		cmd.count = count; //command's number

		save_log(&cmd); //saving log

		if( strcmp(line, "fim") != 0 ) //if the command wasn't EXIT then we'll exit
		{
			system(line); //executes the command
		}else
		{
			return 0;
		}

	}while(1);
}
