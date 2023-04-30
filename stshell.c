#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void sig_handler(int sig){
	write(STDOUT_FILENO, "", 0);
}

char **parse_input(char *input) {
	static char *args[10];
	int index = 0;
	char *tok = strtok(input, " ");
	while (tok != NULL){
		args[index++] = tok;
		tok = strtok(NULL, " ");
	}
	args[index] = NULL;
	return args;
}

void redirect_output(char **args, int j, int flags) {
	char *filename = args[j + 1];
	int fd = open(filename, flags, S_IRUSR | S_IWUSR);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	args[j] = NULL;
}

void handle_pipe(char **args, int j) {
	int pipe_fds[2];
	if (pipe(pipe_fds) < 0){
		exit(1);
	}

	pid_t second_child_pid = fork();
	if (second_child_pid < 0){
		exit(1);
	}

	if (!second_child_pid){
		close(pipe_fds[0]);
		int i = 0;
		char *pipe_args[10];
		while (strcmp(args[i], "|")){
			pipe_args[i] = args[i];
			i++;
		}
		pipe_args[i] = NULL;
		dup2(pipe_fds[1], 1);
		close(pipe_fds[1]);
		execvp(pipe_args[0], pipe_args);
	} else {
		int i = 0;
		for (int k = j + 1; args[k] != NULL; k++){
			args[i++] = args[k];
		}
		args[i] = NULL;
		close(pipe_fds[1]);
		dup2(pipe_fds[0], 0);
		close(pipe_fds[0]);
		wait(NULL);
	}
}

void process_commands(char **args) {
	int j = 0;
	while (args[j] != NULL){
		if (!strcmp(args[j], ">>")){
			redirect_output(args, j, O_WRONLY | O_CREAT | O_APPEND);
			break;
		} else if (!strcmp(args[j], ">")){
			redirect_output(args, j, O_WRONLY | O_CREAT | O_TRUNC);
			break;
		} else if (!strcmp(args[j], "|")){
			handle_pipe(args, j);
			j = -1;
		}
		j++;
	}
}

int main(){
	char input[1024];

	signal(SIGINT, sig_handler);

	while (1){
		printf("\x1b[35mCustomShell~: \x1b[0m");
		fgets(input, 1024, stdin);
		input[strlen(input) - 1] = '\0';

		char **args = parse_input(input);

		if (args[0] == NULL)
			continue;

		if (!strcmp(input, "exit")){
			return 0;
		}

		pid_t child_pid = fork();
		if (child_pid < 0){
			exit(1);
		}
		if (!child_pid){
			signal(SIGINT, SIG_DFL);
			process_commands(args);
			execvp(args[0], args);
		}
		wait(NULL);
	}
}