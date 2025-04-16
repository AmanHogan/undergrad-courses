# Shared Memory Machines

### Symetric Multiprocessor (SMP)
A shared address space with equal time to access shared memory for each proccessor. OS treats each proccessor the same.
All memory is equally accessible

### Nonuniform memory Architecture
Not all memory are equal. Some memory may be more expensive to retrieve than other memory.

Normal Proccess
|Proccess|
|---|
|Stack|
|Text|
|Data|
|Heap|

Multithreaded Proccess
|Proccess|
|---|
|Stack -  Thread 0, Thread 1, ... Thread n|
|Text Shared|
|Data Shared|
|Heap Shared|

What this looks like:


Proccess Memory:

- Thread 1
    - private
- Thread 2
    - private
- Shared
    - Thread 1
    - Thread 2

# Fork Join Programming
Start with a master thread and fork with more threads. Master thread continues, and team of threads execute in parallel and join back to master thread.