#include <headers.h>
int pipefd[2];
char in_file[10000],out_file[10000],buf[4];
int piping(char **args,char *cmd)
{
	int i=0;
	int in,out;
	in = 0;
	out = 0;
	int pipi = 0;
	while(args[i]!=NULL)
	{
		if(strcmp(args[i],"|")==0)
			pipi = 1;
		if(strcmp(args[i],">")==0)
			out = 1;
		if(strcmp(args[i],"<")==0)
			in = 1;
		i++;
	}
	//printf("PI %d",pipi);
	if(!pipi)
		return 0;
	i = 0;
	int cnt = 0,pos = 0;
	char *token;
	char **tokens;
	char delim[] ="|"; 
	char ***cmds;
	int nu_pi=1;
	while(args[i]!=NULL)
	{
		if(args[i][0]=='|')
			nu_pi++;
		i++;
	}
	//printf("%d",nu_pi);
	tokens = malloc(1024*sz(char));
	loop(i,0,nu_pi)
		cmds[i] = malloc(1024*sz(char));
	token = strtok(cmd,delim);//parse for piping
	while(token!=NULL)
	{
		tokens[pos] = token;
		token = strtok(NULL,delim);
		pos+=1;
	}
	i = 0;
	while(tokens[i]!=NULL)
	{
		pos = 0;
		token = strtok(tokens[i]," ");
		while(token!=NULL)
		{
			cmds[i][pos] = strdup(token);
			//printf("%s;",cmds[i][pos]);
			token = strtok(NULL," ");
			pos++;
		}
	//	printf("\n");
		i++;
	}
	int k,j;
	k = 0;
	j = 0;
	cmds[i] = NULL;
	if(out)
	{
		while(strcmp(cmds[i-1][j],">"))
			j++;
		strcpy(out_file,cmds[i-1][j+1]),cmds[i-1][j+1] = NULL;
		cmds[i-1][j]= NULL,cnt = i-1;
	//	printf("%s\n",out_file);
	}
	if(in)
	{
		strcpy(in_file,cmds[0][2]);
		k = 0,j = 0;
		while(k+1!=i)
		{
			while(cmds[k+1][j]!=NULL)
				strcpy(cmds[k][j],cmds[k+1][j]),/*printf("%s",cmds[k][j]),*/j++;
			cmds[k][j] = NULL;
			k++;
			j = 0;
		}
		cmds[k] = NULL;
		cnt = i-2;
		j = 0;
	//	while(cmds[j]!=NULL)
	//		printf("%s ",cmds[j][0]),j++;
	}
	else
		cnt = i-1;
	k = 0;
	int fd,fd1;
	pid_t pid1;
	fd = 0;
	i = 0;
	while(cmds[i]!= NULL)
	{
		pipe(pipefd);
		pid1 = fork();
		if(pid1 < 0)
		{
			perror("fork");
			exit(0);
		}
		else if(pid1 == 0)
		{
			if(in==1)
			{	
				in = 0;
				fd = open(in_file,O_RDONLY,0644);
				if(fd<0)
				{
					perror("Could not open input file\n");
					exit(0);
				}
			}
			close(0);
			dup2(fd,0);
			if(i==cnt && out)
			{
				fd = open(out_file,O_WRONLY | O_TRUNC | O_CREAT,0644);
				dup2(fd,1);
				close(fd);
			}
			if(i<=cnt-1)
			{
				close(1);
				close(pipefd[0]);
				dup2(pipefd[1],1);
			}
			execvp(cmds[i][0],cmds[i]);
			perror("exec");
			exit(0);
		}
		else
		{

			wait(NULL);
			in = 0;
			close(pipefd[1]);
			fd = pipefd[0];
			i++;
		}
	}
	return 1;
}