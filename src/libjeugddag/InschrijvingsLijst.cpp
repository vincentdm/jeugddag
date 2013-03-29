/*
 * InschrijvingsLijst.cpp
 *
 *  Created on: 10-mrt.-2013
 *      Author: vincent
 */

#include "InschrijvingsLijst.h"
#include "CSVFile.h"
#include <cstdlib>
#include <iostream>

inline void println(std::string line) {
	std::cout << line << std::endl;
}

InschrijvingsLijst::InschrijvingsLijst() {
	// TODO Auto-generated constructor stub

}

InschrijvingsLijst::~InschrijvingsLijst() {
	// TODO Auto-generated destructor stub
}

void InschrijvingsLijst::ReadFromCSV(std::string filename) {
	CSVFile * file = new CSVFile();
	file->setHasHeaders(true);
	file->setSeparator(',');
	file->Open(filename);
	CSVFile::DATASET dataset = file->GetDataSet();
	file->Close();
	delete (file);

	CSVFile::DATASET::iterator rowIt;
	for(rowIt=dataset.begin();rowIt!=dataset.end();rowIt++) {
		CSVFile::ROW rij = *rowIt;
		Kind * kind = new Kind();

		kind->nummer=rij[CSV_INSCHRIJVING_NUMMER];
		kind->naam=rij[CSV_INSCHRIJVING_NAAM];
		kind->voornaam=rij[CSV_INSCHRIJVING_VOORNAAM];
		kind->adres=rij[CSV_INSCHRIJVING_ADRES];
		kind->telefoon=rij[CSV_INSCHRIJVING_TELNUMMER];
		kind->gsm=rij[CSV_INSCHRIJVING_GSMNUMMER];
		kind->geboortedatum=rij[CSV_INSCHRIJVING_GEBOORTEDATUM];
		kind->opstapplaats=rij[CSV_INSCHRIJVING_OPSTAPPLAATS];
		kind->leeftijd=calculateAge(rij[CSV_INSCHRIJVING_GEBOORTEDATUM]);

		Inschrijving * inschrijving = new Inschrijving();
		inschrijving->kind=kind;
		this->inschrijvingen.push_back(inschrijving);

		for (int wsId=0;wsId<CSV_INSCHRIJVING_WORKSHOP_COUNT;wsId++) {
			inschrijving->workshopnamen.push_back(rij[CSV_INSCHRIJVING_WORKSHOP_START+wsId]);
		}
		inschrijving->workshopnamen.push_back(rij[CSV_INSCHRIJVING_WORKSHOP_RES]);

	}
}

void InschrijvingsLijst::WriteToCSV(std::string filename) {
	std::vector<Inschrijving *>::iterator iIt;
	CSVFile::DATASET set;

	for(iIt=this->inschrijvingen.begin();iIt!=this->inschrijvingen.end();iIt++) {
		Inschrijving * i = *iIt;
		Kind * k = i->kind;
		CSVFile::ROW row;
		row.push_back(k->naam);
		row.push_back(k->voornaam);
		row.push_back(k->geboortedatum);
		row.push_back(k->telefoon);
		row.push_back(k->gsm);

		std::vector<WorkshopSessie *>::iterator wsIt;
		for(wsIt=k->toegekendeWorkshops.begin();wsIt!=k->toegekendeWorkshops.end();wsIt++) {
			Workshop * w = (*wsIt)->workshop;
			row.push_back(w->naam);
		}

		set.push_back(row);
	}

	CSVFile f;
	f.Write(filename,set);
}


InschrijvingsLijst* InschrijvingsLijst::Merge(
		const std::vector<InschrijvingsLijst*>& lijsten) {

	InschrijvingsLijst * merged = new InschrijvingsLijst();

	std::vector<Inschrijving *>::size_type max=0;
	for(int i = 0;i<lijsten.size();i++) {
		if(lijsten[i]->inschrijvingen.size()>max) {
			max=lijsten[i]->inschrijvingen.size();
		}
	}

	for(int i=0;i<max;i++) {
		for(int lijstIdx=0;lijstIdx<lijsten.size();lijstIdx++) {
			InschrijvingsLijst * lijst = lijsten[lijstIdx];
			if(lijst->inschrijvingen.size()>i) {
				merged->inschrijvingen.push_back(lijst->inschrijvingen[i]);
			}
		}
	}

	return merged;


}

void InschrijvingsLijst::Link(const WorkshopCollection& workshops) {
	std::vector<Inschrijving *>::iterator iIt;
	std::vector<Workshop*>::const_iterator wIt;
	for(iIt=inschrijvingen.begin();iIt!=inschrijvingen.end();iIt++) {
		Inschrijving * inschrijving = *iIt;

		std::vector<std::string>::iterator wnIt;
		for(wnIt=inschrijving->workshopnamen.begin();wnIt!=inschrijving->workshopnamen.end();wnIt++) {

			std::string workshopnaam = *wnIt;

			for(wIt=workshops.workshop_list.begin();wIt!=workshops.workshop_list.end();wIt++) {
				Workshop * workshop = *wIt;

				if(workshopnaam == workshop->naam && inschrijving->kind->leeftijd >= workshop->minLeeftijd && inschrijving->kind->leeftijd <= workshop->maxLeeftijd  ) {
					inschrijving->workshops.push_back(workshop);
				}

			}
		}
	}
}

int InschrijvingsLijst::calculateAge(std::string dob) {
	//dob = YYYY-mm-dd

	int year = std::atoi(dob.substr(0,4).c_str());
	int month = std::atoi(dob.substr(5,2).c_str());
	int day = std::atoi(dob.substr(8,2).c_str());

	int age=JD_YEAR-year;
	if(month>JD_MONTH)
		age--;
	else if(month==JD_MONTH && day < JD_DAY)
		age--;
	return age;



}
