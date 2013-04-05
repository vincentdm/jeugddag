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
#include <list>
struct Kind {
	typedef std::list<WorkshopSessie *> WorkshopSessionList_t;
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
	WorkshopSessionList_t toegekendeWorkshops;

	Kind();
	~Kind();

private:
	static int KindCount;
};

#endif /* KIND_H_ */
