#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  if(argc >= 2) {
    // argv[1] contains the path of the file we want to read
    // To create raw data instructions:
    // Assemble the code into an object file, and then,
    // Use `objcopy` to convert it to raw binary
    
    const char* file_path = argv[1];
    
    // open is a linux syscall to open a file; it return a file descriptor
    int file_desc = open(file_path, O_RDONLY);
    if(file_desc != -1) {
      
      // "stat" is a structure which contains all the deatils of file with file_desc
      struct stat details_buffer;

      // fstat is another linux syscall which fills stat with information about file_desc
      int file_details = fstat(file_desc, &details_buffer);
      
      if(file_details != -1) {
        void* f_ptr = mmap(nullptr,
                                details_buffer.st_size,
                                PROT_EXEC,
                                MAP_PRIVATE,
                                file_desc,
                                0);
        
        if(f_ptr != MAP_FAILED) {
          // let's cast the address to mimic the function which has no parameters and
          // does not return anything.
          
          // we call the function, here.
          ((void (*)(void)) f_ptr)();
          
          //printf("If shellcode would have executed successfully, this would not have been printed!\n");
          
          // we have to be responsibe and unmap the memory.
          int return_value = munmap(f_ptr, details_buffer.st_size);
          assert(return_value != - 1);

          // We should also close the file we have opened.
          close(file_desc);
        } else {
          printf("Failed to read the file.\n");
        }
      } else {
        printf("Failed to retrieve file (%s) details.\n", argv[1]);
      }
    }
    else {
      printf("Faild to open the file (%s).\n", argv[1]);
    }
  } else {
    printf("Please provide the filename.\n");
  }

  return 0;
}

