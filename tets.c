// #include <stdio.h>
// #include <pthread.h>

// // example of rice condition
// int count = 0;

// void *increment_count(void *arg) {
//     for (int i = 0; i < 1000000; ++i) {
//         count++;
//     }
//     return NULL;
// }

// int main() {
//     pthread_t thread1, thread2;

//     pthread_create(&thread1, NULL, increment_count, NULL);
//     pthread_create(&thread2, NULL, increment_count, NULL);

//     pthread_join(thread1, NULL);
//     pthread_join(thread2, NULL);

//     printf("Final count: %d\n", count);

//     return 0;
// }

//example of mutex protction 

#include <stdio.h>
#include <pthread.h>

int count = 0;
pthread_mutex_t mutex;

void *increment_count(void *arg) {
    for (int i = 0; i < 1000000; ++i) {
        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_mutex_init(&mutex, NULL);

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, increment_count, NULL);
    pthread_create(&thread2, NULL, increment_count, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final count: %d\n", count);

    pthread_mutex_destroy(&mutex);

    return 0;
}