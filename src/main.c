/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnanque <bnanque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:23:08 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/27 16:10:06 by bnanque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_command(t_mini *mini)
{
	if (mini->cmd_list)
	{
		free_commands(mini->cmd_list);
		mini->cmd_list = NULL;
	}
	if (mini->tokens)
		free_tokens(&mini->tokens);
}

static void	handle_input(t_mini *mini, char *input)
{
	if (*input)
	{
		add_history(input);
		mini->input_line = input;
		if (parse_input(mini, input) == SUCCESS)
			executor(mini);
	}
	g_received_signal = 0;
	free(input);
	mini->input_line = NULL;
	cleanup_command(mini);
}

static char	*get_input(t_mini *mini)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "exit\n", 5);
			return (NULL);
		}
		if (g_received_signal == SIGINT)
		{
			mini->exit_code = 130;
			g_received_signal = 0;
			if (*input == '\0')
			{
				free(input);
				continue ;
			}
		}
		return (input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*input;

	(void)argc;
	(void)argv;
	ft_memset(&mini, 0, sizeof(t_mini));
	init_env(&mini, envp);
	init_signals();
	while (1)
	{
		input = get_input(&mini);
		if (!input)
			break ;
		handle_input(&mini, input);
	}
	free_env_list(mini.env_list);
	rl_clear_history();
	return (mini.exit_code);
}
