/*
 * CSVFile.cpp
 *
 *  Created on: 9-mrt.-2013
 *      Author: vincent
 */
#include <fstream>
#include <iostream>
#include "stringhelper.h"
#include "CSVFile.h"

CSVFile::CSVFile() {
	this->separator=',';
	this->_hasHeaders=false;

}

bool CSVFile::hasHeaders() const {
	return _hasHeaders;
}

void CSVFile::setHasHeaders(bool hasHeaders) {
	this->_hasHeaders = hasHeaders;
}

char CSVFile::getSeparator() const {
	return separator;
}

void CSVFile::Write(std::string filename, DATASET dataToWrite) {
	std::ofstream f;
	f.open(filename.c_str(),f.trunc);

	DATASET::iterator di;
	for(di=dataToWrite.begin();di!=dataToWrite.end();di++) {
		ROW::iterator ri;
		for(ri=(*di).begin();ri!=(*di).end();ri++) {
			f << *ri <<  this->separator;
		}
		f << std::endl;
	}

	f.close();
}

void CSVFile::setSeparator(char separator) {
	this->separator = separator;
}

void CSVFile::Open(std::string filename) {

	std::ifstream f;
	f.open(filename.c_str());

	this->_dataset.clear();
	bool headerDone=false;

	while(f.is_open() && f.good()) {
		std::string line;
		std::getline(f,line);
		if(!headerDone && this->hasHeaders()) {
			//skip header
			headerDone=true;
			continue;
		}
		if(line.length()==0) {
			continue;//skip empty lines
		}

		std::cout << "Parsing line: " << line << std::endl;
		ROW row = split(line,this->getSeparator());
		this->_dataset.push_back(row);

	}

	f.close();
}

void CSVFile::Close() {
}

CSVFile::DATASET CSVFile::GetDataSet() {
	return this->_dataset;
}

CSVFile::~CSVFile() {
	// TODO Auto-generated destructor stub
}

