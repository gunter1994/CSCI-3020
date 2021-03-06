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

int main(int argc, char *argv[], char** envp)
{
	// Input buffer and commands
	char buffer[BUFFER_LEN] = { 0 };
	char command[BUFFER_LEN] = { 0 };
	char arg[BUFFER_LEN] = { 0 };
    char filename[BUFFER_LEN] = { 0 };

	// Parse the commands provided using argc and argv
    FILE *input = stdin;
    if (argc == 2) {
        strcpy(filename, argv[1]);
        FILE *fp = fopen(filename, "r");
        input = fp;
    }
    

	// Perform an infinite loop getting command input from users
	int args = 0;
	while (fgets(buffer, BUFFER_LEN, input) != NULL)
	{
		// Perform string tokenization to get the command and argument
		if (buffer[strlen(buffer)-1] == '\n') {
			buffer[strlen(buffer)-1] = '\0';
		}
		strcpy(command, strtok(buffer," "));
		if (buffer[strlen(buffer)+1] != '\0') {
			strcpy(arg, strtok(NULL, ""));
			args = 1;
		}
		
		//printf("command: %s\n", command);
		//printf("arg: %s\n", arg);

		// Check the command and execute the operations for each command
		// cd command -- change the current directory
		if (strcmp(command, "cd") == 0)
		{
			if(chdir(arg) == 0) {}

			else if (args == 0) {
				char *buf =	getcwd(buf,BUFFER_LEN);
				printf("%s\n", buf);
			}
			else {fputs("No such directory.\n", stderr); }
		}

        // other commands here...
        else if (strcmp(command, "clr") == 0)
        {
            printf("\033[2J");
        }
        else if (strcmp(command, "dir") == 0)
        {
            DIR *current = opendir(".");
            struct dirent *file;
            while ((file = readdir(current)) != NULL)
            {
                printf("%s\n", file->d_name);
            }
            closedir(current);
        }
        else if (strcmp(command, "environ") == 0)
        {
            char** iter;
            for(iter = envp; *iter != 0; iter++) 
            {
                printf("%s\n", *iter);
            }
        }
        else if (strcmp(command, "echo") == 0)
        {
            if (args == 1) {
                printf("%s\n", arg);
            }
        }
        else if (strcmp(command, "help") == 0)
		{
			system("more README.md");
		}
        else if (strcmp(command, "pause") == 0)
        {
            printf("Press Enter to Continue...");
            char c = 0;
            while (c != '\r' && c != '\n'){
                c = getchar();
            }
        }
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
		args = 0;
		
		strcpy(arg, "");
	}
	return EXIT_SUCCESS;
}
