#include "smallsh.h"

int procline (void)
{
	char *arg[MAXARG + 1];
    char *pipe_arg[MAXARG + 1];
    char infile[MAXWORD] = "";
    char outfile[MAXWORD] = "";
    int toktype;
	int narg,pipe_narg;
	int type;
    BOOLEAN append = FALSE;

    narg = 0;
    pipe_narg = 0;

	for(;;)
	{
		/* 토큰유형에 따라 행동을 취한다. */
		switch (toktype = gettok(&arg[narg])) {
			case ARG :
				if(narg < MAXARG)
					narg++;
				break;
            case PIPE :
               if(narg != 0){
               arg[narg] = NULL;
               memcpy(pipe_arg, arg, (narg+1)*sizeof(char *));
               pipe_narg = narg;
               narg = 0;
            }
              break;
			case INPUT:
                toktype = gettok(&arg[narg]);
                strncpy(infile, arg[narg], MAXWORD - 1);
                infile[MAXWORD - 1] = '\0';  
                break;
            case OUTPUT:
                toktype = gettok(&arg[narg]);
                strncpy(outfile, arg[narg], MAXWORD - 1);
                outfile[MAXWORD - 1] = '\0';  
                break;
            case APPEND:
                toktype = gettok(&arg[narg]);
                strncpy(outfile, arg[narg], MAXWORD - 1);
                outfile[MAXWORD - 1] = '\0'; 
                append = TRUE;
                break;
            case EOL :
			case SEMICOLON :
            case AMPERSAND :
				if (toktype == AMPERSAND)
					type = BACKGROUND;
				else
					type = FOREGROUND;

				if(narg != 0)
                {
                    if(strcmp(arg[0], "#") == 0)
                        printf("주석으로 처리된 명령어입니다.\n");
                    else{
                        arg[narg] = NULL;
                        if(pipe_narg != 0){
                            pipe_arg[pipe_narg] = NULL;
                            runpipe(pipe_arg,arg);
                            }
                        else{
                            runcommand(arg, type,infile,outfile,append);
                            }
                        }
				} /* End of if */

				if(toktype == EOL)
					return;

				narg = 0;
                pipe_narg = 0;
                infile[0] = '\0';
                outfile[0] = '\0';
                append = FALSE;
                break;
		} /* End of switch */
	} /* End of for */
} /* End of procline */
