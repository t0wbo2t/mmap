#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SIZE 10

// Let's create a static memory to store some data
int* buffer = nullptr;

void print_buffer() {
  for(int i = 0; i < SIZE; ++i) {
    printf("%d ", buffer[i]);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  buffer = mmap(nullptr,
                SIZE * sizeof(int),
                PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS,
                0,
                0);
  
  assert(buffer != MAP_FAILED);

  for(int i = 0; i < SIZE; ++i) {
    buffer[i] = i + 1;
  }

  // "fork" is a linux syscall to fork the process.
  // The term "forking the process" indicates that the state of the original processes
  // (including memory, execution flow, and file descriptors) is replicated in the child process.
  // After the fork, the two processes execute independently.
  pid_t pid_child = fork();
  
  // Upon any kind of error, fork() returns -1.
  if(pid_child == -1) {
    perror("Failed to fork the process.\n");
    exit(EXIT_FAILURE);
  } 
  else if(pid_child == 0) {
    for(int i =0; i < (SIZE >> 1); ++i) {
      int temp = buffer[i];
      buffer[i] = buffer[SIZE - i - 1];
      buffer[SIZE - i - 1] = temp; 
    }

    printf("Buffer from Child...\n");
    print_buffer();
  } 
  else {
    int status;
    pid_t pid_status;
    do {
      pid_status = waitpid(pid_child, &status, 0);

      if (pid_status == 0) {
        printf("Child (PID: %d) is still running...\n", pid_child);
        sleep(1);
      } else if (pid_status == -1) {
        perror("Error: waitpid().\n");
        exit(EXIT_FAILURE);
      }
    } while (pid_status == 0);

    if (WIFEXITED(status)) {
        printf("Child (PID: %d) exited with status: %d\n", pid_child, WEXITSTATUS(status));
    }

    printf("Buffer from Parent...\n");
    print_buffer();
  }
  return 0;
}
