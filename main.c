#include "log.h"

int main()
{
	char line[200];
	int opc;
	
	printf("0 para cmd, 1 para log: ");
	scanf("%d", &opc);

	if( opc == 0 )
	{

		do
		{
			printf(">");
			gets(line);

			if( strcmp(line, "quit") != 0 )
			{
				command cmd;
				strcpy( cmd.line, line );
				strcpy( cmd.date, get_time() );

				save_log(&cmd);

				system(line);
			}else
			{
				return 0;
			}

		}while(1);

	}else
	{
		read_log();
	}

	return 0;

}
