/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 18:42:51 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/27 18:43:28 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

char	echo_env(char *str)
{
	if (*(str + 1) == '?')
		ft_putnbr(get_shell()->return_value);
	return (1);
}
