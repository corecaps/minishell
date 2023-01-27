/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 02:28:46 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/27 14:56:17 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/*****************************************************************************
 * test if the current line equals the heredoc strings, if yes
 * free the line and return 1, else return 0
 * @param node the command node where the heredoc list is stored
 * @param prev pointer to he last line tested against
 * @param current_line pointer to the current line
 * @param end the heredoc delimiter
 * @return 1 in case of final line 0 otherwise
 ****************************************************************************/

static int	end_heredoc(t_ast *node, t_here_doc *prev, t_here_doc *current_line,
	const char *end)
{
	if (ft_strncmp(current_line->line, end, ft_strlen(end)) == 0)
	{
		if (prev)
			prev->next = NULL;
		else
			node->here_doc_list = NULL;
		free(current_line->line);
		free(current_line);
		return (1);
	}
	else
		return (0);
}

/*****************************************************************************
 * Store the current line node at the right position in the linked list
 * @param node command node where the heredoc list is stored
 * @param current_line node to store
 ****************************************************************************/

static void	store_heredoc(t_ast *node, t_here_doc *current_line)
{
	t_here_doc	*cursor;

	if (node->here_doc_list == NULL)
		node->here_doc_list = current_line;
	else
	{
		cursor = node->here_doc_list;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = current_line;
	}
}

/***************************************************************************
 * Use Readline to get the complete heredoc until the delimiter is entered
 * @param node The node containing the heredoc
 * @return 0 on success, -1 on malloc error, -7 on readline error
 **************************************************************************/

int	parse_here_doc(t_ast *node)
{
	t_here_doc	*prev;
	t_here_doc	*current_line;
	char		*end;

	prev = NULL;
	end = node->token_node->next_token->value;
	node = node->parent;
	while (node->type != E_COMMAND)
		node = node->parent;
	node->here_doc = 1;
	while (1)
	{
		current_line = malloc(sizeof(t_here_doc));
		if (!current_line)
			return (-1);
		current_line->line = readline("heredoc> ");
		if (current_line->line == NULL)
		{
			write(2,
				"minishell error: here-document delimited by EOF", 47);
			write(2, " (wanted `", 10);
			ft_putstr_fd(end, 2);
			write(2, "')\n", 3);
			if (prev)
				prev->next = NULL;
			free(current_line->line);
			free(current_line);
			return (-7);
		}
		current_line->next = NULL;
		store_heredoc(node, current_line);
		if (end_heredoc(node, prev, current_line, end))
			return (0);
		prev = current_line;
	}
}
