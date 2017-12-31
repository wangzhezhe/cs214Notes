
### Basic

1.what is file system, the basic concept behind it: inode, super block, direct block, indirecr block, double/triple indirect block

http://cs241.cs.illinois.edu/wikibook/file-system-part-1-introduction.html

2.the computation for the size of the file system.

3.Programming to traverse the direactory and show the file info (demo)

4.Common Linux command about the file permission and user group

### Advanced

1.virtual memory

Early CPU using physical address in main memory. Now the CPU access the main memory by generationg a virtual address. If the CPU is 32-bit, the range of the virtual address is from 0 to 2^32-1.

mapping from large address space (virtual address space) into the small address space (physical address spaces). In CPU, the MMU is in charge of the address translation.

2.mmap

using virtual memory to map the fd into the memory. [This tutorial](https://www.youtube.com/watch?v=F3z-SIxu1Tw) show the using of the mmap clearly.

3.the using case of the mmap

please refer to [this](https://stackoverflow.com/questions/5588605/mmap-vs-read).
There are two ways to access the file in Linux, one is using open, read, write syscall, another is using mmap to map the file into the memory directly. If there are large IO transfering operation, the mmap is a better choice.

Using mmap could also implement the sharedMemory betweent the parent process and child process.

4.mount operation

refer to [this](https://unix.stackexchange.com/questions/3192/what-is-meant-by-mounting-a-device-in-linux) and [this](http://www.linfo.org/mounting.html).

in one word, mount is used to associate the device with the specific position in file system.
 
3.virtual file system

refer to [this](http://cs241.cs.illinois.edu/wikibook/file-system-part-5-virtual-file-systems.html#how-do-i-find-out-what-filesystems-are-currently-available-mounted)

Files inside these virtual filesystems **do not exist on the disk**; they are generated dynamically by the kernel when a process requests a directory listing.



