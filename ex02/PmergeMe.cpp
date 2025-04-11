/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:48:12 by fzayani           #+#    #+#             */
/*   Updated: 2025/04/11 15:21:40 by fzayani          ###   ########.fr       */
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
	if(this != &other){
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
				<< " elements with std::deque  :" << time_taken << " us."<< std::endl;

}

template<typename T>
void PmergeMe<T>::sortVector(const std::vector<T>& input){
	_vector = input;
	clock_t start = clock(); //prendre le temps au debut

	mergeInsertSort_(_vector);
	clock_t end = clock();

	double time_taken = double(end - start) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process a range of " << _vector.size()
				<< " elements with std::vector :" << time_taken << " us."<< std::endl;
}

template<typename T>
std::deque<std::pair<T, T> > PmergeMe<T>::makePairs(const std::deque<T>& elements) {
	std::deque<std::pair<T, T> > pairs;
	std::deque<T>elementsCopy = elements;

	bool has_stray = (elementsCopy.size() % 2 != 0);
	typename std::deque<T>::iterator end = has_stray ? elementsCopy.end() - 1 : elementsCopy.end();

	for (typename std::deque<T>::iterator it = elementsCopy.begin(); it != end; it += 2) {
		pairs.push_back(std::make_pair(*it, *(it + 1)));
		if (pairs.back().first > pairs.back().second) {
			std::swap(pairs.back().first, pairs.back().second);
		}
		// Le plus petit élément va en premier position
	}

	return pairs;
}

template<typename T>
std::vector<std::pair<T, T> > PmergeMe<T>::makePairs_(const std::vector<T>& elements){
	std::vector<std::pair<T, T> > pairs;
	std::vector<T> elementsCopy = elements;

	bool has_stray = (elementsCopy.size() % 2 != 0); //verifier si le nb d'elements est pair ou impair

	// auto end = has_stray ? elements.end() - 1 : elements.end(); //creer des pairs
	// for (auto it = elements.begin(); it != end; it += 2)
	typename std::vector<T>::iterator end = has_stray ? elementsCopy.end() - 1 : elementsCopy.end();
	for (typename std::vector<T>::iterator it = elementsCopy.begin(); it != end; it += 2){
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
std::deque<size_t> PmergeMe<T>::calcultateJacobsthatlNumbers(size_t n){
	std::deque<size_t> jacobsthal;
	jacobsthal.push_back(0);
	if(n == 0) return jacobsthal;

	jacobsthal.push_back(1);
	if(n == 1) return jacobsthal;

	for (size_t i = 2; i <= n; ++i){
		jacobsthal.push_back(jacobsthal[i-1] + 2 * jacobsthal[i-2]);
	}
	return jacobsthal;
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
	std::deque<std::pair<T, T> > pairs = makePairs(elements);

	// Debug: Afficher les paires
	// std::cout << "Pairs: ";
	// for (typename std::deque<std::pair<T, T> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it) {
	// 	std::cout << "(" << it->first << "," << it->second << ") ";
	// }
	// std::cout << std::endl;

	// 2. Trier chaque paire
	std::deque<T> larger_elements;
	std::deque<T> smaller_elements;

	//Pour chaque paire, ajouter le plus grand element a large_elements
	// et le plus petit a l'autre
	for (typename std::deque<std::pair<T, T> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it){
		const std::pair<T, T>& pair = *it;
		larger_elements.push_back(pair.first);
		smaller_elements.push_back(pair.second);
	}

	 // Debug: Afficher les éléments
	// std::cout << "Larger elements: ";
	// for (typename std::deque<T>::const_iterator it = larger_elements.begin(); it != larger_elements.end(); ++it) {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;

	// std::cout << "Smaller elements: ";
	// for (typename std::deque<T>::const_iterator it = smaller_elements.begin(); it != smaller_elements.end(); ++it) {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;

	// 3. Tri récursif des éléments plus grands
	//tri recursif des elements les plus grands
	mergeInsertSort(larger_elements);

	//creer une nouvelle sequence principale
	// Debug: Afficher les éléments après tri
    // std::cout << "Larger elements after sorting: ";
    // for (typename std::deque<T>::const_iterator it = larger_elements.begin(); it != larger_elements.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;
	// 4. Construction de la séquence principale
	std::deque<T> result = larger_elements;

	// 5. Insertion des éléments restants selon la séquence de Jacobsthal
	if (!smaller_elements.empty()) {
		// Insérer le premier élément plus petit à sa position correcte
		typename std::deque<T>::iterator pos_it = std::lower_bound(result.begin(), result.end(), smaller_elements[0]);
		result.insert(pos_it, smaller_elements[0]);

		// Debug: Afficher après insertion du premier élément
		// std::cout << "After inserting first element: ";
		// for (typename std::deque<T>::const_iterator it = result.begin(); it != result.end(); ++it) {
		// 	std::cout << *it << " ";
		// }
		// std::cout << std::endl;

		// Calculer les nombres de Jacobsthal nécessaires
		size_t n = smaller_elements.size();
		std::deque<size_t> jacobsthalSequence = calcultateJacobsthatlNumbers(n);

		// Générer l'ordre d'insertion basé sur les nombres de Jacobsthal
		std::deque<size_t> insertionOrder;
		for (size_t i = 2; i < jacobsthalSequence.size() && insertionOrder.size() < n - 1; ++i) {
			size_t current = jacobsthalSequence[i];
			size_t previous = jacobsthalSequence[i-1];

			// Ajouter tous les indices entre previous et current en ordre inverse
			for (size_t j = current; j > previous && j <= n; --j) {
				if (j <= n) {
					insertionOrder.push_back(j);
				}
			}
		}

		// Dans la boucle d'insertion, après chaque insertion

		// Ajouter les indices restants
		for (size_t i = 1; i <= n; ++i) {
			if (std::find(insertionOrder.begin(), insertionOrder.end(), i) == insertionOrder.end()) {
				insertionOrder.push_back(i);
			}
		}

		// Insérer les éléments selon l'ordre calculé
		for (std::deque<size_t>::const_iterator it = insertionOrder.begin(); it != insertionOrder.end(); ++it) {
			size_t idx = *it;
			if (idx < smaller_elements.size() && idx > 0) {
				typename std::deque<T>::iterator pos_it = std::lower_bound(result.begin(), result.end(), smaller_elements[idx]);
				// size_t pos = std::distance(result.begin(), pos_it);

				// Debug: Afficher avant insertion
				// std::cout << "About to insert " << smaller_elements[idx] << " at position " << pos << ": ";
				// for (typename std::deque<T>::const_iterator debug_it = result.begin(); debug_it != result.end(); ++debug_it) {
				// 	std::cout << *debug_it << " ";
				// }
				// std::cout << std::endl;

				// Faire l'insertion
				result.insert(pos_it, smaller_elements[idx]);

				// Debug: Afficher après insertion
				// std::cout << "After inserting " << smaller_elements[idx] << " at position " << pos << ": ";
				// for (typename std::deque<T>::const_iterator debug_it = result.begin(); debug_it != result.end(); ++debug_it) {
				// 	std::cout << *debug_it << " ";
				// }
				// std::cout << std::endl;
			}
		}

		// Si un élément non apparié existe, l'insérer également
		if (has_stray) {
			typename std::deque<T>::iterator pos_it = std::lower_bound(result.begin(), result.end(), stray_element);
			// size_t pos = std::distance(result.begin(), pos_it);

			// // Debug
			// std::cout << "About to insert stray element " << stray_element << " at position " << pos << ": ";
			// for (typename std::deque<T>::const_iterator it = result.begin(); it != result.end(); ++it) {
			// 	std::cout << *it << " ";
			// }
			// std::cout << std::endl;

			result.insert(pos_it, stray_element);

			// Debug
			// std::cout << "After inserting stray element: ";
			// for (typename std::deque<T>::const_iterator it = result.begin(); it != result.end(); ++it) {
			// 	std::cout << *it << " ";
			// }
			// std::cout << std::endl;
		}
	}

	// Mettre à jour le conteneur d'origine
	elements = result;
}

template<typename T>
void PmergeMe<T>::mergeInsertSort_(std::vector<T>& elements) {
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
	std::vector<std::pair<T, T> > pairs = makePairs_(elements);
	std::vector<T> larger_elements;
	std::vector<T> smaller_elements;

	//Pour chaque paire, ajouter le plus grand element a large_elements
	// et le plus petit a l'autre
	// for (const auto& pair : pairs)
	for (typename std::vector<std::pair<T, T> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it){
		const std::pair<T, T>&pair = *it;
		larger_elements.push_back(pair.first);
		smaller_elements.push_back(pair.second);
	}
	//tri recursif des elements les plus grands
	mergeInsertSort_(larger_elements);
	// 4. Construction de la séquence principale
	//creer une nouvelle sequence principale
	std::vector<T> result = larger_elements;

	// 5. Insertion des éléments restants selon la séquence de Jacobsthal
	if (!smaller_elements.empty()) {
		// Insérer le premier élément plus petit au début
		// result.insert(result.begin(), smaller_elements[0]);
		typename std::vector<T>::iterator pos_it = std::lower_bound(result.begin(), result.end(), smaller_elements[0]);
		result.insert(pos_it, smaller_elements[0]);

		// Calculer les nombres de Jacobsthal nécessaires
		size_t n = smaller_elements.size();
		std::deque<size_t> jacobsthalSequence = calcultateJacobsthatlNumbers(n);

		// Générer l'ordre d'insertion basé sur les nombres de Jacobsthal
		std::vector<size_t> insertionOrder;
		for (size_t i = 2; i < jacobsthalSequence.size() && insertionOrder.size() < n - 1; ++i) {
			size_t current = jacobsthalSequence[i];
			size_t previous = jacobsthalSequence[i-1];

			// Ajouter tous les indices entre previous et current en ordre inverse
			for (size_t j = current; j > previous && j <= n; --j) {
				if (j <= n) {
					insertionOrder.push_back(j);
				}
			}
		}

		// Ajouter les indices restants
		for (size_t i = 1; i <= n; ++i) {
			if (std::find(insertionOrder.begin(), insertionOrder.end(), i) == insertionOrder.end()) {
				insertionOrder.push_back(i);
			}
		}

		// Insérer les éléments selon l'ordre calculé
		// for (size_t idx : insertionOrder)
		for (std::vector<size_t>::const_iterator it = insertionOrder.begin(); it != insertionOrder.end(); ++it) {
			size_t idx = *it;
			if (idx < smaller_elements.size() && idx > 0) {
				typename std::vector<T>::iterator pos_it = std::lower_bound(result.begin(), result.end(), smaller_elements[idx]);
				// size_t pos = std::distance(result.begin(), pos_it);

				// Debug: Afficher avant insertion
				// std::cout << "About to insert " << smaller_elements[idx] << " at position " << pos << ": ";
				// for (typename std::vector<T>::const_iterator debug_it = result.begin(); debug_it != result.end(); ++debug_it) {
				// 	std::cout << *debug_it << " ";
				// }
				// std::cout << std::endl;

				// Faire l'insertion
				result.insert(pos_it, smaller_elements[idx]);

				// Debug: Afficher après insertion
				// std::cout << "After inserting " << smaller_elements[idx] << " at position " << pos << ": ";
				// for (typename std::vector<T>::const_iterator debug_it = result.begin(); debug_it != result.end(); ++debug_it) {
				// 	std::cout << *debug_it << " ";
				// }
				// std::cout << std::endl;
			}
		}
		// Si un élément non apparié existe, l'insérer également
		if (has_stray) {
			typename std::vector<T>::iterator pos_it = std::lower_bound(result.begin(), result.end(), stray_element);
			// size_t pos = std::distance(result.begin(), pos_it);
			// std::cout << "About to insert stray element " << stray_element << " at position " << pos << ": ";
			result.insert(pos_it, stray_element);
		}
	}// Mettre à jour le conteneur d'origine
	elements = result;
}

template<typename T>
void PmergeMe<T>::displaySorted() const{
	std::cout << "Deque: ";
	// for (const auto& elem : _deque)
	for (typename std::deque<T>::const_iterator it = _deque.begin(); it != _deque.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	std::cout << "Vector: ";
	// for (const auto& elem : _vector){
	// 	std::cout << elem << " ";
	for (typename std::vector<T>::const_iterator it = _vector.begin(); it != _vector.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
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

