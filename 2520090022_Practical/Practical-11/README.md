# Practical-11

Aim:
Implement a multithreaded counter using POSIX threads and compare race conditions with mutex synchronization.

Files:

- race_condition.c
- mutex_lock.c
- observations.txt

Compile:

gcc race_condition.c -o race_condition -pthread
gcc mutex_lock.c -o mutex_lock -pthread

Run:

./race_condition
./mutex_lock
