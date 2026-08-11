/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:00:00 by miaviles          #+#    #+#             */
/*   Updated: 2026/03/10 10:00:00 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <stdexcept>
#include <cstdlib>   // std::strtol
#include <cctype>    // std::isdigit
#include <climits>   // INT_MAX
#include <cerrno>    // errno
#include <algorithm> // std::lower_bound (allowed in module 09)

/* ------------------------- Orthodox Canonical Form ------------------------ */

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe& other) : _vector(other._vector), _deque(other._deque),
  _sortedVector(other._sortedVector), _sortedDeque(other._sortedDeque)
{
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
  if (this != &other)
  {
    _vector = other._vector;
    _deque = other._deque;
    _sortedVector = other._sortedVector;
    _sortedDeque = other._sortedDeque;
  }
  return *this;
}

PmergeMe::~PmergeMe()
{
}

/* ------------------------- Argument parsing ------------------------------- */

// Validate argv and fill both containers with the parsed positive integers.
void PmergeMe::fillContainers(int argc, char **argv)
{
  for (int i = 1; i < argc; ++i)
  {
    std::string arg(argv[i]);

    // Reject empty tokens first.
    if (arg.empty())
      throw std::runtime_error("Error");

    // Only plain digits are accepted; this also rejects negatives ('-' is not
    // a digit). The cast to unsigned char avoids undefined behaviour when a
    // char has a value outside the unsigned char range.
    for (size_t j = 0; j < arg.size(); ++j)
    {
      if (!std::isdigit(static_cast<unsigned char>(arg[j])))
        throw std::runtime_error("Error");
    }

    // Convert safely: check errno for overflow and make sure it fits in int.
    errno = 0;
    char *end = 0;
    long num = std::strtol(arg.c_str(), &end, 10);
    if (*end != '\0' || errno != 0 || num <= 0 || num > INT_MAX)
      throw std::runtime_error("Error");

    _vector.push_back(static_cast<int>(num));
    _deque.push_back(static_cast<int>(num));
  }
}

/* -------------------------- Jacobsthal helper ----------------------------- */

/*
 * Build the order in which the "pending" elements must be inserted, following
 * the Jacobsthal numbers (1, 3, 5, 11, 21, ...). This particular order is what
 * turns a plain binary-insertion into the Ford-Johnson (merge-insertion) sort:
 * it groups the insertions so the number of comparisons stays minimal.
 *
 * For n pendings it returns 0-based indices, e.g. for n = 5 -> [0, 2, 1, 4, 3]
 * meaning: insert b1, then b3, b2, then b5, b4 (descending inside each group).
 *
 * Note: an optimal implementation also bounds each binary search by the
 * position of the element's partner in the chain. Here the search is done over
 * the whole chain for clarity; the result is identical, only a few extra
 * comparisons are performed.
 */
static std::vector<size_t> buildJacobsthalOrder(size_t n)
{
  std::vector<size_t> order;
  if (n == 0)
    return order;

  order.push_back(0);   // b1 is always inserted first
  size_t prev = 1;      // indices up to 'prev' (1-based) are already scheduled
  size_t jacob = 3;     // next Jacobsthal number
  while (prev < n)
  {
    size_t hi = (jacob < n) ? jacob : n;      // never go past the last index
    for (size_t idx = hi; idx > prev; --idx)  // descending inside the group
      order.push_back(idx - 1);               // 1-based -> 0-based
    size_t next = jacob + 2 * prev;           // J(k+1) = J(k) + 2 * J(k-1)
    prev = jacob;
    jacob = next;
  }
  return order;
}

/* -------------------------- std::vector version --------------------------- */

static void mergeInsertSortVector(std::vector<int>& vec, size_t left, size_t right)
{
  if (right - left <= 1)
    return;

  // Split into pairs: bigger -> mainChain, smaller -> pendings.
  std::vector<int> mainChain;
  std::vector<int> pendings;
  size_t i = left;
  for (; i + 1 < right; i += 2)
  {
    if (vec[i] < vec[i + 1])
    {
      mainChain.push_back(vec[i + 1]);
      pendings.push_back(vec[i]);
    }
    else
    {
      mainChain.push_back(vec[i]);
      pendings.push_back(vec[i + 1]);
    }
  }
  if (i < right) // odd element (straggler) has no partner
    mainChain.push_back(vec[i]);

  // Recursively sort the bigger elements: this is the "main chain".
  mergeInsertSortVector(mainChain, 0, mainChain.size());

  // Insert the pendings into the sorted main chain, following the Jacobsthal
  // order (binary insertion via std::lower_bound keeps the chain sorted).
  std::vector<size_t> order = buildJacobsthalOrder(pendings.size());
  for (size_t o = 0; o < order.size(); ++o)
  {
    int value = pendings[order[o]];
    std::vector<int>::iterator pos =
      std::lower_bound(mainChain.begin(), mainChain.end(), value);
    mainChain.insert(pos, value);
  }

  // Write the sorted block back into the original container.
  for (size_t j = 0; j < mainChain.size(); ++j)
    vec[left + j] = mainChain[j];
}

void PmergeMe::sortVector()
{
  _sortedVector = _vector;
  mergeInsertSortVector(_sortedVector, 0, _sortedVector.size());
}

/* -------------------------- std::deque version ---------------------------- */

static void mergeInsertSortDeque(std::deque<int>& deq, size_t left, size_t right)
{
  if (right - left <= 1)
    return;

  std::deque<int> mainChain;
  std::deque<int> pendings;
  size_t i = left;
  for (; i + 1 < right; i += 2)
  {
    if (deq[i] < deq[i + 1])
    {
      mainChain.push_back(deq[i + 1]);
      pendings.push_back(deq[i]);
    }
    else
    {
      mainChain.push_back(deq[i]);
      pendings.push_back(deq[i + 1]);
    }
  }
  if (i < right)
    mainChain.push_back(deq[i]);

  mergeInsertSortDeque(mainChain, 0, mainChain.size());

  // Same Jacobsthal-ordered binary insertion, but on a std::deque.
  std::vector<size_t> order = buildJacobsthalOrder(pendings.size());
  for (size_t o = 0; o < order.size(); ++o)
  {
    int value = pendings[order[o]];
    std::deque<int>::iterator pos =
      std::lower_bound(mainChain.begin(), mainChain.end(), value);
    mainChain.insert(pos, value);
  }

  for (size_t j = 0; j < mainChain.size(); ++j)
    deq[left + j] = mainChain[j];
}

void PmergeMe::sortDeque()
{
  _sortedDeque = _deque;
  mergeInsertSortDeque(_sortedDeque, 0, _sortedDeque.size());
}

/* -------------------------------- Output ---------------------------------- */

// Print the original (unsorted) sequence.
void PmergeMe::printBefore() const
{
  std::cout << "Before:";
  for (size_t i = 0; i < _vector.size(); ++i)
    std::cout << " " << _vector[i];
  std::cout << std::endl;
}

// Print the sorted sequence (taken from the vector result).
void PmergeMe::printAfter() const
{
  std::cout << "After:";
  for (size_t i = 0; i < _sortedVector.size(); ++i)
    std::cout << " " << _sortedVector[i];
  std::cout << std::endl;
}
