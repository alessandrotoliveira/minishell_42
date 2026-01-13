/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:07:16 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/13 10:49:24 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"
# include "../libft/libft.h"

//token_list.c
t_token	*new_token(char *content, t_token_type type, t_quote quote);
void	token_add_back(t_token **lst, t_token *new);
void	free_tokens(t_token **tokens);

//lexer_utils.c
int		is_whitespace(char c);
int		is_operator(char *str);

//parser_manager.c
int		parse_input(t_mini *mini, char *input);

//lexer.c
int		tokenize_input(t_mini *mini, char *input);

//syntax.c
int		check_syntax(t_token *tokens);

#endif