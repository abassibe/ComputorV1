/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poly.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:30:09 by abassibe          #+#    #+#             */
/*   Updated: 2019/03/06 19:11:23 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLY_HPP
# define POLY_HPP

# include <string>
# include <vector>
# include "Monome.hpp"

class	Poly
{
	public:
		~Poly();
		Poly(std::string polynome);
		Poly(Poly const& copy);
		Poly					&operator=(Poly const& poly);
		void					comput();
		std::vector<Monome*>	equationList;
		std::vector<Monome*>	resultList;
		bool					canBeReduced();
		bool					isValid();
		float					RC1;
		float					RC2;

	private:
		Poly();
		void			getDelta();
		void			deltaEqualZero();
		void			deltaSupZero();
		void			deltaInfZero();
		void			printReducedForm();
		int				printPolynomialDegree();
		void			printSolution();
		void			printFirstDegree();
		size_t			searchMonome(std::string str);
		std::string		equation;
		std::string		result;
		float			delta;
};

#endif
