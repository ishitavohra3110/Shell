#include <headers.h>
char* execPwd()
{	
	return home1;
}
void pinfo(char** args)
{
	pid_t pid;
	if(args[1]==NULL)
	{
		pid = getpid();
	}
	else
		pid = atoi(args[1]);
	printf("pid: %d\n",pid);
	char buf[num2],ptr[num2];
	sprintf(buf,"/proc/%d/status",pid);
	FILE* fd = fopen(buf,"r");
	if(!fd)
		perror("lsh");
	else
	{
		int x;
		while(fscanf(fd,"%s",ptr)!=EOF)
		{
			//printf("%s",ptr);
			if(strcmp(ptr,"State:") == 0)
			{
				while(strcmp(ptr,"Tgid:")!=0)
					printf("%s ",ptr),fscanf(fd,"%s",ptr);
				printf("\n");
			}
			else if(strcmp(ptr,"VmSize:")==0)
			{
				while(strcmp(ptr,"VmLck:")!=0)
					printf("%s ",ptr),fscanf(fd,"%s",ptr);
				printf("\n");
			}

		}
		memset(buf,0,sizeof(char));
		sprintf(buf,"/proc/%d/cmdline",pid);
		FILE *fp = fopen(buf,"r");
		if(fp)
		{
			printf("Executable file: ");
			int r = getc(fp);
			while(r != EOF)
				putchar(r),r = getc(fp);

		}
		printf("\n");
	}
}
