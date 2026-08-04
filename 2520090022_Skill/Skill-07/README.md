# Skill-07

Aim:

Implement child process synchronization using waitpid() and command resolution using the PATH environment variable.

Files:

- skill-07.c
- observations.txt

Compile:

gcc skill-07.c -o skill-07

Run:

./skill-07

Features:

- Uses waitpid()
- Retrieves PATH variable
- Parses PATH directories
- Executes commands using execlp()
- Handles invalid commands
