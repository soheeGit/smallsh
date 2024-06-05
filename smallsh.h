/* smallsh.h -- smallsh 명령 처리기를 위한 정의들 */

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>

#define TRUE 1
#define FALSE 0

#define ERROR (-1)
#define BADFD (-2)

#define EOL 1
#define ARG 2
#define AMPERSAND 3
#define SEMICOLON 4
#define INPUT 5
#define OUTPUT 6
#define APPEND 7
#define PIPE 8

#define MAXFNAME    10
#define MAXARG      512
#define MAXWORD     20
#define MAXFD       20
#define MAXVAR      50
#define MAXNAME     20
#define MAXBUF      512

typedef int BOOLEAN;

typedef enum {
    S_WORD,
    S_BAR,
    S_AMP,
    S_SEMI,
    S_GT,
    S_GTGT,
    S_LT,
    S_NL,
    S_EOF
} SYMBOL;

#define FOREGROUND 0
#define BACKGROUND 1
