#include <stdio.h>
#include <assert.h>
#include <sys/mman.h>

#define N 10

int main(int argc, char *argv[]) {
  int* fib_pool = mmap(nullptr,
                       N * sizeof(int),
                       PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS,
                       0,
                       0);

  
  if(fib_pool != MAP_FAILED) {
    assert(N > 1);
    fib_pool[0] = 0;
    fib_pool[1] = 1;

    for(int i = 2; i < N; ++i) {
      fib_pool[i] = fib_pool[i -1] + fib_pool[i - 2];
    }

    for(int i = 0; i < N;++i) {
      printf("%d\n", fib_pool[i]);
    }

    int unmap_return = munmap(fib_pool, N * sizeof(int));
    if(unmap_return == -1) {
      printf("Failed to unmap the memory.\n");
    }
  } else {
    printf("Failed to map memory.\n");
  }

  return 0;
}
