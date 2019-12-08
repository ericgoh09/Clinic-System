/* <Patient Visit Module>
Project Name     : PatientVisits.c
Written By       : Goh Kok Dong
Student ID       : 18WMD01921
Course Name      : Diploma In Science (Computer Science and Computer Mathematics) DCO1
Tutorial Group   : 2
Date             : 6-12-2018
Purpose          : To record details of each visit / consultation between a patient and doctor
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#define MAX_SIZE 50
#define PATIENTVISIT "patientlist.bin"
#pragma warning (disable:4996)

void displayMenuPv(int *option);
void displayPv();
void addPv(SYSTEMTIME t);
void searchPv();
void modifyPv(SYSTEMTIME t);
void deletePv();
void viewPatientVisited();
void displayReport();
void checkFile(FILE *fptr);

struct Date {
	int day, month, year;
};

typedef struct {
	int hrs, min;
}Time;

typedef struct {
	char name[31];
	int qty;
}MedicineGiven;

typedef struct {
	struct Date date;
	Time time;
	char patientId[41], staffId[41], diagnosis[31], doctor[41];
	MedicineGiven medicine;
	double charges;
	char receiptNo[21];
	struct Date lstModified;
}PatientVisit;

void patientVisits(SYSTEMTIME t) {
	int selection;

	do {
		displayMenuPv(&selection);
		switch (selection) {
		case 1:
			displayPv();
			break;
		case 2:
			addPv(t);
			break;
		case 3:
			searchPv();
			break;
		case 4:
			modifyPv(t);
			break;
		case 5:
			deletePv();
			displayPv();
			break;
		case 6:
			viewPatientVisited();
			break;
		case 7:
			displayReport();
			break;
		case 8:
			printf("\nExiting....\n");
			break;
		default:
			printf("Invalid Option! Please re-enter your option.\n\n");
		}
	} while (selection != 8);

	system("pause");
	system("cls");
}

// Integer option pass by reference
void displayMenuPv(int *option) {
	printf("\n||Patient Visits Information System||\n");
	printf("\t<Menu>\n");
	printf("\t===================================\n");
	printf("\t1. Display list of Patients Visited\n");
	printf("\t2. Add a New Patient Visits Record\n");
	printf("\t3. Search Existing Patients\n");
	printf("\t4. Modify Patient Visits Record\n");
	printf("\t5. Delete Patient Visits Record\n");
	printf("\t6. Search list of Patients Visited in end-of-day\n");
	printf("\t7. Display Report of the day\n");
	printf("\t8. Exit\n");
	printf("\t===================================\n");

	// Read the choice from the user
	printf("Enter your selection > ");
	scanf("%d", option);
}

// To Display all the patient visiting data and information
void displayPv() {

	PatientVisit pv;
	int pCount = 0;

	FILE *fptr;
	// Open the binary file for reading
	fptr = fopen(PATIENTVISIT, "rb");
	
	checkFile(fptr);

	// To read and display all the information from the file
	printf("\n%-18s %-12s %-10s %-18s %-13s %-19s %-9s %-13s %s\n", "Date/Time", "Patient ID", "Staff ID", "Diagnosis", "Doctor Name", "Medicine Given", "Cost", "Receipt No.", "Last Modified");
	printf("%-18s %-12s %-10s %-18s %-13s %-19s %-9s %-13s %s\n", "================", "==========", "========", "================", "===========", "=================", "=======", "===========", "=============");
	while (fread(&pv, sizeof(pv), 1, fptr) != 0) {
		printf("%02d-%02d-%04d %02d:%02d   %-12s %-10s %-18s %-13s %-2d%-17s %-9.2lf %-13s %02d-%02d-%04d\n", pv.date.day, pv.date.month, pv.date.year, pv.time.hrs, pv.time.min, pv.patientId, pv.staffId, pv.diagnosis, pv.doctor, pv.medicine.qty, pv.medicine.name, pv.charges, pv.receiptNo, pv.lstModified.day, pv.lstModified.month, pv.lstModified.year);
		pCount++;
	}
	printf("%-18s %-12s %-10s %-18s %-13s %-19s %-9s %-13s %s\n", "================", "==========", "========", "================", "===========", "=================", "=======", "===========", "=============");
	printf("Total %d patient(s) recorded.\n", pCount);

	fclose(fptr);
}

// To add a new record for the patient visiting information database
void addPv(SYSTEMTIME t) {
	PatientVisit pv;
	char yesno, ans;

	FILE *fptr;
	// Open the binary file for appending
	fptr = fopen(PATIENTVISIT, "ab"); 
	
	checkFile(fptr);

	do {
		// Get the current time from the computer system
		GetLocalTime(&t);
		// Update the newest date to new record based on the system date
		pv.date.day = t.wDay;
		pv.date.month = t.wMonth;
		pv.date.year = t.wYear;

		pv.time.hrs = t.wHour;
		pv.time.min = t.wMinute;

		
		printf("\nEnter staff's ID                  > ");
		rewind(stdin);
		scanf("%[^\n]", pv.staffId);
		printf("===========================================\n");


		do {
			printf("Enter patient's ID            > ");
			rewind(stdin);
			scanf("%[^\n]", pv.patientId);

			printf("Enter the patient's Diagnosis > ");
			rewind(stdin);
			scanf("%[^\n]", pv.diagnosis);

			printf("Enter doctor in charges       > ");
			rewind(stdin);
			scanf("%[^\n]", pv.doctor);

			printf("\nEnter medicine given:\n");
			printf("-----------------------\n");
			printf("Name                          > ");
			rewind(stdin);
			scanf("%[^\n]", pv.medicine.name);

			printf("Quantity                      > ");
			rewind(stdin);
			scanf("%d", &pv.medicine.qty);
			printf("-----------------------\n");

			printf("Enter the charges             > ");
			scanf("%lf", &pv.charges);

			printf("Enter the receipt No.         > ");
			rewind(stdin);
			scanf("%s", pv.receiptNo);

			// Ask user whether wants to continue to add records as a same staff
			
			
			pv.lstModified.day = t.wDay;
			pv.lstModified.month = t.wMonth;
			pv.lstModified.year = t.wYear;

			// To update the record from the variables into the file
			fwrite(&pv, sizeof(pv), 1, fptr);
			printf("\nRecord updated...\n\n");

			printf("Continue to add records as a same staff?(Y = Yes) > ");
			rewind(stdin);
			scanf("%c", &ans);
			ans = toupper(ans);

		} while (ans == 'Y');

		printf("\n===========================================\n");

		// Ask user whether wants to continue to add records
		printf("Continue to add records?(Y = Yes) > ");
		rewind(stdin);
		scanf("%c", &yesno);
		yesno = toupper(yesno);

	} while (yesno == 'Y');

	fclose(fptr);
}

// To search a record in the patient visiting information database
void searchPv() {
	PatientVisit pv;
	int pCount = 0;
	char patientSearch[41], ans, receiptNo[21];

	FILE *fptr;
	do {
		// Open the binary file for reading
		fptr = fopen(PATIENTVISIT, "rb");
		
		checkFile(fptr);

		printf("\nEnter the Receipt No. to search > ");
		scanf("%s", patientSearch);
		rewind(stdin);

		printf("\n%-18s %-12s %-10s %-18s %-13s %-19s %-9s %-13s %s\n", "Date/Time", "Patient ID", "Staff ID", "Diagnosis", "Doctor Name", "Medicine Given", "Cost", "Receipt No.", "Last Modified");
		printf("%-18s %-12s %-10s %-18s %-13s %-19s %-9s %-13s %s\n", "================", "==========", "========", "================", "===========", "=================", "=======", "===========", "=============");
		while (fread(&pv, sizeof(pv), 1, fptr) != 0) {
			if (strcmp(patientSearch, pv.receiptNo) == 0) {
				printf("%02d-%02d-%04d %02d:%02d   %-12s %-10s %-18s %-13s %-2d%-17s %-9.2lf %-13s %02d-%02d-%04d\n", pv.date.day, pv.date.month, pv.date.year, pv.time.hrs, pv.time.min, pv.patientId, pv.staffId, pv.diagnosis, pv.doctor, pv.medicine.qty, pv.medicine.name, pv.charges, pv.receiptNo, pv.lstModified.day, pv.lstModified.month, pv.lstModified.year);
				strcpy(receiptNo, pv.receiptNo);
			}
		}
		printf("%-18s %-12s %-10s %-18s %-13s %-19s %-9s %-13s %s\n", "================", "==========", "========", "================", "===========", "=================", "=======", "===========", "=============");
		if (strcmp(patientSearch, receiptNo) == 0)
			printf("Record Found!!\n");
		else
			printf("Record Not Found\n");

		printf("\nContinue to search?(Y = Yes) > ");
		rewind(stdin);
		scanf("%c", &ans);
		ans = toupper(ans);

		fclose(fptr);
	} while (ans == 'Y');
}

// To modify a record in the patient visiting information database
void modifyPv(SYSTEMTIME t) {
	PatientVisit pvTemp, pv[MAX_SIZE], pvModify;
	char ansConfirm, yesno, receiptNo[11], ansModify, ansConfirmModify;
	int i, option, pCount = 0; // Patient count

	FILE *fptr;
	// Open the binary file for reading
	fptr = fopen(PATIENTVISIT, "rb");

	checkFile(fptr);
	printf("\n");

	do {
		

		// To read the data and information from the file into the array
		for (i = 0; i < MAX_SIZE; i++) {
			if (fread(&pvTemp, sizeof(PatientVisit), 1, fptr) != 0) {
				pv[i] = pvTemp;
				pCount++;
			}
		}

		// Enter the data to search the patient visit information to modify
		printf("Enter Receipt No. to modify > ");
		rewind(stdin);
		scanf("%s", receiptNo);

		
		for (i = 0; i < MAX_SIZE; i++) {
			// Match the record from the array
			if (strcmp(receiptNo, pv[i].receiptNo) == 0) {
				printf("\nRecord found!!\n");
				printf("%-18s %-12s %-10s %-18s %-13s %-19s %-9s %-13s %s\n", "Date/Time", "Patient ID", "Staff ID", "Diagnosis", "Doctor Name", "Medicine Given", "Cost", "Receipt No.", "Last Modified");
				printf("%-18s %-12s %-10s %-18s %-13s %-19s %-9s %-13s %s\n", "================", "==========", "========", "================", "===========", "=================", "=======", "===========", "=============");
				printf("%02d-%02d-%04d %02d:%02d   %-12s %-10s %-18s %-13s %-2d%-17s %-9.2lf %-13s %02d-%02d-%04d\n", pv[i].date.day, pv[i].date.month, pv[i].date.year, pv[i].time.hrs, pv[i].time.min, pv[i].patientId, pv[i].staffId, pv[i].diagnosis, pv[i].doctor, pv[i].medicine.qty, pv[i].medicine.name, pv[i].charges, pv[i].receiptNo, pv[i].lstModified.day, pv[i].lstModified.month, pv[i].lstModified.year);
				printf("%-18s %-12s %-10s %-18s %-13s %-19s %-9s %-13s %s\n\n", "================", "==========", "========", "================", "===========", "=================", "=======", "===========", "=============");

				// Ask the user whether want to modify this record
				printf("Modify this record? (Y = yes) > ");
				rewind(stdin);
				scanf("%c", &ansConfirm);
				ansConfirm = toupper(ansConfirm);

				if (ansConfirm == 'Y') {
					do {
						// List the options for the user to modify
						printf("\nOptions\n");
						printf("===========================\n");
						printf("1 : Date\n");
						printf("2 : Time\n");
						printf("3 : Staff's ID\n");
						printf("4 : Patient's Diagnosis\n");
						printf("5 : Doctor In Charges\n");
						printf("6 : Medicine\n");
						printf("7 : Charges\n");
						printf("8 : Patient's ID\n");
						printf("===========================\n");

						do {
							printf("Choose options to modify > ");
							scanf("%d", &option);
							option = toupper(option);
							rewind(stdin);

							printf("\n");
							if (option == 1) {
								printf("Enter New Date (dd/mm/yy) > ");
								scanf("%d %d %d", &pv[i].date.day, &pv[i].date.month, &pv[i].date.year);
							}
							else if (option == 2) {
								printf("Enter New Time (hrs min) > ");
								scanf("%d %d", &pv[i].time.hrs, &pv[i].time.min);
							}
							else if (option == 3) {
								printf("Enter staff's ID > ");
								scanf("%[^\n]", pv[i].staffId);
							}
							else if (option == 4) {
								printf("Enter the patient's Diagnosis > ");
								scanf("%[^\n]", pv[i].diagnosis);
							}
							else if (option == 5) {
								printf("Enter doctor in charges > ");
								scanf("%[^\n]", pv[i].doctor);
							}
							else if (option == 6) {
								printf("Medicine for customer:\n");
								printf("Name > ");
								scanf("%[^\n]", pv[i].medicine.name);

								printf("Quantity > ");
								rewind(stdin);
								scanf("%d", &pv[i].medicine.qty);
							}
							else if (option == 7) {
								printf("Enter the charges > ");
								scanf("%lf", &pv[i].charges);
							}
							else if (option == 8) {
								printf("Enter the patient's ID > ");
								rewind(stdin);
								scanf("%s", pv[i].patientId);
							}
							else
								printf("Invalid option. Please enter again.\n");

						} while (!(option >= 1 && option <= 8));

						fclose(fptr);

						printf("\nConfirm to modify? (Y = Yes) > ");
						rewind(stdin);
						scanf("%c", &ansConfirmModify);
						ansConfirmModify = toupper(ansConfirmModify);
						
						if (ansConfirmModify == 'Y') {
							// Open the binary file for writing
							fptr = fopen("patientlist.bin", "wb");

							// To check whether the file has been successfully opened
							checkFile(fptr);

							// Get the current time from the computer system
							GetLocalTime(&t);
							// Update the time into the array
							pv[i].lstModified.day = t.wDay;
							pv[i].lstModified.month = t.wMonth;
							pv[i].lstModified.year = t.wYear;

							// Re-assign the data and information into the existing binary file (Modified Data)
							fwrite(&pv, sizeof(PatientVisit), pCount, fptr);

							printf("Modify Successfully.\n");
						}
						else
							printf("Cancelled.\n");
						
						printf("\nContinue modify the same patient? (Y = Yes) > ");
						rewind(stdin);
						scanf("%c", &ansModify);
						ansModify = toupper(ansModify);
					} while (ansModify == 'Y');
				}
				else
					printf("Cancelled.\n");

				
			}
		}
		printf("\nContinue to modify? (Y = Yes) > ");
		rewind(stdin);
		scanf("%c", &yesno);
		yesno = toupper(yesno);
	} while (yesno == 'Y');

	fclose(fptr);
}

// To delete a record in the patient visiting information database
void deletePv() {
	int i, n, pCount = 0, deleted = 0;
	char yesno, ans, receiptNo[11];

	PatientVisit pvTemp, pv[MAX_SIZE] = { 0 };

	FILE *fptr;
	// Open the binary file for reading
	fptr = fopen(PATIENTVISIT, "rb");

	checkFile(fptr);

	// To read the data and information from the file into the array
	for (i = 0; i < MAX_SIZE; i++) {
		if (fread(&pvTemp, sizeof(PatientVisit), 1, fptr) != 0) {
			pv[i] = pvTemp;
			pCount++;
		}
	}

	printf("\nDeleting Function Processing...");

	do {
		// Enter the data to search the patient visits record
		printf("\nEnter Receipt No. To Delete > ");
		scanf("%s", receiptNo);
		rewind(stdin);

		// Find the patient visits record
		for (i = 0; i < pCount; i++) {
			if (strcmp(receiptNo, pv[i].receiptNo) == 0) {
				printf("\nMatching Record Found!!\n");
				printf("%-18s %-12s %-10s %-18s %-13s %-19s %-9s %-13s %s\n", "Date/Time", "Patient ID", "Staff ID", "Diagnosis", "Doctor Name", "Medicine Given", "Cost", "Receipt No.", "Last Modified");
				printf("%-18s %-12s %-10s %-18s %-13s %-19s %-9s %-13s %s\n", "================", "==========", "========", "================", "===========", "=================", "=======", "===========", "=============");
				printf("%02d-%02d-%04d %02d:%02d   %-12s %-10s %-18s %-13s %-2d%-17s %-9.2lf %-13s %02d-%02d-%04d\n", pv[i].date.day, pv[i].date.month, pv[i].date.year, pv[i].time.hrs, pv[i].time.min, pv[i].patientId, pv[i].staffId, pv[i].diagnosis, pv[i].doctor, pv[i].medicine.qty, pv[i].medicine.name, pv[i].charges, pv[i].receiptNo, pv[i].lstModified.day, pv[i].lstModified.month, pv[i].lstModified.year);
				printf("%-18s %-12s %-10s %-18s %-13s %-19s %-9s %-13s %s\n", "================", "==========", "========", "================", "===========", "=================", "=======", "===========", "=============");

				printf("Confirm Delete Record?(Y= Yes) > ");
				scanf("%c", &yesno);
				yesno = toupper(yesno);
				rewind(stdin);

				if (yesno == 'Y') {

					for (n = i; n < pCount; n++) {
						pv[n] = pv[n + 1];
					}
					deleted++;
					pCount--;
				}
			}
		}

		// Ask the user whether continue to on deleting process
		printf("\nContinue to Delete?(Y = Yes) > ");
		scanf("%c", &ans);
		ans = toupper(ans);
		rewind(stdin);

		if (ans != 'Y')
			printf("Total %d patient visiting record(s) deleted.\n\n", deleted);

	} while (ans == 'Y');

	fclose(fptr);

	// Open the binary file for writing
	fptr = fopen("patientlist.bin", "wb");

	checkFile(fptr);

	// Re-assign the data and information into the existing binary file (New Data)
	fwrite(&pv, sizeof(PatientVisit), pCount, fptr);


	printf("Record updated...");

	fclose(fptr);
}

// To view all the patients visited information on a specific day
void viewPatientVisited() {
	PatientVisit pv;
	struct Date pvSearch;
	int patientNo = 0, medicineGiven = 0;
	double chargesCollected = 0;

	FILE *fptr;
	// Open the binary file for reading
	fptr = fopen(PATIENTVISIT, "rb");

	checkFile(fptr);

	// Ask the user to enter the date to view daily report
	printf("\nEnter date to view patient list(dd/mm/yy) > ");
	rewind(stdin);
	scanf("%d %d %d", &pvSearch.day, &pvSearch.month, &pvSearch.year);

	// Display all the patient visits information based on the date that the user entered
	printf("\n%-8s %-12s %-10s %-18s %-13s %-19s %-9s %-13s %s\n", "Time", "Patient ID", "Staff ID", "Diagnosis", "Doctor Name", "Medicine Given", "Cost", "Receipt No.", "Last Modified");
	printf("%-8s %-12s %-10s %-18s %-13s %-19s %-9s %-13s %s\n", "=======", "==========", "========", "================", "===========", "=================", "=======", "===========", "=============");
	while (fread(&pv, sizeof(pv), 1, fptr) != 0) {
		if (pvSearch.day == pv.date.day && pvSearch.month == pv.date.month && pvSearch.year == pv.date.year) {
			printf("%02d:%02d    %-12s %-10s %-18s %-13s %-2d%-17s %-9.2lf %-13s %02d-%02d-%04d\n", pv.time.hrs, pv.time.min, pv.patientId, pv.staffId, pv.diagnosis, pv.doctor, pv.medicine.qty, pv.medicine.name, pv.charges, pv.receiptNo, pv.lstModified.day, pv.lstModified.month, pv.lstModified.year);
			patientNo++;
		}
	}
	printf("%-8s %-12s %-10s %-18s %-13s %-19s %-9s %-13s %s\n", "=======", "==========", "========", "================", "===========", "=================", "=======", "===========", "=============");
	printf("Total %d patient(s) visited on %02d-%02d-%04d.\n\n", patientNo, pvSearch.day, pvSearch.month, pvSearch.year);

	fclose(fptr);
}

// To display a daily report
void displayReport() {
	PatientVisit pv;
	struct Date pvSearch;
	int patientNo = 0, medicineGiven = 0;
	double chargesCollected = 0;

	FILE *fptr;
	// Open the binary file for reading
	fptr = fopen(PATIENTVISIT, "rb");

	checkFile(fptr);

	// Ask the user to enter the date to view daily report
	printf("\nEnter date to view report (dd/mm/yy) > ");
	rewind(stdin);
	scanf("%d %d %d", &pvSearch.day, &pvSearch.month, &pvSearch.year);

	// Calculate all the number of patient visited, charges collected and number of medicine given based on a day
	while (fread(&pv, sizeof(pv), 1, fptr) != 0) {
		if (pvSearch.day == pv.date.day && pvSearch.month == pv.date.month && pvSearch.year == pv.date.year) {
			chargesCollected += pv.charges;
			medicineGiven += pv.medicine.qty;
			patientNo++;
		}
	}

	// Display all the calculated information
	printf("\nOn %02d-%02d-%04d\n", pvSearch.day, pvSearch.month, pvSearch.year);
	printf("======================\n");
	printf("Total of patient visit record(s) = %d\n", patientNo);
	printf("Total charges collect = %.2lf\n", chargesCollected);
	printf("Total of medicine given = %d\n", medicineGiven);

	fclose(fptr);
}

// To check whether the file has been successfully opened
void checkFile(FILE *fptr) {
	if (fptr == NULL) {
		printf("Cannot open file <patientlist.bin>.\n");
		system("pause");
		exit(-1);
	}
}