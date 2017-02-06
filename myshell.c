/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"
#include <string.h>

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here


// Define functions declared in myshell.h here

int main(int argc, char *argv[])
{
    // Input buffer and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };

    // Parse the commands provided using argc and argv


    char *str = NULL;
    // Perform an infinite loop getting command input from users
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Perform string tokenization to get the command and argument
        scanf("%s", str);
        int space = 0;
        int j = 0;
        for(int i = 0; i < strlen(str); i++) {
            if (str[i] == " " && space == 0) {
                space == -1;
            } else if (space = -1) {
                arg[j] = str[i];
            } else {
                command[i] = str[i];
            }
        }
        printf("command %s \n", command);

        // Check the command and execute the operations for each command
        // cd command -- change the current directory
        if (strcmp(command, "cd") == 0)
        {
            if(chdir(arg) == 0) {}

            else if (arg == NULL) { 
            	char *buf =	getcwd(buf,BUFFER_LEN);
            	printf("%s", buf);
            }
            else {puts("No such file or directory."); }
        }

        // other commands here...
        
        // quit command -- exit the shell
        else if (strcmp(command, "quit") == 0)
        {
            return EXIT_SUCCESS;
        }

        // Unsupported command
        else
        {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }
    }
    return EXIT_SUCCESS;
}
