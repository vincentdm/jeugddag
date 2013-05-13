/*
 * nietbetaald.cpp
 *
 *  Created on: 7-mei-2013
 *      Author: vincent
 */

#include <iostream>
#include <string>

#include "InschrijvingsLijst.h"


int main(int argc, char ** argv) {
	std::string inschrijvingslijstNaam = "inschrijvingen.csv";

	for(int i = 1; i< argc; i++) {
		std::string key = std::string(argv[i]);
		if( key == "--lijst" || key == "-l") {
			inschrijvingslijstNaam = std::string(argv[++i]);
		}
	}

	InschrijvingsLijst lijst;
	lijst.ReadFromCSV(inschrijvingslijstNaam);

	InschrijvingsLijst::InschrijvingsLijst_t::iterator iIt;
	for(iIt = lijst.inschrijvingen.begin();iIt != lijst.inschrijvingen.end(); iIt ++) {
		Inschrijving * inschrijving = *iIt;
		if(!inschrijving->kind->betaald) {
			std::cout << inschrijving->kind->email << ", ";
		}
	}
	std::cout << std::endl;


	return 0;
}


