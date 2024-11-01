/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m2kura <m2kura@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:55:07 by hteteria          #+#    #+#             */
/*   Updated: 2024/10/28 23:34:37 by m2kura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	if (!dst || !src)
		return (0);
	i = 0;
	src_len = ft_strlen(src);
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

static void	shift_vault(char **vault, char *line)
{
	char	*temp;

	temp = NULL;
	if (*vault && line)
		temp = ft_strdup(*vault + ft_strlen(line));
	free(*vault);
	*vault = temp;
}

static void	get_line(char *vault, char **line)
{
	size_t	i;
	char	*temp;

	i = 0;
	if (!vault || !vault[i])
		return ;
	while (vault[i] && vault[i] != '\n')
		i++;
	temp = ft_substr(vault, 0, i + (vault[i] == '\n'));
	if (temp)
	{
		*line = malloc((ft_strlen(temp) + 1) * sizeof(char));
		if (!*line)
		{
			free(temp);
			return ;
		}
		ft_strlcpy(*line, temp, ft_strlen(temp) + 1);
		free(temp);
	}
}

static void	read_to_buff(char **vault, char *buff, int fd)
{
	int		count;
	char	*temp;

	count = 1;
	while (count > 0 && *vault)
	{
		count = read(fd, buff, BUFFER_SIZE);
		if (count == -1)
		{
			free(*vault);
			*vault = NULL;
			break ;
		}
		buff[count] = '\0';
		temp = *vault;
		*vault = ft_strjoin(temp, buff);
		free(temp);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
}

char	*get_next_line(int fd)
{
	static char	*vault;
	char		*buff;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!vault)
		vault = ft_strdup("");
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (free(vault), vault = NULL, NULL);
	read_to_buff(&vault, buff, fd);
	get_line(vault, &line);
	shift_vault(&vault, line);
	return (line);
}
