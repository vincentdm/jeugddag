/*
 * Kind.cpp
 *
 *  Created on: 25-mrt.-2013
 *      Author: vincent
 */

#include "jeugddag.h"

#include <stdio.h>

int Kind::KindCount=0;
Kind::Kind()  {
	Kind::KindCount++;
	printf("Nu zijn er %lu Kind objecten\n",Kind::KindCount);
}
Kind::~Kind() {
	Kind::KindCount--;
}




