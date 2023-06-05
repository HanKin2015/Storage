更多详情见：D:\Github\GitBook\gitbook\Web\IPC.md

## 1、shmget和shm_open区别
shmget和shm_open都是用于共享内存的系统调用，但是它们有一些区别。

shmget是System V IPC机制中的一个函数，它通过一个键值来创建或获取一个共享内存段。shmget函数创建的共享内存段可以通过shmat函数映射到进程的地址空间中，从而实现进程间的共享内存。

而shm_open是POSIX IPC机制中的一个函数，它通过一个命名对象来创建或获取一个共享内存段。shm_open函数创建的共享内存段可以通过mmap函数映射到进程的地址空间中，从而实现进程间的共享内存。

因此，shmget和shm_open的主要区别在于它们创建共享内存段的方式不同，一个是通过键值，一个是通过命名对象。此外，它们所属的IPC机制也不同，shmget属于System V IPC机制，而shm_open属于POSIX IPC机制。

## 2、System V IPC机制和System V IPC机制的区别
System V IPC机制和POSIX IPC机制都是用于进程间通信的机制，但是它们有一些区别。

System V IPC机制是Unix操作系统早期的进程间通信机制，它包括三种通信方式：消息队列、共享内存和信号量。在System V IPC机制中，进程通过IPC键值来访问IPC资源，IPC键值是一个整数值，用于标识IPC资源。System V IPC机制的函数包括ftok、msgget、msgsnd、msgrcv、shmget、shmat、shmdt、shmctl、semget、semop和semctl等。

而POSIX IPC机制是Unix操作系统后期引入的进程间通信机制，它也包括三种通信方式：消息队列、共享内存和信号量。在POSIX IPC机制中，进程通过IPC对象的名称来访问IPC资源，IPC对象的名称是一个以斜杠开头的字符串，用于标识IPC资源。POSIX IPC机制的函数包括mq_open、mq_send、mq_receive、mq_close、mq_unlink、shm_open、shm_unlink、mmap、munmap、sem_open、sem_wait、sem_post、sem_close和sem_unlink等。

因此，System V IPC机制和POSIX IPC机制的主要区别在于它们访问IPC资源的方式不同，一个是通过IPC键值，一个是通过IPC对象的名称。此外，它们的函数接口也有所不同。

## 3、那我想实现共享内存，该如何选择它们
如果您想实现共享内存，可以根据以下几点来选择System V IPC机制或POSIX IPC机制：

系统支持：首先需要查看您所使用的操作系统是否支持System V IPC机制或POSIX IPC机制。大多数Unix操作系统都支持这两种机制，但是具体实现可能有所不同。

应用场景：System V IPC机制和POSIX IPC机制都可以用于共享内存，但是它们的应用场景可能有所不同。如果您的应用程序需要在多个进程之间共享大量数据，那么使用共享内存可能是一个不错的选择。如果您的应用程序需要在多个进程之间传递小量数据，那么使用消息队列可能更加适合。

编程习惯：如果您已经熟悉了System V IPC机制的函数接口，那么使用System V IPC机制可能更加方便。如果您更喜欢POSIX风格的函数接口，那么使用POSIX IPC机制可能更加方便。

总之，选择System V IPC机制或POSIX IPC机制主要取决于您的应用场景和编程习惯。如果您不确定哪种机制更适合您的应用程序，可以先尝试使用其中一种机制，如果不满足需求，再尝试使用另一种机制。

## 4、POSIX风格指的是？
POSIX（Portable Operating System Interface for Unix）是一个标准化的操作系统接口，旨在提高不同Unix操作系统之间的兼容性。POSIX定义了一组操作系统接口、库和工具，以便在不同的Unix操作系统上编写可移植的应用程序。

POSIX风格指的是符合POSIX标准的编程风格，包括函数接口、头文件、命名规范等。POSIX标准定义了许多系统调用和库函数，这些函数在不同的Unix操作系统上都有相同的接口和语义。因此，使用POSIX风格的编程可以提高应用程序的可移植性和可重用性。

在Unix操作系统中，POSIX风格的函数接口通常以“posix_”或“p_”为前缀，例如，POSIX共享内存机制的函数接口包括shm_open、shm_unlink、mmap和munmap等。使用这些函数接口可以方便地创建和访问共享内存，而且这些函数在不同的Unix操作系统上都有相同的接口和语义，因此可以提高应用程序的可移植性。

## 5、共享内存是共享临时文件吗
共享内存和共享临时文件是两个不同的概念。

共享内存是一种进程间通信的机制，它允许多个进程共享同一块物理内存，从而实现高效的数据交换。共享内存通常使用特殊的系统调用来创建和管理共享内存区域，例如shmget、shmat、shmdt和shmctl等。

共享临时文件是一种临时文件的使用方式，它允许多个进程共享同一个临时文件，从而实现高效的数据交换。共享临时文件通常使用文件锁和文件映射等技术来实现进程间同步和数据共享。

虽然共享内存和共享临时文件都可以用于进程间通信和数据共享，但是它们的实现方式和使用方法有所不同。共享内存是直接在进程地址空间中映射一块物理内存，而共享临时文件是通过文件系统来实现数据共享。因此，共享内存通常比共享临时文件更快速和高效，但是共享临时文件更加灵活和易于管理。




