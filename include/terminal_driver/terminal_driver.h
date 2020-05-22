/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** terminal_driver
*/

#ifndef TERMINAL_DRIVER_H_
#define TERMINAL_DRIVER_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include <string.h>
#include <ctype.h>
#include <errno.h>

#include <termios.h>

#include "keys.h"

#define CTRL_KEY(k) ((k) & 0x1f)

#define LINE_SIZE 4096

//Usefull struct for handling stdin input
//
//Buffer an array which contains the stdin input
//Index represent the actual position of the cursor relative to the buffer
typedef struct line_s
{
    char buffer[LINE_SIZE];
    int index;
    bool completed;
} line_t;

//Save the actual terminal driver settings at the first function call
//Loads the save from the second function call
void disable_raw_mode(void) __attribute__((constructor, destructor));

void enable_raw_mode(void);

//Main function of input handling
//Calls read_key to get input key
//Redirects the program if the key is special
//Saves the key in the buffer if not
void process_key(line_t *line);

//Prints given error message and exits the program
void die(char *str);

char *get_term_line(void);

void shift_line_right(line_t *line, int key);

#endif /* !TERMINAL_DRIVER_H_ */