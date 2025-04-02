/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:12:59 by fzayani           #+#    #+#             */
/*   Updated: 2025/03/31 17:04:05 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cctype>
#include <sstream>
#include <cstdlib>

Rpn::Rpn(){
}

Rpn::~Rpn(){
}


Rpn::Rpn(const Rpn& other): number(other.number) {}

Rpn& Rpn::operator=(const Rpn& other){
	if(this != &other){
		number = other.number;
	}
	return *this;
}

bool Rpn::isOperateur(char c) const{
	return c == PLUS || c == MUL || c == MOINS || c == DIV;
}

void Rpn::performOperation(char op){
	if(number.size() < 2){
		throw std::runtime_error("Error: need more numbers.");
	}

	int b = number.top(); number.pop();
	int a = number.top(); number.pop();

	switch (static_cast<enum op>(op))
	{
		case PLUS:
			number.push(a + b);
			break;
		case MOINS:
			number.push(a - b);
			break;
		case MUL:
			number.push(a * b);
			break;
		case DIV:
			if(b == 0)
				throw std::runtime_error("Error: by 0 ?? ");
			number.push(a / b);
			break;
		default:
			throw std::runtime_error("Error: not find your operator");
	}
}

void Rpn::calculate(const std::string& expresion){
	std::istringstream iss(expresion);
	std::string token;

	while(iss >> token){
		if(token.size() == 1 && isOperateur(token[0]))
			performOperation(token[0]);
		else{
			try { //verif si c'est un nb
				int num = atoi(token.c_str());
				 // Vérifier si la conversion a réussi
				if (num == 0 && token != "0")
					throw std::runtime_error("Error: Token invalid");
				number.push(num);
			}catch (const std::exception& e){
				throw std::runtime_error("Error: invalid format");
			}
		}
	}
	if(number.size() != 1){
		throw std::runtime_error("Error: expresion invalid");
	}
}

int Rpn::getRes() const{
	if(number.empty()){
		throw std::runtime_error("Error: I dont have any result to show you... :(");
	}
	return number.top();
}