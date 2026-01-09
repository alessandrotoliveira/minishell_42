/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:26:34 by aletude-          #+#    #+#             */
/*   Updated: 2025/10/02 12:52:26 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putcharf(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstrf(char *s)
{
	int	i;

	if (s == NULL)
	{
		return (ft_putstrf("(null)"));
	}
	i = 0;
	while (s[i])
	{
		ft_putcharf(s[i]);
		i++;
	}
	return (i);
}

int	ft_putnbrf(int n)
{
	unsigned int	nb;
	int				count;

	count = 0;
	if (n == -2147483648)
	{
		ft_putstrf("-2147483648");
		return (11);
	}
	if (n < 0)
	{
		ft_putcharf('-');
		nb = -n;
		count++;
	}
	else
		nb = (unsigned int)n;
	if (nb >= 10)
	{
		count += ft_putnbrf (nb / 10);
	}
	count += ft_putcharf((nb % 10) + '0');
	return (count);
}

int	ft_puthexa(unsigned long n, const char *base)
{
	int	count;

	count = 0;
	if (n >= 16)
	{
		count += ft_puthexa(n / 16, base);
	}
	count += ft_putcharf (base[n % 16]);
	return (count);
}

void	ft_putptr(va_list args, int *count)
{
	unsigned long	ptr;

	ptr = (unsigned long)va_arg(args, void *);
	if (ptr == 0)
		*count += ft_putstrf("(nil)");
	else
	{
		*count += ft_putstrf("0x");
		*count += ft_puthexa(ptr, "0123456789abcdef");
	}
}
