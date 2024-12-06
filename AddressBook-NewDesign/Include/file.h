/*************************************************************************************************************************************
** @Name                 : Rajesh jonnalgadda.
** @Date                 : 13/08/2024.
** 
** @File	             : file.h
** 
** Description 			 :This file consist of two functions declarations which will used for save the contacts to the file from the 						 stracture as well as it well load the contacts from the file to the stracture. 
** 
**
***********************************************************************************************************************************/
#define FILE_H

#ifdef FILE_H
#include <Include/contact.h>

void saveContactsToFile(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);

#endif
