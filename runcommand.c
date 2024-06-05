#include "smallsh.h"

/* wait를 선택사항으로 하여 명령을수행한다. */
int runcommand(char **cline, int where, char *infile, char *outfile, BOOLEAN append)
{
	pid_t pid;
	int status;
    	int fd;

	if(strcmp(*cline, "cd") == 0){
                char * path = cline[1];
                if(path==NULL||path==""){
                        chdir(getenv("HOME"));
                         char cdir[1024];
                         memset(&cdir[0], 0, sizeof(cdir));
                         getcwd(cdir, sizeof(cdir));
                         printf("%s\n", cdir);
                }
                else if(path!=NULL){
                        if(path[0]=='/'){
                                int chdirValue = chdir(path);
                                if(chdirValue != 0){
                                        printf("존재하지 않는 폴더입니다.\n");
                                }
                                char cdir[1024];
                                memset(&cdir[0], 0, sizeof(cdir));
                                getcwd(cdir, sizeof(cdir));
                                printf("%s\n", cdir);
                        }
                        else if(strcmp(path, "..")==0){
                                chdir(path);
                                char cdir[1024];
                                memset(&cdir[0], 0, sizeof(cdir));
                                getcwd(cdir, sizeof(cdir));
                                printf("%s\n", cdir);
                        }
                        else{
                                char slashPath[1024];
                                memset(&slashPath[0], 0, sizeof(slashPath));
                                slashPath[0]='/';
                                strcat(slashPath, path);
                                char cdir[1024];
                                memset(&cdir[0], 0, sizeof(cdir));
                                if(getcwd(cdir, sizeof(cdir))!=NULL){
                                        strcat(cdir, slashPath);
                                        int chdirValue = chdir(cdir);
                                        if(chdirValue!=0){
                                                printf("존재하지 않는 폴더입니다.\n");
                                        }
                                }
                                printf("%s\n", cdir);
                        }
                }
        }
        else if(strcmp(*cline, "exit")==0){
                exit(0);
        }
        else if(strcmp(*cline, "path")==0){
                char *path = cline[1];
                if(path != NULL){
                        set_path(path);
                }else{
                        printf("사용법: path <path1> \n");
                }
        }
        else if(strcmp(*cline, "showpath")==0){
                show_path();
        }
        else{
            switch(pid = fork()) {
                case -1 :
                    perror("smallsh");
                    return (-1);
                case 0:
                // 리다이렉션 설정
                    if (infile[0] != '\0') {
                        fd = open(infile, O_RDONLY);
                        if (fd < 0) {
                            perror(infile);
                            exit(1);
                        }
                        dup2(fd, STDIN_FILENO);
                        close(fd);
                    }
                    if (outfile[0] != '\0') {
                        if (append) {
                            fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
                        } else {
                            fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                        }
                        if (fd < 0) {
                            perror(outfile);
                            exit(1);
                        }
                        dup2(fd, STDOUT_FILENO);
                        close(fd);
                    }
                    execvp(cline[0], cline);
                    perror(cline[0]);
                    exit(1);
            } /* End of switch */
        }
	/* 부모의 코드 */
	/* 만일백그라운드 프로세스이면 프로세스 식별자를 프린트하고 퇴장한다. */
	if (where == BACKGROUND)
	{
		printf("[Process id %d]\n",pid);
		return (0);
	}

	/* 프로세스 pid가 퇴장할 때까지 기다린다. */
	if(waitpid(pid, &status, 0) == -1)
		return (-1);
	else
		return (status);
} /* End of runcommadn */
