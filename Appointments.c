/* <Appointments Module>
Project Name   : Appointments.c
Written By     : Chin Yi Hang
Student ID     : 18WMD01981
Course Name    : Diploma In Science (Computer Science and Computer Mathematics) DCO1
Tutorial Group : 2
Purpose        : To record appointments made for visits
*/

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#pragma warning(disable: 4996)
#define MAX_SIZE 50

void errors();
void checkDate(int *day, int *month, int *year);
int periodAppointments();
int menuAppointments();
void makeAppointments();
void searchAppointments();
void listAppointments();
void cancelAppointments();
void modifyAppointments();
void cleanUp();

typedef struct
{
	int day, month, year;
}Date;

struct Data
{
	Date dateInA;
	int timePeriod;
	char patientName[30];
	char patientID[9];
	Date dateMakeA;
};

void appointments()
{
	int choice;
	do
	{
		choice = menuAppointments();
		switch (choice)
		{
		case 1:
			makeAppointments();
			printf("\n\n\n");
			break;
		case 2:
			searchAppointments();
			printf("\n\n\n");
			break;
		case 3:
			listAppointments();
			printf("\n\n\n");
			break;
		case 4:
			cancelAppointments();
			printf("\n\n\n");
			break;
		case 5:
			modifyAppointments();
			printf("\n\n\n");
			break;
		case 6:
			cleanUp();
			printf("\n\n\n");
			break;
		case 0:
			printf("\n\t Exit...");
			break;

		default:
			printf("\n\t Error -Please enter again...");
			break;
		}
	} while (choice != 0);
	printf("\n\n");

	system("pause");
	system("cls");
}

void errors()
{
	printf("\n\t Error!!! -You may contact our staff...");
	printf("\n\t E-mail        > ");
	printf("\n\t Phone number  > ");
}

void checkDate(int *day, int *month, int *year)
{
	int error = 0;
	Date check;

	Date todayDate;
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	todayDate.day = t->tm_mday;
	todayDate.month = t->tm_mon + 1;
	todayDate.year = t->tm_year + 1900;

	do
	{
		printf("\n\t Please enter the date  > ");
		scanf("%d/%d/%d", &check.day, &check.month, &check.year);
		rewind(stdin);
		if (check.year >= 2018 && check.year <= 2100)
		{
			//check month
			if (check.month >= 1 && check.month <= 12)
			{
				//check days
				if ((check.day >= 1 && check.day <= 31) && (check.month == 1 || check.month == 3 || check.month == 5 || check.month == 7 || check.month == 8 || check.month == 10 || check.month == 12))
					break;//valid
				else if ((check.day >= 1 && check.day <= 30) && (check.month == 4 || check.month == 6 || check.month == 9 || check.month == 11))
					break;//valid   
				else if ((check.day >= 1 && check.day <= 28) && (check.month == 2))
					break;//valid    
				else if (check.day == 29 && check.month == 2 && (check.year % 400 == 0 || (check.year % 4 == 0 && check.year % 100 != 0)))
					break;//valid
				else if (check.day == todayDate.day && check.month == todayDate.month && check.year == todayDate.year)
				{
					printf("\n\t Invalid, this is today !!!");
				}
				else
				{
					printf("\n\t Day is invalid.");
					printf("\n\t Error -Please enter again...");
					error++;
				}
			}
			else
			{
				printf("\n\t Month is invalid.");
				printf("\n\t Error -Please enter again...");
				error++;
			}
		}
		//check year
		else
		{
			printf("\n\t Year is invalid.");
			printf("\n\t Error -Please enter again...");
			error++;
		}
		if (error >= 3)
		{
			errors();
		}
	} while (1);

	*day = check.day;
	*month = check.month;
	*year = check.year;
}

int periodAppointments()
{
	int choice;
	int error = 0;
	do
	{
		printf("\n\t The period time to have appointment");
		printf(
			"\n\t 1.(  8 a.m. to  9 a.m. )"
			"\n\t 2.(  9 a.m. to 10 a.m. )"
			"\n\t 3.( 10 a.m. to 11 a.m. )"
			"\n\t 4.( 11 a.m. to 12 p.m. )"
			"\n\t 5.( 12 p.m. to  1 p.m. )"
			"\n\t 6.(  2 p.m. to  3 p.m. )"
			"\n\t 7.(  3 p.m. to  4 a.m. )"
			"\n\t 8.(  4 p.m. to  5 p.m. )"
			"\n\t 9.(  5 p.m. to  6 p.m. )");
		printf("\n\t choose one in the number(1/2/3/4/5/6/7/8/9)  > ");
		scanf("%d", &choice);
		rewind(stdin);
		error++;
		if (error >= 3)
			errors();
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 8 && choice != 9);
	return choice;
}

int menuAppointments()
{
	int choice;
	printf("\n\t Enter 1. To make appointment");
	printf("\n\t       2. To search appointment");
	printf("\n\t       3. List of appointment");
	printf("\n\t       4. To cancel appointment");
	printf("\n\t       5. To modify appoinment");
	printf("\n\t       6. To clean up the past appoinment");
	printf("\n\t       0. Exit");
	printf("\n\t Please enter your choice  > ");
	scanf("%d", &choice);
	rewind(stdin);
	return choice;
}

void makeAppointments()
{
	char sureMakeA = 'X';

	Date todayDate;
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	todayDate.day = t->tm_mday;
	todayDate.month = t->tm_mon + 1;
	todayDate.year = t->tm_year + 1900;

	FILE *fptr;
	fptr = fopen("appointment.bin", "ab");
	if (fptr == NULL)
	{
		printf("\n\t Error! cant open the file!!!");
		exit(-1);
	}

	struct Data dataMakeA;
	struct Data dataA;

	do
	{
		printf("\n\t  Make appointment");
		printf("\n\t =================");
		rewind(stdin);
		checkDate(&dataMakeA.dateInA.day, &dataMakeA.dateInA.month, &dataMakeA.dateInA.year);
		rewind(stdin);
		dataMakeA.timePeriod = periodAppointments();
		rewind(stdin);
		while (fread(&dataA, sizeof(struct Data), 1, fptr))
		{
			if ((dataA.dateInA.day == dataMakeA.dateInA.day && dataA.dateInA.month == dataMakeA.dateInA.month && dataA.dateInA.year == dataMakeA.dateInA.year) && (dataA.timePeriod == dataMakeA.timePeriod))
			{
				printf("\n\t This period has been booked...");
				printf("\n\t Please take another period");
			}
		}
		printf("\n\t Enter patient name  > ");
		scanf("%[^\n]", dataMakeA.patientName);
		rewind(stdin);
		printf("\n\t Enter his/her ID  > ");
		scanf("%[^\n]", dataMakeA.patientID);
		rewind(stdin);
		dataMakeA.dateMakeA = todayDate;
		printf("\n\t %2d/%2d/%d | %d | %s | %9s", dataMakeA.dateInA.day, dataMakeA.dateInA.month, dataMakeA.dateInA.year, dataMakeA.timePeriod, dataMakeA.patientName, dataMakeA.patientID);
		printf("\n\t Are you sure make appoinment? (y = yes)  > ");
		scanf("%c", &sureMakeA);
		rewind(stdin);
		if (toupper(sureMakeA) == 'Y')
		{
			fwrite(&dataMakeA, sizeof(dataMakeA), 1, fptr);
			printf("\n\t Done for making appointment !");
		}
		rewind(stdin);
	} while (toupper(sureMakeA) != 'Y');
	fclose(fptr);
}

void searchAppointments()
{
	int no = 1;
	char nameP[30];
	FILE *fptr;
	fptr = fopen("appointment.bin", "rb");
	if (fptr == NULL)
	{
		printf("\n\t Error! cant open the file!!!");
		exit(-1);
	}
	struct Data search;

	printf("\n\t  Search appointment");
	printf("\n\t =================");
	printf("\n\t Enter name  > ");
	scanf("%[^\n]", nameP);
	rewind(stdin);

	printf("\n\t   Date     | Period |\t\t  Patient Name \t\t| Patient ID | Date that make appointment");
	printf("\n==========================================================================================================");
	while (fread(&search, sizeof(search), 1, fptr))
	{
		if (strcmp(nameP, search.patientName) == 0)
		{
			printf("\n\t %2d/%2d/%d | %4d   |  %-30s  | %9s  | %2d/%2d/%d", search.dateInA.day, search.dateInA.month, search.dateInA.year, search.timePeriod, search.patientName, search.patientID, search.dateMakeA.day, search.dateMakeA.month, search.dateMakeA.year);
			no--;
		}

	}
	if (no == 1)
	{
		printf("\n\t No that appointment !");
	}
	fclose(fptr);
}

void listAppointments()
{
	int totalA = 0;
	char choice;
	FILE *fptr;

	Date todayDate;
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	todayDate.day = t->tm_mday;
	todayDate.month = t->tm_mon + 1;
	todayDate.year = t->tm_year + 1900;

	fptr = fopen("appointment.bin", "rb");
	if (fptr == NULL)
	{
		printf("\n\t Error! cant open the file!!!");
		exit(-1);
	}
	struct Data listOut;
	do
	{
		printf("\n\t All list(A) or today only(B)  > ");
		scanf("%c", &choice);
		rewind(stdin);
		if (toupper(choice) == 'A')
		{
			printf("\n\t  List of the appointments");
			printf("\n\t =================");
			printf("\n\t   Date     | Period |\t\t  Patient Name \t\t| Patient ID");
			printf("\n==========================================================================================================");
			while (fread(&listOut, sizeof(listOut), 1, fptr))
			{
				printf("\n\t %2d/%2d/%d | %4d   |  %-30s  | %9s ", listOut.dateInA.day, listOut.dateInA.month, listOut.dateInA.year, listOut.timePeriod, listOut.patientName, listOut.patientID);
				totalA++;
			}
			printf("\n\t Appointment(s) : %d", totalA);
		}
		else if (toupper(choice) == 'B')
		{
			printf("\n\t  List of today appointments");
			printf("\n\t =================");
			printf("\n\t   Date     | Period |\t\t  Patient Name \t\t| Patient ID");
			printf("\n==========================================================================================================");

			while (fread(&listOut, sizeof(listOut), 1, fptr))
			{
				if (listOut.dateInA.day == todayDate.day && listOut.dateInA.month == todayDate.month && listOut.dateInA.year == todayDate.year)
				{
					printf("\n\t %2d/%2d/%d | %4d   |  %-30s  | %9s ", listOut.dateInA.day, listOut.dateInA.month, listOut.dateInA.year, listOut.timePeriod, listOut.patientName, listOut.patientID);
					totalA++;
				}
			}
			if (totalA == 0)
			{
				printf("\n\t Today no appointment !!!");
			}
			else
			{
				printf("\n\t Appointment(s) : %d", totalA);
			}
		}
		else
		{
			printf("Please tape A or B");
		}
	} while (toupper(choice) != 'A' && toupper(choice) != 'B');
	fclose(fptr);
}

void cancelAppointments()
{
	int i, n, countA = 0, cancel = 0;
	char sureCancel;
	char nameP[30];
	struct Data tempA, dataA[MAX_SIZE];

	FILE *fptr;
	fptr = fopen("appointment.bin", "rb");
	if (fptr == NULL)
	{
		printf("\n\t Error! cant open the file!!!");
		exit(-1);
	}
	fread(&tempA, sizeof(tempA), 1, fptr);
	for (i = 0; i < MAX_SIZE; i++) {
		if (!feof(fptr)) {
			dataA[i] = tempA;

			fread(&tempA, sizeof(tempA), 1, fptr);

			countA++;
		}
	}
	printf("\n\t  Cancel appointment");
	printf("\n\t ====================");
	do {
		printf("\n\t Enter name  > ");
		scanf("%[^\n]", nameP);
		rewind(stdin);
		checkDate(&tempA.dateInA.day, &tempA.dateInA.month, &tempA.dateInA.year);
		rewind(stdin);
		tempA.timePeriod = periodAppointments();
		rewind(stdin);
		for (i = 0; i < MAX_SIZE; i++) {
			if ((strcmp(nameP, tempA.patientName) == 0) && (tempA.dateInA.day == dataA[i].dateInA.day && tempA.dateInA.month == dataA[i].dateInA.month && tempA.dateInA.year == dataA[i].dateInA.year) && (tempA.timePeriod == dataA[i].timePeriod))
			{
				for (i = 0; i < countA; i++)
				{
					if ((strcmp(nameP, tempA.patientName) == 0) && (tempA.dateInA.day == dataA[i].dateInA.day && tempA.dateInA.month == dataA[i].dateInA.month && tempA.dateInA.year == dataA[i].dateInA.year) && (tempA.timePeriod == dataA[i].timePeriod))
					{
						for (n = i; n < countA; n++)
						{
							dataA[n] = dataA[n + 1];
						}
						cancel++;
					}
				}
				countA -= cancel;
			}
		}
		printf("\n\t Sure want to cancel?(y = yes) > ");
		scanf("%c", &sureCancel);
		rewind(stdin);
	} while (toupper(sureCancel) != 'Y');
	fclose(fptr);

	fptr = fopen("appointment.bin", "wb");

	for (i = 0; i < countA; i++)
	{
		fwrite(&dataA[i], sizeof(dataA[i]), 1, fptr);
	}

	printf("\n\t Done !!!");
	fclose(fptr);
}

void modifyAppointments()
{
	char sure, quit, nameP[30];
	char iD[9];
	int no = 1, countA = 0, cancel = 0, i, n;

	Date todayDate;
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	todayDate.day = t->tm_mday;
	todayDate.month = t->tm_mon + 1;
	todayDate.year = t->tm_year + 1900;

	FILE *fptr;
	fptr = fopen("appointment.bin", "rb");
	if (fptr == NULL)
	{
		printf("\n\t Error! cant open the file!!!");
		exit(-1);
	}
	struct Data tempA, dataA[MAX_SIZE], dataCheck;
	fread(&tempA, sizeof(tempA), 1, fptr);
	for (i = 0; i < MAX_SIZE; i++)
	{
		if (!feof(fptr))
		{
			dataA[i] = tempA;
			fread(&tempA, sizeof(tempA), 1, fptr);
			countA++;
		}
	}

	printf("\n\t  Modify appointment");
	printf("\n\t =================");
	do
	{
		do
		{
			printf("\n\t Enter name  > ");
			scanf("%[^\n]", nameP);
			rewind(stdin);
			checkDate(&tempA.dateInA.day, &tempA.dateInA.month, &tempA.dateInA.year);
			rewind(stdin);
			tempA.timePeriod = periodAppointments();
			rewind(stdin);
			for (i = 0; i < MAX_SIZE; i++)
			{

				if ((strcmp(nameP, tempA.patientName) == 0) && (tempA.dateInA.day == dataA[i].dateInA.day && tempA.dateInA.month == dataA[i].dateInA.month && tempA.dateInA.year == dataA[i].dateInA.year) && (tempA.timePeriod == dataA[i].timePeriod))
				{
					for (i = 0; i < countA; i++)
					{
						if ((strcmp(nameP, tempA.patientName) == 0) && (tempA.dateInA.day == dataA[i].dateInA.day && tempA.dateInA.month == dataA[i].dateInA.month && tempA.dateInA.year == dataA[i].dateInA.year) && (tempA.timePeriod == dataA[i].timePeriod))
						{
							strcpy(iD, tempA.patientID);
							printf("\n\t %2d/%2d/%d | %4d   |  %-30s  | %-9s ", tempA.dateInA.day, tempA.dateInA.month, tempA.dateInA.year, tempA.timePeriod, tempA.patientName, tempA.patientID);
							for (n = i; n < countA; n++)
							{
								dataA[n] = dataA[n + 1];
							}
							cancel++;
						}
					}
					countA -= cancel;
				}
			}
			printf("\n\t Want to edit? (y = yes)  > ");
			scanf("%c", &sure);
			rewind(stdin);
		} while (toupper(sure) != 'Y');

		fclose(fptr);
		//Remove the old one
		fptr = fopen("appointment.bin", "wb");
		for (i = 0; i < countA; i++)
		{
			fwrite(&dataA[i], sizeof(dataA[i]), 1, fptr);
		}
		fclose(fptr);
		//create a new one
		fptr = fopen("appointment.bin", "ab");
		checkDate(&tempA.dateInA.day, &tempA.dateInA.month, &tempA.dateInA.year);
		rewind(stdin);
		do
		{
			tempA.timePeriod = periodAppointments();
			rewind(stdin);
			while (fread(&dataCheck, sizeof(struct Data), 1, fptr))
			{
				if ((dataCheck.dateInA.day == tempA.dateInA.day && dataCheck.dateInA.month == tempA.dateInA.month && dataCheck.dateInA.year == tempA.dateInA.year) && (dataCheck.timePeriod == tempA.timePeriod))
				{
					printf("\n\t This period has been booked...");
					printf("\n\t Please take another period");
				}
			}
		} while ((dataCheck.dateInA.day == tempA.dateInA.day && dataCheck.dateInA.month == tempA.dateInA.month && dataCheck.dateInA.year == tempA.dateInA.year) && (dataCheck.timePeriod == tempA.timePeriod));


		tempA.dateMakeA = todayDate;
		printf("\n\t %2d/%2d/%d | %d | %s | %s", tempA.dateInA.day, tempA.dateInA.month, tempA.dateInA.year, tempA.timePeriod, tempA.patientName, tempA.patientID);
		printf("\n\t Are you sure edit appoinment? (y = yes)  > ");
		scanf("%c", &sure);
		rewind(stdin);
		if (toupper(sure) == 'Y')
		{
			strcpy(tempA.patientID, iD);
			strcpy(tempA.patientName, nameP);
			fwrite(&tempA, sizeof(tempA), 1, fptr);
			printf("\n\t Done for modify appointment !");
		}
		rewind(stdin);

		printf("\n\t Quit ? (y = yes)  > ");
		scanf("%c", &quit);
		rewind(stdin);
	} while (toupper(quit) != 'Y');

	fclose(fptr);

	printf("\n\n\n\t ");
	system("pause");
}

void cleanUp()
{
	int i, n, countA = 0, cancel = 0;
	struct Data tempA, dataA[MAX_SIZE];

	Date todayDate;
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	todayDate.day = t->tm_mday;
	todayDate.month = t->tm_mon + 1;
	todayDate.year = t->tm_year + 1900;

	FILE *fptr;
	fptr = fopen("appointment.bin", "rb");
	if (fptr == NULL)
	{
		printf("\n\t Error! cant open the file!!!");
		exit(-1);
	}

	fread(&tempA, sizeof(tempA), 1, fptr);
	for (i = 0; i < MAX_SIZE; i++)
	{
		if (!feof(fptr))
		{
			dataA[i] = tempA;
			fread(&tempA, sizeof(tempA), 1, fptr);
			countA++;
		}
	}

	printf("\n\t  Clean up appointment");
	printf("\n\t ====================");
	for (i = 0; i < countA; i++)
	{
		if ((dataA[i].dateInA.year == todayDate.year) && (dataA[i].dateInA.month < todayDate.month))
		{
			for (n = i; n < countA; n++)
			{
				dataA[n] = dataA[n + 1];
			}
			cancel++;
		}
		if ((dataA[i].dateInA.year == todayDate.year) && (dataA[i].dateInA.month == todayDate.month) && (dataA[i].dateInA.day < todayDate.day))
		{
			for (n = i; n < countA; n++)
			{
				dataA[n] = dataA[n + 1];
			}
			cancel++;
		}
		countA -= cancel;
	}
	fclose(fptr);
	fptr = fopen("appointment.bin", "wb");
	if (fptr == NULL)
	{
		printf("\n\t Error! cant open the file!!!");
		exit(-1);
	}
	for (i = 0; i < countA; i++)
	{
		fwrite(&dataA[i], sizeof(dataA[i]), 1, fptr);
	}
	printf("\n\t Done !!!");
	fclose(fptr);
}