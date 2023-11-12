#ifndef HiddenObject_H
#define HiddenObject_H

/**********Include Headers************/
#include <stdint.h>
#include "Config.h"

/**********Add to config.h************/
/*
enum HiddenObject_ObjectList
{
	HIDDENOBJECT_,
	NUMBER_OF_HIDDENOBJECTS
};

	//HiddenObjects Library
	#define FEATURE_HIDDENOBJECT
	#define HIDDENOBJECT_MAJOR	0
	#define HIDDENOBJECT_MINOR	0
	#define HIDDENOBJECT_PATCH	0
*/

/**********Add to config.c************/
/*
#ifndef HIDDENOBJECT_LIBRARY
	#error "HiddenObjects library was not found"
#endif
*/

/********Semantic Versioning**********/
#define HIDDENOBJECT_LIBRARY

/***********Magic Numbers*************/
/************Enumeration**************/
/*********Object Definition***********/
#ifdef FEATURE_HIDDENOBJECT
typedef struct HiddenObject_t HiddenObject_t;
#else
typedef void HiddenObject_t;
#endif

/****Module Function Prototypes*******/
uint8_t HO_Aquire_HiddenObject_Object(HiddenObject_t **self, enum HiddenObject_ObjectList Index);
uint8_t HO_Return_HiddenObject_Object(HiddenObject_t **self);
uint8_t HO_Reset_HiddenObject(HiddenObject_t *self);

#endif//HiddenObject_H
