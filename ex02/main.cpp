/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:48:41 by fzayani           #+#    #+#             */
/*   Updated: 2025/04/10 14:53:58 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <cstdlib>
#include <limits>

bool isPositiveInteger(const std::string& str) {
	if (str.empty())
		return false;

	for (size_t i = 0; i < str.length(); ++i) {
		if (!std::isdigit(str[i]))
			return false;
		}
	return true;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " [positive integers...]" << std::endl;
		return 1;
	}

	std::vector<int> numbers;

	// Parse command line arguments
	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];

		if (!isPositiveInteger(arg)) {
			std::cerr << "Error" << std::endl;
			return 1;
		}

		int num;
		std::istringstream iss(arg);
		iss >> num;

		// Check for overflow
		if (iss.fail() || num < 0) {
			std::cerr << "Error" << std::endl;
			return 1;
		}

		numbers.push_back(num);
	}

	// Display the sequence before sorting
	std::cout << "Before: ";
	for (size_t i = 0; i < numbers.size(); ++i) {
		std::cout << numbers[i] << " ";
	}
	std::cout << std::endl;

	// Create containers for sorting
	std::deque<int> deque_nums(numbers.begin(), numbers.end());
	std::vector<int> vector_nums = numbers;

	// Create and use PmergeMe sorter
	PmergeMe<int> sorter;

	// Sort using deque
	sorter.sortDeque(deque_nums);

	// Sort using vector
	sorter.sortVector(vector_nums);

	// Display the sorted sequence
	std::cout << "After: ";
	const std::deque<int>& sorted_deque = sorter.getSortedDeque();
	for (size_t i = 0; i < sorted_deque.size(); ++i) {
		std::cout << sorted_deque[i] << " ";
	}
	std::cout << std::endl;

	// Verify that both containers give the same result
	bool same_result = (sorter.getSortedDeque().size() == sorter.getSortedVector().size());

	if (same_result) {
		for (size_t i = 0; i < sorter.getSortedDeque().size(); ++i) {
			if (sorter.getSortedDeque()[i] != sorter.getSortedVector()[i]) {
				same_result = false;
				break;
			}
		}
	}

	if (!same_result) {
		std::cerr << "Warning: Different results between containers!" << std::endl;
	}

	return 0;
}