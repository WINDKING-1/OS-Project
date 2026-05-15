# Enhanced Lazy Page Allocation in xv6

## 1. Introduction

In this project, we implemented lazy page allocation in the xv6 operating system.

Normally, xv6 allocates memory immediately when a process calls `sbrk()`. This means memory is reserved even if the process never uses it.

With lazy allocation, memory pages are only allocated when the process actually accesses them. This helps reduce wasted memory and improves efficiency.



## 2. Problem

The original xv6 system uses eager allocation, which allocates memory directly after calling `sbrk()`.

This can cause:

* wasting memory
* allocating unused pages
* inefficient memory management

Our goal was to delay memory allocation until the memory is really needed.



## 3. What We Implemented

We modified xv6 to support lazy page allocation.

### Changes in `sys_sbrk()`

We changed `sys_sbrk()` so it only increases the process memory size without allocating physical pages immediately.

### Page Fault Handling

When the process accesses an unallocated page:

1. A page fault happens
2. The trap handler catches the fault
3. The kernel allocates a physical page
4. The page is mapped into memory

### Statistics and Logging

We added:

* page fault counters
* lazy allocation counters
* logging messages for allocated pages

Example output:

```text id="vddz2h"
lazy alloc: pid=3 va=0x5000
```



## 4. Files Modified

| File               | Purpose                            |
| ------------------ | ---------------------------------- |
| `kernel/proc.h`    | Added counters                     |
| `kernel/trap.c`    | Count page faults                  |
| `kernel/vm.c`      | Handle lazy allocation and logging |
| `kernel/proc.c`    | Print statistics                   |
| `kernel/sysproc.c` | Enable lazy allocation             |
| `user/lazy_demo.c` | Demo and testing program           |



## 5. Testing

We created a program called `lazy_demo` to test the project.

The program:

* allocates memory using `sbrk()`
* accesses pages one by one
* triggers page faults
* prints allocation logs and statistics

Example output:

```text id="sjlwmx"
lazy allocation demo
sbrk finished
accessing pages

lazy alloc: pid=3 va=0x5000
touched page 0

lazy alloc: pid=3 va=0x6000
touched page 1

pid 3 stats: page_faults=7 lazy_allocs=7
```



## 6. Conclusion

In this project, we successfully implemented lazy page allocation in xv6.

This project helped us better understand:

* virtual memory
* page faults
* demand paging
* trap handling
* memory management in operating systems

We also learned how the kernel dynamically allocates memory only when it is needed.
