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

struct Inschrijving {
	Kind * kind;
	std::vector<std::string> workshopnamen;
	std::vector<Workshop *> workshops;
};


#endif /* INSCHRIJVING_H_ */
