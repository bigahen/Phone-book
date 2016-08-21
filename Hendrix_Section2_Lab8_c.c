// Assignment #8: Phonebook #3
// Author: Austin Hendrix
// Date: 3/11/2016
// Section 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
	char firstName[25];
	char lastName[25];
	char phoneNumber[12];

}Contact;

Contact* addContact(Contact*, int*);
Contact* addContactWithInfo(Contact*, int*, char*, char*, char*);
void showContacts(Contact*, int*);
Contact* deleteContact(Contact*, int*);
void sortByFirst(Contact*, int*);
void sortByLast(Contact*, int*);
void showSingleContact(Contact*, int*);
void randomlyCall(Contact*, int*);
Contact* deleteAllContacts(Contact*, int*);
Contact* loadContactsFromFile(Contact*,int*);
void saveContactsToFile(Contact*,int*);

int main(){
	int choice=4, contactsNum = 0;
	Contact* contacts= (Contact*)malloc(sizeof(Contact));
	srand(time(NULL));
	do{
		printf("Phone Book Application\n");
		printf("\t1) Add Friend\n");
		printf("\t2) Delete Friend\n");
		printf("\t3) Show Phone Book\n");
		printf("\t4) Sort by First Name\n");
		printf("\t5) Sort by Last name\n");
		printf("\t6) Search by Name\n");
		printf("\t7) Randomly call friend\n");
		printf("\t8) Delete everyone\n");
		printf("\t9) Load contacts from file\n");
		printf("\t10) Save contacts to file\n");
		printf("\t0) Exit Application\n");
		scanf("%d",&choice);
		switch(choice){	//Switch statement which allows the user to choose what they would like to do
			
			case 1: 
				contacts = addContact(contacts,&contactsNum);	//adds a contact
				break;
			case 2:
				contacts = deleteContact(contacts,&contactsNum); //deletes a contact
				break;
			case 3:	
				showContacts(contacts,&contactsNum); //shows all contacts 
				break;
			case 4:
				sortByFirst(contacts,&contactsNum); //sort by first name
				break;
			case 5:
				sortByLast(contacts,&contactsNum); //sort by last name
				break;
			case 6:
				showSingleContact(contacts, &contactsNum); //shows single contact
				break;
			case 7:
				randomlyCall(contacts, &contactsNum);//calls a random number
				break;
			case 8:
				contacts = deleteAllContacts(contacts,&contactsNum); //deletes all the contacts 
				break;
			case 9:
				contacts = loadContactsFromFile(contacts,&contactsNum); //loads contacts from file
				break;			
			case 10:
				saveContactsToFile(contacts,&contactsNum); //save contacts to file
				break;
			case 0:
				printf("Thank you for using the Phone Book");
				break; 
					
			default:
				printf("Invalid Choice");
				break;
		}
			
		
	}while(choice != 0);
	
	free(contacts);
	
	return 0;
}

Contact* addContact(Contact* contacts, int* contactsNum){ //appends the array to contacts and then adds the new information for the new contact 
	
	Contact *temp = (Contact*)realloc(contacts,(*contactsNum+1)*sizeof(Contact));
	
	if(temp == NULL)
	{
		printf("OUT OF MEMORY");
		return(contacts);
	}
	contacts = temp;
	printf("Enter First Name: ");
	scanf("%s",contacts[*contactsNum].firstName);
	printf("Enter Last Name: ");
	scanf("%s", contacts[*contactsNum].lastName);
	printf("Enter Phone Number: ");
	scanf("%s", contacts[*contactsNum].phoneNumber);
	(*contactsNum) = *contactsNum + 1;
	printf("Contact added.\n");
	return contacts;
}

Contact* deleteContact(Contact* contacts, int* contactsNum){
	
	char toDeleteFirst[25], toDeleteLast[25];
	printf("First name: ");
	scanf("%s",toDeleteFirst);
	printf("Last name: ");
	scanf("%s", toDeleteLast);
	int i,x;
	for(i = 0; i < *contactsNum; i++){ //looping through all the contacts to look for a match
		
		if(strcmp(toDeleteFirst, contacts[i].firstName) == 0 && strcmp(toDeleteLast, contacts[i].lastName) == 0){
	
			for(x = i; x < *contactsNum; x++){ //in the event of a match, the member takes the information of the one after it
			
					strcpy(contacts[x].firstName, contacts[x+1].firstName);
					strcpy(contacts[x].lastName, contacts[x+1].lastName);
					strcpy(contacts[x].phoneNumber, contacts[x+1].phoneNumber);
				}
			
			
			Contact *temp = (Contact *) realloc(contacts, sizeof(Contact)*((*contactsNum)-1)); 
			
			(*contactsNum)--; 
			printf("Contact deleted.\n");
			return temp; 
			
		}
	}
	
	printf("Your entry did not match any contact.\n");
	return contacts;
}

void showContacts(Contact* contacts, int* contactsNum){ //prints all the contacts
	int i;
	for(i=0; i<(*contactsNum); i++){
		printf("%d. %s %s %s\n", (i+1), contacts[i].firstName, contacts[i].lastName, contacts[i].phoneNumber);
	}
}

void showSingleContact(Contact* contacts, int* contactsNum){ //uses a for loop to search for the given contact's information and print it out
	char firstName[25], lastName[25];
	printf("Enter first name: ");
	scanf("%s",firstName);
	printf("Enter last name: ");
	scanf("%s", lastName);
	int i;
	for(i = 0; i < *contactsNum; i++){
		if(strcmp(firstName, contacts[i].firstName) == 0 && strcmp(lastName, contacts[i].lastName) == 0){
			printf("Phone Number: %s\n",contacts[i].phoneNumber);
		}
	}
	
}

void sortByFirst(Contact* contacts, int* contactsNum){ //Uses bubble sort to sort by first name
	int swapped = 0;
	char firstName[25], lastName[25],phoneNum[12];
	int i;
	while(swapped == 0){
		swapped = 1;
		for(i = 1; i < *contactsNum; i++){
			if(strcmp(contacts[i-1].firstName,contacts[i].firstName)>0){
				
				strcpy(firstName, contacts[i-1].firstName);
				strcpy(lastName, contacts[i-1].lastName);
				strcpy(phoneNum, contacts[i-1].phoneNumber);
				
				strcpy(contacts[i-1].firstName, contacts[i].firstName);
				strcpy(contacts[i-1].lastName, contacts[i].lastName);
				strcpy(contacts[i-1].phoneNumber, contacts[i].phoneNumber);
				
				strcpy(contacts[i].firstName, firstName);
				strcpy(contacts[i].lastName, lastName);
				strcpy(contacts[i].phoneNumber, phoneNum);
				swapped = 0;
				
			}
		}
	}
	printf("Contacts sorted.\n");
}

void sortByLast(Contact* contacts, int* contactsNum){ //Uses buble sort to sort by last name
	int swapped = 0;
	char firstName[25], lastName[25],phoneNum[12];
	int i;
	while(swapped == 0){
		swapped = 1;
		for(i = 1; i < *contactsNum; i++){
			if(strcmp(contacts[i-1].lastName,contacts[i].lastName)>0){
				
				strcpy(firstName, contacts[i-1].firstName);
				strcpy(lastName, contacts[i-1].lastName);
				strcpy(phoneNum, contacts[i-1].phoneNumber);
				
				strcpy(contacts[i-1].firstName, contacts[i].firstName);
				strcpy(contacts[i-1].lastName, contacts[i].lastName);
				strcpy(contacts[i-1].phoneNumber, contacts[i].phoneNumber);
				
				strcpy(contacts[i].firstName, firstName);
				strcpy(contacts[i].lastName, lastName);
				strcpy(contacts[i].phoneNumber, phoneNum);
				swapped = 0;
				
			}
		}
	}
	printf("Contacts sorted.\n");
}

void randomlyCall(Contact* contacts, int* contactsNum){ //randomly chooses a contact to call
	int r = rand()%*contactsNum;
	printf("Calling %s %s... Number - %s\n",contacts[r].firstName, contacts[r].lastName, contacts[r].phoneNumber);
}

Contact* deleteAllContacts(Contact* contacts, int* contactsNum){ //clears the array of contacts
	free(contacts);
	Contact* temp= (Contact*)malloc(sizeof(Contact));
	*contactsNum = 0;
	printf("All contacts deleted.\n");
	return temp;
	
}

Contact* loadContactsFromFile(Contact* contacts, int* contactsNum){ //loads contacts from the file
	printf("Enter your desired file path (Enter \"default\" for default path): ");
	char path[150];
	scanf("%s",path);
	FILE *pRead;
	if(strcmp(path,"default")==0){
		pRead = fopen("C:\\Users\\bigah\\Desktop\\PhoneBook.txt","r");
	}else{
		pRead = fopen(path,"w");
	}
	
	char firstName[25],lastName[25],phoneNumber[12];
	
	while(!feof(pRead)){
		fscanf(pRead,"%s",firstName);
		fscanf(pRead,"%s",lastName);
		fscanf(pRead,"%s",phoneNumber);
		contacts = addContactWithInfo(contacts,contactsNum,firstName,lastName,phoneNumber);
	}
	fclose(pRead);
	return contacts;
}

Contact* addContactWithInfo(Contact* contacts, int* contactsNum, char* firstName, char* lastName, char* phoneNumber){ //adds contacts with the information from the file
	Contact *temp = (Contact*)realloc(contacts,(*contactsNum+1)*sizeof(Contact));
	
	if(temp == NULL)
	{
		printf("OUT OF MEMORY");
		return(contacts);
	}
	contacts = temp;
	strcpy(contacts[*contactsNum].firstName, firstName);
	strcpy(contacts[*contactsNum].lastName, lastName);
	strcpy(contacts[*contactsNum].phoneNumber, phoneNumber);
	(*contactsNum) = *contactsNum + 1;
	printf("Contact added.\n");
	return contacts;
}

void saveContactsToFile(Contact* contacts, int* contactsNum){ //saves all current contacts to the file
	
	printf("Enter your desired file path (Enter \"default\" for default path): ");
	char path[150];
	scanf("%s",path);
	FILE *pWrite;
	if(strcmp(path,"default")==0){
		pWrite = fopen("C:\\Users\\bigah\\Desktop\\PhoneBook.txt","w");
	}else{
		pWrite = fopen(path,"w");
	}

	if(pWrite==NULL){
		
	}else{
		int i;
		for(i = 0; i < *contactsNum;i++){
			fprintf(pWrite,"%s %s %s",contacts[i].firstName,contacts[i].lastName,contacts[i].phoneNumber);
			if(i != (*contactsNum-1)){
				fprintf(pWrite,"\n","");
			}
		}
	}
	fclose(pWrite);
}
