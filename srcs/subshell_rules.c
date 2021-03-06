/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_rules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:45:09 by bdurst            #+#    #+#             */
/*   Updated: 2018/12/09 22:48:47 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

static void	concat_prev_bqt(t_list **lexems, t_token *prev_token)
{
	t_token *token;

	token = (t_token*)(*lexems)->data;
	if (prev_token && (prev_token->type == WORD ||
		prev_token->type == NUM || prev_token->type == NEG_NUM))
	{
		free_join(&prev_token->value, VAL);
		ft_pop_node(lexems, (void*)&clear_lexems);
	}
	if (prev_token && prev_token->type == EQUAL)
		TYPE = VAR_WORD;
}

static void	concat_next_bqt(t_list **lexems, t_list *next_lexems)
{
	t_list	*last_new_token;
	t_token	*next_token;

	next_token = (next_lexems) ? (t_token*)next_lexems->data : NULL;
	if (next_token && !next_token->blank && (next_token->type == WORD ||
		next_token->type == NUM || next_token->type == NEG_NUM))
	{
		last_new_token = *lexems;
		while (last_new_token)
		{
			if (last_new_token->next == next_lexems)
				break ;
			NEXT(last_new_token);
		}
		if (last_new_token)
			free_join(&((t_token*)last_new_token->data)->value, \
				next_token->value);
		ft_pop_node(&next_lexems, (void*)&clear_lexems);
	}
}

static void	set_type_and_next_lexems(t_list **next_lexems, \
			enum e_token *end_type)
{
	if (*next_lexems)
	{
		*end_type = ((t_token*)(*next_lexems)->data)->type;
		*next_lexems = (*next_lexems)->next;
	}
}

void		bqt_rule(t_sh *sh, t_list **lexems,
					char is_cmd)
{
	t_token			*prev_token;
	t_list			*next_lexems;
	t_list			*prev_lexems;
	char			blank;
	enum e_token	end_type;

	prev_lexems = (*lexems)->prev;
	prev_token = (prev_lexems) ? (t_token*)prev_lexems->data : NULL;
	blank = ((t_token*)(*lexems)->data)->blank;
	next_lexems = (*lexems)->next;
	while (next_lexems && ((t_token*)next_lexems->data)->type != EBQT && \
		((t_token*)next_lexems->data)->type != EBQT_INSIDE_ST_OP)
		NEXT(next_lexems);
	set_type_and_next_lexems(&next_lexems, &end_type);
	delete_first_subshell_lexems(&sh->lexer->lexems, lexems);
	if (*lexems)
	{
		subshell(sh, *lexems, end_type, is_cmd);
		delete_subshell_lexems(&sh->lexer->lexems, lexems, BQT, end_type);
		if (prev_token && *lexems != prev_lexems && !blank)
			concat_prev_bqt(lexems, prev_token);
		if (next_lexems && *lexems && *lexems != next_lexems && \
			!((t_token*)next_lexems->data)->blank)
			concat_next_bqt(lexems, next_lexems);
	}
}
