#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int main( int argc, char ** argv )
{
	int sem = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);

	if( sem < 0 )
	{
		perror("msgget");
		return 1;
	}

	unsigned short val = 1;
	if( semctl(sem, 0, SETALL, &val) < 0)
	{
		perror("semctl");
		return 1;
	}



	struct sembuf p;

	p.sem_num = 0;
	p.sem_op = -1;
	p.sem_flg = SEM_UNDO;

	struct sembuf v;

	v.sem_num = 0;
	v.sem_op = 1;
	v.sem_flg = SEM_UNDO;

	int pid = fork();

	if( pid == 0 )
	{

		/* Child */
		while(1)
		{
			if( semop(sem, &p, 1) < 0 )
			{
					printf("Child: SEM deleted\n");
				return 0;
			}

			printf("CHILD holding the sem\n");
			sleep(1);


			semop(sem, &v, 1);
		
		}

	}
	else
	{
		/* Parent */
		int i = 0;
		while(i < 5)
		{
			semop(sem, &p, 1);

			printf("PARENT holding the sem\n");
			sleep(1);
			semop(sem, &v, 1);
			i++;	
		}

		/* Parent delete the sem and unlock the child */
		semctl(sem, 0, IPC_RMID);

		wait( NULL );
		
	}


	return 0;
}
