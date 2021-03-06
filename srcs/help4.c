/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 14:40:14 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/11/15 15:02:28 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

void	help_cd(void)
{
	first_step("cd");
	ft_putendl("\t- cd [-L | -P] [directory]\n");
	ft_putendl("\t-L : Handle the operand dot-dot logically.");
	ft_putendl("\t-P : Handle the operand dot-dot physically.");
	ft_putendl("\tdirectory : Directory absolute or relative path.\n");
	ft_putstr(C_RESET);
}

void	help_shellvar(void)
{
	first_step("shellvar");
	ft_putendl("\t- shellvar: Show shell variable.\n");
	ft_putstr(C_RESET);
}
