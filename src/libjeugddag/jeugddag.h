/*
 * jeugddag.h
 *
 *  Created on: 19-feb.-2013
 *      Author: vincent
 */

#ifndef JEUGDDAG_H_
#define JEUGDDAG_H_

#include <string>
#include <vector>


struct Inschrijving;




struct Workshop;



#include "Workshop.h"



#include "Kind.h"

#include "Inschrijving.h"


#include "InschrijvingsLijst.h"
#include "WorkshopCollection.h"

class Jeugddag {
public:

	Jeugddag();
	~Jeugddag();
	void ReadWorkshops(std::string filename);
	WorkshopCollection * GetWorkshopCollection() {
		return this->workshopCollection;
	}

	void ReadEnrollmentList(std::string filename);
	void MergeEnrollments();
	void LinkEnrollments();

	InschrijvingsLijst * GetEnrollmentList() { return this->enrollmentList; };

private:
	std::vector<InschrijvingsLijst *> enrollmentLists;
	InschrijvingsLijst * enrollmentList;
	WorkshopCollection * workshopCollection;

};

#endif /* JEUGDDAG_H_ */
