/*
 * InschrijvingsLijst.h
 *
 *  Created on: 10-mrt.-2013
 *      Author: vincent
 */

#ifndef INSCHRIJVINGSLIJST_H_
#define INSCHRIJVINGSLIJST_H_

#include <map>
#include <vector>
#include <string>
#include "Inschrijving.h"
#include "WorkshopCollection.h"

#define JD_SESSIE_COUNT 4
#define JD_YEAR 2013
#define JD_MONTH 5
#define JD_DAY 18

#define CSV_INSCHRIJVING_NUMMER			0
#define CSV_INSCHRIJVING_NAAM			1
#define CSV_INSCHRIJVING_VOORNAAM		2
#define CSV_INSCHRIJVING_ADRES			3
#define CSV_INSCHRIJVING_TELNUMMER		4
#define CSV_INSCHRIJVING_GSMNUMMER		5
#define CSV_INSCHRIJVING_EMAIL			6
#define CSV_INSCHRIJVING_GEBOORTEDATUM	7
#define CSV_INSCHRIJVING_OPSTAPPLAATS	8
#define CSV_INSCHRIJVING_WORKSHOP_START	9
#define CSV_INSCHRIJVING_WORKSHOP_COUNT	4
#define CSV_INSCHRIJVING_WORKSHOP_RES	CSV_INSCHRIJVING_WORKSHOP_START+JD_SESSIE_COUNT
#define CSV_INSCHRIJVING_VRIENDJE		CSV_INSCHRIJVING_WORKSHOP_RES+1
#define CSV_INSCHRIJVING_BETAALD		CSV_INSCHRIJVING_VRIENDJE + 1

class InschrijvingsLijst {
public:
	InschrijvingsLijst();
	virtual ~InschrijvingsLijst();

	void ReadFromCSV(std::string filename);
	void WriteToCSV(std::string filename);

	static InschrijvingsLijst * Merge(const std::vector<InschrijvingsLijst*>&);
	void Link(const WorkshopCollection& workshops);
	std::vector<Inschrijving*> inschrijvingen;

private:
	int calculateAge(std::string dob);
};

#endif /* INSCHRIJVINGSLIJST_H_ */
