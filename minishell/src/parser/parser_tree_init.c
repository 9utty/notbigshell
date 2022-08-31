/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:30:10 by gulee             #+#    #+#             */
/*   Updated: 2022/08/31 20:31:00 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree	*init_tree(void)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		null_error("Tree allocation failure error in init tree");
	ft_memset(tree, 0, sizeof(t_tree));
	return (tree);
}

t_node	*init_node(t_token	*token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		null_error("Tree-node allocation failure error in init tree-node");
	ft_memset(node, 0, sizeof(t_node));
	node->data = ft_strdup(token->data);
	node->type = token->type;
	return (node);
}
