#include "tosh.h"
#include <fcntl.h>

void		manage_dchevb(t_tree *node, char *cmd, char none)
{
	int		fd_pipe[2];
	char	*line;

	line = NULL;
	pipe(fd_pipe);
	if (!none)
		set_old_term(get_shell());
	ft_putstr("heredoc> ");
	while (gnl(0, &line) && ft_strcmp(line, cmd))
	{
		ft_putstr("heredoc> ");
		ft_fputendl(line, fd_pipe[1]);
		free(line);
	}
	if (!none)
		set_our_term(get_shell());
	free(line);
	close(fd_pipe[1]);
	if (node->cmds)
	{
		dup2(fd_pipe[0], 0);
		close(fd_pipe[0]);
	}
}

void		manage_chevb(t_fd fd)
{
	if (fd.to != -1)
	{
		dup2(fd.to, 0);
		close(fd.to);
	}
	else
	{
		dup2(fd.file, 0);
		close(fd.file);
	}
	close(fd.file);
}

static char	manage_chev(t_tree *node, t_sh *shell)
{
	t_fd	*fd;

	if (node->token->type == DCHEVB && !node->left)
		manage_dchevb(node, node->right->cmds[0], 0);
	else if (node->token->type == CHEVF || node->token->type == DCHEVF
			|| node->token->type == FRED)
	{
		if (!(fd = (t_fd*)malloc(sizeof(t_fd))))
			exit(-1);
		if (node->token->type == FRED && !ft_strcmp(node->right->cmds[0], "-"))
			fd->file = -2;
		else if ((fd->file = open_file(node)) == -1)
			return (-1);
		if (node->token->type != FRED)
			fd->from = (node->from_fd == -1) ? 1 : node->from_fd;
		else
			fd->from = node->from_fd;
		fd->to = -1;
		fd->type = node->token->type;
		ft_node_push_front(&shell->fds_out, fd);
	}
	return (0);
}

char		operators(t_tree *node, t_sh *shell)
{
	int		ret;

	ret = 0;
	if (node->token->type == PIPE)
	{
		if (shell->fd_pipe == -1)
			shell->fd_pipe = 0;
	}
	else if (node->token->type == CHEVB)
	{
		if ((shell->fd_in.file = open_file(node)) == -1)
			return (-1);
		shell->fd_in.to = node->to_fd;
		shell->fd_in.from = -1;
		shell->fd_in.type = node->token->type;
	}
	else
		return (manage_chev(node, shell));
	return (0);
}
