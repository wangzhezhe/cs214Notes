refer to [this](http://cs241.cs.illinois.edu/wikibook/memory-part-1-heap-memory-introduction.html#intro-to-allocating) for the answer of basic questions.

### Bacic

1.Different memory segment in c/c++, the contents for every segments.

LIH(linux interface Handbook) 119

2.brk, sbrk, malloc, colloc, free

LIH(linux interface Handbook) 141

3.implicit list & explicit list [easy to be neglected]

refer to [this](https://www.youtube.com/watch?v=d_JhP130XO8)

these two ways are used to keep track of the free memory space.

By implicit list, we mix the malloced space and unmalloced space together and assume the heap is a huge list, we need to traverse the block one by one when we want to free some space.

By explicit list, we linked the unmalloced space together(double linked list).

Every node in the linked list consist of meta data and real valid data(payload).

### Reflection

1.different ways of allocation and their corresponding segments(for c) (Memory layout)

refer to LIH 117

array -> stack

variable in function -> stack

static variable & global variable
static int key = 9973 -> initialized data segment
static char mbuf[10240000] -> uninitialized data segment

2.some special cases for string allocation (string literal)

refer to [this](https://stackoverflow.com/questions/25068639/memory-usage-of-literal-strings-in-c) and [this](https://stackoverflow.com/questions/16021454/difference-between-declared-string-and-allocated-string).

```
char * s ="abcd" //code segment, the string literal could not be modified
char str[]="abcde" //stack segment
char str[10]="abcde" //data segment 
```


3.the issues caused by segmentation of different address apace -> scope of the function, isolation between different address space

Lots of question in the exam test the understanding for the scope of the function, when anserwing the questions like what is the problem for the following code, the issue of variable scope should be first considered, The most common case is sending a parameter into a funcionb into functiona, it is possible that when functionb need the value of the parameter, the parameler is already released because the function has returned already. 

Of courese there are all kinds of strategies for this issue like using concurency promitive to let the functiona waiting functionb before return or just using heap to store the value of the variable.

4.the return value of the malloc, if it could fail sometime?

Although the possibility of failure in allocating memory is small, all calls to malloc(), and the related functions that we describe later, should check for this error return.

In real using, we always forget to check the return value of the malloc, which may caused some unexpected behaviors(Golang is better, because it force programmer to check the return error). 

When you want to apply an array in stack area, the instruction could also trigger the segfault, becasue the space of stack area is limited, you could use malloc to replace the operation like apply the large size array, or using c++ stl direactly if it is possible.

5.the difference between malloc and new in practice.

if you programming in c++ and initilizing the struct contains the STL type, obviously you should use new/delete instead of malloc/free. And there are also lots of difference between new and malloc.

  - using new, there will be exception when fail to apply the memory space (the exception mechanism in c++)
  - default contruct functions are called when using new
  - ...

6.the mechanism behind the malloc, if you need to implement a malloc by yourself, what elemtes should you consider?

It's high level materials for this class, it is enough to refer to [this](http://cs241.cs.illinois.edu/wikibook/memory-part-2-implementing-a-memory-allocator.html#) 

