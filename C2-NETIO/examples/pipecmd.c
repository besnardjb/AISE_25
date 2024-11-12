#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char ** argv)
{


	int pipe_fd[2];
	/* R pipe_fd[0] W pipe_fd[1] */
	pipe(pipe_fd);

	pid_t echo_pid = fork();

	if(echo_pid == 0)
	{
		/* echo coucou toi
		 * rediriger STDOUT vers le PIPE */
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);

		char * cmd[] = {"echo", "coucou toi", NULL};

		if( execvp(cmd[0], cmd) < 0)
		{
			perror("execvp");
			return 1;
		}
	}
	else
	{

		pid_t grep_pid = fork();

		if(grep_pid == 0)
		{
			/* echo coucou toi
			 * rediriger STDOUT vers le PIPE */
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[1]);

			char * cmd[] = {"grep", "--color", "toi", NULL};

			if( execvp(cmd[0], cmd) < 0)
			{
				perror("execvp");
				return 1;
			}
		}else
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			wait(NULL);
			wait(NULL);
		}



	}	

	return 0;
}
