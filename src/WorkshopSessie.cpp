/*
 * WorkshopSessie.cpp
 *
 *  Created on: 26-mrt.-2013
 *      Author: vincent
 */

#include "jeugddag.h"
#include <stdio.h>
#define LOGGER_CLASSNAME "WorkshopSessie"
#define LOGGER_MINLEVEL LOG_DEBUG;
#include "logger/logger.h"

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

bool WorkshopSessie::SchrijfIn(Inschrijving * inschrijving) {
	bool ret = true;
	if(this->plaatsenBeschikbaar==0)
		return false;

	this->inschrijvingen.push_back(inschrijving);
	this->plaatsenBeschikbaar--;
	Logger::Log(LOG_INFO,"WorkshopSessie (%s,%s) heeft nog %lu plaatsen beschikbaar van %lu\n",
			this->workshop->naam.c_str(),this->sessie->start.c_str(),this->plaatsenBeschikbaar,this->workshop->capaciteit);


}


