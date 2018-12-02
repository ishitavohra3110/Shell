#include <headers.h>
int main()
{
	//char cur[num];
	getcwd(home1,sz(home1));
	getcwd(cwd,sz(cwd));
	shell_pid = getpid();
	while(1)
	{
		char *cmd;
		char **args;
		char cur[num2];
		getcwd(cur,sz(cur));
		printPrompt(home1,0);
		signal(SIGINT,SIG_IGN);
		signal(SIGTSTP,SIG_IGN);
		int status;
		cmd = readCmd();
		char *store;
		store = strdup(cmd);
		args = parseCmd(cmd);
		fl = piping(args,store);
		if(fl)
			continue;
		fl = redir(args);
		if(fl)
			continue;
		finish();
		if(args[0] == NULL)
			continue;
		if(strcmp(args[cnt-1],"&")==0)
		{
			bg(args);
			continue;
		}
		compare(args);
	
    }
	return 0;
}