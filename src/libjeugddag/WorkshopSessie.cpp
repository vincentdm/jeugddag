/*
 * WorkshopSessie.cpp
 *
 *  Created on: 26-mrt.-2013
 *      Author: vincent
 */

#include "jeugddag.h"
#include <stdio.h>
#include "logger.h"
#include "CSVFile.h"

int WorkshopSessie::WorkshopSessieCount = 0;
WorkshopSessie::WorkshopSessie(Workshop * ws, Sessie * s) {

	WorkshopSessie::WorkshopSessieCount++;

	Logger::Log(LOG_DEBUG,"Nu zijn er %lu WorkshopSessie objecten\n",(unsigned long)WorkshopSessie::WorkshopSessieCount);
	this->plaatsenBeschikbaar=ws->capaciteit;
	this->workshop=ws;
	this->sessie=s;
}

WorkshopSessie::~WorkshopSessie() {
	WorkshopSessie::WorkshopSessieCount--;
	Logger::Log(LOG_DEBUG,"Nu zijn er %lu WorkshopSessie objecten\n",(unsigned long)WorkshopSessie::WorkshopSessieCount);

}

void WorkshopSessie::WriteToCSV(std::string filename) {
	CSVFile f;

	CSVFile::DATASET set;
	std::vector<Inschrijving *>::iterator iIt;
	for(iIt=this->inschrijvingen.begin();iIt!=inschrijvingen.end();iIt++) {
		Inschrijving * i = *iIt;
		Kind * k = i->kind;
		CSVFile::ROW row;
		row.push_back(k->naam);
		row.push_back(k->voornaam);

		set.push_back(row);
	}
	f.Write(filename,set);
}


bool WorkshopSessie::SchrijfIn(Inschrijving * inschrijving) {
	bool ret = true;
	if(this->plaatsenBeschikbaar==0)
		return false;

	this->inschrijvingen.push_back(inschrijving);
	this->plaatsenBeschikbaar--;
	Logger::Log(LOG_INFO,"WorkshopSessie (%s,%s) heeft nog %lu plaatsen beschikbaar van %lu\n",
			this->workshop->naam.c_str(),this->sessie->start.c_str(),this->plaatsenBeschikbaar,this->workshop->capaciteit);


}


