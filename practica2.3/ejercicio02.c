#include <sched.h>
#include <stdio.h>
#include <errno.h>

int main(){
	int sched_policy, min, max, error, curr_prio;
	struct sched_param param;

	if(sched_policy = sched_getscheduler(0) == -1){
		perror("Error getting policy\n");
		return -1;
	}
	else{
		printf("Policy num: %i\t", sched_policy);
		switch(sched_policy) {
			case SCHED_OTHER: printf("Other\t");break;
			case SCHED_FIFO: printf("FIFO\t");break;
			case SCHED_RR: printf("Round-Robin\t");break;
			default: perror("Error\t");break;
		}       
	}
	if (min = sched_get_priority_min(sched_policy) == -1)
		perror("Error getting min priority\n");
	else printf("Min: %i\t", min);
	if (max = sched_get_priority_max(sched_policy) == -1)
		perror("Error getting max priority\n");
	else printf("Max: %i\t", max);
	if ( error = sched_getparam(0, &param) == -1) 
		perror("Error getting parameters\n");
	else {
		curr_prio = param.sched_priority;
		printf("Actual: %i\n", curr_prio);
	}
	return 0;
}
