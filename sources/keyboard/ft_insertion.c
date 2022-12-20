/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/20 11:39:43 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It inserts a character into the input string
 *
 * @param t the term structure
 */
static void	ft_insertion_char(t_term *t)
{
	ft_putc(t->ch);
	t->c_col++;
	ft_shift_nl_addr(t, 1);
	if (t->inp[t->index])
		ft_shift_insert(t);
	t->inp[t->index++] = (char)t->ch;
	t->bytes++;
	if ((t->inp[t->index - 1] == D_QUO || t->inp[t->index - 1] == S_QUO) \
		&& !t->heredoc)
	{
		if (!ft_bslash_escape_check(t, t->index - 1))
			ft_quote_flag_reset(t);
	}
	if (t->inp[t->index - 1] == '<' && !t->heredoc)
	{
		ft_heredoc_handling(t, t->index - 1);
		if (!t->heredoc && t->delim)
			ft_strdel(&t->delim);
	}
	else if (t->inp[t->index - 1] == '\\')
		ft_quote_flag_check(t, t->index - 1);
}

/*
 * If the user is not at the end of the line, the function will
 * insert a new line.
 *
 * @param t the term structure
 */
static void	ft_insertion_enter(t_term *t)
{
	if (!t->nl_addr[t->c_row + 1])
	{
		if (ft_delim_fetch(t))
			return ;
		t->bslash = ft_bslash_escape_check(t, t->bytes);
		if (t->q_qty % 2 \
			|| (t->heredoc \
			&& (t->delim && ft_strcmp(t->nl_addr[t->c_row], t->delim))) \
			|| t->bslash)
		{
			t->history_row = -1;
			ft_memcpy(t->history_buff, t->inp, t->bytes);
			t->inp[t->bytes++] = (char)t->ch;
			ft_create_prompt_line(t, t->bytes);
			t->index = t->bytes;
		}
	}
}

/*
 * It handles the insertion of characters into the input string
 *
 * @param t the t_term struct
 */
void	ft_insertion(t_term *t)
{
	if (t->ch == ENTER)
		ft_insertion_enter(t);
	else
		ft_insertion_char(t);
	ft_trigger_nl(t);
	if (t->inp[t->index])
		ft_print_trail(t);
}
