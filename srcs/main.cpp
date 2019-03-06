/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:29:15 by abassibe          #+#    #+#             */
/*   Updated: 2019/03/05 18:26:44 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Poly.hpp"
#include "Monome.hpp"

static void		error(std::string error)
{
	std::cout << error;
	std::cout << "Examples of valid format :\n";
	std::cout << "  \t\"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"\n";
	std::cout << "or\t\"4 * X^0 + 9 * X^1 = 1 * X^0 + 1 * X^1\"\n";
}

int				main(int ac, char **av)
{
	if (ac != 2)
	{
		error("Computor need one argument.\n");
		return (-1);
	}
	if (((std::string)av[1]).find("=") == std::string::npos)
	{
		error("Syntax error.\n");
		return (-1);
	}
	Poly	poly(av[1]);
	if (!poly.isValid())
	{
		std::cout << "Invalid equation.\n";
		return (-1);
	}
	poly.comput();
	return (0);
}
