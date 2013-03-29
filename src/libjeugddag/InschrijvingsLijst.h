/*
 * InschrijvingsLijst.h
 *
 *  Created on: 10-mrt.-2013
 *      Author: vincent
 */

#ifndef INSCHRIJVINGSLIJST_H_
#define INSCHRIJVINGSLIJST_H_

#include "jeugddag.h"
#include <map>
#include <vector>
#include <string>

#include "WorkshopCollection.h"

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
