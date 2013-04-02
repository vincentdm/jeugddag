#include "jeugddag.h"

Jeugddag::Jeugddag() {

	enrollmentList = 0;
	workshopCollection = 0;
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
