/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 23:06:58 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/05/06 00:33:07 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "21sh.h"

static char go_builtins(t_tree *node, t_env **env, t_sh *shell)
{
	(void)env;
	(void)shell;
	if (!ft_strncmp(node->tokens->data, "echo", 4))
		;
	//echo(list_to_tabstr(node->tokens), *env);
	else if (!ft_strncmp(node->tokens->data, "cd", 2))
		cd(list_to_tabstr(node->tokens), *env, shell);
	else if (!ft_strncmp(node->tokens->data, "setenv", 6))
		;
	//set_env(list_to_tabstr(node->tokens), env);
	else if (!ft_strncmp(node->tokens->data, "unsetenv", 8))
		;
	//unset_env(list_to_tabstr(node->tokens), env);
	else if (!ft_strncmp(node->tokens->data, "env", 3))
		;
	//env_command(list_to_tabstr(node->tokens), *env);
	else if (!ft_strncmp(node->tokens->data, "exit", 4))
		;
	//	exit_command(list_to_tabstr(node->tokens), shell);
	else
		return (0);
	return (1);
}

static void add_to_history(t_sh *shell, char *command)
{
	int i;
	char *tmp;

	if (!ft_strcont(command, "\n"))
		add_line(shell, command);
	else
	{
		i = -1;
		while (command[++i] && command[i] != '\n')
			;
		tmp = ft_strsub(command, 0, i);
		add_line(shell, tmp);
		free(tmp);
	}
	shell->history_pos = -1;
}

void browse_tree(t_tree *node, t_env **env, t_sh *shell)
{
	int fd_in;

	fd_in = 0;
	if (node->left)
		browse_tree(node->left, env, shell);
	if (node->right)
		browse_tree(node->right, env, shell);
	if (node->token)
		operators(node, &fd_in);
	if (node->tokens)
	{
		if (go_builtins(node, env, shell) /* || \
		go_path(commands_tree[i], *env)*/)
			;
		else
		{
			ft_putstr(node->tokens->data);
			ft_putendl(": Command not found.");
		}
	}
}

void go_core(char *command, t_env **env, t_sh *shell)
{
	t_tree *commands_tree;

	(void)env;
	add_to_history(shell, command);
	shell->lexer->line = command;
	shell->current_token = get_next_token(shell->lexer);
	if (!(commands_tree = commands_line_rules(shell)))
		return;
	browse_tree(commands_tree, env, shell);
}
