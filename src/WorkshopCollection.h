/*
 * WorkshopCollection.h
 *
 *  Created on: 8-mrt.-2013
 *      Author: vincent
 */

#ifndef WORKSHOPCOLLECTION_H_
#define WORKSHOPCOLLECTION_H_

#include <string>
#include "jeugddag.h"
#include <map>

class WorkshopCollection {
public:
	WorkshopCollection();
	virtual ~WorkshopCollection();

	void ReadFromCSVFile(std::string fileName);

	std::vector<WorkshopSessie *> GetWorkshopsForSessie(Sessie * sessie);

	std::vector<WorkshopSessie *> GetWorkshopsForSessie(int sessieIdx) {
		return this->GetWorkshopsForSessie(this->sessies[sessieIdx]);
	}

	std::vector<WorkshopSessie *> workshops;
	std::vector<Workshop *> workshop_list;
	std::vector<Sessie *> sessies;
};

#endif /* WORKSHOPCOLLECTION_H_ */
