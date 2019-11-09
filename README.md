# Multithreading-Single-Lane-Bridge-C-

 Simulation of crossing a single lane bridge, using threads.

# General description:

Every car is a thread. Red cars reach one side of the bridge, blue ones on the other.
The frequency of cars arriving, as well as the total number of cars arriving on each side, are parameters of the simulation.

The bridge is the shared memory area we need to manage. The time it takes to cross a car, as well as how many cars on the same side
can pass each time are also parameters of the simulation.

# Analysis:

Notes:
1) In each scenario, the number of threads can be increased by the constant (#define) "threadsNum".
2) There is detailed annotation of the code, using comments in the .c files.
3) Each .c file presents a script (SingleLaneBridge1, SingleLaneBridge2, SingleLaneBridge3, SingleLaneBridge4) of the job.


•Scenario 1: Insecure crossing with collisions.

The threads (red and blue cars) reach the edges of the bridge at different times, but may start crossing the bridge at the same time. So there are more than 1 car on the bridge.
This is because I do not use any lock variables and so other threads can
change the common gauge before the critical point execution from the 1st thread terminates and collisions occur.
Conflicts occur more frequently as the number of threads increases.

•Scenario 2: Safe transit but without justice. Whoever catches up, passes by.

The threads (red and blue cars) reach the ends of the bridge at different times or at the same time, but
cross the bridge at different times. After one finishes its route, the next one "enters" and conflicts are avoided.
This is because I use while loops on the main () so if a red / blue car reaches the edge of the bridge
and there is a blue / red car crossing the bridge, then the car waits for a time equal to the delay time and then crosses the bridge.
In addition, I use a mutex at the critical point of the "redCarFunc" and "blueCarFunc" functions, so that only one thread at a time can increase the counter.

•Scenario 3: Safe crossing with strict switching.

Everything that I described in Scenario 2 applies.
In addition, I used a boolean variable that gives access to the threads depending on its value.
After several experiments with different number of threads (cars), I noticed that strict switching between red and blue cars is observed, even if the cars reach the edge of the bridge at the same time.

•Scenario 4: Safe crossing with rotation and adaptation.

Strict rotation applies, but for adaptation I used an If condition, where if it is the order of the blue cars, but the number of red (nRed) cars arriving on the bridge is greater than the total of nBlue, then break of the loop and passing a red car.
Similarly, the same is true of the other thread group.
This scenario works best with a larger number of threads.

