# Practical-05

Aim:
Implement producer-consumer communication using anonymous pipes and execute the equivalent of the shell command:

ls -l | grep ".c"

Files:

- producer_consumer.c
- pipe_command.c
- observations.txt

Compile:

gcc producer_consumer.c -o producer_consumer
gcc pipe_command.c -o pipe_command

Run:

./producer_consumer
./pipe_command
