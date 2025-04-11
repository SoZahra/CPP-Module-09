/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:46:48 by fzayani           #+#    #+#             */
/*   Updated: 2025/04/10 14:56:11 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <algorithm>
#include <stdint.h>
#include <deque>
#include <vector>
#include <utility>

template<typename T>
class PmergeMe {

	private :
		std::deque<T> _deque; // premier conteneur
		std::vector<T> _vector; // second conteneur pour comparer les perf

	public :
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);

		//methodes
		void sortDeque(const std::deque<T>& input);
		void sortVector(const std::vector<T>& input);

		std::deque<std::pair<T, T> > makePairs(const std::deque<T>& elements);
		std::vector<std::pair<T, T> > makePairs_(const std::vector<T>& elements);
		void mergeInsertSort(std::deque<T>& elements);
		void mergeInsertSort_(std::vector<T>& elements);

		//afficher et acceder aux res

		void displaySorted() const;
		const std::deque<T>& getSortedDeque() const;
		const std::vector<T>& getSortedVector() const;

		std::deque<size_t> calcultateJacobsthatlNumbers(size_t n);
};

#endif