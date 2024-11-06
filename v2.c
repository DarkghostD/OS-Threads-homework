#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int counter;
    int max;
} ThreadData;

void* thread_function(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    for (int i = 0; i < data->max; i++) {
        data->counter++; //Sumar Modificacion / Un counter para un hilo y para otro
    }
    return NULL;
}


int main(int argc, char* argv[]) { 
    if (argc < 3) {
        fprintf("Digitar valor maximo y cantidad de hilos deseado", argv[0]); // Cuantos hilos quiero 
        return 1;
    }

    int max = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].counter = 0;
        thread_data[i].max = max;
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, thread_function, &thread_data[i]);
    }

  
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

  
    int TCount = 0;
    for (int i = 0; i < num_threads; i++) {
        TCount += thread_data[i].counter;
    }

    printf("Total: ", TCount);
    return 0;
}
