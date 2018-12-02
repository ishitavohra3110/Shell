#include <headers.h>
//#define num 1024
int flag = 0;
char* path;
char present[num] = "~";
char* thepath(char *cur,int val)
{
	//printf("%s",cwd);
	if(val == 0)
	{
		if(strcmp(present,"~")!=0)
			strcpy(home1,present);
		return present;
	}
	else if(val == 1)
	{
		//printf("1");

		strcpy(home1,cwd);
		strcpy(present,"~");
		return present;
	}
	else if(val == 2)
	{
		//printf("2");
		return home1;
	}
	else if(val == 3)
	{
		int p;
		flag = 1;
		//printf("%s %s",cur,cwd);
		if(strcmp(cur,"/home")==0 || strcmp(cur,"/")==0)
		{
			strcpy(home1,"/");
			strcpy(present,"/");
			return present;
		}
		if(strcmp(cur,cwd)==0)
		{
			strcpy(present,cwd);
			//printf("3.1");
			rloop(i,strlen(cwd)-1,0)
			{
			//	printf("%s\n",cwd);
				if(cwd[i]=='/')
				{
					p = i;
					break;
				}
			}
		}
		else
		{
		//	printf("3.2");
			rloop(i,strlen(present)-1,0)
			{
				if(present[i]=='/')
				{
					p = i;
					break;
				}	
			}
		}
		memset(cur,0,sizeof(cur));
		loop(i,0,p)
			cur[i] = present[i];
		memset(present,0,sizeof(present));
		loop(i,0,p)
			present[i] = cur[i];
		//printf("%s\n",present);
		return present;
	}
	else 
	{
		flag = 1;
		int test;
		if(cur[0]=='/')
		{
			//printf("4.1");
			strcpy(present,cur);
			test = chdir(present);
		//	printf("%s",present);
			if(test == -1)
			{
				perror("Error ");
				strcpy(present,home1);
			}
			else
			{
				strcpy(home1,present);

			}
		}
		else
		{
			//printf("4.2");
			strcat(present,"/");
			strcat(present,cur);
			test = chdir(present);
			if(test == -1)
			{
				perror("Error ");
				strcpy(present,home1);
			}
			else
				strcpy(home1,present);
		}
		//printf("Pre = %s C = %s",present,cwd);
		if(strcmp(present,cwd)==0)
			strcpy(present,"~");
		return present;
	}
	
}
void printPrompt(char *cur,int val)
{
	char *user;
	char hostname[num];
	user = getenv("USER");
	gethostname(hostname,sz(hostname));
	path = thepath(cur,val);
	if(flag)
		strcpy(path,present);
	if(val)
		return;
	printf(GRN "<%s@%s" RESET,user,hostname);
	printf(":");
	printf(BLU "%s>" RESET,path);
	return;
}
char *getdir(char *dir,int val)
{
	static char ans[num2];
	//printf("VAL = %s HOME = %s\n",dir,home1);
	//printf("VALUE = %d",val);
	if(val == 0)
		return home1;
	else
	{
		if(dir[0]=='/')
			strcpy(ans,dir);
		else
		{
			strcpy(ans,home1);
			strcat(ans,"/");
			strcat(ans,dir);
		}
	}
	//printf("%s",ans);
	return ans;

}
