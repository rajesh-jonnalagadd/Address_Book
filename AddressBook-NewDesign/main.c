#include "Include/contact.h"
#include "Include/colour.h"
#include "Include/file.h"

int Menu(){
	//local variables
	enum menu_criteria;
	int choice;
	//Structure variable
	AddressBook addressBook;
	initialize(&addressBook); // Initialize the address book
	do{
	DEBUG(HRED"\n\n\t\tAddress Book Menu\t\t\n"reset);
	DEBUG(BBLU"1.Create contact\n2.Search contact\n3.Edit contact\n4.Delete contact\n5.List all contacts\n6.Save\n7.Exit");
	DEBUG(BBLU"\nEnter your Option : "reset);
	fflush(stdin);
	choice = getIntegerInput();
	switch (choice) {
	case e_create_contact:{
		createContact(&addressBook);
		break;
	}
	case e_search_contact:{
		searchContact(&addressBook);
		break;
	}
	case e_edit_contact:{
		editContact(&addressBook);
		break;
	}
	case e_delete_contact:{
		deleteContact(&addressBook);
		break;
	}
	case e_list_contact:{
		int sortChoice;
		DEBUG(BYEL"\n\nSelect Display criteria :\n"reset);
		DEBUG(BCYN"\n\t1. Display by Name\n\t2. Display by Phone_Number\n\t3. Display by Email\n\t4. Display by All_Data\n");
		DEBUG("\nEnter your choice : "reset);
		sortChoice = getIntegerInput();
		DEBUG(""reset);
		listContacts(&addressBook, sortChoice);
		break;
	}
	case e_save_contact:{
		save(&addressBook);
		DEBUG(BYEL"\n\n\t\t...Saving and Closing...\n"reset);
		break;
	}
	case e_exit:{
		DEBUG(BYEL"\n\n\t\t ..........Thankyou.......... \t\t\n\n");
		DEBUG(""reset);
		exit(EXIT_SUCCESS);
	}
	default:{
		DEBUG(BYEL"\n\n\t\tInvalid choice. Please try again.\n"reset);
		break;
	}
	}
} while (choice != 7);

	return 0;
}
void Title(void){
	DEBUG(BWHT"\n\t\t----------------------------------------------------------------------------------\n"reset);
	DEBUG(BRED"\n\t\t\t\t\t\tADDRESS BOOK\n"reset);
	DEBUG(BWHT"\n\t\t----------------------------------------------------------------------------------\n"reset);
}

void Login(void){
	int no_of_times=1;
	char user[15];
	char pass[15];
	do
	{

	DEBUG(BHGRN"\n\n\n\n\t\t\t\t\tEnter the Username and Password \n");
	DEBUG("\n\n\n\t\t\t\t\t\t USERNAME : ");
	scanf(" %[^\n]s",user);

	DEBUG("\n\t\t\t\t\t\t PASSWORD : ");
	scanf(" %[^\n]s",pass);

	//Comparing the user name and password 
	if (strcmp(user,"RAJESH")==0 && strcmp(pass,"9999")==0)
	{
		DEBUG("\n\n\n\t\t\t\t\t....... Login Successful .......\n\n\t\t\t\t\t  Wait for %d seconds for Menu\t\t\t\n\n",10);
		//Sleep for ten seconds
		sleep(10);
		// To clear the console screen
		write(1,"\E[H\E[2J",7);
		//Menu  
		Menu();
	}else
	{
	DEBUG(BRED"\n\n\t\t\t\t\t     Incorrect Credentials! "reset);
	no_of_times++;
	}

}while(no_of_times<=2);

	if(no_of_times >2)
	{
		DEBUG(BYEL"\n\n\t\t\t\t   You have cross the limit You cannot login.\t\t\n\n"reset);
		exit(1);

	}
}


int main()
{
	//Function calls for required operation
	Title();
	Login();
	Menu();
	return 0;
}
