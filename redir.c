#include <headers.h>
int in,out,append;
int redir(char **args)
{
	int i=0,pid,pid1,status;
	in = 0,out = 0,append = 0;
	while(args[i]!=NULL)
	{
		if(strcmp(args[i],">>")==0)
			append=1;
		else if(strcmp(args[i],">")==0)
			out=1;
		else if(strcmp(args[i],"<")==0)
			in=1;
		i++;
	}
	if(in==0 && out == 0 && append == 0)
		return 0;	
	pid = fork();
	if(pid==0)
	{
		int fd;
		if(out)
		{
			int i=0;
			char out_file[10000];
			while(args[i]!=NULL)
			{
				if(strcmp(args[i],">")==0) 
				{
					args[i]=NULL;
					strcpy(out_file,args[i+1]);
					printf("%s %s %s",out_file,args[0],args[1]);
				}
				i++;
			}
			fd = open(out_file,O_WRONLY | O_TRUNC | O_CREAT,0644);
			dup2(fd,1);
			close(fd);
		}
		if(in)
		{
			int i=0;
			char in_file[10000];
			while(args[i]!=NULL)
			{
				if(strcmp(args[i],"<")==0)
				{
					args[i]=NULL;
					strcpy(in_file,args[i+1]);
				}
				i++;
			}
			fd = open(in_file,O_RDONLY,0644);
			if(fd<0)
			{
				perror("Could not open input file\n");
				exit(0);
			}
			dup2(fd,0);
			close(fd);
		}
		if(append)
		{
			int i=0;
			char out_file[10000];
			while(args[i]!=NULL)
			{
				if(strcmp(args[i],">>")==0) 
				{
					args[i]=NULL;
					strcpy(out_file,args[i+1]);
				}
				i++;
			}
			fd = open(out_file,O_WRONLY | O_APPEND | O_CREAT,0644);
			dup2(fd,1);
			close(fd);
		}
		signal (SIGINT, SIG_DFL); 
		if(execvp(args[0],args)<0)
		{
			perror("Error executing command\n");
			_exit(-1);
		}
	}
	else
	{
		wait(NULL);
	}

	return 1;
}
