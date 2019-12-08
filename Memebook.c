/*
Project Name : MemeBook.c
Written By : Goh Kok Dong, Leong Yit Wee, Chin Yi Hang, Foo Jia Ern, Ong T'nsam
Group: 2
Date : 23-12-2018
Purpose : 
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <ctype.h>
#pragma warning (disable:4996)

void logo();
void patientInformation();
void patientVisits(SYSTEMTIME t);
void staffInformation();
void appointments();
void medicalSupplies();

struct Date {
	int day, month, year;
};

void main()
{
	SYSTEMTIME t;
	int selection;

	printf("Hospital Information System\n");
	printf("===========================\n");
	logo();

	GetLocalTime(&t);
	printf("System Details - as at %02d-%02d-%04d %02d:%02d\n\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute);

	do {
		selection = menu();
		switch (selection) {
		case 1:
			patientInformation();
			break;
		case 2:
			patientVisits(t);
			break;
		case 3:
			staffInformation();
			break;
		case 4:
			appointments();
			break;
		case 5:
			medicalSupplies();
			break;
		case 6:
			break;
		default:
			printf("Invalid Option! Please re-enter your option.\n\n");
		}
	} while (selection != 6);

	printf("Thank you for using !!\n\n");

	system("pause");
}

void logo() {
	printf(" ___ __ __   ______   ___ __ __   ______        _______   ______   ______   ___   ___     \n");
	printf("/__//_//_/\\ /_____/\\ /__//_//_/\\ /_____/\\     /_______/\\ /_____/\\ /_____/\\ /___/\\/__/\\    \n");
	printf("\\::\\| \\| \\ \\\\::::_\\/_\\::\\| \\| \\ \\\\::::_\\/_    \\::: _  \\ \\\\:::_ \\ \\\\:::_ \\ \\\\::.\\ \\\\ \\ \\   \n");
	printf(" \\:.      \\ \\\\:\\/___/\\\\:.      \\ \\\\:\\/___/\\    \\::(_)  \\/_\\:\\ \\ \\ \\\\:\\ \\ \\ \\\\:: \\/_) \\ \\  \n");
	printf("  \\:.\\-/\\  \\ \\\\::___\\/_\\:.\\-/\\  \\ \\\\::___\\/_    \\::  _  \\ \\\\:\\ \\ \\ \\\\:\\ \\ \\ \\\\:. __  ( (  \n");
	printf("   \\. \\  \\  \\ \\\\:\\____/\\\\. \\  \\  \\ \\\\:\\____/\\    \\::(_)  \\ \\\\:\\_\\ \\ \\\\:\\_\\ \\ \\\\: \\ )  \\ \\ \n");
	printf("    \\__\\/ \\__\\/ \\_____\\/ \\__\\/ \\__\\/ \\_____\\/     \\_______\\/ \\_____\\/ \\_____\\/ \\__\\/\\__\\/ \n\n");
}

int menu() {
	int option;

	printf("<Menu>\n");
	printf("===================================\n");
	printf("1. Patient Information Module\n");
	printf("2. Patient Visit Module\n");
	printf("3. Staff Information Module\n");
	printf("4. Appointments Module\n");
	printf("5. Medical Supplies Module\n");
	printf("6. Exit\n");
	printf("===================================\n");

	printf("Enter your selection > ");
	scanf("%d", &option);
	printf("\n");

	return option;
}

//Modifying..
//void checkFile(FILE *fptr, int option) {
//	if (fptr == NULL) {
//		printf("Cannot open file... \n");
//		switch (option) {
//		case 1:
//			printf("<patientlist.bin>\n");
//			break;
//		case 2:
//			printf("<patientInfo.txt>\n");
//			break;
//		case 3:
//			printf("<staff.txt>\n");
//			break;
//		case 4:
//			printf("<appointment.bin>\n");
//			break;
//		case 5:
//			printf("<Medical Supplies .txt>\n");
//			break;
//		default:
//			printf("<Error>\n");
//		}
//		system("pause");
//		exit(-1);
//	}
//}
