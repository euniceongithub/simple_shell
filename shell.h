#ifndef SHELL_H_
#define SHELL_H_

/* #include <sys/wait.h> */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <stddef.h>

#define SIZEOF_BUFFER 1024
#define WRITE_BUF_SIZE 1024
#define BUF_ERASE -1

#define NORM_COMMAND	0
#define OR_COMMAND		1
#define AND_COMMAND		2
#define CHAIN_COMMAND	3

#define CHNG_LWRCS	1
#define CHANGE_UNSIGNED	2

#define GET_LINE 0
#define STR_TOK 0

#define HISTORY_FILE	".simple_shell_history"
#define HISTORY_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@errorNum: the error code for exit()s
 *@linecount_prec_check: if on count this line of input
 *@fname: the program fileTitle
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@bufferCommand: address of pointer to bufferCommand, on if chaining
 *@bufferCommandType: CMD_type ||, &&, ;
 *@check_file_des: the file_des from which to read line input
 *@n_history: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int errorNum;
	int linecount_prec_check;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **bufferCommand;
	int bufferCommandType;
	int check_file_des;
	int n_history;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command prec_check
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int hsh(info_t *, char **);
int locateCmd(info_t *);
void findCmd(info_t *);
void forkExec(info_t *);

int execCheck(info_t *, char *);
char *dupChar(char *, int, int);
char *findCommand(info_t *, char *, char *);

int loophsh(char **);

void custom_puts(char *);
int custom_putchar(char);
int print_to_fd(char c, int file_des);
int printInputStr(char *str, int file_des);

int stringLen(char *);
int stringCmp(char *, char *);
char *checkHay(const char *, const char *);
char *concatToDest(char *, char *);

char *copyToDest(char *, char *);
char *stringDup(const char *);
void _puts(char *);
int _putchar(char);

char *copyString(char *, char *, int);
char *concatString(char *, char *, int);
char *charLocator(char *, char);

char **splitString(char *, char *);
char **split_String(char *, char);

char *fillMem(char *, char, unsigned int);
void ffree(char **);
void *rrealloc(void *, unsigned int, unsigned int);

int bfree(void **);

int check_interact(info_t *);
int dm_check(char, char *);
int check_letter(int);
int converter(char *);

int strToInt(char *);
void putsError(info_t *, char *);
int decimalPrint(int, int);
char *func_conversion(long int, int, int);
void elimComent(char *);

int close_shell(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

int sh_history(info_t *);
int ama_alias(info_t *);

ssize_t fetchContent(info_t *);
int fetchInput(info_t *, char **, size_t *);
void blockCtrlC(int);

void initInfo(info_t *);
void argInfo(info_t *, char **);
void infoFree(info_t *, int);

char *get_env(info_t *, const char *);
int print_curr_environ(info_t *);
int init_env(info_t *);
int rem_env(info_t *);
int content_env(info_t *);

char **get_environ(info_t *);
int removeEnv(info_t *, char *);
int set_env(info_t *, char *, char *);

char *fetchHistory(info_t *content);
int printHistory(info_t *content);
int getHistory(info_t *content);
int addHistory(info_t *content, char *memBuffer, int n_lines);
int hstry_orgnsd(info_t *content);

list_t *headToNode(list_t **, const char *, int);
list_t *tailToNode(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int deleteNode(list_t **, unsigned int);
void freeNodes(list_t **);

size_t listLength(const list_t *);
char **listToStrings(list_t *);
size_t listPrint(const list_t *);
list_t *beginPrefix(list_t *, char *, char);
ssize_t receive_index(list_t *, list_t *);

int dm_test(info_t *, char *, size_t *);
void chainCheck(info_t *, char *, size_t *, size_t, size_t);
int replaceAlias(info_t *);
int replaceVar(info_t *);
int replace_string(char **, char *);

#endif
