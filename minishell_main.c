/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/04/12 23:15:39 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char *test;
    test = readline("Command : ");
    printf("%s\n", test);
    printf("Hello World!\n");
    free(test);
    return (0);
}