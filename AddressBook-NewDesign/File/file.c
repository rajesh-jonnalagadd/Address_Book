/*************************************************************************************************************************************
** Name                 : Rajesh jonnalgadda.
** Date                 : 13/08/2024.
** 
** @File	            : file.c
** 
** Description 			: This file consist of two functions which will used for save the contacts to the file from the stracture as 						  well as it well load the contacts from the file to the stracture. 
** 
**
***********************************************************************************************************************************/


#include "Include/contact.h"
#include "Include/file.h"

//Save the contacts to the file.
void saveContactsToFile(AddressBook *addressBook){
   FILE *fp;
   fp = fopen("contacts.csv", "w");
   if(fp == NULL){
        DEBUG("Error in opening file \n");
     	return;
     }
   fprintf(fp,"#%d",addressBook->contactCount);
   fprintf(fp,"\n");	
	for (int i = 0; i <= addressBook->contactCount; i++) 
    {	
		fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
	}
   	fclose(fp);
}

//Load the contacts from the file.
void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp;
    char buffer[1024];
    fp = fopen("contacts.csv", "r");
    if (fp == NULL){
        DEBUG("Error opening file \n");
        return;
    }
    if(fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (buffer[0] == '#') {
            addressBook->contactCount = atoi(&buffer[1]);
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (fgets(buffer, sizeof(buffer), fp) != NULL) {
                    sscanf(buffer, "%[^,],%[^,],%[^\n]",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }else{
                    DEBUG("Error reading contact %d\n", i+1);
                    break;
                }
            }
        } else {
            DEBUG("The First line doesn't start with  '#'\n");
            fclose(fp);
            return;
        }
    }else{
        DEBUG("Could not read line\n");
        fclose(fp);
        return;
    }
    fclose(fp);
}

