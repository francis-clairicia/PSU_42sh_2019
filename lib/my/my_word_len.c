/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** my_word_len
*/

#include <stddef.h>

int my_word_len(char const *word)
{
    register int index = 0;

    if (!word)
        return (0);
    for (; word[index] != ' ' &&
        word[index] != '\t' &&
        word[index]; index +=1);
    return (index);
}