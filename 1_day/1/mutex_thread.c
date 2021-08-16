/*fetching a global varible count, having two thread
 * one thread responsible for increment the value of the count
 * variable and another thread responsible for decrement the
 * count value. As count variable common for both the thread
 * its need to have some controlling mechanism to avoid 
 * race around condition. So mutex used in the program to control*/

#include <pthread.h> //header responsible for thread
#include <stdio.h>

int count = 0;
pthread_mutex_t mutex_count; //creating an opaque data type for lock and unlock purpose

void *incth(void *data) // thread for increment
{
    while(1) // continueously increment the value when ever got the lock
    {
        pthread_mutex_lock(&mutex_count); // getting the lock of mutex
        count++;
        printf("inc value: %d\n",count);
        pthread_mutex_unlock(&mutex_count); //release the lock
    }
}

void *decth(void *data) // thread for decrement
{
    while(1)
    {
        pthread_mutex_lock(&mutex_count); // lock mutex
        count--;
        printf("dec value: %d\n",count);
        pthread_mutex_unlock(&mutex_count); //unlock the mutex
    }
}

int main()
{
    /*creating opaque data type variable for threading purpose*/		
    pthread_t p_th_inc;
    pthread_t p_th_dec;
    
    pthread_mutex_init(&mutex_count,NULL); // thread initialization with passing no value
    pthread_create(&p_th_inc,NULL,incth,NULL); // creating thread with default permission and passing NULL value
    pthread_create(&p_th_dec,NULL,decth,NULL);
    pthread_join(p_th_inc,NULL); //to get back the values to the main function from the threads
    pthread_join(p_th_dec,NULL);
    pthread_mutex_destroy(&mutex_count); // destroying the threads after use
    return 0;
}
