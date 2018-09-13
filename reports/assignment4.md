Futures assignment
Colin Thackston
Eric James

We worked together on this assignment trying to implement futures in xinu. In summary,
we could not fully implement futures. We did created a future table modeled off of
the way xinu handles semaphores (see intialize.c in /system). This required us
to edit the future typedef given to us in the assignment to handle the USED 
state that semaphores use. We implemented future alloc which calls a function
that finds the next entry in the future table and assigns is a value. That 
function (future_malloc) works by looping through the future table until it
finds the next availible entry. For future free, we simply freed the memory
for that specific future. We tried to write future_get, but ran into problems
with finding the current thread running. We could not access the thread table
so our plan of grabbing the running thread from there failed. The idea was to
to change the state of the future, set the value of the data, and assign it
to the queue based on that thred called it by grabbing the current thread from
the table. We could not get this implementation to work. In terms of the modes,
we did not fully implement them. The queue mode would have been implemented if
we had been able to access the thread table. 

Our main issues stemmed from a conceptual misunderstanding of how futures
actually work. Translating them from a concept in a functional programming
languange to code in C was quite difficult. 