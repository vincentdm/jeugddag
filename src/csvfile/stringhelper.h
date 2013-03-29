/*
 * stringhelper.h
 *
 *  Created on: 10-mrt.-2013
 *      Author: vincent
 */

#ifndef STRINGHELPER_H_
#define STRINGHELPER_H_

#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}



#endif /* STRINGHELPER_H_ */
