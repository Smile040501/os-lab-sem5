
# Hare and Turtle (Deadline 24-Oct 2021 @ 12:00 hrs)

In this lab, you have to simulate the race from the very popular fable where a
Hare and a Turtle enters a contest to see who runs faster. Use pthreads library
for creating and managing threads, and mutexes for synchronization between
threads. [This tutorial](https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html)
should help you get started with pthreads (and mutexes).


## Minimum requirements of your solution

1.  Create 4 threads: Hare, Turtle, God, and Reporter
2.  The God thread should start the race.
3.  The reporter thread should print the positions of the hare and the turtle on
    the screen as long as the race is in progress. The reporter may choose to
    print the position using GUI, ncurses, or a simple terminal output.
4.  The reporter should also declare the winner of the race.
5.  When the race starts, the Hare and the Turtle starts to increment their
    respective counters (each counter indicates the current position of the hare
    and turtle). The hare should increment its counter relatively faster than the
    turtle). If the hare is sufficiently ahead of the turtle, then the hare
    should sleep for a random amount of time.
6.  God can reposition the hare and the turtle any time before the race finishes.
    
    
NOTE: intervention from God is **OPTIONAL**. Therefore, it is possible that the
God process may choose to not intervene at all. Even in such a scenario, the
race must continue. DO NOT EXPECT GOD'S (or users') INTERVENTION FOR EACH STEP
OF THE RACE.

