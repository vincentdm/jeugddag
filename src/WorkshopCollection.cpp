/*
 * WorkshopCollection.cpp
 *
 *  Created on: 8-mrt.-2013
 *      Author: vincent
 */

#include "WorkshopCollection.h"
#include "CSVFile.h"
#include <cstdlib>

WorkshopCollection::WorkshopCollection() {
	Sessie * s1 = new Sessie();
	s1->start="9:00";
	Sessie * s2 = new Sessie();
	s2->start="10:30";
	Sessie * s3 = new Sessie();
	s3->start="13:00";
	Sessie * s4 = new Sessie();
	s4->start="14:30";

	sessies.push_back(s1);
	sessies.push_back(s2);
	sessies.push_back(s3);
	sessies.push_back(s4);
}

WorkshopCollection::~WorkshopCollection() {

}

void WorkshopCollection::ReadFromCSVFile(std::string fileName) {
	CSVFile * file = new CSVFile();
	CSVFile::DATASET dataset;
	file->setHasHeaders(true);
	file->setSeparator(',');
	file->Open(fileName);
	dataset=file->GetDataSet();
	file->Close();
	delete file;


	CSVFile::DATASET::iterator rowIt;
	for(rowIt=dataset.begin();rowIt!=dataset.end();rowIt++) {
		CSVFile::ROW rij = *rowIt;
		Workshop * ws = new Workshop();
		ws->naam=rij[CSV_WS_NAAM];
		ws->nummer=rij[CSV_WS_ID];
		ws->organisatie=rij[CSV_WS_ORG];
		ws->capaciteit=std::atoi((rij[CSV_WS_CAP]).c_str());
		ws->minLeeftijd=std::atoi((rij[CSV_WS_AGEMIN]).c_str());
		ws->maxLeeftijd=std::atoi((rij[CSV_WS_AGEMAX]).c_str());
		this->workshop_list.push_back(ws);
		for(int sessIdx=0;sessIdx<CSV_WS_SESS_COUNT;sessIdx++) {
			if(rij[CSV_WS_SESS_START+sessIdx] == "J") {
				WorkshopSessie * wss = new WorkshopSessie(ws,sessies[sessIdx]);
				wss->plaatsenBeschikbaar=ws->capaciteit;
				this->workshops.push_back(wss);
			}
		}
	}
}

std::vector<WorkshopSessie*> WorkshopCollection::GetWorkshopsForSessie(
		Sessie* sessie) {
	std::vector<WorkshopSessie*> wsl;
	std::vector<WorkshopSessie*>::iterator wsIt;
	for(wsIt=this->workshops.begin();wsIt!=workshops.end();wsIt++) {
		WorkshopSessie * ws = *wsIt;
		if(ws->sessie!=sessie)
			continue;
		wsl.push_back(ws);
	}
	return wsl;
}
