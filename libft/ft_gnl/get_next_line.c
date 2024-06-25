/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:46:54 by alphan            #+#    #+#             */
/*   Updated: 2023/12/19 15:32:42 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*freadline(int fd, char *fline)
{
	char	*line;
	int		n;

	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line)
		return (NULL);
	n = 1;
	while (!(ft_strchr(line, '\n')) && n)
	{
		n = read(fd, line, BUFFER_SIZE);
		if (n == -1)
			return (free(line), line = NULL, free(fline), fline = NULL, NULL);
		line[n] = 0;
		fline = ft_strjoin2(fline, line);
		if (!fline)
			return (free(line), line = NULL, free(fline), fline = NULL, NULL);
	}
	free(line);
	line = NULL;
	return (fline);
}

char	*ft_getline(char *fline)
{
	char	*line;
	int		i;

	i = 0;
	if (!fline[i])
		return (NULL);
	while (fline[i] && fline[i] != '\n')
		i++;
	if (!fline[i])
		line = ft_calloc(i + 1, sizeof(char));
	else
		line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (fline[i] && fline[i] != '\n')
	{
		line[i] = fline[i];
		i++;
	}
	if (fline[i] && fline[i] == '\n')
		line[i] = fline[i];
	return (line);
}

char	*next_line(char *fline)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (fline[i] && fline[i] != '\n')
		i++;
	if (!fline[i])
	{
		free(fline);
		fline = NULL;
		return (NULL);
	}
	line = ft_calloc(ft_strlen(fline) - i + 1, sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	i++;
	while (fline[i])
		line[j++] = fline[i++];
	free(fline);
	fline = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*fline;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
	{
		free(fline);
		fline = NULL;
		line = NULL;
		return (NULL);
	}
	fline = freadline(fd, fline);
	if (!fline)
		return (free(fline), NULL);
	line = ft_getline(fline);
	fline = next_line(fline);
	return (line);
}

char	*get_next_line_fd(int fd)
{
	static char	*fline[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
	{
		free(fline[fd]);
		fline[fd] = NULL;
		line = NULL;
		return (NULL);
	}
	fline[fd] = freadline(fd, fline[fd]);
	if (!fline[fd])
		return (free(fline[fd]), NULL);
	line = ft_getline(fline[fd]);
	fline[fd] = next_line(fline[fd]);
	return (line);
}
