Aim:
To retrieve the current directory, process exit requests, and implement the export command.

Commands Used:

gcc skill-10.c -o skill-10
./skill-10

Observations:

1. pwd displays the current working directory.
2. export creates or updates environment variables.
3. Variable names are validated.
4. Existing variables can be overwritten.
5. Exported variables are available through getenv().
6. Resources are cleaned up before exit.

Conclusion:

The program demonstrates current directory retrieval, export command implementation, environment variable management, and graceful shell termination.
