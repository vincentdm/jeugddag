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

	Sessie * GetSession(unsigned int id) {
			std::list<Sessie*>::iterator sessIt;
			for(sessIt=this->sessies.begin();sessIt!=this->sessies.end();sessIt++) {
						Sessie * s = *sessIt;
						if(s->id==id)
							return s;
			}
			return 0;
		}

	void ReadFromCSVFile(std::string fileName);


	std::vector<WorkshopSessie *> GetWorkshopsForSessie(Sessie * sessie);

	std::vector<WorkshopSessie *> GetWorkshopsForSessie(int sessieIdx) {
		std::vector<WorkshopSessie*> retvec;
		Sessie * s =GetSession(sessieIdx);
		if(s!=0)
			retvec=GetWorkshopsForSessie(s);

		return retvec;
	}



	std::vector<WorkshopSessie *> workshops;
	std::vector<Workshop *> workshop_list;
	std::list<Sessie *> sessies;
};

#endif /* WORKSHOPCOLLECTION_H_ */
