/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:00:00 by miaviles          #+#    #+#             */
/*   Updated: 2026/03/10 10:00:00 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>

/*
 * PmergeMe: merge-insertion sort (Ford-Johnson family) implemented on two
 * different containers, std::vector and std::deque.
 *
 * Idea for each container:
 *   1. Pair up elements; keep the bigger one in the "main chain" and the
 *      smaller one in "pendings".
 *   2. Sort the main chain recursively (same algorithm).
 *   3. Binary-insert every pending element (std::lower_bound) into the
 *      already sorted main chain.
 *
 * std::map (ex00) and std::stack (ex01) are forbidden here, so we only use
 * std::vector and std::deque.
 */
class PmergeMe
{
  public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void fillContainers(int argc, char **argv);
    void sortVector();
    void sortDeque();
    void printBefore() const;
    void printAfter() const;

  private:
    std::vector<int> _vector;
    std::deque<int> _deque;
    std::vector<int> _sortedVector;
    std::deque<int> _sortedDeque;
};

#endif
