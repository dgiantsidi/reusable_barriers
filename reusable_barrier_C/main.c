#include <stdio.h>
#include <pthread.h>

#define THREADS  3
pthread_mutex_t lock;
int threads_arrived = 0;
int mypredicate = 0;
pthread_cond_t go;

void Barrier() {
    pthread_mutex_lock(&lock);
    threads_arrived++;
    if (threads_arrived == THREADS) {
        threads_arrived = 0;
        pthread_cond_broadcast(&go);
        mypredicate = 1;
    }
    else {
            printf("thread waits %d\n", threads_arrived);
            //while (!mypredicate) Note: if use mypredicate, then the barrier is not
            // reusable
                pthread_cond_wait(&go, &lock); // hope that no spurious awakes will happen
        }
    pthread_mutex_unlock(&lock);

    return NULL;
}


void* thread_function(void* args) {
    int *id = (int*) args;
    printf("Hello from thread %d\n", *id);
    sleep(2*(*id));
    
    Barrier();

    printf("1 Barrier Ends\n");
    Barrier();
    printf("2 Barrier Ends\n");
    Barrier();
    printf("3 Barrier Ends\n");
    Barrier();
    printf("4 Barrier Ends\n");
    Barrier();
    printf("5 Barrier Ends\n");
}


int main () {
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&go, NULL);
    pthread_t th[THREADS];
    int id[THREADS];
    // create threads
    for (int i = 0; i < THREADS; i++) {
        id[i] = i;
        pthread_create(&th[i], NULL, thread_function, &id[i]);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(th[i], NULL);
    }

}
