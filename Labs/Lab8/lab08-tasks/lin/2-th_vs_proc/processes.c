/**
  * SO, 2014
  * Lab #8
  *
  * Task #2, lin
  *
  * Threads vs Processes
  */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>	/* fork */
#include <sys/wait.h>	/* wait */

#include <utils.h>

#define NUM_TASKS 	10
#define NUM_JOBS	20

void do_task()
{
	printf("Process %d doing task\n", getpid());

	/* do some work */
	int i;
	for (i = 0; i < NUM_JOBS; i++)
		sleep(1); /* lazy... :-) */
}

void do_bad_task()
{
	printf("Process %d doing BAD task\n", getpid());

	exit(-1);
}

int main(void)
{
	int i, rc;

	for (i = 0; i < NUM_TASKS; i++) {
		pid_t child_pid = fork();

		switch (child_pid) {
		case -1:
			DIE(child_pid, "fork");
		case 0:
			/* child process */
			do_task();

			exit(0);
			break;
		default:
			/* parent process does not wait for the child process */
			break;
		}
	}


	/* wait for all */
	for (i = 0; i < NUM_TASKS; i++){
		rc = wait(NULL);
		DIE(rc == -1, "wait");
	}

	return 0;
}
