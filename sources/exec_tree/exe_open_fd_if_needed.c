/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_open_fd_if_needed.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:13:07 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/15 16:58:31 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	open_until_fd(int fd, char *terminal)
{
	int	i;

	i = -1;
	while (1)
	{
		i = open(terminal, O_RDWR);
		if (i < 0)
			ft_err_print(NULL, "open_fd_if_needed", "open failed", 2);
		if (i > fd)
		{
			close(i);
			break ;
		}
	}
}

static void	close_previously_closed(int fd, int *closefd)
{
	int	i;

	i = 0;
	while (i < fd)
	{
		if (closefd[i] == 1 && close(i) < 0)
			ft_err_print(NULL, "open_fd_if_needed", "close failed", 2);
		++i;
	}
}

void	open_fd_if_needed(int fd, char *terminal)
{
	struct stat	buf;
	int			*closefd;
	int			i;

	closefd = ft_memalloc(sizeof(*closefd) * (fd + 1));
	i = 0;
	if (fstat(fd, &buf) < 0)
	{
		while (i <= fd)
		{
			if (fstat(i, &buf) < 0)
				closefd[i] = 1;
			++i;
		}
		open_until_fd(fd, terminal);
		close_previously_closed(fd, closefd);
	}
	free(closefd);
}
