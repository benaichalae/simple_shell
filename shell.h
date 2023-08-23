#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 *  * struct liststr - singly linked list
 *   * @num: the number field
 *    * @str: a string
 *     * @next: points to the next node
 *      */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *  * struct passinfo - contains pseudo-arguements to pass into a function,
 *   * allowing uniform prototype for function pointer struct
 *    * @arg: a string generated from getline containing arguements
 *     * @argv:an array of strings generated from arg
 *      * @path: a string path for the current command
 *       * @argc: the argument count
 *        * @line_count: the error count
 *         * @err_num: the error code for exit()s
 *          * @linecount_flag: if on count this line of input
 *           * @fname: the program filename
 *            * @env: linked list local copy of environ
 *             * @environ: custom modified copy of environ from LL env
 *              * @history: the history node
 *               * @alias: the alias node
 *                * @env_changed: on if environ was changed
 *                 * @status: the return status of the last exec'd command
 *                  * @cmd_buf: address of pointer to cmd_buf, on if chaining
 *                   * @cmd_buf_type: CMD_type ||, &&, ;
 *                    * @readfd: the fd from which to read line input
 *                     * @histcount: the history line number count
 *                      */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}
/**
 *  * struct builtin - contains a builtin string and related function
 *   * @type: the builtin command flag
 *    * @func: the function
 *     */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int interactive(info_t *info);
int delimeter(char c, char *delim);
int alphabet(int c);
int _atoi(char *s);
int Mhistory(info_t *info);
int Mexit(info_t *info);
int Mhelp(info_t *info);
int Menv(info_t *info);
char *Mgetenv(info_t *info, const char *name);
int Msetenv(info_t *info);
int Munsetenv(info_t *info);
int populate_env_list(info_t *info);
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _erratoi(char *s);
void print_error(info_t *info, char *estr);
void remove_comments(char *buf);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);
void sigintHandler(__attribute__((unused))int sig_num);
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);
int bfree(void **ptr);
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);
char *_memset(char *s, char b, unsigned int n);
void ffree(char **pp);
char *__memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void fork_cmd(info_t *info);
void find_cmd(info_t *info);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *);
int _putchar(char c);
char **splitter(char *str, char *d);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *new);
int is_chain(info_t *info, char *buf, size_t *p);
char *convert(long int num, int base, int flags);
int print_d(int input, int fd);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);

#endif
