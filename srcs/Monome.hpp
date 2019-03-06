/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Monome.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:57:38 by abassibe          #+#    #+#             */
/*   Updated: 2019/03/04 15:28:11 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONOME_HPP
# define MONOME_HPP

# include <string>

class Monome
{
	public:
		~Monome();
		Monome(std::string monome);
		Monome(Monome const& copy);
		Monome	&operator=(Monome const& copy);
		bool	operator==(Monome const& copy);
		float	coef;
		int		exp;
		char	letter;

	private:
		Monome();
};

#endif
