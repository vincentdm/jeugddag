/*
 * Inschrijving.h
 *
 *  Created on: 2-apr.-2013
 *      Author: vincent
 */

#ifndef INSCHRIJVING_H_
#define INSCHRIJVING_H_

struct Inschrijving;

#include "Kind.h"
#include "Workshop.h"
#include <list>
struct Inschrijving {
	typedef std::list<Workshop *> WorkshopList_t;
	typedef std::list<std::string> WorkshopNameList_t;
	unsigned int id;
	Kind * kind;
	WorkshopNameList_t workshopnamen;
	std::list<Workshop *> workshops;
};


#endif /* INSCHRIJVING_H_ */
