/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:00:00 by miaviles          #+#    #+#             */
/*   Updated: 2026/03/10 10:00:00 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <ctime>
#include <iostream>

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    std::cerr << "Error" << std::endl;
    return (1);
  }
  try
  {
    PmergeMe pm;
    pm.fillContainers(argc, argv);

    pm.printBefore();

    // Time each container. clock() measures CPU time; the measured region
    // includes the internal copy (data management) plus the sort itself.
    clock_t startVec = clock();
    pm.sortVector();
    clock_t endVec = clock();

    clock_t startDeq = clock();
    pm.sortDeque();
    clock_t endDeq = clock();

    pm.printAfter();

    double timeVec = 1000000.0 * (endVec - startVec) / CLOCKS_PER_SEC;
    double timeDeq = 1000000.0 * (endDeq - startDeq) / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << (argc - 1)
              << " elements with std::vector : " << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << (argc - 1)
              << " elements with std::deque : " << timeDeq << " us" << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return (1);
  }
  return (0);
}
