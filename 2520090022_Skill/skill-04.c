```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_LEN 256

typedef enum {
    WORD,
    PIPE,
    INPUT_REDIRECT,
    OUTPUT_REDIRECT,
    APPEND_REDIRECT,
    BACKGROUND
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_LEN];
} Token;

const char *getTypeName(TokenType type) {
    switch (type) {
        case WORD: return "WORD";
        case PIPE: return "PIPE";
        case INPUT_REDIRECT: return "INPUT";
        case OUTPUT_REDIRECT: return "OUTPUT";
        case APPEND_REDIRECT: return "APPEND";
        case BACKGROUND: return "BACKGROUND";
    }

    return "UNKNOWN";
}

/* ---------- TOKENIZER ---------- */

int tokenize(char *input, Token tokens[]) {

    int i = 0;
    int count = 0;

    while (input[i] != '\0') {

        /* Handle whitespace */
        if (isspace((unsigned char)input[i])) {
            i++;
            continue;
        }

        /* Pipe */
        if (input[i] == '|') {
            tokens[count].type = PIPE;
            strcpy(tokens[count].value, "|");
            count++;
            i++;
            continue;
        }

        /* Input redirection */
        if (input[i] == '<') {
            tokens[count].type = INPUT_REDIRECT;
            strcpy(tokens[count].value, "<");
            count++;
            i++;
            continue;
        }

        /* Output / append redirection */
        if (input[i] == '>') {

            if (input[i + 1] == '>') {
                tokens[count].type = APPEND_REDIRECT;
                strcpy(tokens[count].value, ">>");
                count++;
                i += 2;
            }
            else {
                tokens[count].type = OUTPUT_REDIRECT;
                strcpy(tokens[count].value, ">");
                count++;
                i++;
            }

            continue;
        }

        /* Background */
        if (input[i] == '&') {
            tokens[count].type = BACKGROUND;
            strcpy(tokens[count].value, "&");
            count++;
            i++;
            continue;
        }

        /* Normal word */
        int j = 0;

        while (input[i] != '\0' &&
               !isspace((unsigned char)input[i]) &&
               input[i] != '|' &&
               input[i] != '<' &&
               input[i] != '>' &&
               input[i] != '&' &&
               j < MAX_LEN - 1) {

            tokens[count].value[j++] = input[i++];
        }

        tokens[count].value[j] = '\0';
        tokens[count].type = WORD;

        if (j > 0)
            count++;

        if (count >= MAX_TOKENS)
            break;
    }

    return count;
}

/* ---------- PARSER ---------- */

int validateSyntax(Token tokens[], int count) {

    if (count == 0) {
        printf("Empty command.\n");
        return 0;
    }

    /* Command cannot start with pipe */
    if (tokens[0].type == PIPE) {
        printf("Syntax error: command cannot start with '|'.\n");
        return 0;
    }

    for (int i = 0; i < count; i++) {

        /* Pipe validation */
        if (tokens[i].type == PIPE) {

            if (i == count - 1) {
                printf("Syntax error: pipe cannot be last.\n");
                return 0;
            }

            if (tokens[i + 1].type == PIPE) {
                printf("Syntax error: consecutive pipes.\n");
                return 0;
            }
        }

        /* Redirection validation */
        if (tokens[i].type == INPUT_REDIRECT ||
            tokens[i].type == OUTPUT_REDIRECT ||
            tokens[i].type == APPEND_REDIRECT) {

            if (i == count - 1) {
                printf("Syntax error: filename expected after redirection.\n");
                return 0;
            }

            if (tokens[i + 1].type != WORD) {
                printf("Syntax error: expected filename after redirection.\n");
                return 0;
            }
        }

        /* Background validation */
        if (tokens[i].type == BACKGROUND &&
            i != count - 1) {

            printf("Syntax error: '&' must be at the end.\n");
            return 0;
        }
    }

    return 1;
}

/* ---------- EXECUTION STRUCTURE ---------- */

typedef struct {
    char command[MAX_LEN];
    char arguments[MAX_TOKENS][MAX_LEN];
    int argumentCount;

    char inputFile[MAX_LEN];
    char outputFile[MAX_LEN];

    int append;
} Command;

void buildCommand(Token tokens[],
                  int start,
                  int end,
                  Command *cmd) {

    memset(cmd, 0, sizeof(Command));

    for (int i = start; i < end; i++) {

        if (tokens[i].type == WORD) {

            strcpy(cmd->arguments[cmd->argumentCount],
                   tokens[i].value);

            if (cmd->argumentCount == 0) {
                strcpy(cmd->command,
                       tokens[i].value);
            }

            cmd->argumentCount++;
        }

        else if (tokens[i].type == INPUT_REDIRECT) {

            if (i + 1 < end) {
                strcpy(cmd->inputFile,
                       tokens[i + 1].value);
                i++;
            }
        }

        else if (tokens[i].type == OUTPUT_REDIRECT) {

            if (i + 1 < end) {
                strcpy(cmd->outputFile,
                       tokens[i + 1].value);
                cmd->append = 0;
                i++;
            }
        }

        else if (tokens[i].type == APPEND_REDIRECT) {

            if (i + 1 < end) {
                strcpy(cmd->outputFile,
                       tokens[i + 1].value);
                cmd->append = 1;
                i++;
            }
        }
    }
}

void printExecutionStructure(Command *cmd) {

    printf("\nExecution Structure\n");
    printf("-------------------\n");

    printf("Command: %s\n", cmd->command);

    printf("Arguments: ");

    for (int i = 0; i < cmd->argumentCount; i++)
        printf("[%s] ", cmd->arguments[i]);

    printf("\n");

    if (strlen(cmd->inputFile) > 0)
        printf("Input file: %s\n", cmd->inputFile);

    if (strlen(cmd->outputFile) > 0) {
        printf("Output file: %s\n", cmd->outputFile);

        if (cmd->append)
            printf("Mode: APPEND\n");
        else
            printf("Mode: OVERWRITE\n");
    }
}

/* ---------- MAIN ---------- */

int main() {

    char input[MAX_LEN];

    printf("Mini Shell Tokenizer and Parser\n");
    printf("Type 'exit' to quit.\n\n");

    while (1) {

        printf("shell> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0)
            break;

        Token tokens[MAX_TOKENS];

        /* Tokenization */
        int count = tokenize(input, tokens);

        /* Debug token output */
        printf("\nTokens:\n");

        if (count == 0) {
            printf("(empty)\n\n");
            continue;
        }

        for (int i = 0; i < count; i++) {
            printf("[%d] %-12s : %s\n",
                   i,
                   getTypeName(tokens[i].type),
                   tokens[i].value);
        }

        /* Syntax validation */
        printf("\nParser:\n");

        if (!validateSyntax(tokens, count)) {
            printf("Parsing failed.\n\n");
            continue;
        }

        printf("Syntax valid.\n");

        /* Generate execution structures */
        int start = 0;

        for (int i = 0; i <= count; i++) {

            if (i == count ||
                tokens[i].type == PIPE) {

                Command cmd;

                buildCommand(tokens,
                             start,
                             i,
                             &cmd);

                printExecutionStructure(&cmd);

                start = i + 1;
            }
        }

        printf("\nParsing completed successfully.\n\n");
    }

    return 0;
}
```

