#include <headers.h>
void catchc()
{
	kill(child_pid,9);
	return;
}
/*void catchz()
{
//	printf("C_PID = %d",child_pid );
	kill(child_pid,SIGTTIN);
	kill(child_pid,SIGTSTP);
	bg_proc temp;
	strcpy(temp.proc_name,name_of_proc);
	temp.proc_pid = child_pid;
	char ans;
	ans = state(child_pid);
//	printf("ANS = %c",ans);
	if(ans > 'n' && ans < 'n')
		temp.proc_state = ans,proc_jobs[total] = temp;
	total+=1;
	//printf("TOTAL = %d",total);
	return;
}*/
void compare(char **args)
{
	int i=0;
	while(args[i]!=NULL || i < cnt)
	{
		//printf("%s",args[i]);
		if(args[i]==NULL)
		{
			//printf("f");
			i+=1;
			continue;
		}
		if(strcmp(args[i],"pwd")==0)
		{
			printf("pwd executes");
			char *x;
			x = execPwd();
			printf("%s\n",x);
			i++;
		}
		else if(strcmp(args[i],"echo")==0)
		{
			//printf("echo executes");
			int j = i+1;
			while(args[j]!=NULL)
				printf("%s ",args[j]),j++;
			printf("\n");
			i+=j;
		}
		else if(strcmp(args[i],"cd")==0)
		{
			//printf("%s",args[i+1]);
			if(args[i+1] == NULL)
			{
				i+=2;
				printPrompt(home1,1);
				continue;
			}
			else if(strcmp(args[i+1],"~")==0)
				printPrompt(home1,1);
			else if(strcmp(args[i+1],".")==0)
				printPrompt(home1,2);
			else if(strcmp(args[i+1], "..")==0)
				printPrompt(home1,3);
			else
				printPrompt(args[i+1],4);
			i+=1;
		}
		else if(strcmp(args[i],"ls")==0)
		{
			//printf("LS executes");
			char *dir;
			int fl=0;
			if(args[i+1]==NULL)
				fl=1,dir = home1;
			else if(args[i+1][0]=='-')
			{		
				if(args[i+2]==NULL)
					dir = home1;
				else if(args[i+2][0]=='-')
				{
					fl = 2;
					if(args[i+3]==NULL)
						dir = getdir(args[i+3],0);
					else
						dir = getdir(args[i+3],1);

				}
				else
					dir = getdir(args[i+2],1);
			}
			else
				fl=1,dir = getdir(args[i+1],1);
			//printf("%s",dir);
			if(fl==1)
				execLs(dir),i--;
			else if(fl==2)
				execLs_la(dir),i++;
			else if(strcmp(args[i+1],"-l")==0)
				execLs_l(dir);
			else if(strcmp(args[i+1],"-a")==0)
				execLs_a(dir);
			else if(strcmp(args[i+1],"-al")==0 || strcmp(args[i+1],"-la")==0)
				execLs_la(dir);
			i+=2;
		}
		else if(strcmp(args[i],"pinfo")==0)
			pinfo(args),i++;
		else if(strcmp(args[i],"remindme")==0)
		{
			pid_t pid;
			pid = fork();
			if(!pid)
			{
				sleep(atoi(args[i+1]));	
				int j=i+2;
				printf("Reminder :");
				while(args[j]!=NULL)
				printf("%s ",args[j]),j++;
				i+=(j+2);
			}
			break;
		}
		else if(strcmp(args[0],"clock")==0)
		{
			//args[0] args[1] -t // args[2]interval // args[3]n args[4] duration
			int t = 0;
			int duration;
			duration = atoi(args[4]);
			int interval = atoi(args[2]);
			char rtc[num2],rtc_r[num2];
			strcpy(rtc,"/proc/driver/rtc");
			while(1)
			{
				FILE *fd = fopen(rtc,"r");
				fgets(rtc_r,256,fd);
				char **time = parseCmd(rtc_r);
				time[1] = strtok(time[1],"\n");
				printf("%s ",time[1]);
				fgets(rtc_r,256,fd);
				char **date = parseCmd(rtc_r);
				printf("%s",date[1]);
				sleep(interval);
				fclose(fd);
				t += interval;
				if(t>=duration)
					return;
			}
		}
		else if(strcmp(args[i],"setenv")==0)
		{
			if(args[3] != NULL)
			{
				printf("Too many arguments\n");
				return;
			}
			else if(args[1] == NULL)
			{
				printf("Env needed\n");
				return;
			}
			else 
			{
				if(args[2] == NULL) args[2] = " ";
				if(setenv(args[1],args[2],1)!=0)
					perror("shell");
			}
			return;
		}
		else if(strcmp(args[i],"unsetenv")==0)
		{
			if(args[1] == NULL)
				printf("Specify the argument");
			else
				unsetenv(args[1]);
			return;
		}
		else if(strcmp(args[i],"jobs")==0)
		{
			jobs();
			return;
		}
		else if(strcmp(args[i],"kjob")==0)
		{
			kill_job(args);
			return;
		}
		else if(strcmp(args[i],"fg")==0)
		{
			int jobno;
			if(args[1] == NULL)
			{
				printf("Too few Arguments\n");
				return;
			}
			else if(args[2] != NULL)
			{
				printf("Too many Arguments\n");
				return;
			}
			jobno = atoi(args[1]);
			if(jobno>total)
			{
				printf("No such job exists\n");
				return;
			}
			child_pid = proc_jobs[jobno-1].proc_pid;
			strcpy(name_of_proc,proc_jobs[jobno-1].proc_name);
			printf("PID = %d is running in foreground\n",child_pid);
			loop(i,jobno,total)
				proc_jobs[i-1] = proc_jobs[i];
			total-=1;
			int status,pid1,temp;
			temp = child_pid;
			kill(temp,SIGCONT);
			signal(SIGTSTP,catchz);
			signal(SIGINT,catchc);
			pid1 = waitpid(child_pid,&status,WUNTRACED);
			//while(!WIFEXITED(status) && !WIFSIGNALED(status))
    		//	pid1 = waitpid(child_pid, &status, WUNTRACED);
			return;
		}
		else if(strcmp(args[i],"bg")==0)
		{
			int jobno;
			if(args[1]==NULL)
			{
				printf("Too few Arguments\n");
				return;
			}
			else if(args[2] != NULL)
			{
				printf("Too many Arguments\n");
				return;
			}
			jobno = atoi(args[1]);
			if(jobno>total)
			{
				printf("No such job exists\n");
				return;
			}
			//strcpy(proc_jobs[jobno-1].proc_state,"Running");
			//kill(proc_jobs[jobno-1].proc_pid,SIGTTIN);
			kill(proc_jobs[jobno-1].proc_pid,SIGCONT);
			return;
		}
		else if(strcmp(args[i],"overkill")==0)
		{
			loop(i,0,total)
				kill(proc_jobs[i].proc_pid,SIGKILL);
		}
		else if(strcmp(args[i],"quit")==0)
		{
			exit(0);
		}
		else
		{
			fg(args);
			return;
		}
		//	printf("FG executes"),fg(args),i++;
		i++;
	}
}
