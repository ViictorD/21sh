/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 20:22:49 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/10/11 14:46:16 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

static char	fill_fd(t_sh *sh, int *left_fd, int *right_fd, enum e_token type)
{
	*left_fd = ft_atoi(sh->current_token->value);
	eat(sh, FD);
	eat(sh, type);
	if (sh->current_token->type == FD)
	{
		*right_fd = ft_atoi(sh->current_token->value);
		eat(sh, FD);
	}
	else
	{
		*right_fd = -7895474;
		eat(sh, CLOSE_FD);
	}
	return (1);
}

static char	is_fd_type(t_sh *sh, enum e_token type)
{
	if (sh->current_token->type == FD && sh->lexer->lexems->next && \
	((t_token*)sh->lexer->lexems->next->data)->type == type)
		return (1);
	return (0);
}

static char	fred_bred_rules(t_sh *sh, int *left_fd, int *right_fd,
			enum e_token type)
{
	if (is_fd_type(sh, type) && sh->lexer->lexems->next->next && \
		((t_token*)sh->lexer->lexems->next->next->data)->type == FD)
		return (fill_fd(sh, left_fd, right_fd, type));
	else if (sh->current_token->type == type && sh->lexer->lexems->next && \
		((t_token*)sh->lexer->lexems->next->data)->type == FD)
	{
		*left_fd = (type == BRED) ? 0 : 1;
		eat(sh, type);
		*right_fd = ft_atoi(sh->current_token->value);
		eat(sh, FD);
		return (1);
	}
	else if (is_fd_type(sh, type) && sh->lexer->lexems->next->next &&
		((t_token*)sh->lexer->lexems->next->next->data)->type == CLOSE_FD)
		return (fill_fd(sh, left_fd, right_fd, type));
	else if (is_fd_type(sh, type))
	{
		eat(sh, FD);
		eat(sh, type);
		return (-1);
	}
	return (0);
}

static void	*free_return(t_fd *fd, void *ret)
{
	free(fd);
	return (ret);
}

t_fd		*aggregation_rules(t_sh *sh)
{
	t_fd	*fd;
	char	ret;

	if (!(fd = (t_fd*)malloc(sizeof(t_fd))))
		ft_exiterror("Malloc failure in aggregation_rules !", 1);
	if (!sh->current_token)
		return (free_return(fd, NULL));
	if ((ret = fred_bred_rules(sh, &fd->to, &fd->from, BRED)) == -1)
		return (free_return(fd, (void*)-1));
	else if (ret)
		fd->type = BRED;
	else if ((ret = fred_bred_rules(sh, &fd->from, &fd->to, FRED)) == -1)
		return (free_return(fd, (void*)-1));
	else if (ret)
		fd->type = FRED;
	else
		return (free_return(fd, NULL));
	return (fd);
}
