/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:28:59 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/30 19:34:36 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *str, ...);
int		print_format(va_list args, char format);
int		print_string(char *str);
int		print_char(char c);
int		print_number(int n, int unsign);
int		print_pointer(void *ptr);
int		print_hex(unsigned int n, int uppercase);
char	*ft_utoa_base(unsigned long long n, int base, int uppercase);

#endif