# Multithreading-Single-Lane-Bridge-C-

 Simulation of crossing a single lane bridge, using threads.

# General description

Every car is a thread. Red cars reach one side of the bridge, blue ones on the other.
The frequency of cars arriving, as well as the total number of cars arriving on each side, are parameters of the simulation.

The bridge is the shared memory area we need to manage. The time it takes to cross a car, as well as how many cars on the same side
can pass each time are also parameters of the simulation.


