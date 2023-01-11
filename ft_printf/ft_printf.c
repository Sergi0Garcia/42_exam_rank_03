/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 04:28:47 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/11 05:49:43 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_printf_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int ft_printf_str(char *str)
{
	int i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		ft_printf_char(str[i]);
		i++;
	}
	return (i);
}

void ft_printf_int(long long int num, int base, int *len)
{
	char	*hexadecimal = "0123456789abcdef";

	if (num < 0)
	{
		num = num * -1;
		*len = write(1, "-", 1);
	}
	if (num >= base)
		ft_printf_int((num / base), base, len);
	*len = write(1, &hexadecimal[num % base], 1);
}

int ft_printf(const char *str, ...)
{
	int 		i;
	int			print_len;
	va_list		arg;

	print_len = 0;
	i = 0;
	va_start(arg, str);
	
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == 's')
				print_len += ft_printf_str(va_arg(arg, char *));
			if (str[i + 1] == 'i' || str[i + 1] == 'd')
				ft_printf_int((long long int)va_arg(arg, int), 10, &print_len);
			if (str[i + 1] == 'x')
				ft_printf_int((long long int)va_arg(arg, int), 16, &print_len);
			i++;
		}
		else
			print_len += ft_printf_char(str[i]);
		i++;
	}
	va_end(arg);
	return (print_len);
}

int main()
{
	ft_printf("%s\n", "toto");
	ft_printf("Magic %s is %d\n", "number", -12938);
	ft_printf("Hexadecimal for %d is %x\n", 42, -42);
	return (1);
}