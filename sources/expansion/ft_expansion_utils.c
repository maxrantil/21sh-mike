/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:38:31 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/17 21:49:43 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// static int	ft_bslash_null(char *buff, ssize_t pos)
// {
// 	ssize_t	count;

// 	count = pos - 1;
// 	while (count && buff[count] == '\\')
// 		count--;
// 	if ((pos - count) % 2)
// 		return (1);
// 	return (0);
// }

static size_t	ft_bslash_null(char *buff, ssize_t pos)
{
	size_t	len;
	ssize_t	count;

	len = 0;
	count = pos - 1;
	while (buff[count] == '\\')
	{
		len++;
		if (!count)
			break ;
		count--;
	}
	if (len && (len % 2))
	{
		ft_printf("%d %d\n", pos, len);
		return (1);
	}
	return (0);
}
// static int	ft_bslash_null(char *buff, ssize_t pos)
// {
// 	ssize_t	count;

// 	count = pos - 1;
// 	while (buff[count] == '\\')
// 	{
// 		count--;
// 		if (!count)
// 			break ;
// 	}
// 	if ((pos - count) % 2)
// 		return (1);
// 	return (0);
// }

static void	ft_qoute_parse(char *buff, char *quote, int len)
{
	if (!len || buff[len - 1] != '\\' || !ft_bslash_null(buff, len)) // something wrong this condition
	{	
		if (!(*quote))
			*quote = buff[len];
		else if (*quote == buff[len])
			*quote = 0;
		ft_memmove((void *)&buff[len], (void *)&buff[len + 1], \
		ft_strlen(&buff[len + 1]) + 1);
	}	
}

static void	ft_blash_parse(char *buff, char *quote, int len)
{
	if (!(*quote) && ft_bslash_null(buff, len + 1))
	{
		ft_memmove((void *)&buff[len], (void *)&buff[len + 1], \
		ft_strlen(&buff[len + 1]) + 1);
	}
	else if (*quote == D_QUO && !ft_bslash_null(buff, len + 1))
		ft_memmove((void *)&buff[len], (void *)&buff[len + 1], \
			ft_strlen(&buff[len + 1]) + 1);
}

void	ft_quote_blash_removal(char *buff)
{
	int		len;
	char	quote;

	quote = 0;
	len = ft_strlen(buff);
	while (len >= 0)
	{
		if ((buff[len] == S_QUO || buff[len] == D_QUO))
			ft_qoute_parse(buff, &quote, len);
		else if (buff[len] == '\\')
			ft_blash_parse(buff, &quote, len);
		else if (buff[len] == '\n' && len && ft_bslash_null(buff, len))
		{
			ft_memmove((void *)&buff[len], (void *)&buff[len + 1], \
			ft_strlen(&buff[len + 1]) + 1);
			if (len && buff[len - 1] == '\\')
			{
				len--;
				ft_memmove((void *)&buff[len], (void *)&buff[len + 1], \
				ft_strlen(&buff[len + 1]) + 1);
			}
		}
		len--;
	}
}
