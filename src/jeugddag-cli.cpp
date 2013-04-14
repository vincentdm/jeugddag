#include "jeugddag.h"
#include <map>
#include "WorkshopCollection.h"
#include "InschrijvingsLijst.h"
#include <iostream>
#include <algorithm>
#include <cstdio>


#include "logger/logger.h"
void println(std::string line) {
	Logger::Log(LOG_INFO,line);
}



void printHelp() {
	println("syntax is command <[-w|--workshops] workshopfile.csv > <[-l|--lijst] lijstfile.csv > ...");
	println("-l -lijst        Leest een inschrijvingslijst in uit een file");
	println("                 Dit kan zo veel herhaald worden als er inschrijvingsbestanden zijn");
	println("-w -workshops    Leest een workshop bestand in uit een file");
	println("                 Indien niet meegegeven, workshops.csv zal gelezen worden");
}

int main ( int argc, char ** argv ) {

	Logger::Log(LOG_INFO,"Welkom bij Jeugddag-cli");
	Logger::Log(LOG_INFO,"Bezig met opstarten...");

	std::vector<std::string> lijstBestanden;
	std::string workshopfile = "workshops.csv";
	std::string outputfile = "inschrijvingslijst.csv";
	std::string outputdir = "./";
	//parse options
	for(int argIdx = 1;argIdx<argc;argIdx++) {
		std::string arg (argv[argIdx]);

		if(arg=="-l" || arg=="--lijst") {
			lijstBestanden.push_back(std::string(argv[++argIdx]));
		} else if(arg=="-w" || arg=="--workshops") {
			workshopfile=argv[++argIdx];
		} else if (arg=="-o") {
			outputfile = argv[++argIdx];
		} else if (arg=="-od") {
			outputdir = argv[++argIdx];
		} else {
			printHelp();
			return 0;
		}
	}

	Jeugddag jd;

	println("-inlezen workshopbestand:" + workshopfile);
	jd.ReadWorkshops(workshopfile);
	WorkshopCollection * wsc = jd.GetWorkshopCollection();

	println("-inlezen inschrijvingen");
	for(int lijstIdx = 0;lijstIdx<lijstBestanden.size();lijstIdx++) {
		println("--lijst bestand: " + lijstBestanden[lijstIdx]);
		jd.ReadEnrollmentList(lijstBestanden[lijstIdx]);
	}

	println("-samenvoegen inschrijvingslijsten...");
	jd.MergeEnrollments();

	println("-linken inschrijvingslijst");
	jd.LinkEnrollments();

	InschrijvingsLijst * alle = jd.GetEnrollmentList();

	println("-verdelen van de inschrijvingen");
	jd.Sort();

	InschrijvingsLijst::InschrijvingsLijst_t::iterator aIt;
	for(aIt=alle->inschrijvingen.begin();aIt!=alle->inschrijvingen.end();aIt++) {
		Inschrijving * i = *aIt;
		std::cout << "Inschrijving van " << i->kind->naam << " " << i->kind->voornaam << std::endl;
		std::vector<WorkshopSessie *>::iterator wsIt;

	}

	println("-wegschrijven inschrijvingslijst naar " + outputfile);
	alle->WriteToCSV(outputfile);

	std::vector<WorkshopSessie *>::iterator wsIt;
	for(wsIt=wsc->workshops.begin();wsIt!=wsc->workshops.end();wsIt++) {
		WorkshopSessie * ws = *wsIt;
		std::string filename = outputdir + "workshop_" + ws->workshop->naam + "_" + ws->sessie->start + ".csv";
		ws->WriteToCSV(filename);
	}


	return 0;
}
