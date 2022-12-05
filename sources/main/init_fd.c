/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:14:26 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/05 16:45:37 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_21sh.h"

void	exec_closefd(t_closefd *node, char ***environ_cp)
{
	close(node->close_fd);
	if (fork_wrap == 0)
		exec_tree(node->cmd, environ_cp);
}
