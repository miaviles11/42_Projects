/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:22:22 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/14 18:30:11 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook {
	private:
		Contact contacts[8];
		int total_contacts;
		int contact_index;

	public:
		PhoneBook();
		void add_contact();
		void search_contact();
};

#endif
