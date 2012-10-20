#include "pong_time.h"

/* set timer which(REAL, VIRTUAL, PROF)*/

int set_ticker(int n_val_msecs, int n_interval_msecs, int which)
{
	struct itimerval new_timeset;
	long n_interval_sec, n_interval_usecs;
	long n_val_sec, n_val_usecs;

	n_interval_sec = n_interval_msecs / 1000;             /* int part*/
	n_interval_usecs = (n_interval_msecs % 1000) * 1000L; /* remainder*/
	
	n_val_sec = n_val_msecs / 1000;
	n_val_usecs = (n_val_msecs % 1000) * 1000L;
	
	new_timeset.it_value.tv_sec = n_val_sec;
	new_timeset.it_value.tv_usec = n_val_usecs;
	
	new_timeset.it_interval.tv_sec = n_interval_sec;
	new_timeset.it_interval.tv_usec = n_interval_usecs;

	return setitimer(which, &new_timeset, NULL);
}



















