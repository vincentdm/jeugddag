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
		Logger::Log(LOG_INFO,"Aantal workshops vor sessie: %d",workshopsInDezeSessie.size());


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
				if(std::find(kind->toegekendeWorkshops.begin(),kind->toegekendeWorkshops.end(),ws)!=kind->toegekendeWorkshops.end())

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
					if(std::find(kind->toegekendeWorkshops.begin(),kind->toegekendeWorkshops.end(),ws)!=kind->toegekendeWorkshops.end())
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

int main ( int argc, char ** argv ) {

	Logger::Log(LOG_INFO,"Welkom bij Jeugddag-cli");
	Logger::Log(LOG_INFO,"Bezig met opstarten...");

	std::string configfile = "";
	std::vector<std::string> lijstBestanden;
	std::string workshopfile = "workshops.csv";
	//parse options
	for(int argIdx = 1;argIdx<argc;argIdx++) {
		std::string arg (argv[argIdx]);
		if(arg=="-c" || arg == "--configfile") {
			configfile=std::string(argv[++argIdx]);
		} else if(arg=="-l" || arg=="--lijst") {
			lijstBestanden.push_back(std::string(argv[++argIdx]));
		} else if(arg=="-w" || arg=="--workshops") {
			workshopfile=argv[++argIdx];
		}
	}

	Logger::Log(LOG_DEBUG,"-configuratiebestand: "+configfile);

	//parse config file if any
	if(configfile!="") {

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

	delete(wsc);

	return 0;
}
