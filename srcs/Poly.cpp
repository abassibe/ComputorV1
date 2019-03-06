/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poly.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:46:29 by abassibe          #+#    #+#             */
/*   Updated: 2019/03/06 19:05:52 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Poly.hpp"
#include <iostream>
#include <vector>

Poly::Poly()
{}

size_t		Poly::searchMonome(std::string str)
{
	size_t	i = str.find("^");
	if (i == 0)
		return (0);
	i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return (i + 1);
}

Poly::Poly(std::string polynome)
{
	delta = 0;

	size_t	pos = 0;
	char	*mono;
	pos = polynome.find("=");
	equation = polynome.substr(0, pos);
	polynome.erase(0, pos + 1);
	result = polynome;
	while (!equation.empty())
	{
		if (equation.empty() || searchMonome(equation) == 0)
			break;
		pos = searchMonome(equation);
		mono = (char *)(equation.substr(0, pos)).c_str();
		equation = equation.erase(0, pos);
		equationList.push_back(new Monome(mono));
	}
	while (!result.empty())
	{
		if (result.empty() || searchMonome(result) == 0)
			break;
		pos = searchMonome(result);
		mono = (char *)(result.substr(0, pos)).c_str();
		result = result.erase(0, pos);
		resultList.push_back(new Monome(mono));
	}
}

Poly::Poly(Poly const& copy) : equationList(copy.equationList), resultList(copy.resultList)
{}

Poly::~Poly()
{
	for (size_t i = 0; i < equationList.size(); i++)
		delete equationList[i];
	for (size_t i = 0; i < resultList.size(); i++)
		delete resultList[i];
}

Poly	&Poly::operator=(Poly const& copy)
{
	equationList = copy.equationList;
	resultList = copy.resultList;
	return (*this);
}

void	Poly::getDelta()
{
	if (delta != 0)
		return ;
	float	a = 0.0;
	float	b = 0.0;
	float	c = 0.0;
	switch (equationList.size())
	{
		case 1:
			a = equationList[0]->coef;
			break ;
		case 2:
			a = equationList[1]->coef;
			b = equationList[0]->coef;
			break ;
		case 3:
			a = equationList[2]->coef;
			b = equationList[1]->coef;
			c = equationList[0]->coef;
			break ;
	}
	delta = (b * b) - (4 * a * c);
}

void	Poly::deltaEqualZero()
{
	float	a = 0.0;
	float	b = 0.0;
	switch (equationList.size())
	{
		case 1:
			a = equationList[0]->coef;
			break ;
		case 2:
			a = equationList[1]->coef;
			b = equationList[0]->coef;
			break ;
		case 3:
			a = equationList[2]->coef;
			b = equationList[1]->coef;
			break ;
	}
	RC1 = (b * -1) / (2 * a);
}

float	squareRoot(float value)
{
	float	x = value;
	float	y = 1;
	float	e = 0.000001;
	while (x - y > e)
	{
		x = (x + y) / 2;
		y = value / x;
	}
	return (x);
}

void	Poly::deltaSupZero()
{
	float	a = 0.0;
	float	b = 0.0;
	switch (equationList.size())
	{
		case 1:
			a = equationList[0]->coef;
			break ;
		case 2:
			a = equationList[1]->coef;
			b = equationList[0]->coef;
			break ;
		case 3:
			a = equationList[2]->coef;
			b = equationList[1]->coef;
			break ;
	}
	RC1 = ((b * -1) + squareRoot(delta)) / (2 * a);
	RC2 = ((b * -1) - squareRoot(delta)) / (2 * a);
}

void	Poly::deltaInfZero()
{
	float	b = 0.0;
	switch (equationList.size())
	{
		case 2:
			b = equationList[0]->exp;
		case 3:
			b = equationList[1]->exp;
	}
	RC1 = (b * -1) / 2;
	delta = squareRoot(delta * -1) / 2;
}

bool	Poly::isValid()
{
	if (equationList.size() < resultList.size())
	{
		std::cout << "Invalid equation.\n";
		exit(0);
	}
	return (true);
}

void	Poly::printReducedForm()
{
	for (size_t i = 0; i < equationList.size(); i++)
	{
		if (equationList[0]->coef != 0)
			break;
		if (i == equationList.size() - 1)
		{
			std::cout << "All real numbers are solution\n";
			exit(0);
		}
	}
	std::cout << "Reduced form: ";
	std::cout << equationList[0]->coef << " * X^" << equationList[0]->exp;
	for (size_t i = 1; i < equationList.size(); i++)
	{
		if (equationList[i]->coef < 0)
			std::cout << " - " << (equationList[i]->coef * -1) << " * X^" << equationList[i]->exp;
		else
			std::cout << " + " << equationList[i]->coef << " * X^" << equationList[i]->exp;
	}
	std::cout << " = 0\n";
}

int	Poly::printPolynomialDegree()
{
	for (int i = equationList.size() - 1; i >= 0; i--)
	{
		if (equationList[i]->coef != 0)
		{
			if (i > 2)
			{
				std::cout << "The polynomial degree is stricly greater than 2, I can't solve.\n";
				exit(0);
			}
			std::cout << "Polynomial degree: " << i << std::endl;
			return (i);
		}
	}
	return (0);
}

void	Poly::printSolution()
{
	getDelta();
	if (delta > 0)
	{
		deltaSupZero();
		std::cout << "Discriminant is strictly positive, the two solutions are:\n";
		std::cout << RC1 << std::endl;
		std::cout << RC2 << std::endl;
	}
	else if (delta == 0)
	{
		deltaEqualZero();
		std::cout << "Discriminant is null, the solution is:\n";
		std::cout << RC1 << std::endl;
	}
	else 
	{
		deltaInfZero();
		std::cout << "Discriminant is strictly negative, the two solutions in C are:\n";
		std::cout << RC1 << " - " << delta << "i" << std::endl;
		std::cout << RC1 << " + " << delta << "i" << std::endl;
	}
}

void	Poly::printFirstDegree()
{
	float	a = 0.0;
	float	b = 0.0;
	switch (equationList.size())
	{
		case 1:
			a = equationList[0]->coef;
			break ;
		case 2:
			a = equationList[1]->coef;
			b = equationList[0]->coef;
			break ;
		case 3:
			a = equationList[2]->coef;
			b = equationList[1]->coef;
			break ;
	}
	RC1 = (b * -1) / a;
	std::cout << "The solution is:\n";
	std::cout << RC1 << std::endl;
}

void	Poly::comput()
{
	int		degree;
	for (size_t i = 0; i < resultList.size(); i++)
		equationList[i]->coef -= resultList[i]->coef;
	printReducedForm();
	degree = printPolynomialDegree();
	if (degree > 1)
		printSolution();
	else if (degree == 1)
		printFirstDegree();
	else
	{
		std::cout << "The solution is:\n";
		std::cout << "0" << std::endl;
	}
}
