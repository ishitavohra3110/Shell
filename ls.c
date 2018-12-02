#include <headers.h>
void execLs(char *dir)
{
	DIR*p;
	struct dirent *d;
	p = opendir(dir);
	if(p == NULL)
		perror("Cannot find directory");
	else
	{
		while(d = readdir(p))
		{
			if(d->d_name[0] == '.')
				continue;
			printf("%s\n",d->d_name);
		}
	}
}
void permissions(char *file)
{
	char perm[11];
	struct stat st;
	stat(file,&st);
	if(S_ISDIR(st.st_mode))
		perm[0] = 'd';
	else if(S_ISREG(st.st_mode))
		perm[0] = '-';
	else if(S_ISFIFO(st.st_mode))
		perm[0] = '|';
	else if(S_ISSOCK(st.st_mode))
		perm[0] = 's';
	else if(S_ISCHR(st.st_mode))
		perm[0] = 'c';
	else if(S_ISBLK(st.st_mode))
		perm[0] = 'b';
	else
		perm[0] = 'l';
	perm[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
	perm[2] = (st.st_mode & S_IWUSR)  ? 'w' : '-';
	perm[3] = (st.st_mode & S_IXUSR)  ? 'x' : '-';
	perm[4] = (st.st_mode & S_IRGRP)  ? 'r' : '-';
	perm[5] = (st.st_mode & S_IWGRP)  ? 'w' : '-';
	perm[6] = (st.st_mode & S_IXGRP)  ? 'x' : '-';
	perm[7] = (st.st_mode & S_IROTH)  ? 'r' : '-';
	perm[8] = (st.st_mode & S_IWOTH)  ? 'w' : '-';
	perm[9] = (st.st_mode & S_IXOTH)  ? 'x' : '-';
	perm[10] = '\0';
	printf("%s ",perm);
	printf("%d ",(int)st.st_nlink);
	return;
}
void user_gp_time(char *file)
{
	struct group *grp;
	struct passwd *pwd;
	struct stat st; 
	char datestring[num2];
	struct tm time;
	stat(file,&st);
	int uid = st.st_uid;
	int gid = st.st_gid;
	grp = getgrgid(gid);
	printf("%s ",grp->gr_name);
	pwd = getpwuid(uid);
	printf("%s ",pwd->pw_name);
	printf("%d ",(int)st.st_size);
	localtime_r(&st.st_mtime,&time);
	strftime(datestring,sizeof(datestring),"%b %d %T",&time);
	printf("%s",datestring);
	return;

}
void execLs_l(char *dir)
{
	DIR*p;
	char *f;
	struct dirent *d;
	p = opendir(dir);
	if(p == NULL)
		perror("Cannot find directory");
	else
	{
		char now[num2],temp[num2];
		memset(now,0,sizeof(now));
		loop(i,0,strlen(dir))
			now[i]=dir[i];
		while(d = readdir(p))
		{
		//	break;

		//	printf("")
			if(d->d_name[0] == '.')
				continue;
			strcpy(temp,now);
			strcat(temp,"/");
			strcat(temp,d->d_name);
		//	printf("%s %s\n",temp,now);

			permissions(temp);
			user_gp_time(temp);
			printf(" %s\n",d->d_name);
		}
	}
}
void execLs_a(char *dir)
{
	DIR*p;
	struct dirent *d;
	p = opendir(dir);
	if(p == NULL)
		perror("Cannot find directory");
	else
	{
		while(d = readdir(p))
			printf("%s\n",d->d_name);
	}
}
void execLs_la(char *dir)
{
	DIR*p;
	char *f;
	struct dirent *d;
	p = opendir(dir);
	if(p == NULL)
		perror("Cannot find directory");
	else
	{
		char now[num2],temp[num2];
		memset(now,0,sizeof(now));
		loop(i,0,strlen(dir))
			now[i]=dir[i];
		while(d = readdir(p))
		{
			f = d->d_name;
			strcpy(temp,now);
			strcat(temp,"/");
			strcat(temp,f);
			permissions(temp);
			user_gp_time(temp);
			printf(" %s\n",d->d_name);
		}
	}
}