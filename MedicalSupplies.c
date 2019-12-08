/* <Medical Supplies Module>
Project Name   : MedicalSupplies.c
Written By     : Leong Yit Wee
Student ID     : 18WMD01439
Course Name    : Diploma In Science (Computer Science and Computer Mathematics) DCO1
Tutorial Group : 2
Purpose        : To maintain records on stocks of medicine and other medical supplies.
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#pragma warning(disable:4996)
#define MAX_SIZE 50

void menuMs();
void selectMenuMs(int *selection);
void addRecordMs();
void displayMs();
void modifyMs();
void searchMs();
void addQuantityMs();
void reduceQuantityMs();

struct Date {
	int day;
	int month;
	int year;
};

typedef struct {
	char itemID[10];
	char description[70];
	struct Date expiryDate;
	char manufacturerAndCountry[70];
	int quantity;
	char suitableFor[40];
}Information;

void medicalSupplies()
{
	int selection;
	char ans = 'Y';
	while (toupper(ans) == 'Y')
	{
		menuMs();
		do {
			selectMenuMs(&selection);
			if (selection == 1)
				displayMs();
			else if (selection == 2)
				addRecordMs();
			else if (selection == 3)
				modifyMs();
			else if (selection == 4)
				searchMs();
			else if (selection == 5)
				addQuantityMs();
			else if (selection == 6)
				reduceQuantityMs();
		} while (selection != 1 && selection != 2 && selection != 3 && selection != 4 && selection != 5 && selection != 6);

		printf("\nDo you want to continue to use this system? (Y = Yes):");
		scanf(" %c", &ans);
	}
	
	system("pause");
	system("cls");
}

void menuMs() {
	printf("\nMedical Supplies Information System\n");
	printf("1. Display\n");
	printf("2. Add\n");
	printf("3. Modify\n");
	printf("4. Search\n");
	printf("5. Add Quantity\n");
	printf("6. Reduce Quantity\n");
}

void selectMenuMs(int *selection) {
	int select;
	printf("Enter Selection :");
	scanf("%d", &select);
	*selection = select;
}

void addRecordMs() {
	Information info[MAX_SIZE];
	int i = 0, errorCount = 0, numberR = 0, quantity;
	char ans, itemID[10], description[70], manufacturerAndCountry[70], suitableFor[40];
	struct Date expiryDate;

	FILE *fptr;

	printf("\nAdd record (Y/N) :");
	scanf(" %c", &ans);
	rewind(stdin);
	if (toupper(ans) == 'Y') {
		do {
			fptr = fopen("Medical Supplies .txt", "r");
			if (fptr == NULL) {
				printf("Error\n");
			}

			while (fscanf(fptr, "%[^|]|%[^|]|%d-%d-%d|%[^|]|%d|%[^\n]\n", &info[i].itemID, &info[i].description, &info[i].expiryDate.day, &info[i].expiryDate.month, &info[i].expiryDate.year, &info[i].manufacturerAndCountry, &info[i].quantity, &info[i].suitableFor) != EOF) {
				numberR++;
			}
			fclose(fptr);

			fptr = fopen("Medical Supplies .txt", "a");

			if (fptr == NULL) {
				printf("Error\n");
				exit(-1);
			}

			printf("Add Medical Supplies information.\n");
			printf("Enter item id:");
			scanf("%s", &itemID);
			for (i = 0; i < numberR; i++)
			{
				if (strcmp(itemID, info[i].itemID) == 0)
				{
					errorCount++;
				}
			}
			if (errorCount > 0) {
				errorCount = 0;
				printf("Same ID already existed. Try another ID\n");
			}
			else {
				rewind(stdin);
				printf("Enter description:");
				scanf("%[^\n]", &description);
				rewind(stdin);
				printf("Enter expiry date (day-month-year):");
				scanf("%d %d %d", &expiryDate.day, &expiryDate.month, &expiryDate.year);
				rewind(stdin);
				printf("Enter manufacturer and country (name (country)):");
				scanf("%[^\n]", &manufacturerAndCountry);
				rewind(stdin);
				printf("Enter quantity for the item:");
				scanf("%d", &quantity);
				rewind(stdin);
				printf("Enter suitable for what patient:");
				scanf("%[^\n]", &suitableFor);
				rewind(stdin);

				fprintf(fptr, "%s|%s|%2d-%2d-%4d|%s|%d|%s\n", itemID, description, expiryDate.day, expiryDate.month, expiryDate.year, manufacturerAndCountry, quantity, suitableFor);
				printf("Medical Supplies Info added successfully\n");
			}
			fclose(fptr);
			printf("\nAdd another record (Y=Yes) :");
			scanf(" %c", &ans);
			rewind(stdin);
		} while (toupper(ans) == 'Y');

	}
}

void displayMs() {
	Information info[MAX_SIZE];
	FILE *fptr;
	int i = 0;
	fptr = fopen("Medical Supplies .txt", "r");
	if (fptr == NULL) {
		printf("Error\n");
	}

	printf("\nMedical Supplies Details \n");
	printf("--------------------------------------------------------------------------------------------------------------------\n");
	printf("Item ID        Description			    Expiry Date    Manufacturer/country     Quantity  Suitable For     \n");

	while (fscanf(fptr, "%[^|]|%[^|]|%d-%d-%d|%[^|]|%d|%[^\n]\n", &info[i].itemID, &info[i].description, &info[i].expiryDate.day, &info[i].expiryDate.month, &info[i].expiryDate.year, &info[i].manufacturerAndCountry, &info[i].quantity, &info[i].suitableFor) != EOF)
	{
		printf("%-10s %-30s %-02d-%-02d-%-04d	   %-s  %-d    %-2s\n", info[i].itemID, info[i].description, info[i].expiryDate.day, info[i].expiryDate.month, info[i].expiryDate.year, info[i].manufacturerAndCountry, info[i].quantity, info[i].suitableFor);
		i++;
	}
	printf("\n%d Medical Supplies Recorded.\n", i);
	fclose(fptr);
}

void modifyMs() {
	Information info[MAX_SIZE];
	int i = 0, errorCount = 0, numberR = 0, quantity;
	char itemID[10], description[70], manufacturerAndCountry[70], suitableFor[40], ans, confirm;
	struct Date expiryDate;

	FILE *fptr;
	fptr = fopen("Medical Supplies .txt", "r");
	if (fptr == NULL)
	{
		printf("Error.\n");
	}

	while (fscanf(fptr, "%[^|]|%[^|]|%d-%d-%d|%[^|]|%d|%[^\n]\n", &info[i].itemID, &info[i].description, &info[i].expiryDate.day, &info[i].expiryDate.month, &info[i].expiryDate.year, &info[i].manufacturerAndCountry, &info[i].quantity, &info[i].suitableFor) != EOF)
	{
		i++;
	}
	numberR = i;
	fclose(fptr);
	do
	{
		confirm = ' ';
		rewind(stdin);
		printf("\nEnter the Item ID that you wish to modify:");
		scanf("%[^\n]", itemID);
		rewind(stdin);

		for (i = 0; i < numberR; i++)
		{
			if (strcmp(info[i].itemID, itemID) == 0)
			{
				while (toupper(confirm) != 'Y')
				{
					printf("Enter new description:");
					scanf("%[^\n]", &description);
					rewind(stdin);
					printf("Enter new expiry date (day-month-year):");
					scanf("%d %d %d", &expiryDate.day, &expiryDate.month, &expiryDate.year);
					rewind(stdin);
					printf("Enter new manufacturer and country (name (country)):");
					scanf("%[^\n]", &manufacturerAndCountry);
					rewind(stdin);
					printf("Enter new quantity for the item:");
					scanf("%d", &quantity);
					rewind(stdin);
					printf("Enter new suitable for what patient:");
					scanf("%[^\n]", &suitableFor);
					rewind(stdin);

					strcpy(info[i].description, description);
					info[i].expiryDate.day = expiryDate.day;
					info[i].expiryDate.month = expiryDate.month;
					info[i].expiryDate.year = expiryDate.year;
					strcpy(info[i].manufacturerAndCountry, manufacturerAndCountry);
					info[i].quantity = quantity;
					strcpy(info[i].suitableFor, suitableFor);

					printf("\nThe new Medical Supplies info:\n");
					printf("Item ID                   : %s\n", info[i].itemID);
					printf("Description               : %s\n", description);
					printf("Expiry Date               : %2d-%2d-%4d\n", expiryDate.day, expiryDate.month, expiryDate.year);
					printf("Manufacturer and country  : %s\n", manufacturerAndCountry);
					printf("Quantity                  : %d\n", quantity);
					printf("Suitable For              : %s\n", suitableFor);

					printf("Do you sure about the change:");
					scanf("%c", &confirm);
					rewind(stdin);
					if (toupper(confirm) != 'Y')
						printf("Please modify again thank you \n\n");
				}

				FILE* fptr;
				fptr = fopen("Medical Supplies .txt", "w");
				if (fptr == NULL)
				{
					printf("Error.\n");
				}
				printf("\nMedical Supplies Info successfully modified.\n");
				printf("\n Medical Supplies Report after Modify\n");
				printf("--------------------------------------------------------------------------------------------------------------------\n");
				printf("Item ID        Description			    Expiry Date    Manufacturer/country     Quantity  Suitable For     \n");
				for (i = 0; i < numberR; i++)
				{
					printf("%-10s %-30s %-02d-%-02d-%-04d	   %-s  %-d    %-2s\n", info[i].itemID, info[i].description, info[i].expiryDate.day, info[i].expiryDate.month, info[i].expiryDate.year, info[i].manufacturerAndCountry, info[i].quantity, info[i].suitableFor);
					fprintf(fptr, "%s|%s|%d-%d-%d|%s|%d|%2s\n", info[i].itemID, info[i].description, info[i].expiryDate.day, info[i].expiryDate.month, info[i].expiryDate.year, info[i].manufacturerAndCountry, info[i].quantity, info[i].suitableFor);
				}

				fclose(fptr);
			}
			else
			{
				errorCount++;
			}
		}
		if (errorCount == numberR)
		{
			errorCount = 0;
			printf("Invalid Item ID\n");
		}
		printf("\nDo you want to continue modify (Y=Yes):");
		scanf(" %c", &ans);
		rewind(stdin);
	} while (toupper(ans) == 'Y');
}

void searchMs() {
	Information info[MAX_SIZE];
	int i = 0, errorCount = 0, numberR = 0;
	char search[10], ans;

	FILE*fptr;
	fptr = fopen("Medical Supplies .txt", "r");
	if (fptr == NULL)
	{
		printf("Error.\n");
	}

	while (fscanf(fptr, "%[^|]|%[^|]|%d-%d-%d|%[^|]|%d|%[^\n]\n", &info[i].itemID, &info[i].description, &info[i].expiryDate.day, &info[i].expiryDate.month, &info[i].expiryDate.year, &info[i].manufacturerAndCountry, &info[i].quantity, &info[i].suitableFor) != EOF) {
		i++;
	}
	numberR = i;
	fclose(fptr);
	do {
		rewind(stdin);
		printf("Enter the Item ID you want search for:");
		scanf("%[^\n]", search);
		rewind(stdin);
		for (i = 0; i < numberR; i++) {
			if (strcmp(search, info[i].itemID) == 0) {
				printf("\nMedical Supplies info:\n");
				printf("Item ID                   : %s\n", info[i].itemID);
				printf("Description               : %s\n", info[i].description);
				printf("Expiry Date               : %2d-%2d-%4d\n", info[i].expiryDate.day, info[i].expiryDate.month, info[i].expiryDate.year);
				printf("Manufacturer and country  : %s\n", info[i].manufacturerAndCountry);
				printf("Quantity                  : %d\n", info[i].quantity);
				printf("Suitable For              : %s\n", info[i].suitableFor);
			}
			else {
				errorCount++;
			}
		}
		if (errorCount == numberR) {
			errorCount = 0;
			printf("Invalid Item ID.\n");
		}
		printf("Do you want to continue searching (Y=Yes):");
		scanf(" %c", &ans);
	} while (toupper(ans) == 'Y');
}

void addQuantityMs() {
	Information info[MAX_SIZE];
	int i = 0, quantity, numberR = 0, errorCount = 0;
	char ans, confirm = ' ', itemID[10];

	FILE *fptr;
	fptr = fopen("Medical Supplies .txt", "r");
	if (fptr == NULL)
	{
		printf("Error.\n");
	}

	while (fscanf(fptr, "%[^|]|%[^|]|%d-%d-%d|%[^|]|%d|%[^\n]\n", &info[i].itemID, &info[i].description, &info[i].expiryDate.day, &info[i].expiryDate.month, &info[i].expiryDate.year, &info[i].manufacturerAndCountry, &info[i].quantity, &info[i].suitableFor) != EOF)
	{
		i++;
	}
	numberR = i;
	fclose(fptr);
	do
	{
		confirm = ' ';
		rewind(stdin);
		printf("\nEnter the Item ID that you wish to add quantity:");
		scanf("%[^\n]", itemID);
		rewind(stdin);

		for (i = 0; i < numberR; i++)
		{
			if (strcmp(info[i].itemID, itemID) == 0)
			{
				do
				{
					do
					{
						printf("Enter quantity that need to add :");
						scanf("%d", &quantity);
						rewind(stdin);
						if (quantity < 0)
							printf("Please Enter Valid Quantity.\n");
					} while (quantity < 0);

					info[i].quantity += quantity;
					printf("\nThe new Medical Supplies info after add:\n");
					printf("Item ID                   : %s\n", info[i].itemID);
					printf("Description               : %s\n", info[i].description);
					printf("Expiry Date               : %2d-%2d-%4d\n", info[i].expiryDate.day, info[i].expiryDate.month, info[i].expiryDate.year);
					printf("Manufacturer and country  : %s\n", info[i].manufacturerAndCountry);
					printf("Quantity                  : %d\n", info[i].quantity);
					printf("Suitable For              : %s\n", info[i].suitableFor);

					printf("Do you sure about the change:");
					scanf("%c", &confirm);
					rewind(stdin);
					if (toupper(confirm) != 'Y')
					{
						info[i].quantity -= quantity;
						printf("Please enter again thank you \n\n");
					}
				} while (toupper(confirm) != 'Y');

				FILE* fptr;
				fptr = fopen("Medical Supplies .txt", "w");
				if (fptr == NULL)
				{
					printf("Error.\n");
				}
				printf("\nQuantity of Medical Supplies Info successfully Added.\n");

				for (i = 0; i < numberR; i++)
				{
					fprintf(fptr, "%s|%s|%d-%d-%d|%s|%d|%2s\n", info[i].itemID, info[i].description, info[i].expiryDate.day, info[i].expiryDate.month, info[i].expiryDate.year, info[i].manufacturerAndCountry, info[i].quantity, info[i].suitableFor);
				}

				fclose(fptr);
			}
			else
			{
				errorCount++;
			}
		}
		if (errorCount == numberR)
		{
			errorCount = 0;
			printf("Invalid Item ID\n");
		}
		printf("\nDo you want to continue adding (Y=Yes):");
		scanf(" %c", &ans);
		rewind(stdin);
	} while (toupper(ans) == 'Y');
}

void reduceQuantityMs() {
	Information info[MAX_SIZE];
	int i = 0, quantity, numberR = 0, errorCount = 0;
	char ans, confirm = ' ', itemID[10];

	FILE *fptr;
	fptr = fopen("Medical Supplies .txt", "r");
	if (fptr == NULL)
	{
		printf("Error.\n");
	}

	while (fscanf(fptr, "%[^|]|%[^|]|%d-%d-%d|%[^|]|%d|%[^\n]\n", &info[i].itemID, &info[i].description, &info[i].expiryDate.day, &info[i].expiryDate.month, &info[i].expiryDate.year, &info[i].manufacturerAndCountry, &info[i].quantity, &info[i].suitableFor) != EOF)
	{
		i++;
	}
	numberR = i;
	fclose(fptr);
	do
	{
		confirm = ' ';
		rewind(stdin);
		printf("\nEnter the Item ID that you wish to reduce quantity:");
		scanf("%[^\n]", itemID);
		rewind(stdin);

		for (i = 0; i < numberR; i++)
		{
			if (strcmp(info[i].itemID, itemID) == 0)
			{
				do
				{
					do
					{
						printf("Enter quantity that need to reduce :");
						scanf("%d", &quantity);
						rewind(stdin);
						if (quantity < 0 && quantity > info[i].quantity)
							printf("Please Enter Valid Quantity.\n");
					} while (quantity < 0 && quantity > info[i].quantity);

					info[i].quantity -= quantity;
					printf("\nThe new Medical Supplies info after Reduce:\n");
					printf("Item ID                   : %s\n", info[i].itemID);
					printf("Description               : %s\n", info[i].description);
					printf("Expiry Date               : %2d-%2d-%4d\n", info[i].expiryDate.day, info[i].expiryDate.month, info[i].expiryDate.year);
					printf("Manufacturer and country  : %s\n", info[i].manufacturerAndCountry);
					printf("Quantity                  : %d\n", info[i].quantity);
					printf("Suitable For              : %s\n", info[i].suitableFor);

					printf("Do you sure about the change:");
					scanf("%c", &confirm);
					rewind(stdin);
					if (toupper(confirm) != 'Y')
					{
						info[i].quantity += quantity;
						printf("Please enter again thank you \n\n");
					}
				} while (toupper(confirm) != 'Y');

				FILE* fptr;
				fptr = fopen("Medical Supplies .txt", "w");
				if (fptr == NULL)
				{
					printf("Error.\n");
				}
				printf("\nQuantity of Medical Supplies Info successfully reduced.\n");

				for (i = 0; i < numberR; i++)
				{
					fprintf(fptr, "%s|%s|%d-%d-%d|%s|%d|%2s\n", info[i].itemID, info[i].description, info[i].expiryDate.day, info[i].expiryDate.month, info[i].expiryDate.year, info[i].manufacturerAndCountry, info[i].quantity, info[i].suitableFor);
				}

				fclose(fptr);
			}
			else
			{
				errorCount++;
			}
		}
		if (errorCount == numberR)
		{
			errorCount = 0;
			printf("Invalid Item ID\n");
		}
		printf("\nDo you want to continue reducing (Y=Yes):");
		scanf(" %c", &ans);
		rewind(stdin);
	} while (toupper(ans) == 'Y');
}
