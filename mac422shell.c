/* Default libraries */
#include <stdio.h>
#include <string.h>

/* Minix libraries */
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

/* Auxiliar functions */
void select_command    (char *cmd, char *path);

/* Shell programs */
void protegepracaramba (char *path);
void liberageral       (char *path);
void rodeveja          (char *path);
void rode              (char *path);

/**
 * @func main
 * @param  argc Number of arguments of the running program
 * @param  argv Array of strings with program arguments
 * @return 0 if success, nonzero otherwise
 */
int main(int argc, char **argv)
{
    char cmd[18], path[256];
    
    while(printf("> ") && scanf("%s %s", cmd, path) != EOF)
        select_command(cmd,path);
    
    return 0;
}

/**
 * @func select command
 * @param cmd  String with command to be executed
 * @param path Argument to the shell's command
 */
void select_command(char *cmd, char *path)
{
    if(strncmp("protegepracaramba",cmd,18) == 0)
        protegepracaramba(path);
    else if(strncmp("liberageral",cmd,12) == 0)
        liberageral(path);
    else if(strncmp("rodeveja",cmd,8) == 0)
        rodeveja(path);
    else if(strncmp("rode",cmd,4) == 0)
        rode(path);
    else 
        fprintf(stderr, "Command not found!");
}

/**
 * @func protegepracaramba
 * Changes the file permissions to 000
 * @param path Path to file
 */
void protegepracaramba(char *path)
{
    chmod(path, 0000);
}

/**
 * @func liberageral
 * Changes the file permissions to 777
 * @param path Path to file
 */
void liberageral(char *path)
{
    chmod(path, 0777);
}

/**
 * @func rodeveja
 * Holds the shell's prompt while running a program
 * @param path Path to file
 */
void rodeveja(char *path)
{
    if(fork() != 0)
    {
        /* father process */
        int status;
        wait(&status);
        printf("=> programa '%s' retornou com código %d\n", path, status);
    }
    else
    {
        /* child process */
        execve(path, NULL, NULL);
    }
}

/**
 * @func rode
 * Run a program without hold the shell's prompt
 * @param path Path to file
 */
void rode(char *path)
{
    if(fork() == 0)
    {
        /* child process */
        execve(path, NULL, NULL);
    }
}
