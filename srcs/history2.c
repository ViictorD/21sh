/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 20:56:37 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/12/03 17:09:48 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "tosh.h"

void		add_line(t_sh *shell, char *toadd)
{
	int		i;
	char	**new;

	if (!shell->history)
	{
		if (!(shell->history = (char**)malloc(sizeof(char*) * 2)))
			ft_exiterror("Malloc failed", 1);
		shell->history[0] = ft_strdup(toadd);
		shell->history[1] = NULL;
		return ;
	}
	if (!(new = (char**)malloc(sizeof(char*) * \
		(ft_counttab(shell->history) + 2))))
		ft_exiterror("Malloc failed", 1);
	i = -1;
	new[0] = ft_strdup(toadd);
	while (shell->history[++i])
		new[i + 1] = ft_strdup(shell->history[i]);
	new[i + 1] = NULL;
	ft_strdelpp(&(shell->history));
	shell->history = new;
}

static char	**convert_history(char *str, int count)
{
	int		i;
	int		j;
	int		last;
	char	**out;

	if (!(out = (char**)malloc(sizeof(char*) * (count + 1))))
		ft_exiterror("Malloc failed", 1);
	last = 0;
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == '\n')
		{
			out[++j] = ft_strsub(str, last, i - last);
			last = i + 1;
		}
	}
	out[++j] = NULL;
	return (out);
}

char		**get_history(t_sh *shell, off_t size, char *home, \
				char is_42sh_logs)
{
	int		i;
	int		fd;
	int		count;
	char	history[size + 1];

	if ((fd = open(home, O_RDONLY)) == -1)
		return (NULL);
	if (read(fd, history, size) == -1)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	history[size] = '\0';
	i = -1;
	count = 0;
	while (history[++i])
		if (history[i] == '\n')
			++count;
	if (is_42sh_logs)
		shell->history = convert_history(history, count);
	else
		return (convert_history(history, count));
	return (NULL);
}

void		load_history(t_sh *shell, t_env *env)
{
	char		*home;
	struct stat	buff;

	if (!(home = find_env(env, "HOME")))
		return ;
	home = ft_strjoin(home, "/.42sh_history");
	if (!stat(home, &buff) && buff.st_size <= HIST_MAX_SIZE && \
		S_ISREG(buff.st_mode))
	{
		get_history(shell, buff.st_size, home, 1);
		shell->hist_first = ft_counttab(shell->history);
	}
	else
		shell->history = NULL;
	free(home);
}

void		save_history(t_sh *shell)
{
	int		i;
	int		fd;
	char	*home;

	if (!shell->history || !(home = find_env(shell->env, "HOME")))
		return ;
	home = ft_strjoin(home, "/.42sh_history");
	if ((fd = open(home, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) != -1)
	{
		i = -1;
		while (shell->history[++i])
		{
			write(fd, shell->history[i], ft_strlen(shell->history[i]));
			write(fd, "\n", 1);
		}
		close(fd);
	}
	free(home);
}
