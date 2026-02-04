/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:36:03 by miaviles          #+#    #+#             */
/*   Updated: 2026/01/29 19:21:03 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main()
{
    std::cout << "---- Valid Constructors ----" << std::endl;
    try {
        Bureaucrat a("Alice", 1);
        Bureaucrat b("Bob", 150);

        std::cout << a << std::endl;
        std::cout << b << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << "Error in valid constructor: " << e.what() << std::endl;
    }

    std::cout << "\n---- Invalid Constructor ----" << std::endl;
    try {
        Bureaucrat c("Charles", 200);
    }
    catch (std::exception &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n---- Increments and Decrements ----" << std::endl;
    try {
        Bureaucrat d("Diana", 2);
        std::cout << d << std::endl;

        d.increment();
        std::cout << d << std::endl;

        d.increment();
        std::cout << d << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << "Error incrementing: " << e.what() << std::endl;
    }

    std::cout << "\n---- Decrement to Limit ----" << std::endl;
    try {
        Bureaucrat e("Edward", 149);
        std::cout << e << std::endl;

        e.decrement();
        std::cout << e << std::endl;

        e.decrement();
    }
    catch (std::exception &e) {
        std::cerr << "Error decrementing: " << e.what() << std::endl;
    }

    return (0);
}
