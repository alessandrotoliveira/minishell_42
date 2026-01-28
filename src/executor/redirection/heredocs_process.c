/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:18:07 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/26 09:18:07 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sigint(int sig)
{
	g_received_signal = sig;
	write(1, "\n", 1);
}

void	setup_heredoc_signal(struct sigaction *old)
{
	struct sigaction	new;

	new.sa_handler = heredoc_sigint;
	new.sa_flags = 0;
	sigemptyset(&new.sa_mask);
	sigaction(SIGINT, &new, old);
}

void	restore_heredoc_signal(struct sigaction *old)
{
	sigaction(SIGINT, old, NULL);
}
