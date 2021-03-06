/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 23:39:09 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/12/06 18:44:57 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

static char	execve_cmds(t_sh *shell, t_tree *node, t_env *env)
{
	char	*path;
	char	**envi;
	int		ret;

	if ((path = get_path(node, shell->save_env ? shell->save_env : env, shell)))
	{
		envi = conv_env(env);
		ret = execve(path, node->cmds, envi);
		free(path);
		if (envi)
			ft_strdelpp(&envi);
	}
	else if (!shell->have_write_error)
	{
		ft_fputstr("42sh: ", 2);
		ft_fputstr(node->cmds[0], 2);
		ft_fputendl(": command not found", 2);
		ret = EXIT_FAILURE;
	}
	else
		ret = EXIT_FAILURE;
	return (ret);
}

char		run_binary(t_tree *node, t_env *env, t_sh *shell)
{
	int		fd[2];
	int		ret;
	int		heredoc_pipe[2];

	set_old_term(shell, *(node->cmds));
	if (node->parent && node->parent->TYPE == DCHEVB && \
		(ret = pipe(heredoc_pipe)) == -1)
		errexit("42sh", "pipe failure !\n");
	if ((ret = get_fd(shell, fd)) != -1)
	{
		if ((g_father = fork()) == -1)
			ft_exiterror("fork failure !", -1);
		else if (!g_father)
		{
			ret = EXIT_SUCCESS;
			manage_child_fd(shell, node, fd, heredoc_pipe);
			if (node->cmds && node->cmds[0] && node->cmds[0][0])
				ret = execve_cmds(shell, node, env);
			exit(ret);
		}
		else
			ret = father(shell, fd, heredoc_pipe, node->parent);
	}
	set_our_term(shell);
	return (ret);
}

char		run_builtins(t_tree *node, t_env **env, t_sh *shell)
{
	int		ret;
	int		fd[2];
	int		heredoc_pipe[2];

	set_old_term(shell, "123");
	if (node->parent && node->parent->TYPE == DCHEVB && \
		(ret = pipe(heredoc_pipe)) == -1)
		errexit("42sh", "pipe failure !\n");
	if ((ret = get_fd(shell, fd)) != -1)
	{
		if ((g_father = fork()) == -1)
			ft_exiterror("fork failure !", -1);
		else if (!g_father)
		{
			ret = EXIT_SUCCESS;
			manage_child_fd(shell, node, fd, heredoc_pipe);
			if (node->cmds && node->cmds[0] && node->cmds[0][0])
				ret = go_builtins(node->cmds, env, shell);
			exit(ret);
		}
		else
			ret = father(shell, fd, heredoc_pipe, node->parent);
	}
	set_our_term(shell);
	return (ret);
}
