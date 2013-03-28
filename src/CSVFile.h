/*
 * CSVFile.h
 *
 *  Created on: 9-mrt.-2013
 *      Author: vincent
 */

#ifndef CSVFILE_H_
#define CSVFILE_H_

#include <vector>
#include <string>
#include <iostream>

class CSVFile {
public:
	typedef std::vector<std::string> ROW;
	typedef std::vector<ROW> DATASET;
	CSVFile();
	virtual ~CSVFile();

	void Open(std::string filename);
	void Close();
	void Write(std::string filename,DATASET dataToWrite);
	bool hasHeaders() const;
	void setHasHeaders(bool hasHeaders);
	char getSeparator() const;
	void setSeparator(char separator);

	DATASET GetDataSet();

private:
	DATASET _dataset;
	bool _hasHeaders;
	char separator;
};

#endif /* CSVFILE_H_ */
