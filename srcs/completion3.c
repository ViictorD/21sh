/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 19:12:01 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/12/08 18:33:15 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

static void	create_bin_tab2(DIR *dir, char *part, char **tab, int *i)
{
	t_dirent	*ent;

	while ((ent = readdir(dir)))
	{
		if ((!part && ft_strcmp(ent->d_name, ".") && ft_strcmp(ent->d_name, \
			"..")) || (part && !ft_strncmp(ent->d_name, part, ft_strlen(part))))
		{
			if (ent->d_type == DT_DIR)
			{
				tab[++*i] = ft_memalloc(ft_strlen(ent->d_name) + 2);
				ft_strcpy(tab[*i], ent->d_name);
				tab[*i][ft_strlen(ent->d_name)] = '/';
			}
			else
				tab[++*i] = ft_strdup(ent->d_name);
		}
	}
}

char		**create_bin_tab(char **path, char *part, int nb)
{
	DIR			*dir;
	char		**tab;
	int			i;
	int			count;

	if (!(tab = malloc(nb * sizeof(char**) + 1)))
		return (NULL);
	count = -1;
	i = -1;
	while (path[++count])
	{
		if (!(dir = opendir(path[count])))
		{
			tab[++count] = NULL;
			ft_strdelpp(&tab);
			return (NULL);
		}
		create_bin_tab2(dir, part, tab, &i);
		closedir(dir);
	}
	if (part)
		add_builtins(tab, part, &i);
	tab[++i] = NULL;
	return (tab);
}

char		**create_print_tab(char *path, char *part, int nb, int i)
{
	DIR			*dir;
	t_dirent	*ent;
	char		**tab;

	if (!(dir = opendir(path)) || \
		!(tab = malloc(nb * sizeof(char**) + 1)))
		return (NULL);
	while ((ent = readdir(dir)))
	{
		if ((!part && ft_strcmp(ent->d_name, ".") && ft_strcmp(ent->d_name, \
			"..")) || (part && !ft_strncmp(ent->d_name, part, ft_strlen(part))))
		{
			if (ent->d_type == DT_DIR)
			{
				tab[++i] = ft_memalloc(ft_strlen(ent->d_name) + 2);
				ft_strcpy(tab[i], ent->d_name);
				tab[i][ft_strlen(ent->d_name)] = '/';
			}
			else
				tab[++i] = ft_strdup(ent->d_name);
		}
	}
	tab[++i] = NULL;
	closedir(dir);
	return (tab);
}
