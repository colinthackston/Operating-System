
Questions
1. Starvation is when one process hogs a resource from another and the process
"starves out" because it cannot access that resource. It stops the process from
executing and locks up the program. The given program is not starvation-free 
because it can hog the lock from unlocking

2. Deadlock is when 2 competing actions wait for the other to finish an neither
of them do. It occurs when a process enters a wait state because the resource it
needs is being used by someone else. That other process is also waiting on a 
resource used by the other process and the whole thing locks up. This protocol is
deadlock free

Explanation-
My program implements test and set instead of a compare and swap technique. After
the shell gathers the data, it initates the mom process which waits on the bowl
condition variable. If the bowl is empty, it will refill it and print out the 
statement out. It then unlocks the bowl and tells the scheduler to reschedule 
because otherwise the system will deadlock. Without this resched(), the program
will fail. The child process works by looping as long as it has not eaten the 
total number of worms. It locks access to the bowl, eats a worm by incrementing
its own internal candidate and drementing the global couter as well. If it has
eaten its fill, it ends itself and will reschedule. 