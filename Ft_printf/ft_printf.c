/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:28:01 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/30 20:00:37 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
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
		len += print_pointer(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		len += print_number(va_arg(args, int), 0);
	else if (format == 'u')
		len += print_number(va_arg(args, int), 1);
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
		if (str[i] == '%')
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

/*int main()
{
	int print_return;
	
	print_return = ft_printf("Esto es un caracter: %c\n", 'W');
	ft_printf("El retorno de ft_printf es: %d\n", print_return);

	print_return = ft_printf("Esto es un string: %s\n", "Hola que tal?");
	ft_printf("El retorno de ft_printf es: %d\n", print_return);

	print_return = ft_printf("Esto es un string NULL: %s\n", (char *)NULL);
	ft_printf("El retorno de ft_printf es: %d\n", print_return);

	print_return = ft_printf("Esto es un entero negativo: %d\n", -42);
	ft_printf("El retorno de ft_printf es: %d\n", print_return);

	print_return = ft_printf("Esto es un unsigned int: %u\n", 42);
	ft_printf("El retorno de ft_printf es: %d\n", print_return);

	print_return = ft_printf("Esto es un hexadecimal en minusculas: %x\n", 255);
	ft_printf("El retorno de ft_printf es: %d\n", print_return);

	print_return = ft_printf("Esto es un hexadecimal en mayusculas: %X\n", 255);
	ft_printf("El retorno de ft_printf es: %d\n", print_return);

	int	n = 42;
	print_return = ft_printf("Esto es un puntero: %p\n", &n);
	ft_printf("El retorno de ft_printf es: %d\n", print_return);

	print_return = ft_printf("Esto es un porcentaje: %%\n");
	ft_printf("El retorno de ft_printf es: %d\n", print_return);

	return (0);
}*/
