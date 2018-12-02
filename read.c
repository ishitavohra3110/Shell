#include <headers.h>
char *readCmd()
{
	int bufSize,pos;
	bufSize = num2;
	pos = 0;
	char *buf;
	buf = malloc(sizeof(char) * bufSize);
	int c;
	while(1)
	{
		c = getchar();
		if (c == EOF || c == '\n')
		{
			buf[pos] = '\0';
			return buf;
		}
		else
			buf[pos] = c;
		pos++;
	}

}
char **parseCmd(char *cmd)
{
	cnt = 0;
	int pos=0;
	char *token;
	char **tokens;
	tokens = malloc(num2 * sz(char));
	token = strtok(cmd," ");
	while(token!=NULL)
	{
		//printf("!");
		cnt+=1;
		tokens[pos] = token;
		token = strtok(NULL," ");
		if(strcmp(tokens[pos],";")==0)
			tokens[pos] = NULL;
		pos+=1;
	}
	return tokens;
}
