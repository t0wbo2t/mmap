# Memory Mapping Experiments

This repository contains a collection of C programs that explore the functionality and use cases of **memory-mapped files** (mmap). These experiments focus on the low-level management of memory, utilizing mmap to perform various operations such as memory allocation, file I/O, inter-process communication (IPC), and executing raw instruction files.

---

## Introduction

In this repository, we investigate the versatile uses of `mmap` to map files or devices into memory. The purpose is to understand memory management at a low level and experiment with its applications across different areas.

---

## Experiments

### Memory Allocation

This section demonstrates how `mmap` can be used to allocate memory. Programs that experiment with dynamically allocated memory via `mmap` are implemented to show its efficiency, and it’s potential in managing memory wth precise control.

### Reading and Writing Files

Here, we explore how `mmap` can be used for file I/O operations. By mapping files into memory, the programs read and write data directly through memory access, improving performance and offering more flexibility over traditional file handling.

### IPC Mechanism

Theis experiment utilize `mmap` as an inter-process communication mechanism. By mapping shared memory into multiple processes, the repository demonstrates the potential for efficient communication between processes, avoiding traditional methods like pipes or message queues.

### Executing Raw Instruction Files

One of the unique experiments in this repository involves using `mmap` to map raw instruction files into memory and executing them. This showcases how mmap can be applied in executing binary instruction streams directly from memory, allowing for lower-level manipulation and exploration of instruction execution.


## Contributing

Feel free to fork this repository and submit pull requests! Contributions are always welcome to enhance the experiments or add new use cases of `mmap`. If you have suggestions or improvements, please open an issue to discuss them.
