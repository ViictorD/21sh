/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 12:32:55 by bdurst            #+#    #+#             */
/*   Updated: 2016/05/27 12:32:55 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ascii.h"

int		ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
