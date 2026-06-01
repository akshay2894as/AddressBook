// AKSHAY SATISH SURYAVANSHI
// Date: 28/04/2026
// Batch: ECEP 26001B
// Description: ADDRESSBOOK

#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fp;  // File pointer

    // Open file in write mode
    if((fp = fopen("contacts.txt","w+")) == NULL)
    {
        printf("File Not Found\n");
        return;
    }

     // Write each contact in CSV format
    for(int i = 0; i < addressBook -> contactCount; i++)
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(fp); // Close file
    printf("\n*************************************************************************************\n");
    printf("|                            SAVED SUCCESSFULY                                      |\n");
    printf("*************************************************************************************\n");
  
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp;  // File pointer
    
    // Open file in read mode
    if((fp = fopen("contacts.","r")) == NULL)
    {
        printf("File Not Found\n");
        return;
    }
    
     // Read contact details until end of file
    while((fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[addressBook -> contactCount].name,
                                addressBook->contacts[addressBook -> contactCount].phone,
                                addressBook->contacts[addressBook -> contactCount].email)) == 3)
        {
            addressBook->contactCount++; // Increment contact count
        }
        fclose(fp);  // Close file
}
