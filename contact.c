#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
// #include "populate.h"

int arr[100];   // stores matched contact indexes
int mapcount = 0;   // number of matched results

// display all contacts
void listContacts(AddressBook *addressBook) 
{
    if(addressBook->contactCount == 0)
    {
        printf("No Contact Available!\n");
        return;
    }
    printf("\n------------------------------------------------------------------------------------\n");
    printf("%-5s %-20s %-15s %-30s\n", "S.No","Name", "Phone", "Email");
    printf("\n------------------------------------------------------------------------------------\n");

    for(int i=0; i<addressBook->contactCount; i++)
    {
        printf("%-5d %-20s %-15s %-30s\n", i+1, 
            addressBook->contacts[i].name, 
            addressBook->contacts[i].phone, 
            addressBook->contacts[i].email);
    }

    printf("\n------------------------------------------------------------------------------------\n");
    
}

// initialize address book
void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

// print single contact
void printcontact(int s,Contact *c)
{
     printf("%d. Name: %s | Phone: %s | Email: %s\n", s+1, c->name, c->phone, c->email);
}
    


void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

// validate name
int isvalidname(char *name)
{
    for(int i=0; name[i] != '\0';i++)
    {
        if(!((name[i]>= 'a' && name[i]<= 'z') || (name[i]>= 'A' && name[i]<= 'Z') || (name[i]==' ')))
        {
            return 0;
        }
    }

    return 1;
}

// validate phone
int isvalidphone(char *phone)
{
    int len=strlen(phone);

    if(len != 10)
        return 0;

    if(phone[0] < '6' || phone[0] > '9')
        return 0;

    for(int i = 0; i < len; i++)
    {
        if(phone[i] >= '0' && phone[i] <= '9')
        {

        }
        else
            return 0;
    }

    return 1;
}

// validate email
int isvalidemail(char *email)
{
    int count=0;
    if(email[0] >='0' && email[0] <='9')
        return 0;


    for(int i = 0; email[i] !='\0'; i++)
    {
        if(email[i]=='@')
            count++;

        if(email[i] >= 'A' && email[i] <= 'Z')
            return 0;
    }

    if(count != 1)
        return 0;

    if(strstr(email,".com") == NULL)
        return 0;

    return 1;
}
// check if phone already exists
int isphoneexist(AddressBook *addressBook,char *phone){
for (int i = 0; i < addressBook->contactCount; i++) {
    if (strcmp(addressBook->contacts[i].phone,phone) == 0) {   
        return 1;
    }
}
  return 0;
}
// check if email already exists
int isemailexist(AddressBook *addressBook,char *email){
for (int i = 0; i < addressBook->contactCount; i++) {
    if (strcmp(addressBook->contacts[i].email,email) == 0) {   
        return 1;
    }
}
  return 0;
}

// create new contact
void createContact(AddressBook *addressBook)
{
    char name[50];
    char phone[20];
    char email[50];

    int attempt=0;

    while(attempt < 3)
    {
	    printf("Enter the Name: ");
        scanf(" %[^\n]", name);

        if(isvalidname(name))
            break;

        printf("Invalid Name! Only alphabets allowed.\n");
        attempt++;

        if(attempt==3)
        {
            printf("Too many invalid attempts. creation cancelled\n");
            return;
        }
    }

    attempt = 0;
    while(attempt < 3)
    {
        printf("Enter Phone Number: ");
        scanf(" %s", phone);

        if(isvalidphone(phone))
            break;

        else
        {
            printf("Invalid Phone! Must be 10 digits and start from 6 to 9.\n");
            attempt++;
        }

        if(attempt==3)
        {
            printf("Too many invalid attempts. creation cancelled\n");
            return;
        }
    }

    attempt = 0;
    while(attempt < 3)
    {
        printf("Enter your email_id: ");
        scanf(" %[^\n]", email);

        if(isvalidemail(email))
            break;

        printf("Invalid email!\n");
            attempt++;
        
        if(attempt==3)
        {
            printf("Too many invalid attempts. creation cancelled\n");
            return;
        }
    }

    if(addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address book is full!\n");
        return;
    }
    strcpy(addressBook -> contacts[addressBook -> contactCount].name, name);
    strcpy(addressBook -> contacts[addressBook -> contactCount].phone, phone);
    strcpy(addressBook -> contacts[addressBook -> contactCount].email, email);
    addressBook -> contactCount++;
    printf("Contact added successfully!\n");
}

// search by name
void searchbyname(AddressBook *addressBook)
{
    char name[50];
    int attempts = 0;
    mapcount = 0;  

    while(attempts < 3)
    {
        printf("Enter Name: ");
        scanf(" %[^\n]", name);

        if(isvalidname(name))
            break;

        printf("Invalid Name!\n");
        attempts++;
    }

    if(attempts == 3)
        return;

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(name, addressBook->contacts[i].name) == 0)
        {
            printcontact(mapcount, &addressBook->contacts[i]);
            arr[mapcount] = i;
            mapcount++;
        }
    }

    if(mapcount == 0)
        printf("Contact not found!\n");
}

// search by phone number
void searchbyphone(AddressBook *addressBook)
{
    char phone[20];
    int attempts = 0;
    mapcount = 0;  

    while(attempts < 3)
    {
        printf("Enter your Phone Number: ");
        scanf(" %[^\n]", phone);

        if(isvalidphone(phone))
            break;

        printf("Invalid phone no!\n");
        attempts++;
    }

    if(attempts == 3)
        return;

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            printcontact(mapcount, &addressBook->contacts[i]);
            arr[mapcount] = i;
            mapcount++;
        }
    }

    if(mapcount == 0)
        printf("Contact not found!\n");
}

// search by email
void searchbyemail(AddressBook *addressBook)
{
    char email[50];
    int attempts = 0;
    mapcount = 0;  

    while(attempts < 3)
    {
        printf("Enter your Email_id: ");
        scanf(" %[^\n]",email);

        if(isvalidemail(email))
            break;

        printf("Invalid email!\n");
        attempts++;
    }

    if(attempts == 3)
        return;

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(email, addressBook->contacts[i].email) == 0)
        {
            printcontact(mapcount, &addressBook->contacts[i]);
            arr[mapcount] = i;
            mapcount++;
        }
    }

    if(mapcount == 0)
        printf("Contact not found!\n");
}

// menu for searching the contact
void searchContact(AddressBook *addressBook) 
{
    printf("1.Search by Name.\n");
    printf("2.Search by Phone number.\n");
    printf("3.Search by Email_id.\n");
    int choice;
    int index, found=0;
    printf("Enter your choice:");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
            searchbyname(addressBook);
            break;
        case 2:
            searchbyphone(addressBook);
            break;
        case 3:
            searchbyemail(addressBook);
            break;
        default:
            printf("Invalid choice!\n");
    }
    
}

// editing the contact details
void editContact(AddressBook *addressBook)
{
    searchContact(addressBook);
    if(mapcount==0)
    return; 
    int attempts=0;
    int serial;
    while(attempts<3){
    printf("Enter your choice to edit contact: ");
        scanf("%d", &serial);

        if(serial >= 1 && serial <= mapcount)
            break;

        printf("Invalid Choice!\n");
        attempts++;
    }
    if(attempts == 3)
    {
        printf("Too many invalid attempts!\n");
        return;
    }
    int index = arr[serial - 1];
    int choice;
    printf("\nEdit Contact:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Exit\n");
    printf("Enter  your choice: ");
    scanf("%d", &choice);
   attempts=0;

   switch(choice)
   {
    case 1:{
        char name[30];
            while(attempts < 3)
            {
                printf("Enter the name to update: ");
                scanf(" %[^\n]", name);

                if(isvalidname(name))
                {
                    strcpy(addressBook->contacts[index].name, name);
                    printf(" Your Name has been updated successfully!\n");
                    return;
                }
                printf("Invalid Name!\n");
                attempts++;
            }
            break;
    }
    case 2:{
        char phone[20];
        while(attempts<3)
        {
            printf("Enter new Phone Number to be update: ");
            scanf("%s",phone);
            if(isvalidphone(phone))
            {
                strcpy(addressBook->contacts[index].phone,phone);
                printf("Your Phone Number is updated successfully\n");
                return;
            }
            printf("Invalid Phone Number!\n");
        }
        break;
    }
    case 3:{
        char email[30];
            while(attempts < 3)
            {
                printf("Enter new email to update: ");
                scanf("%s", email);

                if(isvalidemail(email))
                {
                    strcpy(addressBook->contacts[index].email, email);
                    printf("Your Email has been Updated Successfully!\n");
                    return;
                }
                printf("Invalid Email!\n");
                attempts++;
            }
            break;
    }
    case 4:
       return;

    default:
     printf("Invalid choice!\n");
      return;
   }
    printf("Too many invalid attempts!\n");
    
}

// deleting the contact
void deleteContact(AddressBook *addressBook)
{
	searchContact(addressBook);
    if(mapcount==0)
    return;

    int serial,attempts=0;
    while(attempts<3){
        printf("Enter the Contact to delete: ");
        scanf("%d",&serial);
        if(serial >= 1 && serial <= mapcount)
            break;

        printf("Invalid Choice!\n");
        attempts++;
    }
    if(attempts == 3)
    {
        printf("Too many invalid attempts!\n");
        return;
    }

    int index = arr[serial - 1];  
    for(int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("Contact Deleted Sccessfully!\n");
   
}
