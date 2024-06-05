#include "smallsh.h"
#include <signal.h>

char *prompt ="Team 5> ";
char *current_path;


void sigint_handler(int sig) {
    // 신호 처리기 내용
}

void sigquit_handler(int sig) {
    // 신호 처리기 내용
}
void set_path(char *new_path) {
        current_path=strdup(new_path);
}

void show_path(){
        printf("현재 환경변수 경로: ");
        if (current_path != NULL) {
                printf("%s", current_path);
        }
        printf("\n");
}

int main(void)
{
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
    perror("signal");
    return EXIT_FAILURE;
  }

    if (signal(SIGQUIT, sigquit_handler) == SIG_ERR) {
        perror("signal");
        return EXIT_FAILURE;
    }
    char *system_path = getenv("PATH");
    if(system_path == NULL) {
        fprintf(stderr, "Error: PATH environment variable not found\n");
        return 1;
        }
    current_path = strdup(system_path);
    while(userin(prompt) != EOF)
		procline();

	return EXIT_SUCCESS;
}
