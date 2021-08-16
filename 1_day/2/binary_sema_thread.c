/*avoiding race around condition using binary semaphore*/

#include <pthread.h> // for thread
#include <stdio.h>
#include <semaphore.h> // for semaphore

int count =0;
sem_t sem_c; //initialize an opaque datatype for semphore

void *incth(void *data) // increment thread
{
    while(1) // continueous increment
    {
        sem_wait(&sem_c); //making semaphore value decrement to 0
        count++;
        printf("Inc value: %d\n",count);
        sem_post(&sem_c); //increse the semaphore value to 1
    }
}


void *decth(void *data) // decrementing thread
{
    while(1)
    {
        sem_wait(&sem_c); // semaphore value decrement to zero
        count--;
        printf("Dec value: %d\n",count);
        sem_post(&sem_c); // semaphre value increment to 1
    }
}


int main()
{
    pthread_t p_th_inc, p_th_dec; // creatinf opaque data type for thread
    sem_init(&sem_c,0,1); // initialize semaphore giving information that it is shared 
    			  //between threads and passing thevalue one
    pthread_create(&p_th_inc,NULL,incth,NULL); // creating a thread with opaque data type
    					       //with default attributes for a specific thread and 
					       //sendin NULL value
    pthread_create(&p_th_dec,NULL,decth,NULL);

    pthread_join(p_th_inc,NULL); //join thread with main program with NULL exit status
    pthread_join(p_th_dec,NULL);
    sem_destroy(&sem_c);// destroy semaphore
    return 0;
}
