/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:59:13 by aletude-          #+#    #+#             */
/*   Updated: 2025/10/02 12:52:55 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_u(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_putnbr_u(n / 10);
	count += ft_putcharf((n % 10) + '0');
	return (count);
}

int	ft_format(va_list args, char format)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += ft_putcharf(va_arg(args, int));
	else if (format == 's')
		count += ft_putstrf(va_arg(args, char *));
	else if (format == 'p')
		ft_putptr(args, &count);
	else if (format == 'd' || format == 'i')
		count += ft_putnbrf(va_arg(args, int));
	else if (format == 'u')
		count += ft_putnbr_u(va_arg(args, unsigned int));
	else if (format == 'x')
		count += ft_puthexa(va_arg(args, unsigned int), "0123456789abcdef");
	else if (format == 'X')
		count += ft_puthexa(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (format == '%')
		count += ft_putcharf ('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format [i + 1])
			count += ft_format(args, format[++i]);
		else
			count += ft_putcharf (format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
