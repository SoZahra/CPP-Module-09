/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:48:12 by fzayani           #+#    #+#             */
/*   Updated: 2025/04/08 17:52:17 by fzayani          ###   ########.fr       */
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

	bool has_stray = (elements.size() % 2 != 0) //verifier si le nb d'elements est pair ou impair

	auto end = has_stray ? elements.end() - 1 : elements.end(); //creer des pairs
	for (auto it = elements.begin(); it != end; it += 2){
		pairs.push_back(std::make_pair(*it, *(it + 1)));
		if(pairs.back().second > pairs.back().first){
			std::swap(pairs.back().first, pairs.back().second);
		} // Ce bloc vérifie si le deuxième élément de la paire est plus grand que le premier.
		// Si c'est le cas, il les échange pour que l'élément
		// le plus grand soit en première position dans la paire.
	}

	return pairs;
}

template<typename T>
void PmergeMe<T>::mergeInsertSort(std::deque<T>& elements){

	if(elements.size() <= 1){
		return; //si vide ou qu'un seul element
	}

	// 1. Former des paires
	bool has_stray = (elements.size() % 2 != 0);
	T stray_element;

	// si nb impair d'elements sauvegarde l'element non apparie
	if(has_stray){
		stray_element = elements.back();
		elements.pop_back();
	}

	//utiliser la fonction makePairs que nous avons deja implementee
	std::deque<std::pair<T, T>> pairs = makePairs(elements);
	// 2. Trier chaque paire
	// 3. Tri récursif des éléments plus grands
	std::deque<T> larger_elements;
	std::deque<T> smaller_elements;

	//Pour chaque paire, ajouter le plus grand element a large_elements
	// et le plus petit a l'autre
	for (const auto& pair : pairs){
		larger_elements.push_back(pair.first);
		smaller_elements.push_back(pair.second);
	}
	//tri recursif des elements les plus grands
	mergeInsertSort(larger_elements);
	// 4. Construction de la séquence principale
	//creer une nouvelle sequence principale
	std::deque<T> result = larger_elements;

	// 5. Insertion des éléments restants selon la séquence de Jacobsthal
}

template<typename T>
std::deque<size_t> PmergeMe<T>::calcultateJacobsthatlNumbers(size_t n){
	std::deque<size_t> jacobsthal;
	jacobsthal.push_back(0);
	if(n == 0) return jacobsthal;
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

