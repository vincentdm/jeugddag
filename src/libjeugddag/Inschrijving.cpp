/*
 * Inschrijving.cpp
 *
 *  Created on: 14-apr.-2013
 *      Author: vincent
 */



#include "Inschrijving.h"

bool Inschrijving::WorkshopRequested(Workshop* w) {

	std::list<Workshop *>::iterator wIt;
	bool found = false;
	for(wIt=this->workshops.begin();wIt!=workshops.end() && !found;wIt++) {
		if(*wIt == w)
			found = true;
	}

	return found;
}

bool Inschrijving::WorkshopDone(Workshop* w) {
	bool found = false;
	Kind::WorkshopSessionList_t::iterator wsIt;
	for(wsIt = this->kind->toegekendeWorkshops.begin();wsIt!=this->kind->toegekendeWorkshops.end();wsIt++) {
		WorkshopSessie * ws = *wsIt;
		if(ws->workshop == w)
			found=true;
	}
	return found;

}
