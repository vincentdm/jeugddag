#include "jeugddag.h"
#include <cstdio>

using std::printf;

Jeugddag::Jeugddag() {

	enrollmentList = 0;
	workshopCollection = 0;
	numberOfSessions=4;


}

Jeugddag::~Jeugddag() {

	if(enrollmentList!=0) {
		delete enrollmentList;
		enrollmentList=0;
	}

	if (workshopCollection !=0) {
		delete workshopCollection;
		workshopCollection=0;
	}

	std::vector<InschrijvingsLijst *>::iterator iIt;
	for(iIt=enrollmentLists.begin();iIt!=enrollmentLists.end();iIt++) {
		delete (*iIt);
	}

}

void Jeugddag::ReadWorkshops(std::string filename) {
	this->workshopCollection = new WorkshopCollection();
	this->workshopCollection->ReadFromCSVFile(filename);
}

void Jeugddag::ReadEnrollmentList(std::string filename) {
	InschrijvingsLijst * il = new InschrijvingsLijst();
	il->ReadFromCSV(filename);
	this->enrollmentLists.push_back(il);
}

void Jeugddag::MergeEnrollments() {
	this->enrollmentList = InschrijvingsLijst::Merge(this->enrollmentLists);
}

void Jeugddag::LinkEnrollments() {
	this->enrollmentList->Link(*this->workshopCollection);
}

bool Jeugddag::Assign(Inschrijving* enrollee, WorkshopSessie* ws) {

	//places available?
	if(ws->plaatsenBeschikbaar==0)
		return false;


	Workshop * workshop = ws->workshop;

	//workshop is for enrollees age?
	if(workshop->minLeeftijd > enrollee->kind->leeftijd || workshop->maxLeeftijd < enrollee->kind->leeftijd)
		return false;

	//workshop done already?
	if(enrollee->WorkshopDone(workshop))
		return false;

	//all checks pass!
	//enroll!
	ws->SchrijfIn(enrollee);
	enrollee->kind->toegekendeWorkshops.push_back(ws);

	return true;


}

void Jeugddag::Sort() {
	sessions=workshopCollection->sessies;

	std::list<Sessie *>::iterator sessIt;
	WorkshopSessie * assignedWorkshopSession;
	for(sessIt=sessions.begin();sessIt!=sessions.end();sessIt++) {
		//for each session
		Sessie * sessie = *sessIt;
		printf("[INFO] toewijzen voor sessie %d\n",sessie->id);
		std::vector<WorkshopSessie *> availableWorkshops = this->workshopCollection->GetWorkshopsForSessie(sessie);

		//for each enrollee
		std::list<Inschrijving*>::iterator enrollIt;
		for(enrollIt=this->enrollmentList->inschrijvingen.begin();
				enrollIt!=this->enrollmentList->inschrijvingen.end();
				enrollIt++) {
			Inschrijving * enrollee = *enrollIt;
			printf("[INFO] Kind %s %s\n",enrollee->kind->naam.c_str(),enrollee->kind->voornaam.c_str());

			if(enrollee->kind->toegekendeWorkshops.size() >= sessie->id ) {
				printf("[INFO]   Heeft al een workshop voor deze sessie!\n");
				continue;
			}


			bool foundWorkshop=false;
			assignedWorkshopSession = NULL;

			std::list<Workshop *>::iterator wantedWorkshopIt;
			for(wantedWorkshopIt=enrollee->workshops.begin();
					wantedWorkshopIt!=enrollee->workshops.end() && !foundWorkshop;
					wantedWorkshopIt++) {

				Workshop * wantedWorkshop = *wantedWorkshopIt;
				printf("[DEBUG]    wil workshop %s\n",wantedWorkshop->naam.c_str());

				std::vector<WorkshopSessie *>::iterator availableWorkshopIt;
				for(availableWorkshopIt=availableWorkshops.begin();
						availableWorkshopIt!=availableWorkshops.end() && !foundWorkshop;
						availableWorkshopIt++) {

					WorkshopSessie * availableWorkshop = *availableWorkshopIt;
					if(availableWorkshop->workshop==wantedWorkshop) {
						foundWorkshop = this->Assign(enrollee,availableWorkshop);
						assignedWorkshopSession=availableWorkshop;
					}

				}


			}//end foreach wanted workshop in enrollment

			if(!foundWorkshop) {
				printf("[WARNING]: Kind %s %s kon geen workshop toegewezen krijgen voor sessie %d\nzelf 1 proberen toewijzen\n",
						enrollee->kind->naam.c_str(),enrollee->kind->voornaam.c_str(),sessie->id);
				std::vector<WorkshopSessie *>::iterator availableWorkshopIt;
				for(availableWorkshopIt=availableWorkshops.begin();
						availableWorkshopIt!=availableWorkshops.end() && !foundWorkshop;
						availableWorkshopIt++) {

					WorkshopSessie * ws = *availableWorkshopIt;
					foundWorkshop = this->Assign(enrollee,ws);
					assignedWorkshopSession=ws;

				}

			}

			if(!foundWorkshop) {
				printf("[ERROR]: Kind %s %s kon geen workshop toegewezen krijgen voor sessie %d\n",
						enrollee->kind->naam.c_str(),enrollee->kind->voornaam.c_str(),sessie->id);
			} else {
				/*
				 * OK, we managed to enroll someone for some workshop,
				 * now try to enroll the "friend" for the same workshop.
				 */

				if(enrollee->vriendje == 0) {
					//bummer, the enrollee has no friend assigned.
					//so we have to continue
					continue;
				} else {
					//the enrollee has a friend, now check if the "friend"
					//also likes this workshop
					if(enrollee->vriendje->WorkshopRequested(assignedWorkshopSession->workshop) &&
							enrollee->vriendje->WorkshopDone(assignedWorkshopSession->workshop) &&
							enrollee->vriendje->kind->toegekendeWorkshops.size() < sessie->id) {
						//the "friend" also wants to do this workshop
						//and has not done this workshop already
						//and has not been assigned to a workshop for this session
						this->Assign(enrollee->vriendje,assignedWorkshopSession);
					}
				}


			}

			printf("\n");
		}//end foreach enrollee
		printf("\n\n");
	}//end foreach session

}
