/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aggregation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:26:00 by jakken            #+#    #+#             */
/*   Updated: 2022/12/06 17:05:50 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void exec_aggregate(t_aggregate *node, char ***environ_cp, char *terminal)
{
//	if (fork_wrap() == 0)
//	{
		if (dup2(node->open_fd, node->close_fd) < 0)
		{
			ft_printf("21sh: dup: bad filedescriptor\n");
			exit (0);
		}
		exec_tree(node->cmd, environ_cp, terminal);
//		exit (0);
//	}
//	wait (0);
}
