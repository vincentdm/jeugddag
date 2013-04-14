/*
 * InschrijvingsLijst.h
 *
 *  Created on: 10-mrt.-2013
 *      Author: vincent
 */

#ifndef INSCHRIJVINGSLIJST_H_
#define INSCHRIJVINGSLIJST_H_

#include <map>
#include <list>
#include <string>
#include "Inschrijving.h"
#include "WorkshopCollection.h"

#define JD_SESSIE_COUNT 4
#define JD_YEAR 2013
#define JD_MONTH 5
#define JD_DAY 18

#define CSV_INSCHRIJVING_NUMMER				0
#define CSV_INSCHRIJVING_NAAM				CSV_INSCHRIJVING_NUMMER + 1
#define CSV_INSCHRIJVING_VOORNAAM			CSV_INSCHRIJVING_NAAM + 1
#define CSV_INSCHRIJVING_ADRES				CSV_INSCHRIJVING_VOORNAAM + 1
#define CSV_INSCHRIJVING_TELNUMMER			CSV_INSCHRIJVING_ADRES + 1
#define CSV_INSCHRIJVING_EMAIL				CSV_INSCHRIJVING_TELNUMMER + 1
#define CSV_INSCHRIJVING_GEBOORTEDATUM		CSV_INSCHRIJVING_EMAIL + 1
#define CSV_INSCHRIJVING_OPSTAPPLAATS		CSV_INSCHRIJVING_GEBOORTEDATUM + 1
#define CSV_INSCHRIJVING_WORKSHOP_START		CSV_INSCHRIJVING_OPSTAPPLAATS + 1
#define CSV_INSCHRIJVING_WORKSHOP_COUNT		4
#define CSV_INSCHRIJVING_WORKSHOP_RES_START	CSV_INSCHRIJVING_WORKSHOP_START+JD_SESSIE_COUNT
#define CSV_INSCHRIJVING_WORKSHOP_RES_COUNT	1
#define CSV_INSCHRIJVING_VRIENDJE			CSV_INSCHRIJVING_WORKSHOP_RES+CSV_INSCHRIJVING_WORKSHOP_RES_COUNT
#define CSV_INSCHRIJVING_BETAALD			CSV_INSCHRIJVING_VRIENDJE + 1

class InschrijvingsLijst {
public:
	typedef std::list<Inschrijving *> InschrijvingsLijst_t;
	InschrijvingsLijst();
	virtual ~InschrijvingsLijst();

	void ReadFromCSV(std::string filename);
	void WriteToCSV(std::string filename);

	static InschrijvingsLijst * Merge(const std::vector<InschrijvingsLijst*>&);
	void Link(const WorkshopCollection& workshops);
	InschrijvingsLijst_t inschrijvingen;

	static bool CompareInschrijving(Inschrijving * i1,Inschrijving * i2);

private:
	int calculateAge(std::string dob);
};

#endif /* INSCHRIJVINGSLIJST_H_ */
