/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:42:07 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/05 16:42:42 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_fd_split(int fd, char c)
{
	char	*content;
	char	**lines;

	content = ft_fd_to_str(fd);
	if (content == NULL)
		return (NULL);
	lines = ft_split(content, c);
	free(content);
	return (lines);
}
