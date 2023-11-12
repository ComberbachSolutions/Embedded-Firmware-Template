/******************************************************************************
Version History:
v0.0.0	YYYY-MM-DD	Craig Comberbach	Compiler: [Compiler] [Version]
* First version
 *****************************************************************************/
/************Header Files*************/
#include "HiddenObject.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/********Semantic Versioning**********/
#ifdef FEATURE_HIDDENOBJECT
	#if HIDDENOBJECT_MAJOR != 0
		#error "HiddenObject library major revision update is available"
	#elif HIDDENOBJECT_MINOR != 0
		#error "HiddenObject library minor revision update is available"
	#elif HIDDENOBJECT_PATCH != 0
		#error "HiddenObject library patch revision update is available"
	#endif

/***********Magic Numbers*************/
/************Enumeration**************/
/*********Object Definition***********/
struct HiddenObject_t
{
	int16_t integer;
	float floater;
	int8_t character;
	int16_t array[5];
	int32_t *pointer;
	bool isOwned;
} Selves[NUMBER_OF_HIDDENOBJECTS] = {
	[0 ... NUMBER_OF_HIDDENOBJECTS - 1] = {
										   .integer = 1,
										   .floater = 2.0,
										   .character = '3',
										   .array = {0},
										   .array[0] = 4,
										   .array[1] = 5,
										   .array[2] = 6,
										   .array[3] = 7,
										   .array[4] = 8,
										   .pointer = NULL,
										   .isOwned = false,
										   }
};

/**********Global Variables***********/
/*****Local Function Prototypes*******/
/*********Main Body Of Code***********/
uint8_t HO_Aquire_HiddenObject_Object(HiddenObject_t **self, enum HiddenObject_ObjectList ID)
{
	uint8_t ReturnCode = 0;
	if((ID < NUMBER_OF_HIDDENOBJECTS) && (Selves[ID].isOwned == false))
	{
		*self = &Selves[ID];
		ReturnCode = 1;
	}
	return ReturnCode;
}

uint8_t HO_Return_HiddenObject_Object(HiddenObject_t **self)
{
	if(*self != NULL)
	{
		(*self)->isOwned = false;
	}
	*self = NULL;

	return 1;
}

uint8_t HO_Reset_HiddenObject(HiddenObject_t *self)
{
	if(self != NULL)
	{
		self->integer = 1;
		self->floater = 2.0;
		self->character = '3';
		self->array[0] = 4;
		self->array[1] = 5;
		self->array[2] = 6;
		self->array[3] = 7;
		self->array[4] = 8;
		return 1;
	}

	return 0;
}

#endif//FEATURE_HIDDENOBJECT
