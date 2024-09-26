# Garbage Collector in C

## Why?
A garbage collector is important because it helps manage memory allocation in computer programs. In languages like Java and Python, memory allocation is handled automatically by the language runtime environment. When a program creates objects or variables, it uses memory in the computer's RAM. If the program doesn't properly manage this memory, it can lead to memory leaks, which means that memory is allocated but never freed up. Over time, this can cause the program to run out of memory and crash.

A garbage collector automatically identifies and frees up memory that is no longer being used by the program. This allows the program to continue running without crashing due to memory issues. Garbage collectors can also optimize memory usage by compacting memory and reducing fragmentation, which can improve performance.

Overall, garbage collectors are an essential component of modern programming languages because they simplify memory management for developers, help prevent memory leaks, and improve the overall performance and stability of programs.

## How a garbage collector works
Here is a simplified explanation of how a garbage collector works:
- Allocation: When a new object is created, the garbage collector allocates memory for it in the heap, which is a region of memory dedicated to dynamic memory allocation.

- Reference Counting: The garbage collector uses reference counting to keep track of which objects are being used by the program. Reference counting involves tracking the number of references to each object. An object is considered in use if its reference count is greater than zero.

- Mark and Sweep: The garbage collector periodically performs a mark and sweep operation to identify and free memory that is no longer in use. During the mark phase, the garbage collector traverses the heap, starting from the root set (which includes all objects that are directly accessible from the program). The garbage collector marks each object that is still in use by setting a flag on it. In the sweep phase, the garbage collector frees all memory that was not marked during the mark phase.

- Compaction: To optimize memory usage, some garbage collectors also perform a compaction phase. During this phase, the garbage collector moves live objects closer together in memory, which reduces fragmentation and makes more efficient use of available memory.

The exact implementation of a garbage collector can vary depending on the programming language and the specific garbage collector algorithm used. Some garbage collectors use more sophisticated techniques, such as generational garbage collection or concurrent garbage collection, to further optimize performance.

## About this implementation
C is a powerful programming language that allows for low-level memory management. While this gives developers greater control over memory allocation, it also means that managing memory in C can be challenging, and the risk of memory leaks and buffer overflows is high. One way to address these issues is to write a garbage collector in C.

A garbage collector is a program that automatically frees memory that is no longer in use by the application. By implementing a garbage collector, the developer can focus on the logic of the program without worrying about memory allocation and deallocation, leading to less buggy and more reliable software.

In C, garbage collectors can be particularly useful in large-scale projects that require complex memory management. Garbage collectors can also improve performance by reducing the overhead associated with manual memory management. Instead of explicitly deallocating memory, the garbage collector can free memory as needed, which can lead to more efficient memory usage and faster program execution.

Another benefit of writing a garbage collector in C is that it can help address security vulnerabilities related to memory. C is susceptible to buffer overflow attacks, which can be mitigated by a garbage collector that can detect and prevent these types of vulnerabilities.

Overall, while garbage collection is not a natural feature of C, it can provide significant benefits in terms of simplifying memory management, improving performance, and enhancing security. As such, implementing a garbage collector in C can be a worthwhile investment for developers who want to build more robust, secure, and scalable applications.

## Structure
```main.c``` --> This file contains all the gc fuctions and a simple VM for a basic functioning
```test.c``` --> The test file contains all the specific function to provide a proof-of-concept of the gc

### Code
[Here](https://github.com/filippo-ferrando/garbage-collector) you can find the GitHub repo with my code

### Credits
The code is based on the gorgeous guide written by [@munificent](https://github.com/munificent)
