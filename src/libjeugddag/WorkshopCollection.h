/*
 * WorkshopCollection.h
 *
 *  Created on: 8-mrt.-2013
 *      Author: vincent
 */

#ifndef WORKSHOPCOLLECTION_H_
#define WORKSHOPCOLLECTION_H_

#include <string>
#include <map>

#include "Workshop.h"


#define CSV_WS_ID		0
#define CSV_WS_NAAM 		1
#define CSV_WS_ORG  		2
#define CSV_WS_CAP	  		3
#define CSV_WS_AGEMIN 		4
#define CSV_WS_AGEMAX 		5
#define CSV_WS_SESS_START 	6
#define CSV_WS_SESS_COUNT	4

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
