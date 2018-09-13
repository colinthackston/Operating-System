Colin Thackston
Assignment2 report/markdown

Explantion- the program works by taking in user data and checking to see whether
it is an appropriate argument. Inappropriate commands are thrown out and the user
is reprompted. Once the arguments are entered, the program begins the timer
by creating the processes. The process calls the ring function which prints the 
values and decrements the gloabl variable which represents the number of 
iterations. It passes that value to the next index of the array for the next 
process to use

1. My program hangs because after a certain number of iterations, it enters into
a while(1) loop which halts the execution. This is called a race-condition where
two processes do not communicate and one continues to execute 

2. The program loops because the entire system creation sits inside a while(1) 
loop which makes the whole sequence repeat. A process that does nothing in a loop
is just called the null process in an OS

3. Chaos was supposed to work by swapping values in the mailbox, however, I 
could not get this behavior to execute properly. A race condition can also cause
this to happen because the processes execute concurrently instead of handing 
off execution.  

4. Xinu does not allow processes to execute concurrently. In this aspect, they
behave much more like threads because they all share the same memory space. 