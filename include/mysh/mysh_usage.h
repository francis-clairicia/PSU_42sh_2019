/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** mysh_usage.h
*/

#ifndef MYSH_USAGE_H_

#define MYSH_USAGE_H_

static const char usage[] = {
    "USAGE\n\t%s\nDESCRITION\n"
    "\tA small instance of a shell containing basic\n"
    "\tfunctionnalities.\n\n"
    "\tCompute commands using the prompt by typing on your\n"
    "\tkeyboard.\n\tYou can also use redirections such as:\n"
    "\t\t'>', '>>', '<', '|'.\n\n\n\tBuilt-in's:\n\n"
    "\tcd 'TARGETED DIRECTORY':\n"
    "\t\tallows you to move between directories.\n"
    "\t\t-> run with '-' to go back to the directory you\n"
    "\t\tpreviously visited.\n"
    "\t\t-> run with '~' (or no target) to go to your home\n"
    "\t\tdirectory.\n\n\tenv:\n"
    "\t\tshows the current state of your environment.\n\n"
    "\tsetenv 'VARIABLE' 'VALUE':\n"
    "\t\tsets an environment variable to a certain value.\n\n"
    "\tunsetenv 'VAR1' 'VAR2' 'VAR3' ...:\n"
    "\t\tunsets variables from your environment.\n\n"
    "\texit:\n"
    "\t\texits from the shell.\n"
};

#endif /* MYSH_USAGE_H_ */