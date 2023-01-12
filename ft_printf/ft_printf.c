/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 04:28:47 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/12 08:22:10 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int ft_printf_char(int c)
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

void ft_print_num(long long int num, int base, int *len)
{
	char *hexadecimal = "0123456789abcdef";

	if (num < 0)
	{
		num *= -1;
		*len += write(1, "-", 1);
	}
	if (num >= base)
		ft_print_num((num / base), base, len);
	*len += write(1, &hexadecimal[num % base], 1);
}

int ft_printf(const char *str, ...)
{
	int			i;
	int			print_len;
	va_list		arg;

	i = 0;
	print_len = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1])
			{
				if (str[i + 1] == 'c')
					print_len += ft_printf_char(va_arg(arg, int));
				if (str[i + 1] == 's')
					print_len += ft_printf_str(va_arg(arg, char *));
				if (str[i + 1] == 'd' || str[i + 1] == 'i')
					ft_print_num(va_arg(arg, int), 10, &print_len);
				if (str[i + 1] == 'x')
					ft_print_num(va_arg(arg, unsigned int), 16, &print_len);
				if (str[i + 1] == '%')
					print_len += ft_printf_char('%');
				i++;
			}
		}
		else
			print_len += ft_printf_char(str[i]);
		i++;
	}
	va_end(arg);
	return (print_len);
}

// int main()
// {
// 	int len;
// 	len = ft_printf("w%w%w%w");
// 	printf("\nlen: %i\n", len);
// 	// ft_printf(" - Len: %i\n", ft_printf("%c", 'a'));
// 	// ft_printf(" - Len: %i\n", ft_printf("%s", "toto"));
// 	// ft_printf(" - Len: %i\n",ft_printf("%%"));
// 	// ft_printf(" - Len: %i\n", ft_printf("Magic %s is %d", "number", 42));
// 	// ft_printf(" - Len: %i\n", ft_printf("Hexadecimal for %d is %x", 42, 42));
// 	// ft_printf(" - Len: %i\n", ft_printf("Hexadecimal for %d is %X\n", 42, 42));
// 	// ft_printf(" - Len: %i\n", printf("Hexadecimal for %d is %X\n", 42, 42));
// 	return (1);
// }