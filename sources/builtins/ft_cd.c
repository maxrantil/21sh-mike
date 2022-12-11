/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:10:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/11 21:27:39 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	ft_chdir_expanded(t_session *sesh, char **path)
{
	chdir(*path);
	ft_dir_change(sesh);
	ft_strdel(path);
	return (0);
}

static int	ft_cd_expand_error(char **cmd)
{
	if (!((*cmd) + 1) || !ft_strcmp(((*cmd) + 1), "--"))
		ft_putendl("cd: HOME not set");
	if (!ft_strcmp(((*cmd) + 1), "~-")
		|| !ft_strcmp(((*cmd) + 1), "-"))
		ft_putendl("cd: OLDPWD not set");
	return (1);
}

static char	*ft_cd_expand(t_session *sesh, char **cmd)
{
	char	**env;

	if (ft_arrlen(cmd) == 1 \
		|| !ft_strcmp(((*cmd) + 1), "--"))
	{
		env = ft_env_get(sesh, "HOME");
		if (env)
			return (ft_strdup(ft_strchr(*env, '=') + 1));
	}
	else if (!ft_strcmp(((*cmd) + 1), "-"))
	{
		env = ft_env_get(sesh, "OLDPWD");
		if (env)
		{
			ft_putendl(ft_strchr(*env, '=') + 1);
			return (ft_strdup(ft_strchr(*env, '=') + 1));
		}
	}
	return (NULL);
}

static bool	ft_cd_expand_parse(t_session *sesh, char **cmd)
{
	char	*path;

	path = ft_cd_expand(sesh, cmd);
	if (path)
		return (ft_chdir_expanded(sesh, &path));
	else
		return (ft_cd_expand_error(cmd));
}

int	ft_cd(t_session *sesh, char **cmd)
{
	sesh->exit_stat = 0;
	if (ft_arrlen(cmd) > 2) // TODO: error for too many arguments
		return (1);
	if (!ft_cd_expand_parse(sesh, cmd))
		return (1);
	if (!ft_addr_check(*(cmd + 1)))
	{
		if (chdir(*(cmd + 1)))
			sesh->exit_stat = 1;
		else
			ft_dir_change(sesh);
	}
	else
		sesh->exit_stat = 1;
	return (0);
}
