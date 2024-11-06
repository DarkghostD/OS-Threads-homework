#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int max;

void *mythread(void *arg) {
  char *letter = arg;
  int i;
  int local_counter = 0;
  printf("%s: begin[addr of i: %p]\n", letter, &i);
  for (i = 0; i < max; i++) {
    local_counter = local_counter + 1;
  }
  printf("%s: done, local counter = %d\n", letter, local_counter);
  return (void*)(long)local_counter;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: main-first <loopcount>\n");
    exit(1);
  }
  max = atoi(argv[1]);

  pthread_t p1, p2;
  printf("main: begin\n");
  pthread_create(&p1, NULL, mythread, "A");
  pthread_create(&p2, NULL, mythread, "B");

  int result1, result2;
  pthread_join(p1, (void**)&result1);
  pthread_join(p2, (void**)&result2);

  int total = result1 + result2;
  printf("main: done\n [total: %d]\n [should: %d]\n", total, max * 2);
  return 0;
}
