/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/04/15 10:51:49 by ldoppler         ###   ########.fr       */
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
