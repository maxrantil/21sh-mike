/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_error_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:32:10 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/16 20:08:29 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	free_cmd_node(t_cmdnode *node)
{
	if (node)
	{
		while (node->cmd)
		{
			ft_memdel((void **)&node->cmd);
			++node->cmd;
		}
	}
}

static void	free_redir_node(t_redir **redir)
{
	free_cmd_node((t_cmdnode *)(*redir)->cmd);
	ft_memdel((void **)&(*redir)->filepath);
	*redir = NULL;
}

int	error_tok(t_token *tokens, t_treenode *redir_head, char *msg, char *symbol)
{
	if (!symbol && msg)
		ft_err_print(NULL, NULL, msg, 2);
	else if (symbol && msg)
		ft_err_print(NULL, msg, symbol, 2);
	while (tokens && tokens->token)
	{
		free_token(&(*tokens));
		++tokens;
	}
	while (redir_head)
	{
		free_redir_node(((t_redir **)&redir_head));
		++redir_head;
	}
	return (1);
}
