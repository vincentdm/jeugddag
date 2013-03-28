/*
 * Kind.cpp
 *
 *  Created on: 25-mrt.-2013
 *      Author: vincent
 */

#include "jeugddag.h"

#include <stdio.h>

int Workshop::WorkshopCount=0;
Workshop::Workshop()  {
	Workshop::WorkshopCount++;
	printf("Nu zijn er %lu Workshop objecten\n",Workshop::WorkshopCount);
}
Workshop::~Workshop() {
	Workshop::WorkshopCount--;
	printf("Nu zijn er %lu Workshop objecten\n",Workshop::WorkshopCount);
}
