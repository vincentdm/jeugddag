/*
 * Workshop.h
 *
 *  Created on: 2-apr.-2013
 *      Author: vincent
 */

#ifndef WORKSHOP_H_
#define WORKSHOP_H_

#include <string>
#include <vector>

struct Workshop;
struct Sessie;
class WorkshopSessie;

#include "Inschrijving.h"

struct Workshop {
	std::string nummer;
	std::string naam;
	std::string organisatie;
	int capaciteit;
	int minLeeftijd;
	int maxLeeftijd;

	Workshop();
	~Workshop();

private:
	static int WorkshopCount;
};

struct Sessie {
	std::string start;

};

class WorkshopSessie {
public:
	Workshop * workshop;
	Sessie * sessie;
	int plaatsenBeschikbaar;
	std::vector<Inschrijving *> inschrijvingen;

	WorkshopSessie(Workshop * workshop,Sessie * sessie);
	~WorkshopSessie();
	void WriteToCSV(std::string filename);

	bool SchrijfIn(Inschrijving *);
private:
	static int WorkshopSessieCount;
	WorkshopSessie();
	WorkshopSessie(WorkshopSessie&);
};


#endif /* WORKSHOP_H_ */
