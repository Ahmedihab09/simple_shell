#ifndef SHELL_H
#define SHELL_H

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

/* for read/write buffers */
#define RBF 1024
#define WBF 1024
#define BUFf -1

/* for command chaining */
#define CMDnorm	0
#define CMDor		1
#define CMDand		2
#define CMDchain	3

/* for convert_number_to_string() */
#define convLC	1
#define convUnsign	2

/* 1 if using system getline() */
#define useGL 0
#define useStrotk 0

#define fileHist	".simple_shell_history"
#define maxHist	4096

extern char **environ;


/**
 * struct list_str1 - singly linked list
 * @number: the number field
 * @stri: aa string
 * @next: points to the next node
 */
typedef struct list_str1
{
	int number;
	char *stri;
	struct list_str1 *next;
} fantasyList;

/**
 *struct infoPass1 - contains pseudo-arguements to pass into aa function,
 *					allowing uniform prototype for function pointer struct
 *@fantasyarg: aa string generated from getline containing arguements
 *@fantasyargv: an array of strings generated from fantasyarg
 *@fantasypath: aa string fantasypath for the current command
 *@fantasyargc: the argument count
 *@lcount: the error count
 *@err_number: the error code for exit()s
 *@LcountFlag: if on count this line of input
 *@fantasy_filename: the program filename
 *@fantasy_environment_list: linked list local copy of environ
 *@environ: custom modified copy of environ from LL fantasy_environment_list
 *@fantasy_history_list: the fantasy_history_list node
 *@fantasy_alias_list: the fantasy_alias_list node
 *@fantasy_environment_changed: on if environ was changed
 *@fantasy_command_status: the return fantasy_command_status of the last exec'd command
 *@fantasy_command_buffer: address of pointer to fantasy_command_buffer, on if chaining
 *@fantasy_command_buffer_type: CMD_type ||, &&, ;
 *@fantasy_read_file_descriptor: the fd from which to read line input
 *@fantasy_history_count: the fantasy_history_list line number count
 */
typedef struct infoPass1
{
	char *fantasyarg;
	char **fantasyargv;
	char *fantasypath;
	int fantasyargc;
	unsigned int lcount;
	int err_number;
	int LcountFlag;
	char *fantasy_filename;
	fantasyList *fantasy_environment_list;
	fantasyList *fantasy_history_list;
	fantasyList *fantasy_alias_list;
	char **environ;
	int fantasy_environment_changed;
	int fantasy_command_status;
	char **fantasy_command_buffer;
	int fantasy_command_buffer_type;
	int fantasy_read_file_descriptor;
	int fantasy_history_count;
} FantasyInfot;

#define FANTASY_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct FantasyBuiltin - contains aa FantasyBuiltin string and related function
 *@typee1: the FantasyBuiltin command flag
 *@funct: the function
 */
typedef struct FantasyBuiltin
{
	char *typee1;
	int (*funct)(FantasyInfot *);
} FantasyBuiltinTable;

void printNumbersFrom1To10();

/* hsh_1.c */
int hsh(FantasyInfot *, char **);
int find_fantasy_builtin(FantasyInfot *);
void find_fantasy_command(FantasyInfot *);
void execute_fantasy_command(FantasyInfot *);

/* fantasy_path.c */
int is_executable(FantasyInfot *, char *);
char *copy_substring(char *, int, int);
char *find_command_path(FantasyInfot *, char *, char *);

/* err_string_functions_1.c */
void print_error_messages(char *);
int write_error_character(char);
int write_character_to_fd(char character, int fd);
int print_string_to_fd(char *stri, int fd);

/* string_functions_1.c */
int get_string_length(char *);
int compare_strings(char *, char *);
char *string_starts_with(const char *, const char *);
char *concatenate_strings(char *, char *);

/* string_functions_2.c */
char *copy_string(char *, char *);
char *duplicate_string(const char *);
void print_string(char *);
int write_character_to_stdout(char);

/* string_functions_3.c */
char *copy_partial_string(char *, char *, int);
char *concatenate_partial_strings(char *, char *, int);
char *find_character_in_string(char *, char);

/* string_functions_4.c */
char **split_string_by_delimiters(char *, char *);
char **split_string_by_delimiter(char *, char);

/* memory_functions_1.c */
char *_memset(char *, char, unsigned int);
void free_string_array(char **);
void *custom_realloc(void *, unsigned int, unsigned int);
int safely_free_pointer(void **);

/* more_functions_1.c */
int is_interactive_mode(FantasyInfot *);
int is_delimiter(char, char *);
int is_alpha(int );
int custom_atoi(char *);

/* more_functions_2.c */
int strToInt (char *);
void print_error_message(FantasyInfot *, char *);
int print_line_number(int, int);
char *convert_number_to_string(long int, int, int);
void remove_first_comment(char *);

/* builtin__emulators1.c */
int exitShell(FantasyInfot *);
int changeDirectory(FantasyInfot *);
int showHelp(FantasyInfot *);

/* builtin__emulators2.c */
int myhist(FantasyInfot *);
int myalias1(FantasyInfot *);

/* get_line.c module */
ssize_t getInput(FantasyInfot *);
int customGetline(FantasyInfot *, char **, size_t *);
void blockCtrlC(int);

/* data.c module */
void initializeInfo(FantasyInfot *);
void populateInfo(FantasyInfot *, char **);
void freeInfo(FantasyInfot *, int);

/* env_1.c module */
int env(FantasyInfot *);
char *getEnvironmentVariable(FantasyInfot *, const char *);
int setEnvironmentVariable(FantasyInfot *);
int unsetEnvironmentVariable(FantasyInfot *);
int populateEnvironmentList(FantasyInfot *);

/* env_2.c module */
char **copyEnvironment(FantasyInfot *);
int my_unsetenv(FantasyInfot *, char *);
int my_setenv(FantasyInfot *, char *, char *);

/* file_standard_io_functions.c */
char *getHistoryFile(FantasyInfot *information);
int writeHistory(FantasyInfot *information);
int readHistory(FantasyInfot *information);
int buildHistoryList(FantasyInfot *information, char *buffer, int linecount);
int renumberHistory(FantasyInfot *information);

/* liststr_1.c module */
fantasyList *addNode(fantasyList **, const char *, int);
fantasyList *addNodeEnd(fantasyList **, const char *, int);
size_t printListStr(const fantasyList *);
int deleteNodeAtIndex(fantasyList **, unsigned int);
void freeList(fantasyList **);

/* liststr_2.c module */
size_t listLength(const fantasyList *);
char **listToStrings(fantasyList *);
size_t printList(const fantasyList *);
fantasyList *nodeStartsWith(fantasyList *, char *, char);
ssize_t getNodeIndex(fantasyList *, fantasyList *);

/* tool_chain.c */
int IsChain(FantasyInfot *, char *, size_t *);
void CheckChain(FantasyInfot *, char *, size_t *, size_t, size_t);
int ReplaceAliases(FantasyInfot *);
int ReplaceVariables(FantasyInfot *);
int ReplaceString(char **, char *);

#endif