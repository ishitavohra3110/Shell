#include <headers.h>
char state(int pid)
{
	char buf[num],buf1[num];
	sprintf(buf,"/proc/%d/status",pid);
	FILE* fd = fopen(buf,"r");
	char a;
	a = 'n';
	if(fd < 0)
		return a;
	int x;
	fgets(buf1,256,fd);
	fgets(buf1,256,fd);
	fgets(buf1,256,fd);
	char **ps = parseCmd(buf1);
	int len = strlen(ps[0]);
	return ps[0][len-1];
}
void catchz()
{
	//printf("C_PID = %d",child_pid );
	kill(child_pid,SIGTTIN);
	kill(child_pid,SIGTSTP);
	bg_proc temp;
	strcpy(temp.proc_name,name_of_proc);
	temp.proc_pid = child_pid;
	char ans;
	ans = state(child_pid);
	//printf("ANS = %c",ans);
	if(ans > 'n' && ans < 'n')
		temp.proc_state = ans,proc_jobs[total] = temp;
	total+=1;
	//printf("TOTAL = %d",total);
	return;
}
void fg(char **args)
{
	pid_t pid,pid1;
	strcpy(name_of_proc,args[0]);
	pid = fork();
	child_pid = pid;
	//printf("CHILD = %d\n",child_pid);
	int status;
	if(pid == 0)
	{
		signal(SIGINT,SIG_DFL);
		signal(SIGTSTP,catchz);
		//printf("%s\n",name_of_proc);
		if(execvp(args[0],args) == -1)
			perror("exec");
	}
	else
	{
		//signal(SIGTSTP,catchz);

		pid1 = waitpid(pid,&status,WUNTRACED);
		/*if(!WIFSIGNALED(status))
		{
			bg_proc temp;
			strcpy(temp.proc_name,name_of_proc);
			temp.proc_pid = child_pid;
			char ans;
			ans = state(child_pid);
			printf("ANS = %c",ans);
			if(ans > 'n' && ans < 'n')
				temp.proc_state = ans,proc_jobs[total] = temp;
			total+=1;
		}*/

		// while(!WIFEXITED(status) && !WIFSIGNALED(status))
    		// pid1 = waitpid(pid, &status, WUNTRACED);
	}
    return; 
}
void bg(char **args)
{
	args[cnt-1] = NULL;
	pid_t pid;
	int status;
	pid = fork();
	if(pid < 0)
	{	
		printf("Forking Error!");
		return;
	}
	else if(pid == 0)
	{
		setpgid(0,0);
		status = execvp(args[0],args);
		if(status==-1)
		{
			printf("Command not found!");
			exit(0);
		}

	}
	else if(pid!=0)
	{
		strcpy(name[pid],args[0]);
		bg_proc temp;
		temp.proc_pid = pid;
		strcpy(temp.proc_name,args[0]);
		char ans;
		ans = state(pid);
		if(ans > 'n' || ans < 'n')
		{
			temp.proc_state = ans;
			proc_jobs[total++] = temp;
		}
	}
	return;
}
void finish()
{
	//printf("finish");
	pid_t pid;
	int status;
	pid = waitpid(-1,&status,WNOHANG);
	while(1)
	{
		if(pid>0)
		{
			printf("%s having pid %d exited\n",name[pid],pid);
			int var = total;
			int temp;
			while(var--)
			{
				if(proc_jobs[var].proc_pid == pid)
					temp = var;
			}
			loop(i,temp,total)
				proc_jobs[i] = proc_jobs[i+1];
			total--;


		}
		else
			return;
		pid = waitpid(-1,&status,WNOHANG);
	}
}
void jobs()
{
	char ans;
	loop(i,0,total)
	{
		ans = state(proc_jobs[i].proc_pid);
	//	printf("ANS = %c ",ans);
		if(ans == 'n') continue;
		printf("[%d] %c %s[%d]\n",i+1,ans,proc_jobs[i].proc_name,proc_jobs[i].proc_pid);
	}
	return;
}
void kill_job(char **args)
{
	pid_t pid;
	if(args[1]==NULL || args[2]==NULL )
	{
		printf("Too few Arguments\n");
		return;
	}
	else if(args[3]!=NULL)
	{
		printf("Too many Arguments\n");
		return;
	}
	int i = atoi(args[1]);
	if(i > total)
	{
		printf("No such job exists");
		return;
	}
	int sig = atoi(args[2]);
	pid = proc_jobs[i-1].proc_pid;
	kill(pid,sig);
	return;
}