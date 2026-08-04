# Skill-19

Aim:

Implement signal handling and SIGINT forwarding.

Files:

- skill-19.c
- observations.txt

Compile:

gcc skill-19.c -o skill-19

Run:

./skill-19

Features:

- Registers SIGINT handler
- Uses sigaction()
- Protects the shell process
- Forwards SIGINT to foreground jobs
- Waits for child process completion
