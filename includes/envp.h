/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:58:20 by alphan            #+#    #+#             */
/*   Updated: 2024/07/21 19:07:48 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include <stdbool.h>

extern int	g_signal;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
	bool			hidden_bis;
	bool			hidden;
}					t_envp;

t_envp	*search_envp_key(t_envp **envp, char *key);

#endif
