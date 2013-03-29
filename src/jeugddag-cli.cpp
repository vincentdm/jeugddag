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

WorkshopSessie * SearchWorkshop(std::vector<WorkshopSessie *> ws,Workshop * w) {
	std::vector<WorkshopSessie *>::iterator wsIt;
	for(wsIt==ws.begin();wsIt!=ws.end();wsIt++) {
		if((*wsIt)->workshop==w) {
			return *wsIt;
		}
	}
}


void Verdeel(InschrijvingsLijst * lijst,WorkshopCollection *wsc ) {
	for(int sessieIdx=0;sessieIdx<JD_SESSIE_COUNT;sessieIdx++) {
		Logger::Log(LOG_INFO,"\nVerdelen workshops voor sessie: %d",(sessieIdx+1));
		std::vector<WorkshopSessie *> workshopsInDezeSessie = wsc->GetWorkshopsForSessie(sessieIdx);
		Logger::Log(LOG_INFO,"Aantal workshops voor sessie: %d",workshopsInDezeSessie.size());


		std::vector<Inschrijving*>::iterator it;
		for(it=lijst->inschrijvingen.begin();it!=lijst->inschrijvingen.end();it++) {
			Inschrijving * inschrijving = *it;
			Kind * kind = inschrijving->kind;
			Logger::Log(LOG_INFO,"Sessie %d: toewijzen kind %s %s\n",(sessieIdx+1),kind->voornaam.c_str(),kind->naam.c_str());

			std::vector<WorkshopSessie *>::iterator wsIt;
			bool workshopGevonden=false;
			for(wsIt=workshopsInDezeSessie.begin();wsIt!=workshopsInDezeSessie.end();wsIt++) {
				WorkshopSessie * ws = *wsIt;
				Workshop * workshop = ws->workshop;

				//check als er nog plaats is in deze sessie
				if(ws->plaatsenBeschikbaar==0)
					continue;

				//check als workshop nog niet is toegevoegd

				std::vector<WorkshopSessie *>::iterator kwsIt;
				bool workshopToegekend=false;
				for(kwsIt=kind->toegekendeWorkshops.begin();kwsIt!=kind->toegekendeWorkshops.end();kwsIt++) {
					WorkshopSessie * kws = *kwsIt;
					if(kws->workshop == workshop) {
						workshopToegekend = true;
					}
				}
				if(workshopToegekend)
					continue;


				//check if workshop is gevraagd
				if(std::find(inschrijving->workshops.begin(),inschrijving->workshops.end(),workshop)==inschrijving->workshops.end())
					continue;

				//ok er is nog plaats en het kind heeft de workshop gevraagd, voeg de sessie toe
				ws->SchrijfIn(inschrijving);
				kind->toegekendeWorkshops.push_back(ws);
				workshopGevonden=true;
				Logger::Log(LOG_INFO,"Kind %s %s heeft workshop %s toegewezen voor sessie %d\n",kind->voornaam.c_str(),kind->naam.c_str(),ws->workshop->naam.c_str(),(sessieIdx+1));
				Logger::Log(LOG_INFO,"workshop %s heeft nog %d plaatsen over van %d\n",ws->workshop->naam.c_str(),ws->plaatsenBeschikbaar,ws->workshop->capaciteit);
				break;
			}

			//wat als...
			//.. er nu geen workshop gevonden is voor een kind?
			//... dan zoeken we er nu een!
			if(!workshopGevonden) {
				for(wsIt=workshopsInDezeSessie.begin();wsIt!=workshopsInDezeSessie.end();wsIt++) {
					WorkshopSessie * ws = *wsIt;
					//workshop nog plaats?
					if(ws->plaatsenBeschikbaar==0)
						continue;
					//workshop al gedaan?
					std::vector<WorkshopSessie *>::iterator kwsIt;
					bool workshopToegekend=false;
					for(kwsIt=kind->toegekendeWorkshops.begin();kwsIt!=kind->toegekendeWorkshops.end();kwsIt++) {
						WorkshopSessie * kws = *kwsIt;
						if(kws->workshop == workshop) {
							workshopToegekend = true;
						}
					}
					if(workshopToegekend)
						continue;
					//workshop in juiste leeftijdsgroep
					if(ws->workshop->maxLeeftijd >= kind->leeftijd && ws->workshop->minLeeftijd <= kind->leeftijd) {
						ws->SchrijfIn(inschrijving);
						kind->toegekendeWorkshops.push_back(ws);

						workshopGevonden=true;
						break;
					}
				}
				if(!workshopGevonden) {
					Logger::Log(LOG_WARNING,"Kind %s %s kon geen workshop toegewezen krijgen voor sessie %d\n",
							kind->voornaam.c_str(),kind->naam.c_str(),(sessieIdx+1));
				} else {
					WorkshopSessie * ws = *wsIt;
					Logger::Log(LOG_INFO,"Kind %s %s heeft workshop %s toegewezen (door ons) voor sessie %d\n",
							kind->voornaam.c_str(),kind->naam.c_str(),ws->workshop->naam.c_str(),(sessieIdx+1));
					Logger::Log(LOG_INFO,"workshop %s heeft nog %d plaatsen over van %d\n",ws->workshop->naam.c_str(),ws->plaatsenBeschikbaar,ws->workshop->capaciteit);
				}
			}



		}
	}
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

	std::vector<InschrijvingsLijst *> lijsten;

	println("-inlezen workshopbestand:" + workshopfile);
	WorkshopCollection * wsc = new WorkshopCollection();
	wsc->ReadFromCSVFile(workshopfile);

	println("-inlezen inschrijvingen");
	for(int lijstIdx = 0;lijstIdx<lijstBestanden.size();lijstIdx++) {
		println("--lijst bestand: " + lijstBestanden[lijstIdx]);
		InschrijvingsLijst * il = new InschrijvingsLijst();
		il->ReadFromCSV(lijstBestanden[lijstIdx]);
		lijsten.push_back(il);
	}

	println("-samenvoegen inschrijvingslijsten...");
	InschrijvingsLijst * alle = InschrijvingsLijst::Merge(lijsten);

	println("-linken inschrijvingslijst");
	alle->Link(*wsc);

	println("-verdelen van de inschrijvingen");
	Verdeel(alle,wsc);

	std::vector<Inschrijving*>::iterator aIt;
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



	delete(wsc);

	return 0;
}
