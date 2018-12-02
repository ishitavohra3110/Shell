#ifndef HEADERS_H
#define HEADERS_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <fcntl.h>
#include <headers.h>
#define GRN   "\x1B[32m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"
#define num 1024
#define sz sizeof
#define num2 800000
#define num1 5000
#define loop(i,a,b) for(int i=a;i<b;i++)
#define rloop(i,a,b) for(int i=a;i>=b;i--)
void printPrompt(char *cur,int val);
char *readCmd();
char **parseCmd(char *cmd);
void compare(char **args);
char* execPwd();
char* getdir();
void execLs();
void execLs_l();
void execLs_la();
void execLs_a();
void pinfo(char **args);
void fg(char **args);
void bg(char **args);
void finish();
void jobs();
void kill_job(char **args);
void send_signal();
void catchz();
void catchc();
char state(int pid);
int piping(char **args,char *cmd);
int redir(char **args);
int cnt,fl,jobs_cnt,total;
pid_t shell_pid,child_pid;
char name[num1][100];
char home1[num2],cwd[num2],name_of_proc[num2];
typedef struct{
	char proc_state;
	char proc_name[num1];
	pid_t proc_pid;
}bg_proc;
bg_proc proc_jobs[num];
//redir redirection flag
#endif