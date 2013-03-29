/*
 * jeugddag.h
 *
 *  Created on: 19-feb.-2013
 *      Author: vincent
 */

#ifndef JEUGDDAG_H_
#define JEUGDDAG_H_

#include <string>
#include <vector>


struct Inschrijving;

/*
 * Nummer
 * Naam
 * Organisatie
 * Capaciteit
 * Leeftijd min
 * Leeftijd max
 * Sessie1
 * Sessie2
 * Sessie3
 * Sessie4
 */

#define JD_SESSIE_COUNT 4
#define JD_YEAR 2013
#define JD_MONTH 5
#define JD_DAY 18

#define CSV_WS_ID		0
#define CSV_WS_NAAM 		1
#define CSV_WS_ORG  		2
#define CSV_WS_CAP	  		3
#define CSV_WS_AGEMIN 		4
#define CSV_WS_AGEMAX 		5
#define CSV_WS_SESS_START 	6
#define CSV_WS_SESS_COUNT	JD_SESSIE_COUNT

/*
 * Nummer
 * Naam
 * Voornaam
 * Adres
 * Telefoonnummer
 * GSM
 * Email
 * Geboortedatum
 * Opstapplaats
 * Workshop1
 * Workshop2
 * Workshop3
 * Workshop4
 * Workshop
 * reserve
 * Naam
 * vriendje
 * betaald (J/N)
 */


struct Workshop;



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
#define CSV_INSCHRIJVING_WORKSHOP_COUNT	JD_SESSIE_COUNT
#define CSV_INSCHRIJVING_WORKSHOP_RES	CSV_INSCHRIJVING_WORKSHOP_START+JD_SESSIE_COUNT
#define CSV_INSCHRIJVING_VRIENDJE		CSV_INSCHRIJVING_WORKSHOP_RES+1
#define CSV_INSCHRIJVING_BETAALD		CSV_INSCHRIJVING_VRIENDJE + 1

struct Kind {
	std::string nummer;
	std::string naam;
	std::string voornaam;
	std::string adres;
	std::string telefoon;
	std::string gsm;
	std::string email;
	std::string opstapplaats;
	std::string geboortedatum;
	int	leeftijd;
	std::string naamVriendje;
	Kind * vriendje;
	bool betaald;
	std::vector<WorkshopSessie *> toegekendeWorkshops;

	Kind();
	~Kind();

private:
	static int KindCount;
};

struct Inschrijving {
	Kind * kind;
	std::vector<std::string> workshopnamen;
	std::vector<Workshop *> workshops;
};


#endif /* JEUGDDAG_H_ */
