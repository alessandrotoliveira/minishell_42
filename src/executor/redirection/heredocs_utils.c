/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:18:41 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/26 09:18:41 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char_to_str(char *str, char c)
{
	char	*new_str;
	int		len;
	int		i;

	len = 0;
	if (str)
		len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(str);
	return (new_str);
}

char	*process_var_expansion(char *result,
						char *line, int *i, t_mini *mini)
{
	int		len;
	char	*var_name;
	char	*var_value;

	len = get_var_len(&line[*i + 1]);
	if (len > 0)
	{
		var_name = ft_substr(line, *i + 1, len);
		var_value = get_token_value(mini, var_name);
		free(var_name);
		result = ft_strjoinfree(result, var_value);
		*i += len + 1;
		return (result);
	}
	result = append_char_to_str(result, line[*i]);
	(*i)++;
	return (result);
}

char	*expand_line_vars(char *line, t_mini *mini)
{
	char	*result;
	int		i;

	if (!ft_strchr(line, '$'))
		return (ft_strdup(line));
	result = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] != '\0' && line[i + 1] != ' ')
			result = process_var_expansion(result, line, &i, mini);
		else
		{
			result = append_char_to_str(result, line[i]);
			i++;
		}
	}
	return (result);
}

/* ================= RAW INPUT ================= */

char	*grow_buffer(char *old, size_t old_len)
{
	char	*new;
	size_t	i;

	new = malloc(old_len + 2);
	if (!new)
	{
		free(old);
		return (NULL);
	}
	i = 0;
	while (i < old_len)
	{
		new[i] = old[i];
		i++;
	}
	new[i] = '\0';
	free(old);
	return (new);
}

char	*append_char(char *line, size_t *len, char c)
{
	char	*new_line;

	new_line = grow_buffer(line, *len);
	if (!new_line)
		return (NULL);
	new_line[*len] = c;
	(*len)++;
	new_line[*len] = '\0';
	return (new_line);
}
