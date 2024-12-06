/*************************************************************************************************************************************
** @Name                 : Rajesh jonnalgadda.
** @Date                 : 13/08/2024.
** 
** @File	             : contact.h
** 
** @Description    		: This file consist of the structure and enum  and function declarations which used in this project.
** 
**
***********************************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


#define DEBUG printf
#define EXIT_SUCCESS 0

#pragma pack(1)

int sum_of_data;

#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct 
{
    char name[50];
    char phone[20];
    char email[20];
} Contact;

typedef struct 
{
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;
 
//enum for the search option
enum search_criteria
{
	e_search_by_name =1,
	e_search_by_phone,
	e_search_by_email
};

//enum for the list option
enum list_criteria
{
	e_list_by_name =1,
	e_list_by_phone,
	e_list_by_email,
	e_list_whole_data
};

//enum for the edit option
enum edit_criteria
{
	e_edit_by_name =1,
	e_edit_by_phone,
	e_edit_by_email,
	e_edit_whole_data
};
//enum for the delete option
enum delete_criteria
{
	e_delete_by_name =1,
	e_delete_by_phone,
	e_delete_by_email
};

//enum for main menu
enum menu_criteria
{
	e_create_contact =1,
	e_search_contact,
	e_edit_contact,
	e_delete_contact,
	e_list_contact,
	e_save_contact,
	e_exit
};

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void save(AddressBook *addressbook);

int getIntegerInput();
void List_by_Whole_Data(AddressBook *addressBook);
void LIst_by_Email(AddressBook *addressBook);
int Search_by_Member(AddressBook *addressBook,char list_by_name[]);
void Edit_by_Member(AddressBook *addressBook,char edit_member[],int serial_number);
int Existed_or_Not(AddressBook *addressBook,char member[]);
int search_by_Member(AddressBook *addressBook,char search_by_member[]);
void Delete_by_Member(AddressBook *addressBook,char *edit_member,int serial_number);
#endif
