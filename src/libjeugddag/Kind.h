/*
 * Kind.h
 *
 *  Created on: 2-apr.-2013
 *      Author: vincent
 */

#ifndef KIND_H_
#define KIND_H_

struct Kind;
#include "Workshop.h"

struct Kind {
	std::string nummer;
	std::string naam;
	std::string voornaam;
	std::string adres;
	std::string telefoon;
	std::string gsm;
	std::string email;
	std::string opstapplaats;
	std::string geboortedatum;
	int	leeftijd;
	std::string naamVriendje;
	Kind * vriendje;
	bool betaald;
	std::vector<WorkshopSessie *> toegekendeWorkshops;

	Kind();
	~Kind();

private:
	static int KindCount;
};

#endif /* KIND_H_ */
