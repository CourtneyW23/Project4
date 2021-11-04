# Project4

Process Scheduling

Purpose:
The goal of this homework is to learn about process scheduling inside an operating system. You will work on the specified scheduling algorithm and simulate its performance.

Task:
In this project, you will simulate the process scheduling part of an operating system. You will implement time-based scheduling, ignoring almost every other aspect of the os. In particular, this project will involve a main executable managing the execution of concurrent user processes just like a scheduler/dispatcher does in an os. You may use message queues or semaphores for synchronization, depending on your choice.

oss [-h] [-s t] [-l f]

Log Output
Your program should send enough output to a log file such that it is possible for me to determine its operation. For example, assuming queue 0 is our ready queue:
OSS: Generating process with PID 3 and putting it in queue 0 at time 0:5000015
OSS: Dispatching process with PID 2 from queue 0 at time 0:5000805,
OSS: total time this dispatch was 790 nanoseconds
OSS: Receiving that process with PID 2 ran for 400000 nanoseconds
OSS: Putting process with PID 2 into queue 0
OSS: Dispatching process with PID 3 from queue 0 at time 0:5401805,
OSS: total time this dispatch was 1000 nanoseconds
OSS: Receiving that process with PID 3 ran for 270000 nanoseconds,
OSS: not using its entire time quantum
OSS: Putting process with PID 3 into blocked queue
OSS: Dispatching process with PID 1 from queue 0 at time 0:5402505,
OSS: total time spent in dispatch was 7000 nanoseconds
etc


