/*
Author : Goran Vujnovic
Project Name : Phonebook using linked list
Date created : 29/08/2023
Description : By using this file we can save contacts and do these operations in it.
   0) stop the program
   1) load users
   2) add a user to list
   3) view all users
   4) remove a user from list
*/


// Included the headers
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>


// Macro definitions
#define stop_the_program           0
#define load_users                 1
#define add_a_user_to_list         2
#define view_all_users             3
#define remove_a_user_from_list    4


// Global variables.
const char* filename = "Format_Imenika.txt";


// Defining user data type.
typedef struct
 {
	char name[20];
	char surname[20];
	int number;

 }User;

typedef struct List
 {
	 User date;
	struct List *next;

 }List;

 // Pointer to the first element of the list (global variable).
List *head = NULL;


// All function prototypes.
void Print_menu();
int Stop_the_program();
void Load_users();
int Adding_users_to_the_list();
void View_all_users();
void Add_a_user();
int Add_new_user_in_txt();
void Remove_a_user_from_list();


// This will print main menu.
void Print_menu()
 {
    printf("\n\n");
    printf("\t\t****************************************************************\n");
    printf("\t\t*                  Welcome TO My phone book                    *\n");
    printf("\t\t****************************************************************\n\n");
    printf("\t\t\t0) Stop the program\n\n");
    printf("\t\t\t1) Load users\n\n");
    printf("\t\t\t2) Add a user to list\n\n");
    printf("\t\t\t3) View all users\n\n");
    printf("\t\t\t4) Remove a user from list\n\n");
    printf("\t\t\t\tEnter your Choice : ");
    fflush(stdout);
 }


// This function will stop the program.
int Stop_the_program()
{
	printf("\n\n");
	printf("\n\t\t\t\t******************************************************************************\n");
	printf("\t\t\t\t*                  Program is stopped!                                       *\n");
	printf("\t\t\t\t*                  You have to restart the program...                        *\n");
	printf("\t\t\t\t******************************************************************************\n\n\n");
	fflush(stdout);

	return 1; // return error code 1
}


// This function loads users from a .txt file in binary format
void Load_users(const char* filename)
 {
	FILE *file;

	file = fopen("Format_Imenika.txt", "rb");

	if(file == NULL)
	   	{
	   		printf("\n\t\t\t\t******************************************************************************\n");
	   	        printf("\t\t\t\t*                   Error opening the file for reading!                       *\n");
	   		printf("\t\t\t\t******************************************************************************\n\n\n");

	   	}

	User user;

	while((fread(&user, sizeof(User), 1, file) == 1))
	{
		Adding_users_to_the_list(user.name, user.surname, user.number);

	}
	fclose(file);

	printf("\n\t\t\t\t******************************************************************************\n");
	printf("\t\t\t\t*                  You have successfully loaded users                        *\n");
 	printf("\t\t\t\t******************************************************************************\n\n\n");
 }


// This function adding users to the list.
int Adding_users_to_the_list(char *name, char *surname, int number)
 {
	List *new = (List *)malloc(sizeof(List));

	    if (new == NULL)
	    {
	        printf("Memory allocation failed.\n");
	        return 0;  // Indicate failure
	    }

	    strcpy(new->date.name, name);
	    strcpy(new->date.surname, surname);
	    new->date.number = number;
	    new->next = NULL;

	    if (head == NULL)
	    {
	        head = new;
	    }
	    else
	    {
	        List *current = head;

	        while (current->next != NULL)
	        {
	            current = current->next;
	        }
	        current->next = new;
 	    }

 	    printf("\n\t\t\t\t******************************************************************************\n");
 	    printf("\t\t\t\t*                  User added successfully to the list                       *\n");
 	    printf("\t\t\t\t******************************************************************************\n\n\n");

 	    return 1;  // Indicate success
 }

// This function prints all users to the console
void View_all_users()
 {
	List *current = head;
	int i = 0;

	printf("\n\t\t\t\t******************************************************************************\n");
   	printf("\t\t\t\t*                  Here is all records listed in phonebook                   *\n");
   	printf("\t\t\t\t******************************************************************************\n\n\n");

 	while(current != NULL)
   	{
   		printf("\t\t\t\t%d) Name: %s, Surname: %s, Number: %d\n\n", i + 1, current->date.name, current->date.surname, current->date.number);

   		current = current->next;
   		i++;
   		fflush(stdout);

   	 }
 }
// This function adds a new user
void Add_a_user()
 {
 	char name[20], surname[20];
	int number;

 	printf("\n\t\t\t\t******************************************************************************\n");
 	printf("\t\t\t\t*                  Enter information about the new user                        *\n");
 	printf("\t\t\t\t******************************************************************************\n\n\n");
 	printf("\t\t\t\tEnter name : ");
 	fflush(stdout);
 	scanf("%s",name);
 	printf("\n\n");
 	printf("\t\t\t\tEnter surname :  ");
 	fflush(stdout);
 	scanf("%s",surname);
 	printf("\n\n");
 	printf("\t\t\t\tEnter number : ");
 	fflush(stdout);
 	scanf("%d",&number);

 	if (Adding_users_to_the_list(name, surname, number))
 	{
 		Add_new_user_in_txt(filename, name, surname, number);

 		printf("\n\n");
 		printf("\t\t\t\tUser added successfully!\n\n");
 		fflush(stdout);
 	}
 	else
 	{
 		printf("\n\n");
 		printf("\t\t\t\tFailed to add user!\n");
 		fflush(stdout);
 	}
 }


// This function writes a new user in a .txt file in binary format
int Add_new_user_in_txt(const char* filename, const char* name, const char* surname, int number)
 {
	FILE *file;
  	file = fopen(filename, "ab+");

  	if(file == NULL)
  	{
  		printf("\n\t\t\t\t******************************************************************************\n");
  	        printf("\t\t\t\t*                   Error opening the file for writing!                     *\n");
  		printf("\t\t\t\t******************************************************************************\n\n\n");
  		return 2; // return error code 2
  	}

  	User user;
  	strcpy(user.name, name);
  	strcpy(user.surname, surname);
  	user.number = number;

    size_t users_written = fwrite(&user, sizeof(User), 1, file);
    if(users_written == 0)
    {
    	printf("\n\t\t\t\t******************************************************************************\n");
    	printf("\t\t\t\t*                   You have not added any users!                     *\n");
    	printf("\t\t\t\t******************************************************************************\n\n\n");
    	return 3; // return error code 3
    }
  	fclose(file);
 }


 // This function remove a user from list.
void Remove_a_user_from_list()
 {
	/* Initialization of pointer "current" to the beginning of list */
	List *current = head;

	/* keeping track of the previous node as you iterate through the linked list */
	List *previous = NULL;

	/* Tracks the user's position in the list that is currently being checked */
	int i = 1;

        /* Variable declaration through which we check the phone number */
	int number;

        /* Checking if the list is empty */
	if (head == NULL)
	{
		printf("\t\t\t\tThe list is empty!\n");
		return;
	}

	printf("\n\t\t\t\t******************************************************************************\n");
	printf("\t\t\t\t*                          Pay attention!                                    *\n");
	printf("\t\t\t\t*               You will delete the user from the List                       *\n");
	printf("\t\t\t\t******************************************************************************\n\n\n");
	printf("\t\t\t\tEnter Phone number of the user you want to remove from phone book: ");
	fflush(stdout);
	scanf("%d", &number);

	/* Check if the first element is the one requested */
	if (current->date.number == number)
	{
		printf("\n\n");
		printf("\t\t\t\tThe user is 1st in the list\n");

	    /* Update the "head" pointer to the second node in the list */
	    head = current->next;

	    /* Freeing the memory of the first node */
	    free(current);

	    printf("\n\n");
	    printf("\t\t\t\tUser removed from the list.\n");
	    return;
	}

	/* Iterating through the linked list to find a user with a specific phone number to remove from the list */
	while (current != NULL)
	{
		/* Checks if the phone number of the current user located in the node pointed to by "current" */
		if (current->date.number == number)
		{
			printf("\n\n");
			printf("\t\t\t\tWe delete user no. %d in list\n", i);

		/* In this way, the current node is deleted, it is bypassed and the nodes are reconnected */
	        previous->next = current->next;

	        /* Freeing the memory of the current node */
	        free(current);

	        printf("\n\n");
	        printf("\t\t\t\tUser removed from the list.\n");
	        return;
		}

                /* It ensures that the node being removed is properly removed from the list and the list remains connected without interruption */
	        previous = current;
	        current = current->next;


	        /* Increments the variable by 1 each time it is executed */
	        i++;
	}
	printf("\t\t\t\tUser was not found in the list.\n");
 }


 // This function will start our program.
void start()
 {
	int choice;
   	while(1)
   	{
   		Print_menu();

   		scanf("%d",&choice);
   		switch(choice)
   		{
   			case stop_the_program:
   			{
   				Stop_the_program();
   				return;
   			}
   			break;

   			case load_users:
   			{
   				Load_users(filename);
   			}
   			break;

   			case add_a_user_to_list:
   			{
   				Add_a_user();
   			}
                        break;

   			case view_all_users:
   			{
   				View_all_users();

   			}
   		        break;

   			case remove_a_user_from_list:
   			{
   				Remove_a_user_from_list();
   			}
   			break;
   		}
   	}
 }


 // Program starts here.
int main()
 {
	start();
   	return 0;
 }

