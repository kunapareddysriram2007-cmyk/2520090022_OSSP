# Practical-12

Aim:
Implement the Producer-Consumer problem using semaphores and POSIX threads. Demonstrate deadlock prevention using resource ordering.

Files:

- producer_consumer.c
- deadlock.c
- observations.txt

Compile:

gcc producer_consumer.c -o producer_consumer -pthread
gcc deadlock.c -o deadlock -pthread

Run:

./producer_consumer
./deadlock
