/*************************************************************************************************************************************
** Name                 : Rajesh jonnalgadda.
** Date                 : 13/08/2024.
** 
** @File	            : contact.c
** 
** Description 			: This file consist of functions definitions for each and every operations uwed in this project.
** 
**
***********************************************************************************************************************************/

#include "Include/contact.h"
#include "Include/populate.h"
#include "Include/colour.h"
#include "Include/file.h"

//Global variable 
static char Phone[11];
static char Gmail[20];

//Checking data already existed or not 
int Existed_or_Not(AddressBook *addressBook,char member[]){
	return search_by_Member(addressBook,member);
}

//Input phone number from the user
char Enter_Phone_Number(AddressBook *addressBook,char Phone[])
{	
	int phone_flag =1;
	int comparing_flag;
	
	while(phone_flag)
	{
		char phone[11];
		fflush(stdin);
		scanf("%s",phone);
	if(strlen(phone) > 10)
	{
		DEBUG(BYEL"\n\tEnter only ten numbers:\n"reset);
		DEBUG(BGRN"\nENter Phone Number:\n"reset);
	}else if(strlen(phone) <10)
	{
		DEBUG(BYEL"\n\tEnter upto 10 numbers:\n"reset);
		DEBUG(BGRN"\nEnter Phone Number:\n"reset);
	}
	
	if(strlen(phone) == 10)
	{	
		for(int i=0;i<10; i++)
		{
			if(phone[i] >= '0' && phone[i] <= '9')
			{
				comparing_flag = 1;
			}else
			{
				comparing_flag =0;
				break;
			}
		}

		if(comparing_flag == 0 )
		{
			 DEBUG(BYEL"\n\tEnter only numbers :\n"reset);
			 DEBUG(BBLU"\nEnter Phone Number : ");
		}
		if(comparing_flag == 1)
		{		
			int existed_or_not;
        	existed_or_not = Existed_or_Not(addressBook,phone); //checking already exist or not 
			if(existed_or_not == 0) 
			{
				DEBUG(BYEL"\n\t\tPhone number already exists. "reset BGRN"\n\nPlease enter a new number = ");
			}else{
		    	strcpy(Phone,phone);
		    	phone_flag = 0;
			}
         }
	}
	}
}


//Inpur email from the user
char Enter_Gmail(AddressBook *addressBook,char Gmail[])
{
 	const char *symbol = "@";
 	const char *dotcom = ".com";
	char gmail[25];
	int email_flag = 1;	
	while(email_flag)
	{
		DEBUG(BGRN"\n\nEnter Input Gmail :"reset);
		DEBUG(BYEL"\n\t\t\tMake sure Have you entered only lower case letters or not ?\n\t\t\t Enter Email In This Format ___@___.com\n"reset);
		fflush(stdout);
		scanf("%s",gmail);
		
		char *symbol_exist_or_not = strstr(gmail,symbol);	
		if(symbol_exist_or_not == NULL){
			DEBUG(BYEL"\n\t @symbol is missing in the Entered Email"reset);	
		}
			
		char *dotcom_exist_or_not = strstr(gmail,dotcom);
		if(dotcom_exist_or_not == NULL){
			DEBUG(BYEL"\n\t.com symbol is missing in the Entered Email"reset);
		}
	
		if((symbol_exist_or_not != NULL) && (dotcom_exist_or_not != NULL))
		{	
			int existed_or_not;
			existed_or_not = Existed_or_Not(addressBook,gmail); //checking already exist or not 
			if(existed_or_not == 0){
				DEBUG(BYEL"\n\tAlready_existed\n"reset);
				fflush(stdin);
			}else{
				strcpy(Gmail,gmail);
				DEBUG(BYEL"\n\t\tNot existed\n"reset);
				email_flag =0;
			}
		}
	}
}

//Edit the data by which member you want  
void Edit_by_Member(AddressBook *addressBook,char edit_by_member[],int serial_number){
	enum edit_criteria;
	int edit_by_name_choice;
	DEBUG(BMAG"\nWhat do you want to edit of %s Details ?\n",edit_by_member);
	DEBUG("\n\t1.Edit_only_Name\n\t2.Edit_only_Phone\n\t3.Edit_only_Email\n\t4.Edit_Whole_data\n\nOption : "reset);
	edit_by_name_choice = getIntegerInput();
	switch(edit_by_name_choice){
		case e_edit_by_name:{
				DEBUG(BMAG"Enter New Name for the contact : "reset);
				scanf("%[^\n]",addressBook->contacts[serial_number-1].name);
				break;
			}
		case e_edit_by_phone:{
				char phone[11];
				DEBUG(BMAG"Enter New Number for the contact : "reset);
				Enter_Phone_Number(addressBook,phone);
				strcpy(addressBook->contacts[serial_number-1].phone,phone);
				break;
			}
		case e_edit_by_email:{
				char gmail[20];
				DEBUG(BMAG"Enter New Email for the contact : "reset);
				Enter_Gmail(addressBook,gmail);
				strcpy(addressBook->contacts[serial_number-1].email,gmail);
				break;
			}
		case e_edit_whole_data:{
				DEBUG(BMAG"Enter New Name for the contact : "reset);
				scanf("%[^\n]",addressBook->contacts[serial_number-1].name);
				
				char phone[11];
			 	DEBUG(BMAG"Enter New Number for the contact : "reset);
				Enter_Phone_Number(addressBook,phone);
				strcpy(addressBook->contacts[serial_number-1].phone,phone);
				
				char gmail[20];
				DEBUG(BMAG"Enter New Email for the contact : "reset);
				Enter_Gmail(addressBook,gmail);
				strcpy(addressBook->contacts[serial_number-1].email,gmail);
				break;
			}
		default:{
				DEBUG(BMAG"INVALID CHOICE FOR EDIT OPTION OF %s EDit_by_name",edit_by_member);
				DEBUG(""reset);
				break;
			}
	}
}

//Taking only input values from the user 

int getIntegerInput(){
    int input;
    char buffer[100];
    while (1) 
	{
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
		{	
			if (sscanf(buffer, "%d", &input) == 1) //Check if the input can be converted to an integer  
			{
				return input;
			}else 
			{
                		DEBUG(BYEL"\n\t\tPlease enter only integer values.\n"reset);
						DEBUG(BBLU"\nEnter your Option : "reset);
            }
        }
    }
}


//Display the contacts as per criteria
void listContacts(AddressBook *addressBook, int sortCriteria) {
    // Sort contacts based on the chosen criteria
	enum list_criteria;
	DEBUG(BCYN"");	
	switch(sortCriteria){
		case e_list_by_name :{
			//List data by the Name
			char list_by_name[25];
			int flag;
			DEBUG("Enter input Name to list : ");
			scanf("%[^\n]",list_by_name);
			flag = Search_by_Member(addressBook,list_by_name);
			if(flag ==1){
				DEBUG(BWHT"\n\nEntered %s Name is Not Found in the Data\n",list_by_name);
				DEBUG(""reset);
			}
			break;
		}
		case e_list_by_phone:{
			//List by phone
			char list_by_phone[25];
			int flag;
			scanf("%[^\n]",list_by_phone);
			flag = Search_by_Member(addressBook,list_by_phone);
			if(flag ==1){
				DEBUG(BWHT"\n\nEntered %s Phone_Number is Not Found in the Data\n",list_by_phone);
				DEBUG(""reset);
			}
			break;
		}
		case e_list_by_email:{
			char list_by_email[25]; //List by email
			int flag;
			scanf("%[^\n]",list_by_email);
			flag = Search_by_Member(addressBook,list_by_email);
			if(flag ==1){
				DEBUG(BWHT"\n\nEntered %s Email is Not Found in the Data\n",list_by_email);
				DEBUG(""reset);
			}
			break;
		}
		case e_list_whole_data:{
			List_by_Whole_Data(addressBook);	//List whole Data 
			break;
		}
		default:{
			DEBUG(BRED"\nInvalid Choice For View The Data"reset);
			break;
		}
	}
}

//Searching the stracture present or not member 
int Search_by_Member(AddressBook *addressBook,char search_by_member[]) {
	int flag=1;
	DEBUG(BRED"\n-------------------------------------------------------------------------------------------------"reset);
	DEBUG(BYEL"\n  Serial_Number\t    Name\t  \tMobile_Number\t    Email\n"reset);
	DEBUG(BRED"-------------------------------------------------------------------------------------------------"reset);
	for(int i=0;i<addressBook->contactCount;i++){
		if(strstr(addressBook->contacts[i].name,search_by_member) !=NULL){
			flag =0;
			DEBUG(BWHT"\n%-20d%-20s%-20s%-20s",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
		}else if(strstr(addressBook->contacts[i].phone,search_by_member) != NULL){
			flag =0;
			DEBUG(BWHT"\n%-20d%-20s%-20s%-20s",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			
		}else if (strstr(addressBook->contacts[i].email,search_by_member) != NULL){
			flag =0;
			DEBUG(BWHT"\n%-20d%-20s%-20s%-20s",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			DEBUG(""reset);
		}
	}
	DEBUG(BRED"\n\n-------------------------------------------------------------------------------------------------"reset);
		return flag;
}

//Searching the stracture present or not member 
int search_by_Member(AddressBook *addressBook,char search_by_member[]){
	int flag=1;
	fflush(stdout);
	for(int i=0; i<addressBook->contactCount; i++){
		if(strcmp(addressBook->contacts[i].phone,search_by_member)==0){
			flag = 0;
		}else if(strcmp(addressBook->contacts[i].email,search_by_member)==0){
			flag =0;
		}
	}
		return flag;
}

//DIsplay the whole data of the contacts 
void List_by_Whole_Data(AddressBook *addressBook)
{
	DEBUG(BRED"\n---------------------------------------------------------------------------------------------------\n");
    DEBUG(BWHT"\n\tTotal number of contacts: %d\n", addressBook->contactCount);
	DEBUG(" "reset);
	DEBUG(BRED"\n---------------------------------------------------------------------------------------------------\n"reset);
	DEBUG(BYEL"\n Serial_Number\t\tName\t\t   Mobile_Number\t\tEmail\n"reset);
	DEBUG(BRED"\n---------------------------------------------------------------------------------------------------\n"reset);
	for (int i=0; i<addressBook->contactCount; i++){
	DEBUG(BWHT"\n %-20d\t%-20s%-20s\t%-20s",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	DEBUG(""reset);
	}
	DEBUG(BRED"\n---------------------------------------------------------------------------------------------------\n"reset);
}

//Initilize the input data to stracture 
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

//Save the contents to the file
void save(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
}

//Create the new contact 
void createContact(AddressBook *addressBook){
	int no_of_data = 1;
	int existed_or_not;

#if 0
   	DEBUG(BWHT"\n\tTotal Contact data Present in Structure is : %d \n",addressBook->contactCount);
	DEBUG(""reset);
	DEBUG("\n\nHow many entry do you want to add = ");
	no_of_data = getIntegerInput();
#endif
	
	sum_of_data = no_of_data + addressBook->contactCount; 

	for(int i=addressBook->contactCount; i<sum_of_data; i++)
    	{
		fflush(stdout);
		DEBUG(BGRN"\nEnter First Name = "reset);
		scanf("%[^\n]",addressBook->contacts[i].name);
		
		fflush(stdout);
		DEBUG(BGRN"Enter Phone Number = "reset);
		Enter_Phone_Number(addressBook,Phone);
		strcpy(addressBook->contacts[i].phone,Phone);

		fflush(stdout);	
		Enter_Gmail(addressBook,Gmail);
		strcpy(addressBook->contacts[i].email,Gmail);
		addressBook->contactCount++;

    	}

}

//Search the contact as per chossen criteria
void searchContact(AddressBook *addressBook) {
    /* Define the logic for search */
    enum search_criteria;
	int searchCriteria;
    DEBUG(BCYN"\nBy which Member you want to search :\n");
    DEBUG("\t1.Search_by_Name\n\t2.Searh_by_Mobile_Number\n\t3.Search_by_Email\n\nOption : ");
    searchCriteria = getIntegerInput();
	switch(searchCriteria){
		case e_search_by_name:{
			//Search by the Name
			static char search_by_name[25];
			int flag;
			DEBUG("Enter the Name to search : \n");
			scanf("%[^\n]",search_by_name);	
			flag = Search_by_Member(addressBook,search_by_name);
			if(flag == 1){
				DEBUG(BYEL"\n\n\tEntered %s Name is Not Found in the data",search_by_name);
				DEBUG(""reset);
			}	
			break;
		}
		case e_search_by_phone:{
			//Search by phone
			static char search_by_phone[25];
			int flag;
			DEBUG("Enter the Phone Number to search : \n");
			scanf("%[^\n]",search_by_phone);
			flag = Search_by_Member(addressBook,search_by_phone);
			if(flag == 1){
				DEBUG(BYEL"\n\n\tEntered %s Name is Not Found in the data",search_by_phone);
				DEBUG(""reset);
			}	
			break;
		}
		case e_search_by_email:{
			//Search by email
			static char search_by_email[25];
			int flag;
			DEBUG("Enter the Email to search : \n");
			scanf("%[^\n]",search_by_email);
			flag = Search_by_Member(addressBook,search_by_email);
			if(flag == 1){
				DEBUG(BYEL"\n\n\tEntered %s Name is Not Found in the data",search_by_email);
				DEBUG(""reset);
			}	
			break;
		}
		default:{
			DEBUG(BRED"\nInvalid Choice For Search The Data"reset);
			break;
		}
	}
}

void editContact(AddressBook *addressBook){
	/* Define the logic for Editcontact */
	enum edit_criteria;
	int editCriteria;
    DEBUG(BGRN"By which Member you want to Edit  :\n");
    DEBUG("\n\t1.Edit_by_Name\n\t2.Edit_by_Mobile_Number\n\t3.Edit_by_Email\n\nEnter you Option : ");
    editCriteria = getIntegerInput();
	switch(editCriteria){
		case e_edit_by_name:{
			//Edit by the Name
			static char edit_by_name[50];
			int flag;
			DEBUG(BGRN"Enter the Name to Edit : \n");
			scanf("%[^\n]",edit_by_name);
			flag = Search_by_Member(addressBook,edit_by_name);
			if(flag != 1)
			{
				int serial_number;
				DEBUG("\n\nEntered %s name is found in the Data\n",edit_by_name);
				DEBUG("\nEnter the Serial number of the contact its already diaplayed in the console \n");
		DEBUG(BYEL"\n\nBe carefull if you Entered the serial number wrongly it will Edit unwanted data and you can't Get the data you want"reset);
			
				serial_number = getIntegerInput();
				if(serial_number == 0)
				{
					DEBUG(BYEL"\n\t\tSerial Number starts from 1 only you Entered wrong Serial Number\n\t\t"reset);
				}else
				{
					Edit_by_Member(addressBook,edit_by_name,serial_number);	
				}	
				
			}else
			{
				DEBUG(BGRN"\n\n\tEntered %s Name is not in Found the Data to Edit\n",edit_by_name);
				DEBUG(""reset);
			}
			break;
		}
		case e_edit_by_phone:{
			//Search by phone
			
			static char edit_by_phone[25];
			int flag;
			DEBUG(BGRN"\nEnter the Phone Number to Edit : \n");
			scanf("%[^\n]",edit_by_phone);
			flag = Search_by_Member(addressBook,edit_by_phone);
			if(flag !=1){
				int serial_number;
				
				DEBUG("\n\nEntered %s Phone Number is found in the existing data :\n",edit_by_phone);
				DEBUG("\n\tEnter the Serial number of the contact its already diaplayed in the console \n");
				DEBUG(BYEL"\n\nBe carefull if you Entered the serial number wrongly it will Edit unwanted data and you can't Get the data you want"reset);
				serial_number = getIntegerInput();			
				
				if(serial_number == 0){
					DEBUG(BYEL"\n\t\tSerial Number starts from 1 only you Entered wrong Serial Number\n\t\t"reset);
				}else{
					Edit_by_Member(addressBook,edit_by_phone,serial_number);	
				}
			}else{
				DEBUG(BGRN"\n\n\tEntered %s Phone_Numberis not in Found the Data to Edit\n",edit_by_phone);
				DEBUG(""reset);
			}
			break;
		}
		case e_edit_by_email:{
			//Edit by email
			static char edit_by_email[25];
			int flag;
			DEBUG("\nEnter the Email to Edit : \n");
			scanf("%[^\n]",edit_by_email);
			flag = Search_by_Member(addressBook,edit_by_email);
			if(flag !=1){
				int serial_number;
				DEBUG("\nEntered %s Email is found in the existing data :\n\n",edit_by_email);
				DEBUG(BYEL"\n\nEnter the Serial number of the contact its already diaplayed in the console \n"reset);
				DEBUG(BYEL"\n\nBe carefull if you Entered the serial number wrongly it will Edit unwanted data and you can't Get the data you want"reset);
				serial_number = getIntegerInput();		
				if(serial_number == 0){
					DEBUG(BYEL"\n\t\tSerial Number starts from 1 only you Entered wrong Serial Number\n\t\t"reset);
				}else{
					Edit_by_Member(addressBook,edit_by_email,serial_number);
				}
			}else{
				DEBUG(BGRN"\n\n\tEntered %s Email is not in Found the Data to Edit\n",edit_by_email);
				DEBUG(""reset);
			}
			break;
		}
		default:
		{
			DEBUG(BRED"\nInvalid Choice For Edit The Data"reset);
			break;
		}
	}

}

//Delete the contact as per you requirement 
void deleteContact(AddressBook *addressBook) {
    enum delete_criteria;
	int deleteCriteria;
    int flag;
    DEBUG(BGRN"\nDelete By\n\t1. Delete_by_Name\n\t2. Delete_by_Phone\n\t3. Delete_by_Email\n"reset);
    DEBUG(BGRN"Choose option to Delete: "reset);
    deleteCriteria = getIntegerInput();
    switch (deleteCriteria)
   	{
		case e_delete_by_name:{
            // Delete the Element by its Name
            static char delete_name[50];
            DEBUG(BGRN"\nEnter the input Name to Delete the data: "reset);
            scanf(" %[^\n]", delete_name);
            flag = Search_by_Member(addressBook, delete_name);
			if (flag == 0) {
				int serial_number;
				DEBUG(BGRN"\n\nEnter %s Name is found in the Existing data \n",delete_name);
				DEBUG(BGRN"Enter the Serial number of the contact its already diaplayed in the console \n"reset);
				DEBUG(BYEL"\n\nBe carefull if you Entered the serial number wrongly it will delete unwanted data and you can't get it back"reset);

				serial_number = getIntegerInput();			
				if(serial_number == 0){
					DEBUG(BYEL"\n\t\tSerial Number starts from 1 only you Entered wrong Serial Number\n\t\t"reset);
				}else{
					Delete_by_Member(addressBook,delete_name,serial_number);	
				}
			}else{
				DEBUG(BYEL"Element is not found in the data\n"reset);
			}
			break;
		}
        case e_delete_by_phone: {
            // Delete the Element by its Phone
            static char delete_phone[15];
            DEBUG(BGRN"\nEnter the input Phone to Delete the data: ");
            scanf(" %[^\n]", delete_phone);
            
            flag = Search_by_Member(addressBook, delete_phone);
                        
            if (flag == 0){
				int serial_number;
				DEBUG("Enter %s Name is found in the Existing data \n",delete_phone);
				if(serial_number){
					DEBUG(BGRN"Enter the Serial number of the contact its already diaplayed in the console \n"reset);
					DEBUG(BYEL"\n\nBe carefull if you Entered the serial number wrongly it will delete unwanted data and you can't get it back"reset);
					serial_number = getIntegerInput();
					if(serial_number == 0){
						DEBUG(BYEL"\n\t\tSerial Number starts from 1 only you Entered wrong Serial Number\n\t\t"reset);
					}else{
						Delete_by_Member(addressBook,delete_phone,serial_number);
					}
				}else{
							DEBUG(BYEL"Enter number Start from 1 only"reset);
				}
			 }else{
                DEBUG(BYEL"\nElement is not found in the data\n"reset);
			 }
            break;    
        }
        case e_delete_by_email:{
            // Delete the Element by its Email
            char delete_email[50];
            DEBUG(BGRN"Enter the input Email to Delete the data: "reset);
            scanf(" %[^\n]", delete_email);
            flag = Search_by_Member(addressBook, delete_email);
            if (flag == 0){
				int serial_number;
				DEBUG(BWHT"\n\t\tEnter %s Name is found in the Existing data \n",delete_email);
				DEBUG(""reset);
				DEBUG(BYEL"\nEnter the Serial number of the contact its already diaplayed in the console \n"reset);
				DEBUG(BYEL"\n\nBe carefull if you Entered the serial number wrongly it will delete unwanted data and you can't get it back"reset);
				serial_number = getIntegerInput();
					if(serial_number == 0)
					{
						DEBUG(BYEL"\n\t\tSerial Number starts from 1 only you Entered wrong Serial Number\n\t\t"reset);
					}else{
						Delete_by_Member(addressBook,delete_email,serial_number);
					}
			}else{
                DEBUG(BGRN"Element is not found in the data\n"reset);
            }
            break;    
        }
        default: {
            DEBUG(BRED"\nInvalid choice for delete option \n"reset);
        }
	}
}

//Delete by member 
void Delete_by_Member(AddressBook *addressBook, char delete_member[],int serial_number){
	int new_serial_number = serial_number - 1;
    for (int i = 0; i < addressBook->contactCount; i++){
		    for (int j = new_serial_number; j < addressBook->contactCount; j++) {
		        addressBook->contacts[j] = addressBook->contacts[j + 1];
		    }
			addressBook->contactCount = addressBook->contactCount-1;
		  	DEBUG(BYEL"\n\nContact deleted successfully.\n"reset);
		   	return;
     }
    DEBUG(BYEL"\n\nError in deleting contact.\n"reset);
}
