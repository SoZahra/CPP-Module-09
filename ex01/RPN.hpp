/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:12:56 by fzayani           #+#    #+#             */
/*   Updated: 2025/03/31 16:53:16 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>

class Rpn {

	private :
		enum op
		{
			PLUS = '+',
			MUL = '*',
			MOINS = '-',
			DIV = '/',
			NOTHING = 0,
			NUM = 1,
		};

		std::stack<int> number; //stocker les num

	public :
		Rpn();
		~Rpn();
		Rpn(const Rpn& other);
		Rpn& operator=(const Rpn& other);

		//methodes
		void calculate(const std::string& expresion);
		int getRes() const;
		bool isOperateur(char c) const;
		void performOperation(char op);

};

#endif