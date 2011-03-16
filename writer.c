#include "log.h"

int main()
{
	char line[SIZE_LINE];
	int count = 0;
	command cmd;

	do
	{
		printf(">");
		gets(line);

		count++;

		strcpy( cmd.line, line );
		strcpy( cmd.time, get_time() );
		strcpy( cmd.date, get_date() );
		cmd.count = count;

		save_log(&cmd);

		if( strcmp(line, "quit") != 0 )
		{
			system(line);
		}else
		{
			return 0;
		}

	}while(1);
}
