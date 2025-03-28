/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:56:12 by fzayani           #+#    #+#             */
/*   Updated: 2025/03/28 18:12:07 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>


Date::Date(int y, int m, int d): year(y), month(m), day(d) {}

bool Date::operator<(const Date& other) const{
	if(year != other.year){
		return year < other.year;
	}
	if(month != other.month){
		return month < other.month;
	}
	return day < other.day;
}

bool isLeapYear(int year){
	return (year % 4 == 0 && year % 100 != 0 ) || (year % 400 == 0);
}

bool isValidDate(const Date& date){
	if(date.year < 0 || date.month < 1 || date.month > 12 || date.day < 1)
		return false;

	int daysInMonth;
	switch(date.month){
		case 2 : //pour fevrier
			daysInMonth = isLeapYear(date.year) ? 29 : 28;
			break;
		case 4: case 6: case 9: case 11: //Avril, Juin, Septembre, Novembre
			daysInMonth = 30;
			break;
		default: //janvier, Mars, Mai, Juillet, Août, Octobre, Décembre
			daysInMonth =  31;
			break;
	}
	return date.day <= daysInMonth;
}

bool parseDate(const std::string& dateStr, Date& date){
	std::istringstream iss(dateStr);
	char dash1, dash2;

	if(!(iss >> date.year >> dash1 >> date.month >> dash2 >>date.day)||
		(dash1 != '-' || dash2 != '-')){
		return false;
	}
	return isValidDate(date);
}

std::string trim(const std::string& str){
	size_t first = str.find_first_not_of(" \t");
	if(first == std::string::npos)
		return "";
	size_t last = str.find_last_not_of(" \t");
	return str.substr(first, last - first + 1);
}

BitcoinExchange::BitcoinExchange(){
}

BitcoinExchange::~BitcoinExchange(){
}

bool BitcoinExchange::loadExchangeRates(const std::string& filename){
	std::ifstream file(filename.c_str());
	if(!file.is_open()){
		std::cerr << "Error: could not open file." << std::endl;
		return false;
	}
	std::string line;
	std::getline(file, line); //skipe header line

	while(std::getline(file, line)){
		std::istringstream iss(line);
		std::string dateStr;
		float rate;

		if(std::getline(iss, dateStr, ',') && (iss >> rate)){
			Date date;
			if(parseDate(dateStr, date)){
				exchangeRates[date] = rate;
			}
		}
	}
	file.close();
	return true;
}

float BitcoinExchange::getExchangeRate(const Date& date) const{
	std::map<Date, float>::const_iterator it = exchangeRates.upper_bound(date);

	//si map vide ou date avant l'entree
	if(it == exchangeRates.begin() && (date < it->first || exchangeRates.empty()) ){
		return -1;
	}
	//si la date est apres la dernier entree ou date sup
	if(it == exchangeRates.end() || (date < it->first)){
		--it; //prendre celui d'avant
	}
	return it->second;
}

void BitcoinExchange::processInputFile(const std::string& filename){
	std::ifstream file(filename.c_str());
	if(!file.is_open()){
		std::cerr << "Error: could not open file" << std::endl;
		return;
	}
	std::string line;
	std::getline(file, line);

	while(std::getline(file, line)){
		std::istringstream iss(line);
		std::string dateStr;
		std::string valueStr;

		if(std::getline(iss, dateStr, '|') && (iss >> valueStr)){
			dateStr = trim(dateStr);
			valueStr = trim(valueStr);

			Date date;
			if(!parseDate(dateStr, date)){
				std::cout << "Error: bad input." << std::endl;
				continue;
			}
			float value;
			try{
				std::istringstream iss(valueStr);
				if(!(iss >> value) || iss.peek() != EOF){
					std::cout << "Error: invalid value => " << valueStr << std::endl;
					continue;
				}
				if(value < 0){
					std::cout << "Error: not a positive number." << std::endl;
					continue;
				}
				if (value > 1000) {
					std::cout << "Error: too large a number." << std::endl;
					continue;
				}
			}catch(const std::exception& e){
				std::cout << "Error: invalid input" << valueStr << std::endl;
				continue;
			}

			float rate = getExchangeRate(date);
			if(rate < 0){
				std::cout << "Error: no exchange rate available for date" << dateStr << std::endl;
				continue;
			}
			float result = value * rate;
			std::cout << dateStr << " => " << value << " = " << result << std::endl;
		}else{
			std::cout << "Error: bad input => " << line <<  std::endl;
		}
	}
	file.close();
}
