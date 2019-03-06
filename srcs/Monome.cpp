/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Monome.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:16:12 by abassibe          #+#    #+#             */
/*   Updated: 2019/03/05 18:00:32 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Monome.hpp"

Monome::Monome()
{}

Monome::Monome(std::string monome)
{
	std::string		tempCoef;
	std::string		tempExp;
	size_t			pos = 0;

	pos = monome.find("*");
	if (pos == std::string::npos)
	{
		std::cout << "Syntax error\n";
		exit(0);
	}
	tempCoef = monome.substr(0, pos);
	monome.erase(0, pos + 1);
	tempExp = monome;

	for (int i = tempCoef.length() - 1; i > 0; i--)
	{
		if (tempCoef[i] >= '0' && tempCoef[i] <= '9')
			break;
		if (tempCoef[i] < '0' || tempCoef[i] > '9')
			tempCoef.erase(i);
	}
	for (int i = tempCoef.length() - 1; i >= 0; i--)
	{
		if (i == 0)
		{
			try
			{
				coef = std::stof(tempCoef);
				if (coef > INT_MAX || coef < INT_MIN)
					throw std::string("Out of range number\n");
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << "Error: " << e.what() << "\n";
				exit(0);
			}
			catch (std::string const& error)
			{
				std::cout << error;
				exit(0);
			}
			break;
		}
		if ((tempCoef[i] < '0' || tempCoef[i] > '9') && tempCoef[i] != '.')
		{
			coef = std::stof(tempCoef.substr(i + 1));
			if ((tempCoef[i] == '-') || (i > 0 && tempCoef[i - 1] == '-'))
				coef *= -1;
			break;
		}
	}
	pos = tempExp.find("^");
	if (pos == std::string::npos)
	{
		std::cout << "Syntax error\n";
		exit(0);
	}
	tempExp = tempExp.erase(0, pos + 1);
	try
	{
		exp = std::stoi(tempExp);
		if (exp > INT_MAX || exp < INT_MIN)
			throw std::string("Out of range number\n");
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "Error: " << e.what() << "\n";
		exit(0);
	}
	catch (std::string const& error)
	{
		std::cout << error;
		exit(0);
	}
	switch (exp)
	{
		case 0:
			letter = 'c';
			break;
		case 1:
			letter = 'b';
			break;
		case 2:
			letter = 'a';
			break;
		default:
			letter = 'n';
			break;
	}
}

Monome::Monome(Monome const& copy) : coef(copy.coef), exp(copy.exp)
{}

Monome::~Monome()
{}

Monome	&Monome::operator=(Monome const& copy)
{
	coef = copy.coef;
	exp = copy.exp;
	letter = copy.letter;
	return (*this);
}

bool	Monome::operator==(Monome const& copy)
{
	if (coef == copy.coef && exp == copy.exp)
		return true;
	return false;
}
