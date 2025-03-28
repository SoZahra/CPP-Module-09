/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:56:10 by fzayani           #+#    #+#             */
/*   Updated: 2025/03/28 14:24:09 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXHANGE_HPP
#define BITCOINEXHANGE_HPP

#include <string>
#include <map>

//struct data
struct Date
{
	int year;
	int month;
	int day;

	Date(int y = 0, int m = 0, int d = 0); //constructeur
	bool operator<(const Date& other) const; //operateur de comparaison pour utiliser Date comme cle
};

class BitcoinExchange {
	private :
		std::map<Date, float> exchangeRates;

	public :
		BitcoinExchange();
		~BitcoinExchange();

		bool loadExchangeRates(const std::string& filename); // charger le fichier de taux de change
		void processInputFile(const std::string& filename); // traiter le fichier d'entree
		float getExchangeRate(const Date& date) const; //get le tux de change a une date precise
};

bool isLeapYear(int year);
bool isValidDate(const Date& date);
bool parseDate(const std::string& dateStr, Date& date);
std::string trim(const std::string& str);

#endif