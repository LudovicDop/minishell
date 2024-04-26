/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/04/27 00:15:09 by ludovicdopp      ###   ########.fr       */
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
    char *tmp;
    /*execve(pathname, argv, envp)*/

    /* Command for TEST */
    /* ping -c 5 google.com | grep rtt | wc -w */
    /* 3 different command have to be executed at the same time */
    cmd = malloc(sizeof(t_cmd));
    printf("\033[31;1mcmd : %p\033[m\n", cmd);
    glob = malloc(sizeof(t_tab));
    printf("\033[31;1mglob : %p\033[m\n", glob);
    printf("\n");
    for(int i = 0; i < 3; i++)
    {
        cmd[i] = malloc(sizeof(t_cmd));
        printf("\033[31;1mcmd[%d] : %p!\033[m\n",i, &cmd[i]);
    }
    printf("\n");

    (*cmd)->arg = malloc(sizeof(char));
    printf("\033[31;1mcmd[%d].arg = %p\033[m\n",0, (*cmd)->arg);
    printf("\n");
    for (int i = 0; i < 1; i++)
    {
        (*cmd[i]).tab_ref = glob;
        printf("\033[31;1m(*cmd[%d]).tab_ref : %p\033[m\n", i, &(*cmd[i]).tab_ref);
    }
    printf("\n");
    glob->envp = envp;
    // while (1)
    // {
        tmp = readline("===>");
        add_history(tmp);
        start_parsing(tmp, cmd);
        //execution_main(cmd);
        fprintf(stderr, "\n");
        fprintf(stderr, "\033[34;1mEXIT\033[m\n");
        fprintf(stderr, "\n");
        free_everything(cmd);

        printf("\033[32;1mtmp : %p\033[m\n", tmp);
        free(tmp);
        printf("\033[32;1mglob : %p\033[m\n", glob);
        free(glob);
    // }
    return (0);
}


