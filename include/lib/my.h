/*
** EPITECH PROJECT, 2019
** Header for libmy.a
** File description:
** Contains the prototypes of all functions in libmy.a
*/

#ifndef HEADER_MY_H
#define HEADER_MY_H

#include <sys/types.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

#define UNUSED __attribute__((unused))

int my_putchar(char c);
int my_put_nbr(long nb);
int my_putnbr_base(int nbr, char const *base);
void my_swap(int *a, int *b);
int my_putstr(char const *str);
int my_putstr_error(char const *str);
int my_putstr_fd(int fd, char const *str);
int my_strlen(char const *str);
ssize_t my_strlen_until_c(const char *str, const char c);
ssize_t my_strlen_until_list_c(const char *str, const char list[]);
ssize_t my_strnlen(const char *str, const ssize_t n);
bool my_is_char_in_str(const char *str, const char c);
bool my_isalpha(const char c);
int my_getnbr(char const *str);
long my_getnbr_long(char const *str);
int my_getnbr_base(char const *str, char const *base);
void my_sort_int_array(int *array, int size);
int my_pow(int nb, int p);
int my_sqrt(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char **my_str_to_word_array(char const *str, char const *separators);
int my_array_len(const void *array);
char **my_array_dup(char * const * src);
bool my_arrcmp(char **first, char **second);
int my_array_contains(char * const *array, char const *to_find);
void my_show_word_array(char * const *array);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
int my_strstr_index(char const *str, char const *to_find);
int my_strcmp(char const *s1, char const *s2);
bool my_mass_strcmp(const char *template, ...);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isprintable(char const *str);
int my_str_isalphanum(char const *str);
int my_str_contains_only(char const *str, char const *valid);
int my_showstr(char const *str);
int my_showmem(char const *str, int size);
char *my_strcat(char *dest, char const *src);
char *my_strcat_malloc(char *restrict first, char *restrict second,
                const bool free_first, const bool free_second);
char *my_strncat(char *dest, char const *src, int nb);
char *my_strncat_malloc(const char *first, const char *second, const ssize_t n);
char *my_strdup(char const *src);
char *my_strndup(char const *src, int n);
char *my_strdup_char_i(const char *template, const char c, size_t *index);
char *my_strdup_list_i(const char *template, const char list[], size_t *index);
char *my_strdup_until_list_c(const char *template, const char list[]);
char *my_nbr_to_str(int nb);
int my_nbr_len(long nb);
char *my_strchr(char *str, int c);
int my_strchr_index(char const *str, int c);
bool my_loop_in_str_while_list_c(const char *str, const char *list, size_t *i);
char *convert_base(char const *nbr, char const *base_from, char const *base_to);
char *convert_to_base(int nbr, char const *base);
char *get_next_line(int fd);
int get_next_line_2(char **line, int fd);
char *join_path(char const *path_1, char const *path_2);
void *my_memset(void *buffer, int c, size_t size);
void *my_malloc_array(size_t width, size_t height, size_t size);
void my_free_array(void *array);

size_t my_get_bitshift(const void *variable);
ssize_t my_absolute_getnbr(const char *str);

int my_printf(char const *format, ...);
int my_dprintf(int fd, char const *format, ...);

int my_vprintf(char const *format, va_list ap);
int my_vdprintf(int fd, char const *format, va_list ap);

bool match(const char *first, const char *second);

#endif
