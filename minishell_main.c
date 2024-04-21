/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/04/21 18:57:58 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define MAX_PATH_SIZE 1024

void   handle_sigcont(int sig)
{
    printf("TEST\n");
} 

char    *get_current_path(void)
{
    char    *cwd;

    cwd = malloc(sizeof(char) * MAX_PATH_SIZE);
    if (!cwd)
        return (NULL);
    if (getcwd(cwd, MAX_PATH_SIZE) != NULL)
    {
        //printf("current directory : %s\n", cwd);
        cwd = ft_strchr(cwd + 1, '/');
        return (cwd);
    }
    else
    {
        perror("getcwd");
        return (NULL);
    }
    return (NULL);
}
int main(int argc, char **argv, char **envp) 
{
    t_cmd **cmd;
    t_tab *glob;
    /*execve(pathname, argv, envp)*/

    /* Command for TEST */
    /* ping -c 5 google.com | grep rtt | wc -w */
    /* 3 different command have to be executed at the same time */
    cmd = malloc(sizeof(t_cmd) * 6);
    glob = malloc(sizeof(t_tab));
    cmd[0] = malloc(sizeof(t_cmd));
    cmd[1] = malloc(sizeof(t_cmd));
    cmd[2] = malloc(sizeof(t_cmd));
    cmd[3] = malloc(sizeof(t_cmd));
    cmd[4] = malloc(sizeof(t_cmd));
    cmd[5] = malloc(sizeof(t_cmd));
    cmd[6] = malloc(sizeof(t_cmd));

    for (int i = 0; i < 6; i++)
    {
        (*cmd[i]).tab_ref = glob;
    }
    /* cmd->arg will be malloc with 4 because the command ping */
    /* contain 4 arguments (include the name of the program) */
    (*cmd[0]).arg = malloc(sizeof(char*) * 3);
    (*cmd[0]).arg[0] = ft_strdup("cat");
    (*cmd[0]).arg[1] = ft_strdup("fichier.txt");
    (*cmd[0]).arg[2] = NULL;

    (*cmd[1]).arg = malloc(sizeof(char*) * 3);
    (*cmd[1]).arg[0] = ft_strdup("grep");
    (*cmd[1]).arg[1] = ft_strdup("motif");
    (*cmd[1]).arg[2] = NULL;

    (*cmd[2]).arg = malloc(sizeof(char*) * 3);
    (*cmd[2]).arg[0] = ft_strdup("sed");
    (*cmd[2]).arg[1] = ft_strdup("s/motif/remplacement/");
    (*cmd[2]).arg[2] = NULL;


    (*cmd[3]).arg = malloc(sizeof(char*) * 3);
    (*cmd[3]).arg[0] = ft_strdup("sort");
    (*cmd[3]).arg[1] = NULL;
    
    (*cmd[4]).arg = malloc(sizeof(char*) * 2);
    (*cmd[4]).arg[0] = ft_strdup("uniq");
    (*cmd[4]).arg[1] = NULL;
    /* For the moment I will just put a NULL value for envp */

    /* Nothing to see will init everything to null */

    /* Init the pathname need to search it by default with env */
    (*cmd[0]).pathname = malloc(sizeof(char*) * 1);
    (*cmd[0]).pathname = ft_strdup("/bin/cat");

    (*cmd[1]).pathname = malloc(sizeof(char*) * 1);
    (*cmd[1]).pathname = ft_strdup("/usr/bin/grep");  

    (*cmd[2]).pathname = malloc(sizeof(char*) * 1);
    (*cmd[2]).pathname = ft_strdup("/usr/bin/sed");  

    (*cmd[3]).pathname = malloc(sizeof(char*) * 1);
    (*cmd[3]).pathname = ft_strdup("/usr/bin/sort");

    (*cmd[4]).pathname = malloc(sizeof(char*) * 1);
    (*cmd[4]).pathname = ft_strdup("/usr/bin/uniq");

    /*any redirection?*/
    (*cmd[4]).any_redirection = true;
    (*cmd[4]).arg_redirection = malloc(sizeof(char*) * 3);
    
    (*cmd[4]).arg_redirection[0] = ft_strdup(">>");
    (*cmd[4]).arg_redirection[1] = ft_strdup("file");
    (*cmd[4]).arg_redirection[2] = NULL;


    int i = 0;
    while (i < 4)
    {
        ((*cmd[i]).last_cmd) = false;
        i++;
    }


    (cmd[5]) = 0;
    execution_main(cmd);
    return (0);
}


