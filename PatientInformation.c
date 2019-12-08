/* <Patient Information Module>
Project Name   : PatientInformation.c
Written By     : Ong T'nsam
Student ID     : 18WMD01549
Course Name    : Diploma In Science (Computer Science and Computer Mathematics) DCO1
Tutorial Group : 2
Purpose        : To handle patient registration and maintain patient profiles. 
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#pragma warning(disable:4996)
#define MAX_SIZE 50

//variable declaration
typedef struct {
	int day, month, year;
}Date;

//variable declaration
typedef struct
{
	Date registration;
	char id[15], idEntered[15], name[20], gender, contactNo[15], allergies[15];
}Patient;

void menuPatient(int *choice);//display menu for user to choose which function to perform
void displayAllPatient(Patient patient);//display all patient's information
void addPatient(Patient patient);//add new patient's information
void modifyPatient(Patient patient, Patient p [MAX_SIZE]);//modify patient's information
void searchPatient(Patient patient);//search based on specific criteria and display all the related patients' information
void viewPatient(Patient patient);//view information of patient by entering patient's ID or name
void tableHeader();//display the header of the table of patients' information


void patientInformation()
{
	//variable declaration
	int choice;
	Patient patient = { NULL };
	Patient p[MAX_SIZE] = { NULL };

	FILE*fptr;

	fptr = fopen("patientInfo.txt", "r");//open the file for reading
	if (fptr == NULL)//to check whether the file has been opened successfully
	{
		printf("Unable to open the file patientInfo.txt\n");
		system("pause");
		exit(-1);
	}

	do
	{
		menuPatient(&choice);
		switch (choice)
		{
		case 1:
			displayAllPatient(patient);//display all patient's information
			break;
		case 2:
			addPatient(patient);//add new patient's information
			break;
		case 3:
			modifyPatient(patient, p);//modify patient's information 
			break;
		case 4:
			searchPatient(patient);//search based on specific criteria and display all related patients' information
			break;
		case 5:
			viewPatient(patient);//view patient's information by entering patient's ID or name
			break;
		case 6:
			printf("Exit!\n");
			break;
		default:
			printf("Invalid choice. Please try again!\n\n");
		}
	} while (choice != 6);

	system("pause");
	system("cls");
}

void tableHeader()
{
	printf("                                      PATIENT'S INFORMATION\n");
	printf("Registration Date      ID           Name              Gender     Contact Number       Allergies\n");
	printf("-----------------------------------------------------------------------------------------------\n");
}

void menuPatient(int *choice)
{
	printf("\nPatient Information \n");
	printf("------------------------\n");
	printf("1. Display all patients' information\n");
	printf("2. Add new patient's information\n");
	printf("3. Modify patient's information\n");
	printf("4. Search patient's information based on specific criteria\n");
	printf("5. View information of patient chosen\n");
	printf("6. Exit\n");
	printf("Enter your choice :");
	scanf("%d", &*choice);
	rewind(stdin);
}

void displayAllPatient(Patient patient)
{
	FILE*fptr;
	int noOfPatient = 0;

	fptr = fopen("patientInfo.txt", "r");//open the file for reading
	if (fptr == NULL) //to check whether the file has been opened successfully
	{
		printf("Unable to open the file patientInfo.txt\n");
		system("pause");
		exit(-1);
	}

	printf("\n<Display all patients' information>\n\n");
	tableHeader();
	while (fscanf(fptr, "%d-%d-%d|%[^\|]|%[^\|]|%c|%[^\|]|%[^\n]\n", &patient.registration.day, &patient.registration.month, &patient.registration.year, &patient.id, &patient.name, &patient.gender, &patient.contactNo, &patient.allergies) != EOF)
	{
		printf("%2d-%2d-%-12d  %-15s %-20s %c %18s %18s\n", patient.registration.day, patient.registration.month, patient.registration.year, patient.id, patient.name, patient.gender, patient.contactNo, patient.allergies);
		noOfPatient++;
	}

	printf("<%d patient(s) recorded>\n", noOfPatient);//show the total amount of patient's record

	fclose(fptr);
}

void addPatient(Patient patient)
{
	FILE*fptr;

	fptr = fopen("patientInfo.txt", "a");//open the file for appending
	if (fptr == NULL)//to check whether the file has been opened successfully
	{
		printf("Unable to open the file patientInfo.txt\n");
		system("pause");
		exit(-1);
	}
	printf("\n<Add Patient's record>\n");
	printf("------------------------\n");
	printf("Enter the date of patient register in the clinic:");
	scanf("%d-%d-%d", &patient.registration.day, &patient.registration.month, &patient.registration.year);
	rewind(stdin);
	printf("Enter patient's ID : ");
	scanf("%[^\n]", &patient.id);
	rewind(stdin);
	printf("Enter patient's name : ");
	scanf("%[^\n]", &patient.name);
	rewind(stdin);
	printf("Enter patient's gender :");
	scanf("%c", &patient.gender);
	rewind(stdin);
	printf("Enter patient's contact number :");
	scanf("%[^\n]", &patient.contactNo);
	rewind(stdin);
	printf("Enter patient's allergies :");
	scanf("%[^\n]", &patient.allergies);
	rewind(stdin);

	//add new patients' information into the file
	fprintf(fptr, "%d-%d-%d|%s|%s|%c|%s|%s\n", patient.registration.day, patient.registration.month, patient.registration.year, patient.id, patient.name, patient.gender, patient.contactNo, patient.allergies);


	fclose(fptr);
}

void modifyPatient(Patient patient, Patient p[MAX_SIZE] )
{
	//variable declaration
	FILE*fptr;
	int i = 0, count = 0, noOfPatient = 0;
	char modifyCode, sureModify, modify;

	fptr = fopen("patientInfo.txt", "r");//open the file for reading
	if (fptr == NULL)//to check whether the file has been opened successfully
	{
		printf("Unable to open the file patientInfo.txt\n");
		system("pause");
		exit(-1);
	}

	while (fscanf(fptr, "%d-%d-%d|%[^\|]|%[^\|]|%c|%[^\|]|%[^\n]\n", &patient.registration.day, &patient.registration.month, &patient.registration.year, &patient.id, &patient.name, &patient.gender, &patient.contactNo, &patient.allergies) != EOF)
	{
		noOfPatient++;
		p[i].registration.day = patient.registration.day;
		p[i].registration.month = patient.registration.month;
		p[i].registration.year = patient.registration.year;
		strcpy(p[i].id, patient.id);
		strcpy(p[i].name, patient.name);
		p[i].gender = patient.gender;
		strcpy(p[i].contactNo, patient.contactNo);
		strcpy(p[i].allergies, patient.allergies);
		i++;

	}
	printf("<Modification of patient's information>\n");
	printf("----------------------------------------\n");
	printf("Enter patient's ID for modification :");
	scanf("%[^\n]", &patient.idEntered);
	rewind(stdin);
	for (i = 0; i < noOfPatient; i++)
	{
		if (strcmp(p[i].id, patient.idEntered) == 0)
		{
			printf("Record found :\n");
			printf("Registration Date      ID           Name              Gender     Contact Number       Allergies\n");
			printf("-----------------------------------------------------------------------------------------------\n");
			printf("%2d-%2d-%-12d  %-15s %-20s %c %18s %18s\n", p[i].registration.day, p[i].registration.month, p[i].registration.year, p[i].id, p[i].name, p[i].gender, p[i].contactNo, p[i].allergies);
			printf("Sure to modify (Y/N)?");
			scanf("%c", &sureModify);
			rewind(stdin);
			sureModify = toupper(sureModify);
			if (sureModify == 'Y')
			{
				do
				{
					printf("\nEnter code for modification (N-name, G-gender, C-contact no, A-allergies) :");
					scanf("%c", &modifyCode);
					rewind(stdin);
					switch (modifyCode)
					{
					case'N':
						printf("Enter new name :");
						scanf("%[^\n]", &p[i].name);
						rewind(stdin);
						break;
					case'G':
						printf("Enter new gender :");
						scanf("%[^\n]", &p[i].gender);
						rewind(stdin);
						break;
					case'C':
						printf("Enter new contact number :");
						scanf("%[^\n]", &p[i].contactNo);
						rewind(stdin);
						break;
					case'A':
						printf("Enter new allergies :");
						scanf("%[^\n]", &p[i].allergies);
						rewind(stdin);
						break;
					default:
						printf("Invalid modification code. Please try again!\n");
						return -1;
					}

					printf("Do you want to modify again for the same patient (Y/N)?");
					scanf("%c", &modify);
					rewind(stdin);
					modify = toupper(modify);
				} while (modify == 'Y');
				count++;
			}
			else
			{
				printf("Modification of patient's information cancelled.\n");
			}


		}
	}

	printf("<%d record(s) modified>\n", count);//display the total amount of patient's record modified

	fclose(fptr);

	fptr = fopen("patientInfo.txt", "w");//open the file for writing
	if (fptr == NULL)//to check whether the file has been opened successfully
	{
		printf("Unable to open the file patientInfo.txt\n");
		system("pause");
		exit(-1);
	}

	for (i = 0; i < noOfPatient; i++)
	{
		fprintf(fptr, "%d-%d-%d|%s|%s|%c|%s|%s\n", p[i].registration.day, p[i].registration.month, p[i].registration.year, p[i].id, p[i].name, p[i].gender, p[i].contactNo, p[i].allergies);
	}

	fclose(fptr);
}

void searchPatient(Patient patient)
{
	//variable declaration
	Date registration;
	FILE*fptr;
	char searchCode;
	int day, month, year, pCount = 0;
	char gender, allergies[15];

	fptr = fopen("patientInfo.txt", "r");//open the file for reading
	if (fptr == NULL)//to check whether the file has been opened successfully
	{
		printf("Unable to open the file patientInfo.txt\n");
		system("pause");
		exit(-1);
	}

	printf("\n<Search patient's information>\n");
	printf("----------------------------\n");
	printf("R-registration date\n");
	printf("G-gender\n");
	printf("A-allergies\n");
	printf("Enter code for searching :");
	scanf("%c", &searchCode);
	rewind(stdin);

	if (searchCode == 'R')
	{
		printf("Enter registration date :");
		scanf("%d-%d-%d", &day, &month, &year);
		rewind(stdin);
		tableHeader();
		while (fscanf(fptr, "%d-%d-%d|%[^\|]|%[^\|]|%c|%[^\|]|%[^\n]\n", &patient.registration.day, &patient.registration.month, &patient.registration.year, &patient.id, &patient.name, &patient.gender, &patient.contactNo, &patient.allergies) != EOF)
		{
			if (day == patient.registration.day &&month == patient.registration.month&&year == patient.registration.year)
			{
				printf("%2d-%2d-%-12d  %-15s %-20s %c %18s %18s\n", patient.registration.day, patient.registration.month, patient.registration.year, patient.id, patient.name, patient.gender, patient.contactNo, patient.allergies);
				pCount++;
			}
		}
		printf("<%d of patient listed>\n", pCount);
	}

	else if (searchCode == 'G')
	{
		printf("Enter patient's gender :");
		scanf("%c", &gender);
		rewind(stdin);
		tableHeader();
		while (fscanf(fptr, "%d-%d-%d|%[^\|]|%[^\|]|%c|%[^\|]|%[^\n]\n", &patient.registration.day, &patient.registration.month, &patient.registration.year, &patient.id, &patient.name, &patient.gender, &patient.contactNo, &patient.allergies) != EOF)
		{
			if (gender == patient.gender)
			{
				printf("%2d-%2d-%-12d  %-15s %-20s %c %18s %18s\n", patient.registration.day, patient.registration.month, patient.registration.year, patient.id, patient.name, patient.gender, patient.contactNo, patient.allergies);
				pCount++;
			}
		}
		printf("<%d of patient listed>\n", pCount);
	}

	else if (searchCode == 'A')
	{
		printf("Enter patient's allergies :");
		scanf("%[^\n]", &allergies);
		rewind(stdin);
		tableHeader();
		while (fscanf(fptr, "%d-%d-%d|%[^\|]|%[^\|]|%c|%[^\|]|%[^\n]\n", &patient.registration.day, &patient.registration.month, &patient.registration.year, &patient.id, &patient.name, &patient.gender, &patient.contactNo, &patient.allergies) != EOF)
		{
			if (strcmp(allergies, patient.allergies) == 0)
			{
				printf("%2d-%2d-%-12d  %-15s %-20s %c %18s %18s\n", patient.registration.day, patient.registration.month, patient.registration.year, patient.id, patient.name, patient.gender, patient.contactNo, patient.allergies);
				pCount++;
			}
		}
		printf("<%d of patient listed>\n", pCount);

	}
	else
	{
		printf("Invalid option. Please try again.\n");
	}

	fclose(fptr);
}

void viewPatient(Patient patient)
{
	//variable declaration
	Date registration;
	FILE*fptr;
	char viewCode, nameEntered[20];
	fptr = fopen("patientInfo.txt", "r");
	if (fptr == NULL)//to check whether the file has been opened successfully
	{
		printf("Unable to open the file patientInfo.txt\n");
		system("pause");
		exit(-1);
	}

	printf("\n<View patient's information>\n");
	printf("---------------------------\n");
	printf("I-ID\n");
	printf("N-Name\n");
	printf("Enter code to view patient's information:");
	scanf("%c", &viewCode);
	rewind(stdin);

	if (viewCode == 'I')
	{
		printf("View based on patient's ID.\n");
		printf("Enter patient's ID :");
		scanf("%[^\n]", &patient.idEntered);
		rewind(stdin);
		tableHeader();
		while (fscanf(fptr, "%d-%d-%d|%[^\|]|%[^\|]|%c|%[^\|]|%[^\n]\n", &patient.registration.day, &patient.registration.month, &patient.registration.year, &patient.id, &patient.name, &patient.gender, &patient.contactNo, &patient.allergies) != EOF)
		{
			if (strcmp(patient.id, patient.idEntered) == 0)
			{
				printf("%2d-%2d-%-12d  %-15s %-20s %c %18s %18s\n", patient.registration.day, patient.registration.month, patient.registration.year, patient.id, patient.name, patient.gender, patient.contactNo, patient.allergies);

			}
		}
	}

	else if (viewCode == 'N')
	{
		printf("\nView based on patient's name.\n");
		printf("Enter patient's name :");
		scanf("%[^\n]", &nameEntered);
		rewind(stdin);
		tableHeader();
		while (fscanf(fptr, "%d-%d-%d|%[^\|]|%[^\|]|%c|%[^\|]|%[^\n]\n", &patient.registration.day, &patient.registration.month, &patient.registration.year, &patient.id, &patient.name, &patient.gender, &patient.contactNo, &patient.allergies) != EOF)
		{
			if (strcmp(nameEntered, patient.name) == 0)
			{
				printf("%2d-%2d-%-12d  %-15s %-20s %c %18s %18s\n", patient.registration.day, patient.registration.month, patient.registration.year, patient.id, patient.name, patient.gender, patient.contactNo, patient.allergies);

			}
		}
	}

	else
	{
		printf("Invalid option. Please try again.\n");
	}
	fclose(fptr);
}