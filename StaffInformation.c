/* <Staff Information Module>
Project Name   : StaffInformation.c
Written By     : Foo Jia Ern
Student ID     : 18WMD01662
Course Name    : Diploma In Science (Computer Science and Computer Mathematics)
Tutorial Group : 2
Purpose        : To store the information of medical staff, i.e doctor and nurse
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#pragma warning (disable:4996)
#define OT 8
#define MAXSIZE 50

struct Remuneration
{
	double basicSalary, totalSalary, bonus;
	int ot;
};

struct DateEmployed
{
	int day, month, year;

};

typedef struct
{
	char id[5], name[20], ic[15], designation[20], gender, hpNo[12], address[35], qualification[50];
	int leave;

	struct Remuneration wages;
	struct DateEmployed dateEmployed;

}PersonalInfo;

void menuStaff(int *choice);                            //diplay menu for the user to choose and return user's choice using output parameter.
void addStaff(PersonalInfo pInfo);                      //enable the user to add new staff record.
void displayStaff(PersonalInfo pInfo);                  //display staff records.
void modifyStaff();                                     //modify staff records stored in file.
void searchStaff(PersonalInfo pInfo);                   //search staffs based on specific criteria.
void viewStaff(PersonalInfo pInfo);                     //view particular staff information based on staff name.
void benefitStaff(PersonalInfo pInfo);                  //check whether a particular staff has used the free health service provided by the clinic or not.
int override();                                         //to check whether user name and password input is correct
PersonalInfo payroll(PersonalInfo pInfo);               //calculate bonus and total salary the staff should have.

void staffInformation() {
	PersonalInfo pInfo = { NULL };
	int choice;

	do {                                                      //enable the user to enter choice when not equal to exit.
		menuStaff(&choice);									  //menu function return user's choice using output parameter.

		
		switch (choice) {                                    //function is called based on the choice of the user.
		case 1:
			if (override()) {
				addStaff(pInfo);
				break;
			}
			else
				break;

		case 2:
			displayStaff(pInfo);
			break;

		case 3:
			if (override()) {
				modifyStaff();
				break;
			}
			else
				break;

		case 4:
			viewStaff(pInfo);
			break;

		case 5:
			benefitStaff(pInfo);
			break;

		case 6:
			searchStaff(pInfo);
			break;

		case 7:
			printf("Bye-bye\n");
			break;

		default:
			printf("Invalid option! Please enter your choice again!\n");
		}
	} while (choice != 7);

	system("pause");
	system("cls");
}

void menuStaff(int *choice)                                     
{
	printf("*\\_/*\\_/*\\_/*\\_/*\\_/*\\_/*\n");
	printf("* Staff MENU            *\n");
	printf("* ============          *\n");
	printf("* 1. Add staff          *\n");
	printf("* 2. Display staff      *\n");
	printf("* 3. Modify staff       *\n");
	printf("* 4. View staff         *\n");
	printf("* 5. Benefit of staff   *\n");
	printf("* 6. Search staff       *\n");
	printf("* 7. Exit               *\n");
	printf("*\\_/*\\_/*\\_/*\\_/*\\_/*\\_/*\n");
	printf("Enter your choice: ");
	scanf(" %d", &*choice);                                //user input their choice.
}

void addStaff(PersonalInfo pInfo) {                        
	FILE *fp;

	int no = 1, staffAdd = 0;
	char ans, option;

	fp = fopen("staff.txt", "a");                          //staff.txt file is open for appending new staff record entered.

	if (fp == NULL) {
		printf("Error! Cannot open staff.txt file!\n\n");
		system("pause");
		exit(0);
	}

	do {
		printf("*******************************************************\n");   //enter new staff records 
		printf("Enter %d staff ID (EXIT = -999)        : ", no);
		scanf(" %[^\n]", &pInfo.id);

		if (strcmp(pInfo.id, "-999") == 0)
			break;
		else {
			printf("Enter %d staff Name                    : ", no);
			scanf(" %[^\n]", &pInfo.name);
			printf("Enter %d staff IC                      : ", no);
			scanf(" %[^\n]", &pInfo.ic);
			printf("Enter %d staff Designation             : ", no);
			scanf(" %[^\n]", &pInfo.designation);
			printf("Enter %d staff gender                  : ", no);
			scanf(" %c", &pInfo.gender);

			while (pInfo.gender != 'M' && pInfo.gender != 'F')
			{
				printf("Invalid gender!!! Please enter again\n");

				printf("Enter %d staff gender : ", no);
				rewind(stdin);
				scanf("%c", &pInfo.gender);
			}

			printf("Enter %d staff Contact No.             : ", no);
			scanf(" %[^\n]", &pInfo.hpNo);
			printf("Enter %d staff Address                 : ", no);
			scanf(" %[^\n]", &pInfo.address);
			printf("Enter %d staff Qualification           : ", no);
			scanf(" %[^\n]", &pInfo.qualification);
			printf("Enter %d staff Date Employed (dd-mm-yy): ", no);
			scanf(" %d-%d-%d", &pInfo.dateEmployed.day, &pInfo.dateEmployed.month, &pInfo.dateEmployed.year);
			printf("Enter %d staff Basic Salary            : ", no);
			scanf(" %lf", &pInfo.wages.basicSalary);
			printf("Enter %d staff OT hour(s)              : ", no);
			scanf(" %d", &pInfo.wages.ot);
			printf("Enter %d staff leave(day)              : ", no);
			scanf(" %d", &pInfo.leave);

			pInfo = payroll(pInfo);                           //payroll function is called to calculate bonus.
			fprintf(fp, "%s|%s|%s|%s|%c|%s|%s|%s|%d-%d-%d|%lf|%lf|%d|%d|%lf\n", pInfo.id, pInfo.name, pInfo.ic, pInfo.designation, pInfo.gender, pInfo.hpNo, pInfo.address, pInfo.qualification, pInfo.dateEmployed.day, pInfo.dateEmployed.month, pInfo.dateEmployed.year, pInfo.wages.basicSalary, pInfo.wages.totalSalary, pInfo.wages.ot, pInfo.leave, pInfo.wages.bonus);    //records of new staff is appended into the file

			printf("*******************************************************\n");
			no++;
			staffAdd++;                                      //calculate number of new staff added.

			printf("Any more new staff records (Y/N): ");    //ask the user if still wanted to add anymore new staff record.
			scanf(" %c", &ans);
		}
	} while (toupper(ans) == 'Y');                       //user continue to add new staff record if ans is Yes.
	printf("< %d staff(s) added.>\n\n", staffAdd);

	fclose(fp);
}

void displayStaff(PersonalInfo pInfo) {                   
	FILE *fp;
	
	int staffCount = 0, choice;

	fp = fopen("staff.txt", "r");                          //staff.txt file is open for reading staff records only.

	if (fp == NULL) {
		printf("Error! Cannot open staff.txt file!\n\n");
		system("pause");
		exit(0);
	}

	SYSTEMTIME t;
	GetLocalTime(&t);

	printf("<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("< Display:                                   >\n");
	printf("< 1. Personal Info                           >\n");            //display general information of staffs
	printf("< 2. Employment Info (password required)     >\n");            //display employment information of staff for management only (user id and password is required).
	printf("<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("Enter your choice: ");
	scanf(" %d", &choice);

	if (choice == 1) {
		printf("Staff details - as at %d-%d-%d\n", t.wDay, t.wMonth, t.wYear);
		printf("                                                             STAFF INFORMATION\n");                   //print general information of staffs.
		printf("ID     Name             IC                Designation    Gender    Contact NO.    Address                          Qualification            Date Employed\n");
		printf("==     ====             ==                ===========    ======    ===========    =======                          =============            =============\n");
		while (fscanf(fp, "%[^\|]|%[^\|]|%[^\|]|%[^\|]|%c|%[^\|]|%[^\|]|%[^\|]|%d-%d-%d|%lf|%lf|%d|%d|%lf\n", &pInfo.id, &pInfo.name, &pInfo.ic, &pInfo.designation, &pInfo.gender, &pInfo.hpNo, &pInfo.address, &pInfo.qualification, &pInfo.dateEmployed.day, &pInfo.dateEmployed.month, &pInfo.dateEmployed.year, &pInfo.wages.basicSalary, &pInfo.wages.totalSalary, &pInfo.wages.ot, &pInfo.leave, &pInfo.wages.bonus) != EOF) {
			printf("%-6s %-16s %-17s %-16s %-5c   %-14s %-32s %-25s %02d-%02d-%4d \n", pInfo.id, pInfo.name, pInfo.ic, pInfo.designation, pInfo.gender, pInfo.hpNo, pInfo.address, pInfo.qualification, pInfo.dateEmployed.day, pInfo.dateEmployed.month, pInfo.dateEmployed.year);

			staffCount++;                                          //sum up total number of staff.
		}
		printf("< %d staff(s) listed>\n\n", staffCount);           //print the total number of staff.
	}
	else if (choice == 2) {
		if (override()) {
			staffCount = 0;

			printf("Staff details - as at %d-%d-%d\n", t.wDay, t.wMonth, t.wYear);
			printf("                                                        STAFF INFORMATION\n");                   //display information of that particular staff.
			printf("ID     Name             IC                Designation    Gender    Total Salary(RM)    Salary(RM)    OT(hr)    Leave    Bonus(RM)\n");
			printf("==     ====             ==                ===========    ======    ================    ==========    ======    =====    =========\n");

			while (fscanf(fp, "%[^\|]|%[^\|]|%[^\|]|%[^\|]|%c|%[^\|]|%[^\|]|%[^\|]|%d-%d-%d|%lf|%lf|%d|%d|%lf\n", &pInfo.id, &pInfo.name, &pInfo.ic, &pInfo.designation, &pInfo.gender, &pInfo.hpNo, &pInfo.address, &pInfo.qualification, &pInfo.dateEmployed.day, &pInfo.dateEmployed.month, &pInfo.dateEmployed.year, &pInfo.wages.basicSalary, &pInfo.wages.totalSalary, &pInfo.wages.ot, &pInfo.leave, &pInfo.wages.bonus) != EOF) {
				printf("%-6s %-16s %-17s %-16s %-7c %16.2lf %13.2lf %9d %8d %12.2lf\n", pInfo.id, pInfo.name, pInfo.ic, pInfo.designation, pInfo.gender, pInfo.wages.totalSalary, pInfo.wages.basicSalary, pInfo.wages.ot, pInfo.leave, pInfo.wages.bonus);

				staffCount++;                                     //sum up total number of staff.
			}
			printf("< %d staff(s) listed>\n\n", staffCount);       //print the total number of staff.
		}
		else
			printf("Employment info can't be displayed!\n");        //employment information won't be display when user override functoion return 0.
	}
	fclose(fp);
}

void modifyStaff() {                    
	PersonalInfo pITemp[MAXSIZE], pInfo[MAXSIZE];
	FILE *fp;

	int staffCount = 0, i = 0, choice, modifyCount = 0, found = 0;
	char staffID[5], confirmation, modify, modifyStaff;

	fp = fopen("staff.txt", "r");                    //staff.txt file is open for reading staff records only.

	if (fp == NULL) {
		printf("Error! Cannot open staff.txt file!\n\n");
		system("pause");
		exit(0);
	}

	for (i = 0; i < MAXSIZE; i++) {                           //staff rocords which are stored in struct pIfo is copied to another struct pITemp.
		while (fscanf(fp, "%[^\|]|%[^\|]|%[^\|]|%[^\|]|%c|%[^\|]|%[^\|]|%[^\|]|%d-%d-%d|%lf|%lf|%d|%d|%lf\n", &pInfo[i].id, &pInfo[i].name, &pInfo[i].ic, &pInfo[i].designation, &pInfo[i].gender, &pInfo[i].hpNo, &pInfo[i].address, &pInfo[i].qualification, &pInfo[i].dateEmployed.day, &pInfo[i].dateEmployed.month, &pInfo[i].dateEmployed.year, &pInfo[i].wages.basicSalary, &pInfo[i].wages.totalSalary, &pInfo[i].wages.ot, &pInfo[i].leave, &pInfo[i].wages.bonus) != EOF) {
			strcpy(pITemp[i].id, pInfo[i].id);
			strcpy(pITemp[i].name, pInfo[i].name);
			strcpy(pITemp[i].ic, pInfo[i].ic);
			strcpy(pITemp[i].designation, pInfo[i].designation);
			pITemp[i].gender = pInfo[i].gender;
			strcpy(pITemp[i].hpNo, pInfo[i].hpNo);
			strcpy(pITemp[i].address, pInfo[i].address);
			strcpy(pITemp[i].qualification, pInfo[i].qualification);
			pITemp[i].dateEmployed.day = pInfo[i].dateEmployed.day;
			pITemp[i].dateEmployed.month = pInfo[i].dateEmployed.month;
			pITemp[i].dateEmployed.year = pInfo[i].dateEmployed.year;
			pITemp[i].wages.basicSalary = pInfo[i].wages.basicSalary;
			pITemp[i].wages.totalSalary = pInfo[i].wages.totalSalary;
			pITemp[i].wages.ot = pInfo[i].wages.ot;
			pITemp[i].leave = pInfo[i].leave;
			pITemp[i].wages.bonus = pInfo[i].wages.bonus;

			staffCount++;                           ////sum up total number of staff.
			break;
		}
	}
	do {
		printf("Enter Staff ID to be modified: ");         //user have to input staff id to modify that particular staff.
		scanf(" %[^\n]", &staffID);
		for (i = 0; i < staffCount; i++) {                     //loop is used to compare staff id input with every staff id records stored in the file.
			if (strcmp(staffID, pITemp[i].id) == 0) {
				found = 1;
				do {
					printf("================================================\n");        //display that particular staff information.
					printf("Staff ID             : %s\n", pITemp[i].id);
					printf("Staff Name           : %s\n", pITemp[i].name);
					printf("Staff IC             : %s\n", pITemp[i].ic);
					printf("Staff Designation    : %s\n", pITemp[i].designation);
					printf("Staff Gender         : %c\n", pITemp[i].gender);
					printf("Staff Contact No.    : %s\n", pITemp[i].hpNo);
					printf("Staff Address        : %s\n", pITemp[i].address);
					printf("Staff Qualification  : %s\n", pITemp[i].qualification);
					printf("Staff Date Employed  : %d-%d-%d\n", pITemp[i].dateEmployed.day, pITemp[i].dateEmployed.month, pITemp[i].dateEmployed.year);
					printf("Staff Salary         : %lf\n", pITemp[i].wages.basicSalary);
					printf("Staff OT             : %d\n", pITemp[i].wages.ot);
					printf("Staff Leave          : %d\n", pITemp[i].leave);
					printf("================================================\n\n");

					printf("Changes on:\n");                      //display the menu on which changes is chosed to modify for that particular staff.
					printf("1. Name\n");
					printf("2. IC\n");
					printf("3. Designation\n");
					printf("4. Gender\n");
					printf("5. Contact No.\n");
					printf("6. Address\n");
					printf("7. Qualification\n");
					printf("8. Date Employed\n");
					printf("9. Salary\n");
					printf("10. OT\n");
					printf("11. Leave\n");
					printf("================================================\n");
					printf("Enter choice: ");                       //user input which choice of changes to be made on a particular staff.
					scanf(" %d", &choice);

					switch (choice) {
					case 1:
						printf("Enter new name: ");
						scanf(" %[^\n]", pInfo[i].name);
						break;

					case 2:
						printf("Enter new IC: ");
						scanf(" %[^\n]", pInfo[i].ic);
						break;

					case 3:
						printf("Enter new designation: ");
						scanf(" %[^\n]", pInfo[i].designation);
						break;

					case 4:
						printf("Enter new gender: ");
						scanf(" %c", &pInfo[i].gender);
						break;

					case 5:
						printf("Enter new contact no.: ");
						scanf(" %[^\n]", pInfo[i].hpNo);
						break;

					case 6:
						printf("Enter new address: ");
						scanf(" %[^\n]", pInfo[i].address);
						break;

					case 7:
						printf("Enter new qualification: ");
						scanf(" %[^\n]", pInfo[i].qualification);
						break;

					case 8:
						printf("Enter new date employed: ");
						scanf(" %d-%d-%d", &pInfo[i].dateEmployed.day, &pInfo[i].dateEmployed.month, &pInfo[i].dateEmployed.year);
						break;

					case 9:
						printf("Enter new salary: ");
						scanf(" %lf", &pInfo[i].wages.basicSalary);
						break;

					case 10:
						printf("Enter OT hour(s) : ");
						scanf(" %d", &pInfo[i].wages.ot);
						break;

					case 11:
						printf("Enter new leave: ");
						scanf(" %d", &pInfo[i].leave);
						break;

					default:
						printf("Invalid option!\n");

					}
					printf("Sure to modify(YES= Y): ");                   //confirm with the user sure or not to modify the staff information.
					scanf(" %c", &confirmation);

					if (confirmation == 'Y') {                            //copy the changes in stuct pInfo into struct pITemp.
						switch (choice) {
						case 1:
							strcpy(pITemp[i].name, pInfo[i].name);
							break;

						case 2:
							strcpy(pITemp[i].ic, pInfo[i].ic);
							break;

						case 3:
							strcpy(pITemp[i].designation, pInfo[i].designation);
							break;

						case 4:
							pITemp[i].gender = pInfo[i].gender;
							break;

						case 5:
							strcpy(pITemp[i].hpNo, pInfo[i].hpNo);
							break;

						case 6:
							strcpy(pITemp[i].address, pInfo[i].address);
							break;

						case 7:
							strcpy(pITemp[i].qualification, pInfo[i].qualification);
							break;

						case 8:
							pITemp[i].dateEmployed.day = pInfo[i].dateEmployed.day;
							pITemp[i].dateEmployed.month = pInfo[i].dateEmployed.month;
							pITemp[i].dateEmployed.year = pInfo[i].dateEmployed.year;
							pInfo[i] = payroll(pInfo[i]);
							pITemp[i].wages.bonus = pInfo[i].wages.bonus;
							pITemp[i].wages.totalSalary = pInfo[i].wages.totalSalary;
							break;

						case 9:
							pITemp[i].wages.basicSalary = pInfo[i].wages.basicSalary;
							pInfo[i] = payroll(pInfo[i]);
							pITemp[i].wages.bonus = pInfo[i].wages.bonus;
							pITemp[i].wages.totalSalary = pInfo[i].wages.totalSalary;
							break;

						case 10:
							pITemp[i].wages.ot = pInfo[i].wages.ot;
							pInfo[i] = payroll(pInfo[i]);
							pITemp[i].wages.bonus = pInfo[i].wages.bonus;
							pITemp[i].wages.totalSalary = pInfo[i].wages.totalSalary;
							break;

						case 11:
							pITemp[i].leave = pInfo[i].leave;
							pInfo[i] = payroll(pInfo[i]);
							pITemp[i].wages.bonus = pInfo[i].wages.bonus;
							pITemp[i].wages.totalSalary = pInfo[i].wages.totalSalary;
							break;

						default:
							printf("Invalid option!\n");
						}
						printf("Record is updated!\n\n");
					}
					else
						printf("No record is updated!\n\n");

					printf("Continue to modify the same staff? (YES = Y): ");          //ask the user whether still want to continue to modify that particular staff.
					scanf(" %c", &modifyStaff);
				} while (toupper(modifyStaff) == 'Y');
				modifyCount++;                                             //sum up total number of staff that is successfully modified.
			}
		}
		if (found == 0)
			printf("Staff ID entered does not exist!!\n");
		printf("Do you still want to modify records(YES=Y): ");          //ask the user whether still want to continue to modify.
		scanf(" %c", &modify);
		printf("\n");
	} while (toupper(modify) == 'Y');

	printf("Numbers of staff(s) modify: %d\n", modifyCount);             //print total number of staff that is successfully modified.
	fclose(fp);

	fp = fopen("staff.txt", "w");                               //staff.txt file is open for writting staff records into the file.
	if (fp == NULL) {
		printf("Error! Cannot open staff.txt file!\n\n");
		system("pause");
		exit(0);
	}

	for (i = 0; i < staffCount; i++) {                        //write the latest staff records into file.

		fprintf(fp, "%s|%s|%s|%s|%c|%s|%s|%s|%d-%d-%d|%lf|%lf|%d|%d|%lf\n", pITemp[i].id, pITemp[i].name, pITemp[i].ic, pITemp[i].designation, pITemp[i].gender, pITemp[i].hpNo, pITemp[i].address, pITemp[i].qualification, pITemp[i].dateEmployed.day, pITemp[i].dateEmployed.month, pITemp[i].dateEmployed.year, pITemp[i].wages.basicSalary, pITemp[i].wages.totalSalary, pITemp[i].wages.ot, pITemp[i].leave, pITemp[i].wages.bonus);

	}

	fclose(fp);
}

void viewStaff(PersonalInfo pInfo) {               
	FILE *fp;

	int found = 0, choice;
	char name[20];

	fp = fopen("staff.txt", "r");                   //staff.txt file is open for reading staff records only.

	if (fp == NULL) {
		printf("Error! Cannot open staff.txt file!\n\n");
		system("pause");
		exit(0);
	}

	printf("<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("View:\n");
	printf("1. Personal Info\n");                           //view genral information of that particular staff.
	printf("2. Employment Info (password required)\n");     //view employment information of that particular staff.
	printf("<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("Enter your choice: ");
	scanf(" %d", &choice);

	if (choice == 1) {
		printf("Viewing based on:\n");                      //Prompt user to input staff name.
		printf("\t1. Name         :");
		scanf(" %[^\n]", &name);

		printf("                                                                      STAFF INFORMATION\n");                //display information of that particular staff.
		printf("ID     Name             IC                Designation    Gender    Contact NO.    Address                          Qualification           Date Employed\n");
		printf("==     ====             ==                ===========    ======    ===========    =======                          =============           =============\n");

		while (fscanf(fp, "%[^\|]|%[^\|]|%[^\|]|%[^\|]|%c|%[^\|]|%[^\|]|%[^\|]|%d-%d-%d|%lf|%lf|%d|%d|%lf\n", &pInfo.id, &pInfo.name, &pInfo.ic, &pInfo.designation, &pInfo.gender, &pInfo.hpNo, &pInfo.address, &pInfo.qualification, &pInfo.dateEmployed.day, &pInfo.dateEmployed.month, &pInfo.dateEmployed.year, &pInfo.wages.basicSalary, &pInfo.wages.totalSalary, &pInfo.wages.ot, &pInfo.leave, &pInfo.wages.bonus) != EOF) {
			if (strcmp(pInfo.name, name) == 0) {             //loop is used to compare staff name input with every staff name records stored in the file.
				printf("%-6s %-16s %-17s %-16s %-5c   %-14s %-32s %-24s %02d-%02d-%4d\n", pInfo.id, pInfo.name, pInfo.ic, pInfo.designation, pInfo.gender, pInfo.hpNo, pInfo.address, pInfo.qualification, pInfo.dateEmployed.day, pInfo.dateEmployed.month, pInfo.dateEmployed.year);
				found = 1;                           //if strcmp return true found equls to 1.
			}
		}

		printf("\n");
		if (found == 0)                              //print no employee info when found = 0.
			printf("No Employee info!\n");

	}
	else if (choice == 2) {
		if (override()) {
			printf("Viewing based on:\n");                    //Prompt user to input staff name.
			printf("\t1. Name         :");
			scanf(" %[^\n]", &name);

			printf("                                                        STAFF INFORMATION\n");                   //display information of that particular staff.
			printf("ID     Name             IC                Designation    Gender    Total Salary(RM)    Salary(RM)    OT(hr)    Leave    Bonus(RM)\n");
			printf("==     ====             ==                ===========    ======    ================    ==========    ======    =====    =========\n");

			while (fscanf(fp, "%[^\|]|%[^\|]|%[^\|]|%[^\|]|%c|%[^\|]|%[^\|]|%[^\|]|%d-%d-%d|%lf|%lf|%d|%d|%lf\n", &pInfo.id, &pInfo.name, &pInfo.ic, &pInfo.designation, &pInfo.gender, &pInfo.hpNo, &pInfo.address, &pInfo.qualification, &pInfo.dateEmployed.day, &pInfo.dateEmployed.month, &pInfo.dateEmployed.year, &pInfo.wages.basicSalary, &pInfo.wages.totalSalary, &pInfo.wages.ot, &pInfo.leave, &pInfo.wages.bonus) != EOF) {
				if (strcmp(name, pInfo.name) == 0) {            //loop is used to compare staff name input with every staff name records stored in the file. 
					printf("%-6s %-16s %-17s %-16s %-7c %16.2lf %13.2lf %9d %8d %12.2lf\n", pInfo.id, pInfo.name, pInfo.ic, pInfo.designation, pInfo.gender, pInfo.wages.totalSalary, pInfo.wages.basicSalary, pInfo.wages.ot, pInfo.leave, pInfo.wages.bonus);
					found = 1;                        //if strcmp return true found equls to 1.
				}
			}
			printf("\n");

			if (found == 0)                            //print no employee info when found = 0.
				printf("No Employee info!\n");
		}
	}
	fclose(fp);
}

void benefitStaff(PersonalInfo pInfo)                               //check whether a particular staff has used the free health service provided by the clinic or not.
{
	FILE *fp;

	int exist = 0, choice, regDay, regMonth, regYear, found = 0;
	char name[20], designation[20], hpNo[13], pId[9], pName[20], pGender, pContactNo[13], pAllergies[20];

	fp = fopen("staff.txt", "r");                   //staff.txt file is open for reading staff records only.

	if (fp == NULL) {
		printf("Error! Cannot open patientInfo.txt file!\n\n");
		system("pause");
		exit(0);
	}

	printf("Enter staff name: ");                     //prompt the user to enter staff name.
	scanf(" %[^\n]", name);
	printf("Enter staff contact number: ");           //prompt the user to enter staff contact number.
	scanf(" %[^\n]", hpNo);

	while (fscanf(fp, "%[^\|]|%[^\|]|%[^\|]|%[^\|]|%c|%[^\|]|%[^\|]|%[^\|]|%d-%d-%d|%lf|%lf|%d|%d|%lf\n", &pInfo.id, &pInfo.name, &pInfo.ic, &pInfo.designation, &pInfo.gender, &pInfo.hpNo, &pInfo.address, &pInfo.qualification, &pInfo.dateEmployed.day, &pInfo.dateEmployed.month, &pInfo.dateEmployed.year, &pInfo.wages.basicSalary, &pInfo.wages.totalSalary, &pInfo.wages.ot, &pInfo.leave, &pInfo.wages.bonus) != EOF) {
		if (strcmp(pInfo.name, name) == 0 && strcmp(pInfo.hpNo, hpNo) == 0) {             //loop is used to compare staff name input with every staff name records stored in the file.
			printf("Staff exist!\n");
			exist = 1;    //if strcmp return true found equls to 1.
			break;
		}
	}

	if (exist == 0)                            //print staff does not exist when found = 0.
		printf("Staff does not exist!\n");

	fclose(fp);

	fp = fopen("patientInfo.txt", "r");          //patientInfo.txt file is open for reading patient records only.

	while (fscanf(fp, "%d-%d-%d|%[^\|]|%[^\|]|%c|%[^\|]|%[^\n]\n", &regDay, &regMonth, &regYear, &pId, &pName, &pGender, &pContactNo, &pAllergies) != EOF) {
		if (strcmp(name, pName) == 0)
			if (strcmp(hpNo, pContactNo) == 0) {               //loop is used to compare staff name input and staff contact number input with every staff name and contact number records stored in the file.
				printf("%s had used the free health service.\n", name);
				found = 1;                                      //if strcmp return true found equls to 1.
				break;
			}

	}
	if (exist == 1)
		if (found == 0)                                  // //print staff still able to enjoy free health service when found = 0.
			printf("Staff can still enjoy the free health service.\n");

	fclose(fp);
	printf("\n");
}

void searchStaff(PersonalInfo pInfo) {                 
	FILE *fp;
	int i = 0, choice, yearEmployed = 0, staffCount = 0;
	char designation[20] = { NULL }, gender = { NULL };
	fp = fopen("staff.txt", "r");                       //staff.txt file is open for reading staff records only.      

	if (fp == NULL) {
		printf("Unable to open the file staffInfo.txt\n");
		system("pause");
		exit(-1);
	}

	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	printf("|| SEARCH MENU         ||\n");
	printf("|| 1. Designation      ||\n");
	printf("|| 2. Year Employed    ||\n");
	printf("|| 3. Gender           ||\n");
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	printf("Search satff's information based on one of the criteria (1-3): ");           //prompt user to input choice of criteria to search staffs which belongs to it.
	scanf("%d", &choice);

	switch (choice) {
	case 1:
		printf("Enter designation :");
		scanf(" %[^\n]", &designation);
		break;

	case 2:
		printf("Enter year employed :");
		scanf(" %d", &yearEmployed);
		break;

	case 3:
		printf("Enter staff gender :");
		scanf(" %c", &gender);
		break;

	default:
		printf("Invalid choice. Please try again!\n");
		return -1;
	}

	printf("                                                                      STAFF INFORMATION\n");   //display staff(s) that has the criteria.
	printf("ID     Name              IC                Designation    Gender    Contact NO.    Address                          Qualification           Date Employed\n");
	printf("==     ====              ==                ===========    ======    ===========    =======                          =============           =============\n");

	while (fscanf(fp, "%[^\|]|%[^\|]|%[^\|]|%[^\|]|%c|%[^\|]|%[^\|]|%[^\|]|%d-%d-%d|%lf|%lf|%d|%d|%lf\n", &pInfo.id, &pInfo.name, &pInfo.ic, &pInfo.designation, &pInfo.gender, &pInfo.hpNo, &pInfo.address, &pInfo.qualification, &pInfo.dateEmployed.day, &pInfo.dateEmployed.month, &pInfo.dateEmployed.year, &pInfo.wages.basicSalary, &pInfo.wages.totalSalary, &pInfo.wages.ot, &pInfo.leave, &pInfo.wages.bonus) != EOF) {
		if (strcmp(designation, pInfo.designation) == 0 || yearEmployed == pInfo.dateEmployed.year || gender == pInfo.gender) {
			printf("%-6s %-17s %-17s %-14s %-9c %-14s %-32s %-24s %02d-%02d-%4d\n", pInfo.id, pInfo.name, pInfo.ic, pInfo.designation, pInfo.gender, pInfo.hpNo, pInfo.address, pInfo.qualification, pInfo.dateEmployed.day, pInfo.dateEmployed.month, pInfo.dateEmployed.year);
			staffCount++;                      //sum up the number of staffs that have the criteria.
		}
	}
	printf("< %d staff(s) listed>\n\n", staffCount);      //display the total number of staffs that have the criteria.

	fclose(fp);
}

int override() {                              
	char password[10], username[8], password1[20], username1[8];

	int i = 0;

	strcpy(username, "uclinic");
	strcpy(password, "jefoo1352");

	printf(".....................................\n");
	printf("User ID and password required!!\n");
	printf(".....................................\n");
	printf(":Enter USER name : ");                                //prompt user to input user name
	scanf(" %[^\n]", &username1);
	printf(":Enter 9 digit password: ");                          //prompt user to input password
	scanf(" %[^\n]", &password1);
	printf(".....................................\n");

	if (strcmp(username, username1) == 0 && strcmp(password, password1) == 0) {     //to compare whwther user name and password input is correct
		printf("Correct username and password!\n\n");
		return 1;
	}
	else {
		printf("Invalid Password or Invalid ID\n\n");
		return 0;
	}
}

PersonalInfo payroll(PersonalInfo pInfo) {           
	FILE *fp;
	fp = fopen("staff.txt", "r");

	int leave, yearOfEmployment;

	SYSTEMTIME t;
	GetLocalTime(&t);                                            //get the current date.

	if (pInfo.dateEmployed.year == t.wYear)                      //bonus will not be given to the staff that is newly added.
		pInfo.wages.bonus = 0.0;
	else {
		yearOfEmployment = t.wYear - pInfo.dateEmployed.year;    //substract the current year with year employed of the staff to get how many years the staff have worked.

		if ((yearOfEmployment / 5) == 0)                         //get the maximum leave of that particular staff
			leave = 15;
		else if ((yearOfEmployment / 5) == 1)
			leave = 17;
		else if ((yearOfEmployment / 5) == 2)
			leave = 19;
		else
			leave = 20;

		if (pInfo.leave <= leave)                                   //bonus equals basic salary when leave equals to or less than maximum leave
			pInfo.wages.bonus = pInfo.wages.basicSalary;
		else                                                         //bonus equals zero when leave exceed maximum leave
			pInfo.wages.bonus = 0.0;
	}
	pInfo.wages.totalSalary = pInfo.wages.basicSalary + (pInfo.wages.ot *OT) + pInfo.wages.bonus;            //sum up basic salary with OT and bonus to get total salary

	return pInfo;
}
