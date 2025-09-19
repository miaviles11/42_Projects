/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:42:31 by miaviles          #+#    #+#             */
/*   Updated: 2025/09/18 16:59:10 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
	private:
		int                 _rawBits;
		static const int    _fractionalBits = 8;

	public:
		Fixed(void);
		Fixed(const Fixed& other);
		Fixed& operator=(const Fixed& other);
		~Fixed();

		Fixed(const int value);
		Fixed(const float value);

		int     getRawBits(void) const;
		void    setRawBits(int const raw);
		float   toFloat(void) const;
		int     toInt(void) const;

		bool    operator>(const Fixed& other) const;
		bool    operator<(const Fixed& other) const;
		bool    operator>=(const Fixed& other) const;
		bool    operator<=(const Fixed& other) const;
		bool    operator==(const Fixed& other) const;
		bool    operator!=(const Fixed& other) const;

		Fixed   operator+(const Fixed& other) const;
		Fixed   operator-(const Fixed& other) const;
		Fixed   operator*(const Fixed& other) const;
		Fixed   operator/(const Fixed& other) const;

		Fixed&  operator++();
		Fixed&  operator--();
		Fixed   operator++(int);
		Fixed   operator--(int);

		static Fixed&       min(Fixed& a, Fixed& b);
		static const Fixed& min(const Fixed& a, const Fixed& b);
		static Fixed&       max(Fixed& a, Fixed& b);
		static const Fixed& max(const Fixed& a, const Fixed& b);
};

std::ostream& operator<<(std::ostream& os, const Fixed& fx);

#endif
