/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:56:11 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/24 16:08:25 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	slen;
	char	*str;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		len = 0;
	else if (len > (slen - start))
		len = slen - start;
	str = (char *) malloc ((len + 1) * sizeof (char));
	if (!str)
		return (NULL);
	i = 0;
	j = start;
	while (s[i] && len--)
		str[i++] = s[j++];
	str[i] = '\0';
	return (str);
}
