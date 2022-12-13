/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_tilde.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:57:35 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/13 22:24:42 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It returns the environment variable name that corresponds to the tilde key
 * 
 * @param str The string to be expanded.
 * 
 * @return The key for the environment variable.
 */
static char	*tilde_key(char *str, int *stilde)
{
	if (!ft_strcmp(str, "~+"))
		return ("PWD");
	else if (!ft_strcmp(str, "~-"))
		return ("OLDPWD");
	else if (*str == '~')
	{
		*stilde = 1;
		return ("HOME");
	}
	// else if (!ft_strcmp(str, "~"))
	// 	return ("HOME");
	return (NULL);
}

/**
 * It takes a string and returns a string with the tilde expanded.
 * 
 * @param sesh the session struct
 * @param str the string to be expanded
 * 
 * @return The value of the key in the environment.
 */
char	*ft_expansion_tilde(t_session *sesh, char *str)
{
	char	*key;
	char	**env;
	int		stilde;

	env = NULL;
	stilde = 0;
	key = tilde_key(str, &stilde);
	if (key)
	{
		env = ft_env_get(sesh, key);
		if (env)
		{
			if (stilde)
				return (ft_strjoin(ft_strchr(*env, '=') + 1, str + 1));
			else
				return (ft_strdup(ft_strchr(*env, '=') + 1));
		}
	}
	return (ft_strdup(str));
}
