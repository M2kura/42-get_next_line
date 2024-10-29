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

static int	find_nl_size(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i + 2);
}

static void	shift_buffer(int i, char *buffer)
{
	int	j;

	j = 0;
	if (i != BUFFER_SIZE)
	{
		while (i + 1 != BUFFER_SIZE)
		{
			buffer[j] = buffer[i];
			j++;
			i++;
		}
	}
	buffer[j] = '\0';
}

static void	make_line(char *buffer, char *line)
{
	int	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] != '\n' && i == BUFFER_SIZE - 1)
		line[i] = '\n';
	else
		i--;
	line[i + 1] = '\0';
	shift_buffer(i + 1, buffer);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	size_t		bytes_read;
	char		*line;

	if (!buffer[0])
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
		if (bytes_read <= 0)
			return (NULL);
		buffer[bytes_read] = '\0';
	}
	line = (char *)malloc(find_nl_size(buffer) * sizeof(char));
	if (!line)
		return (NULL);
	make_line(buffer, line);
	return (line);
}

// int main() {
// 	int fd = open("41_no_nl", O_RDONLY);
// 	if (fd == -1)
//         return 1;
// 	char *line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		line = get_next_line(fd);
// 	}
// 	return (0);
// }