# Practical-06

Aim:
Implement client-server communication using Named Pipes (FIFOs) and demonstrate POSIX signal handling.

Files:

- server.c
- client.c
- signal_handling.c
- observations.txt

Compile:

gcc server.c -o server
gcc client.c -o client
gcc signal_handling.c -o signal_handling

Run:

Terminal-1:
./server

Terminal-2:
./client

Signal Program:

./signal_handling

Send Signals:

kill -SIGINT <PID>
kill -SIGTERM <PID>
kill -SIGUSR1 <PID>
