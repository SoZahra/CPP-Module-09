/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:48:12 by fzayani           #+#    #+#             */
/*   Updated: 2025/04/02 18:25:35 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template<typename T>
PmergeMe<T>::PmergeMe(){
}

template<typename T>
PmergeMe<T>::~PmergeMe(){
}

template<typename T>
PmergeMe<T>::PmergeMe(const PmergeMe& other) : _deque(other._deque), _vector(other._vector)
{}

template<typename T>
PmergeMe<T>& PmergeMe<T>::operator=(const PmergeMe& other){
	if(this != other){
		_deque = other._deque;
		_vector = other._vector;
	}
	return *this;
}

template<typename T>
void PmergeMe<T>::sortDeque(const std::deque<T>& input){
	_deque = input;
	clock_t start = clock(); //prendre le temps au debut

	mergeInsertSort(_deque);
	clock_t end = clock();

	double time_taken = double(end - start) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process a range of " << _deque.size()
				<< " elements with std::deque :" << time_taken << " us."<< std::endl;

}


template<typename T>
void PmergeMe<T>::sortVector(const std::vector<T>& input){
	_vector = input;
	clock_t start = clock(); //prendre le temps au debut

	mergeInsertSort(_vector);
	clock_t end = clock();

	double time_taken = double(end - start) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process a range of " << _vector.size()
				<< " elements with std::vector :" << time_taken << " us."<< std::endl;
}

template<typename T>
std::deque<std::pair<T, T>> PmergeMe<T>::makePairs(const std::deque<T>& elements){
	std::deque<std::pair<T, T>> pairs;

	return pairs;
}

template<typename T>
void PmergeMe<T>::mergeInsertSort(std::deque<T>& elements){

	if(elements.size() <= 1){
		return; //si vide ou qu'un seul element
	}

	// 1. Former des paires
	// 2. Trier chaque paire
	// 3. Tri récursif des éléments plus grands
	// 4. Construction de la séquence principale
	// 5. Insertion des éléments restants selon la séquence de Jacobsthal
}

template<typename T>
void PmergeMe<T>::displaySorted() const{
	// return std::sort <<
}

template<typename T>
const std::deque<T>& PmergeMe<T>::getSortedDeque() const{
	return _deque;
}

template<typename T>
const std::vector<T>& PmergeMe<T>::getSortedVector() const{
	return _vector;
}

// Instanciation explicite pour les types courants
template class PmergeMe<int>;
template class PmergeMe<double>;

