/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:42:27 by miaviles          #+#    #+#             */
/*   Updated: 2025/09/18 17:47:20 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void) : _rawBits(0) {}

Fixed::~Fixed() {}

Fixed::Fixed(const Fixed& other)
{
	*this = other;
}

Fixed& Fixed::operator=(const Fixed& other)
{
	if (this != &other)
	{
		this->_rawBits = other.getRawBits();
	}
	return (*this);
}

int	Fixed::getRawBits(void) const
{
	return (this->_rawBits);
}

void	Fixed::setRawBits(int const raw)
{
	this->_rawBits = raw;
}

Fixed::Fixed(int value)
{
	_rawBits = value * (1 << _fractionalBits);
}

int Fixed::toInt(void) const
{
	return _rawBits / (1 << _fractionalBits);
}

Fixed::Fixed(float value)
{
	_rawBits = static_cast<int>(roundf(value * (1 << _fractionalBits)));
}

float Fixed::toFloat(void) const
{
    return (static_cast<float>(_rawBits) / static_cast<float>(1 << _fractionalBits));
}

std::ostream& operator<<(std::ostream& os, const Fixed& fx)
{
    os << fx.toFloat();
    return os;
}

bool Fixed::operator<(const Fixed& other) const
{
	return (this->_rawBits < other._rawBits);
}

bool Fixed::operator>(const Fixed& other) const
{
	return (this->_rawBits > other._rawBits);
}

bool Fixed::operator<=(const Fixed& other) const
{
	return (this->_rawBits <= other._rawBits);
}

bool Fixed::operator>=(const Fixed& other) const
{
	return (this->_rawBits >= other._rawBits);
}

bool Fixed::operator==(const Fixed& other) const
{
	return (this->_rawBits == other._rawBits);
}

bool Fixed::operator!=(const Fixed& other) const
{
	return (this->_rawBits != other._rawBits);
}

Fixed Fixed::operator+(const Fixed& other) const
{
	return (Fixed(this->toFloat() + other.toFloat()));
}

Fixed Fixed::operator-(const Fixed& other) const
{
	return (Fixed(this->toFloat() - other.toFloat()));
}

Fixed Fixed::operator*(const Fixed& other) const
{
	return (Fixed(this->toFloat() * other.toFloat()));
}

Fixed Fixed::operator/(const Fixed& other) const
{
	if (other.toFloat() == 0)
	{
		return (Fixed(0));
	}
	return (Fixed(this->toFloat() / other.toFloat()));
}

Fixed& Fixed::operator++()
{
	this->_rawBits += (1 << _fractionalBits);
	return *this;
}

Fixed& Fixed::operator--()
{
	this->_rawBits -= (1 << _fractionalBits);
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed temp(*this);
	this->_rawBits += (1 << _fractionalBits);
	return temp;
}

Fixed Fixed::operator--(int)
{
	Fixed temp(*this);
	this->_rawBits -= (1 << _fractionalBits);
	return temp;
}

Fixed& Fixed::min(Fixed& a, Fixed& b)
{
	return (a < b ? a : b);
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
	return (a < b ? a : b);
}

Fixed& Fixed::max(Fixed& a, Fixed& b)
{
	return (a > b ? a : b);
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
	return (a > b ? a : b);
}
