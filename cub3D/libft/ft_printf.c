/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:28:01 by miaviles          #+#    #+#             */
/*   Updated: 2025/02/20 18:25:45 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_format(va_list args, char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += print_char((char)va_arg(args, int));
	else if (format == 's')
		len += print_string(va_arg(args, char *));
	else if (format == 'p')
		len += print_pointer((size_t)va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		len += ft_putl_fd(va_arg(args, int), 1);
	else if (format == 'u')
		len += ft_putl_fd(va_arg(args, unsigned int), 1);
	else if (format == 'x')
		len += print_hex(va_arg(args, unsigned int), 0);
	else if (format == 'X')
		len += print_hex(va_arg(args, unsigned int), 1);
	else if (format == '%')
		len += print_char('%');
	return (len);
}

int	ft_printf(char const *str, ...)
{
	int		len;
	int		i;
	va_list	args;

	len = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != 0)
		{
			len += print_format(args, str[i + 1]);
			i++;
		}
		else
			len += print_char(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}

/*#include <stdio.h>

int	main(void)
{
	int original_print_return;
	int fake_print_return;
	
	fake_print_return = ft_printf("Esto es un caracter: %c\n", 'W');
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un caracter: %c\n", 'W');
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un string: %s\n", "Hola que tal?");
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un string: %s\n", "Hola que tal?");
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un string NULL: %s\n", (char *)NULL);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un string NULL: %s\n", (char *)NULL);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un entero negativo: %d\n", -42);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un entero negativo: %d\n", -42);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un unsigned int: %u\n", 42);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un unsigned int: %u\n", 42);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un hex en minusculas: %x\n", 255);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un hex en minusculas: %x\n", 255);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un hex 0 en minusculas: %x\n", 0);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un hex 0 en minusculas: %x\n", 0);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un hex en mayusculas: %X\n", 255);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un hex en mayusculas: %X\n", 255);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un hex 0 en mayusculas: %X\n", 0);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un hex 0 en mayusculas: %X\n", 0);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	int	n = 42;
	fake_print_return = ft_printf("Esto es un puntero: %p\n", &n);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un puntero: %p\n", &n);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un porcentaje: %%\n");
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un porcentaje: %%\n");
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un vacío: %p\n", NULL);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un vacío: %p\n", NULL);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	
	return (0);
}*/