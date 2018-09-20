/*	Filename: limJ.c
 	Programmed by: Johanna Koon Gan U. Lim
 	Last Modified: April 10, 2018
 	Version: 1 (The deleted game's folder is deleted)
 	Function/Purpose/Use: This program is a the back-end application for the Jeopardy Game.  	
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<dir.h>
#pragma GCC diagnostic ignored "-Wreturn-type"
#define MAX_CATEGORIES 4
#define MIN 0
#define QUESTION_LENGTH	200	
#define ANSWER_LENGTH 50
#define DIRECTORY_LENGTH 100
#define NAMES 35
#define NUM_OF_QandA 5
#define sChoiceLEN 255				

//this structure stores the categories' questions and answers 
struct sQA{	
	char sQuestion[QUESTION_LENGTH], 
		 sAnswer[ANSWER_LENGTH], 
	 	 sQuestionCAPS[QUESTION_LENGTH];
};

//this structure stores the category names and the structure sQAV
struct sCatNames{
	char sCategoryName[NAMES], 
	     sCategoryNameCAPS[NAMES];
	struct sQA s[NUM_OF_QandA];
};

//this structure stores the final jeopardy questions, answers, and value
struct finalJeopardy{
	char sFinalQuestion[QUESTION_LENGTH], 
		 sFinalAnswer[ANSWER_LENGTH];
};

//this structure stores the games and their contents
struct gameType{
	char gameName[NAMES];
	struct sCatNames sGCQA[MAX_CATEGORIES];
	struct finalJeopardy fj;
	int nNumOfCat;
	struct gameType *pLink;
};
typedef struct gameType gT;
typedef gT *gameTypePtr;

//this function returns the "values" of phase one fcn's choices
int getVal(char sChoice[]){
	if(strcmp("0",sChoice)==0) return 0;
	if(strcmp("1",sChoice)==0) return 1;
	if(strcmp("2",sChoice)==0) return 2;
	if(strcmp("3",sChoice)==0) return 3;
	if(strcmp("4",sChoice)==0) return 4;
	if(strcmp("5",sChoice)==0) return 5;
	if(strcmp("6",sChoice)==0) return 6;
	if(strcmp("7",sChoice)==0) return 7;
	if(strcmp("8",sChoice)==0) return 8;
	else return 9;
}

//this function returns the "values" of phase two fcn's choices
int getValPHASE2(char sChoice[]){
	if((strcmp("A",sChoice)==0)||(strcmp("a",sChoice)==0)) return 0;
	if((strcmp("D",sChoice)==0)||(strcmp("d",sChoice)==0)) return 1;
	if((strcmp("S",sChoice)==0)||(strcmp("s",sChoice)==0)) return 2;
	if((strcmp("V",sChoice)==0)||(strcmp("v",sChoice)==0)) return 3;
	if((strcmp("P",sChoice)==0)||(strcmp("p",sChoice)==0)) return 4;
	if((strcmp("E",sChoice)==0)||(strcmp("e",sChoice)==0)) return 5;
	else return 9;
}

//this function acquires and stores the uppercase forms of the stored category names and questions
gameTypePtr getUppercase(gameTypePtr pNode){
	int i, k;
	for(i=0;i<pNode->nNumOfCat;i++){
		strcpy(pNode->sGCQA[i].sCategoryNameCAPS,pNode->sGCQA[i].sCategoryName);
		strupr(pNode->sGCQA[i].sCategoryNameCAPS); //convert category names into uppercase form
		for(k=0;k<NUM_OF_QandA;k++){
			strcpy(pNode->sGCQA[i].s[k].sQuestionCAPS, pNode->sGCQA[i].s[k].sQuestion);
			strupr(pNode->sGCQA[i].s[k].sQuestionCAPS); //convert questions into uppercase form
		}
	}
}


//this function adds a category and its name, questions, and answers
int addCQA(gameTypePtr pNode){
	if(pNode->nNumOfCat==MAX_CATEGORIES)
		printf("Sorry, There Are Already Four Categories. Please Delete A Category first.\n");
	if(pNode->nNumOfCat<MAX_CATEGORIES){
		int i, j, nValue = 100, nCheck = 0, len, lenQ, lenA;
		char sUserInput[NAMES], sCatName[NAMES];
		printf("Enter Category Name: ");
		gets(sUserInput); strcpy(sCatName,sUserInput); len = strlen(sUserInput); strcat(sUserInput,"\n"); strupr(sUserInput);
		if(len==0)
			nCheck = 1;
		for(i=0;i<pNode->nNumOfCat;i++){
			if(strcmp(sUserInput,pNode->sGCQA[i].sCategoryNameCAPS)==0)
				nCheck = 1;
		}
		while(nCheck==1){
			printf("\nSorry, This Category Name Is Invalid Or It Already Exists.\nPlease Enter Another Name.\n\n");
			nCheck = 0;
			printf("Enter Category Name: ");
			gets(sUserInput); strcpy(sCatName,sUserInput); len = strlen(sUserInput); strcat(sUserInput,"\n"); strupr(sUserInput);
			if(len==0)
				nCheck = 1; 
			for(i=0;i<pNode->nNumOfCat;i++){
				if(strcmp(sUserInput,pNode->sGCQA[i].sCategoryNameCAPS)==0)
					nCheck = 1;
			}	
		}
		if(nCheck!=1){
			strcpy(pNode->sGCQA[pNode->nNumOfCat].sCategoryName,sCatName); strcat(pNode->sGCQA[pNode->nNumOfCat].sCategoryName,"\n");
			for(j=0;j<NUM_OF_QandA;j++){
				printf("Value Of Question %d Is %d\n", j+1, nValue);
				printf("Enter Question %d: ", j+1);
				gets(pNode->sGCQA[pNode->nNumOfCat].s[j].sQuestion); lenQ = strlen(pNode->sGCQA[pNode->nNumOfCat].s[j].sQuestion); 
				if(lenQ==0)
					nCheck = 2;
				while(nCheck==2){
					printf("\nSorry, Please Enter A Question.\n\n"); printf("\nEnter Question %d: ", j+1);
					nCheck = 0;
					gets(pNode->sGCQA[pNode->nNumOfCat].s[j].sQuestion); lenQ = strlen(pNode->sGCQA[pNode->nNumOfCat].s[j].sQuestion); 
					if(lenQ==0)
						nCheck = 2;
				}
				strcat(pNode->sGCQA[pNode->nNumOfCat].s[j].sQuestion,"\n");
				printf("Enter Answer %d: ", j+1);
				gets(pNode->sGCQA[pNode->nNumOfCat].s[j].sAnswer); lenA = strlen(pNode->sGCQA[pNode->nNumOfCat].s[j].sAnswer); 
				if(lenA==0)
					nCheck = 2;
				while(nCheck==2){
					printf("\nSorry, Please Enter An Answer.\n\n"); printf("\nEnter Answer %d: ", j+1);
					nCheck = 0;
					gets(pNode->sGCQA[pNode->nNumOfCat].s[j].sAnswer); lenA = strlen(pNode->sGCQA[pNode->nNumOfCat].s[j].sAnswer);
					if(lenQ==0)
						nCheck = 2;
				}
				strcat(pNode->sGCQA[pNode->nNumOfCat].s[j].sAnswer,"\n");
				nValue+=100;
				printf("\n");	
			}
			pNode->nNumOfCat += 1;
			getUppercase(pNode);
		}
		return pNode->nNumOfCat;
	}
}

//this function deletes a chosen category's name, questions, and answers
int deleteCQA(gameTypePtr pNode){
	if(pNode->nNumOfCat==MIN)
		printf("Sorry, No Categories To Delete.\n");
	if(pNode->nNumOfCat>MIN){
		int i, catNameIndex = -1;
		char nUserCatName[NAMES];
		printf("Enter Category Name:\n");
		gets(nUserCatName); strupr(nUserCatName); strcat(nUserCatName,"\n");
		for(i=0;i<pNode->nNumOfCat;i++){
			if(strcmp(nUserCatName,pNode->sGCQA[i].sCategoryNameCAPS)==0)
				catNameIndex = i;
		}
		if(catNameIndex!=-1){
			for(i=catNameIndex;i<pNode->nNumOfCat-1;i++)
				pNode->sGCQA[i] = pNode->sGCQA[i+1];
			pNode->nNumOfCat -= 1;
			return pNode->nNumOfCat;
		}
		if(catNameIndex==-1){
			printf("not found\n");
			return pNode->nNumOfCat;
		}
	}
}

//this function edits a chosen category's name, questions, and answers
gameTypePtr editCQA(gameTypePtr pNode){
	int i, j, nChoice = 0, catNameIndex = -1, len = 0, check = 0;
	char cUserCatName[NAMES], cUserCatNameHOLDER[NAMES], sChoice[sChoiceLEN];
	if(pNode->nNumOfCat==MIN)
		printf("Sorry, No Categories To Edit\n");
	else{
		printf("Enter The Category Name You Wish To Edit:\n");
		gets(cUserCatName); strupr(cUserCatName); strcat(cUserCatName,"\n");
		for(i=0;i<pNode->nNumOfCat;i++){
			if(strcmp(cUserCatName,pNode->sGCQA[i].sCategoryNameCAPS)==0)
				catNameIndex = i;
		}
		if(catNameIndex==-1)
			printf("not found\n");
		
		if(catNameIndex!=-1){
			puts("What Do You Wish To Edit? (Enter Options: 1 - 3)\n 1. Category Name\n 2. Question\n 3. Answer\nChoice: ");
			gets(sChoice);
			int nVal = getVal(sChoice);
			while(nVal<1||nVal>3){
				puts("Sorry. Invalid Input. Please Select Again\nChoice: ");
				gets(sChoice);
				nVal = getVal(sChoice);
			}
			
			switch(nVal){
				case 1: printf("Enter The New Category Name:\n");
						gets(cUserCatName); strcpy(cUserCatNameHOLDER,cUserCatName); len = strlen(cUserCatName); strcat(cUserCatName,"\n"); strupr(cUserCatName);
						if(len == 0)
							check = 1;
						for(i=0;i<pNode->nNumOfCat;i++){
							if(strcmp(cUserCatName,pNode->sGCQA[i].sCategoryNameCAPS)==0)
								check = 1;
						}
						while(check==1){
							printf("\nSorry, This Category Name Is Invalid, It Already Exists, Or It Is The Old Category Name.\nPlease Enter Another Name.\n\n");
							check = 0;
							printf("Enter The New Category Name:\n");
							gets(cUserCatName); strcpy(cUserCatNameHOLDER,cUserCatName); len = strlen(cUserCatName); strcat(cUserCatName,"\n"); strupr(cUserCatName);
							if(len == 0)
								check = 1;
							for(i=0;i<pNode->nNumOfCat;i++){
								if(strcmp(cUserCatName,pNode->sGCQA[i].sCategoryNameCAPS)==0)
									check = 1;
							}
						}
						if(check!=1){
							strcpy(pNode->sGCQA[catNameIndex].sCategoryName,cUserCatNameHOLDER); strcat(pNode->sGCQA[catNameIndex].sCategoryName,"\n");
						}
						break;
				case 2: printf("Enter The Question You Wish To Edit (Enter Options: 1 - 5):\n");
						for(j=0;j<NUM_OF_QandA;j++)		
							printf("\t %d. %s\n", j+1, pNode->sGCQA[catNameIndex].s[j].sQuestion);			
						printf("\nChoice: ");
						gets(sChoice);
						nChoice = getVal(sChoice);
						while((nChoice<1)||(nChoice>5)){
							printf("Sorry. Invalid Input. Please Select Again\nChoice: ");
							gets(sChoice);
							nChoice = getVal(sChoice);
						}
						printf("Enter the New Question:\n");
						gets(pNode->sGCQA[catNameIndex].s[nChoice-1].sQuestion); strcat(pNode->sGCQA[catNameIndex].s[nChoice-1].sQuestion,"\n");
						break;
				case 3: printf("Enter The Answer You Wish To Edit (Enter Options: 1 - 5):\n");
						for(j=0;j<NUM_OF_QandA;j++)	
							printf("\t %d. %s\n", j+1, pNode->sGCQA[catNameIndex].s[j].sAnswer);			
						printf("\nChoice: ");
						gets(sChoice);
						nChoice = getVal(sChoice);
						while((nChoice<1)||(nChoice>5)){
							printf("Sorry. Invalid Input. Please Select Again\nChoice: ");
							gets(sChoice);
							nChoice = getVal(sChoice);
						}
						printf("Enter the New Answer:\n");
						gets(pNode->sGCQA[catNameIndex].s[nChoice-1].sAnswer); strcat(pNode->sGCQA[catNameIndex].s[nChoice-1].sAnswer,"\n");
						break;
			}
			getUppercase(pNode);
		}
	}
}

//this function edits the final jeopardy's question, answer, and value
gameTypePtr editFJ(gameTypePtr pNode){
	char sChoice[sChoiceLEN];
	printf("What Do You Wish To Do ? (Enter Options: 1 - 3)\n 1. Edit Question\n 2. Edit Answer\n 3. View Current Final Jeopardy Question And Answer\n Choice: ");
	gets(sChoice);
	int nVal = getVal(sChoice);
	while(nVal<1||nVal>3){
		printf("Sorry. Invalid Input. Please Select Again.\nChoice (1 - 3): ");
		gets(sChoice); printf("\n");
		nVal = getVal(sChoice);
	}
	switch(nVal){
		case 1: printf("Enter The New Final Jeopardy Question:\n"); gets(pNode->fj.sFinalQuestion); strcat(pNode->fj.sFinalQuestion,"\n"); break;
		case 2: printf("Enter The New Final Jeopardy Answer:\n"); gets(pNode->fj.sFinalAnswer); strcat(pNode->fj.sFinalAnswer,"\n"); break;
		case 3: printf("Final Jeopardy\n\n\tQuestion: %s\tAnswer: %s\n", pNode->fj.sFinalQuestion, pNode->fj.sFinalAnswer); break;
	}
}

//this function views the category names, questions, answers, and values by category
void viewByCat(gameTypePtr pNode){
	if(pNode->nNumOfCat==MIN)
		printf("Sorry. Nothing To Display.");
	if(pNode->nNumOfCat>MIN){
		int i, j, nVal;
		printf("\n\nVIEW ALL DETAILS BY CATEGORIES:\n\n");
		for(i=0;i<pNode->nNumOfCat;i++){
			printf("Category Name %d is %s\n\n", i+1, pNode->sGCQA[i].sCategoryName);
			nVal = 100;
			for(j=0;j<NUM_OF_QandA;j++){
				printf("\t Value Of Question %d Is %d\n", j+1, nVal);			
				printf("\t Question %d: %s\n", j+1, pNode->sGCQA[i].s[j].sQuestion);			
				printf("\t Answer %d: %s\n", j+1, pNode->sGCQA[i].s[j].sAnswer);
				nVal+=100;	
			}
		}
	}
}

//this function views the category names, questions, answers, and values by value
void viewByVal(gameTypePtr pNode){
	if(pNode->nNumOfCat==MIN)
		printf("Sorry. Nothing To Display.");
	if(pNode->nNumOfCat>MIN){
		int i, j, nValue =100;
		printf("\n\nVIEW ALL DETAILS BY VALUES (100 - 500):\n\n");
		for(i=0;i<NUM_OF_QandA;i++){
			printf("Questions With Value of %d:\n\n", nValue);
			nValue+=100;
			for(j=0;j<pNode->nNumOfCat;j++){
				printf("\t Category Name %d is %s", j+1, pNode->sGCQA[j].sCategoryName);			
				printf("\t Question %d: %s\n", i+1, pNode->sGCQA[j].s[i].sQuestion);			
				printf("\t Answer %d: %s\n", i+1, pNode->sGCQA[j].s[i].sAnswer);
			}
		}
	}
}

//this function gets a keyword from the user and searches any match for it from the questions
void search(gameTypePtr pNode){
	int i, j, nPlace = 0;
	char sUserInput[QUESTION_LENGTH];
	char* ret;
	printf("Enter a keyword:\n");
	gets(sUserInput); strupr(sUserInput);
	printf("Search Results:\n\n");
	for(i=0;i<pNode->nNumOfCat;i++){
		for (j=0;j<NUM_OF_QandA;j++){
			ret = strstr(pNode->sGCQA[i].s[j].sQuestionCAPS,sUserInput);
			if(ret!=NULL){
				nPlace++;
				printf("   %d. %s\n", nPlace, pNode->sGCQA[i].s[j].sQuestion);
				printf("\t question number %d of category %s\n\n", j+1, pNode->sGCQA[i].sCategoryName);
			}
		}
	}
	if(nPlace==0)
		puts("\tNot Found");
}

//this function adds a game
gameTypePtr addGame(gameTypePtr *pFirst){
	gameTypePtr pNew, pRun;
	char sUserInput[NAMES];
	int check = 0, len = 0;
	puts("Enter New Game Name: ");
	gets(sUserInput); strupr(sUserInput); len = strlen(sUserInput);
	pRun = *pFirst;
	if(len==0)
		check = 1;
	while(pRun!=NULL){
		if(strcmp(sUserInput,pRun->gameName)==0)
			check = 1;
		pRun = pRun->pLink;
	}
	while(check==1){
		printf("\nSorry, This Game Name Is Invalid Or It Already Exists.\nPlease Enter Another Name.\n\n");
		check = 0;
		puts("Enter New Game Name: ");
		gets(sUserInput); strupr(sUserInput); len = strlen(sUserInput);
		pRun = *pFirst;
		if(len==0)
			check = 1;
		while(pRun!=NULL){
			if(strcmp(sUserInput,pRun->gameName)==0)
				check = 1;
			pRun = pRun->pLink;
		}
	}
	if(check!=1){
		pNew = malloc(sizeof(gT));
		strcpy(pNew->gameName,sUserInput); strupr(pNew->gameName);
		pNew->nNumOfCat = 0;
		pNew->pLink = *pFirst;
		*pFirst = pNew;
	}
}

//this function deletes the deleted game's folder and its contents
gameTypePtr deleteFolderAndContents(char folderName[]){
	char forFJ[DIRECTORY_LENGTH], forCat[DIRECTORY_LENGTH], forQues1[DIRECTORY_LENGTH], forAns1[DIRECTORY_LENGTH], forQues2[DIRECTORY_LENGTH], forAns2[DIRECTORY_LENGTH], forQues3[DIRECTORY_LENGTH], forAns3[DIRECTORY_LENGTH], forQues4[DIRECTORY_LENGTH], forAns4[DIRECTORY_LENGTH];
	strcpy(forFJ,folderName); strcat(forFJ,"\\finalj.txt");
	strcpy(forCat,folderName); strcat(forCat,"\\categories.txt");
	strcpy(forQues1,folderName); strcat(forQues1,"\\column1-questions.txt"); strcpy(forAns1,folderName); strcat(forAns1,"\\column1-answers.txt");
	strcpy(forQues2,folderName); strcat(forQues2,"\\column2-questions.txt"); strcpy(forAns2,folderName); strcat(forAns2,"\\column2-answers.txt");
	strcpy(forQues3,folderName); strcat(forQues3,"\\column3-questions.txt"); strcpy(forAns3,folderName); strcat(forAns3,"\\column3-answers.txt");
	strcpy(forQues4,folderName); strcat(forQues4,"\\column4-questions.txt"); strcpy(forAns4,folderName); strcat(forAns4,"\\column4-answers.txt");
	//deleting the folder's contents
	remove(forFJ);
	remove(forCat);
	remove(forQues1); remove(forAns1);
	remove(forQues2); remove(forAns2);
	remove(forQues3); remove(forAns3);
	remove(forQues4); remove(forAns4);
	//deleting the folder
	rmdir(folderName);
}

//this function deletes a game
char* deleteGame(gameTypePtr *pFirst, char sCurrentGame[]){
   gameTypePtr pRun, pTrail; 
   char userGameName[NAMES];
   if(*pFirst == NULL){
   		printf("Sorry, No Games To Delete.\n");
   		return sCurrentGame;
   }else{
   	printf("Enter Game Name: ");
   	gets(userGameName); strupr(userGameName);
   	if(strcmp(userGameName,(*pFirst)->gameName)==0){ 
   		pRun = *pFirst;
	 	*pFirst = (*pFirst)->pLink;
	 	free(pRun);
	 	deleteFolderAndContents(userGameName);
	 	if(strcmp(sCurrentGame,userGameName)==0)
			return "No Game Selected";
		else
			return sCurrentGame;
	}else{
		pRun = *pFirst;
		while((strcmp(userGameName, pRun->gameName)!=0) && (pRun->pLink != NULL)){ 
		          pTrail = pRun;
		          pRun = pRun->pLink;
		}
		if(strcmp(userGameName, pRun->gameName)==0){
		    pTrail->pLink = pRun->pLink;
			free(pRun);
			deleteFolderAndContents(userGameName);
	 		if(strcmp(sCurrentGame,userGameName)==0)
				return "No Game Selected";
			else
				return sCurrentGame;
		}else{
			printf("\n\tGame Not Found\n");
			return sCurrentGame;
		 }
	   }
	}
}

//this function allows the user to choose the currently active/selected game
char* selectGame(gameTypePtr pFirst, char sCurrentGame[]){
	char userGameName[NAMES];
	gameTypePtr pRun;
	if(pFirst==NULL){
		printf("Sorry, No Games to Select From\n");
		return sCurrentGame;
	}
	else{
		pRun = pFirst;
		printf("Enter Game Name: ");
		gets(userGameName); strupr(userGameName);
		while(strcmp(userGameName,pRun->gameName)!=0 && pRun->pLink!=NULL)
			pRun = pRun->pLink;
		if(strcmp(userGameName,pRun->gameName)==0)
			return pRun->gameName;	
		else{
			printf("\n\tGame Not Found\n");
			return sCurrentGame;
		}
	}
}

//this function allows the user to view the list of created games
void viewGames(gameTypePtr pFirst){
	gameTypePtr pRun = pFirst;
	int nCtr = 1;
	if(pFirst==NULL)
		printf("Sorry, No Games To Display.\n");
	if(pFirst!=NULL){
		printf("Games:\n");
		while (pRun!=NULL){
			printf("%d. %s\n", nCtr, pRun->gameName);
			nCtr++;
			pRun = pRun->pLink;
		}
		printf("\n");
	}
}

//this function allows the user to save the current game, used in phase 1 menu
gameTypePtr saveGame(gameTypePtr pNode){
	char folderName[NAMES], forFJ[DIRECTORY_LENGTH], forCat[DIRECTORY_LENGTH], forQues1[DIRECTORY_LENGTH], forAns1[DIRECTORY_LENGTH], forQues2[DIRECTORY_LENGTH], forAns2[DIRECTORY_LENGTH], forQues3[DIRECTORY_LENGTH], forAns3[DIRECTORY_LENGTH], forQues4[DIRECTORY_LENGTH], forAns4[DIRECTORY_LENGTH];
	FILE *fp1, *fp2, *fp3, *fp4, *fp5, *fp6, *fp7, *fp8, *fp9, *fp10;
	int i, j, newLineChk;
	printf("\nNote: The Name Of The Folder Will Be The Name Of The Game The Next Time The Folder Is Loaded.\n\nEnter The Name Of The Folder To Save The Game In: ");
	gets(folderName); strupr(folderName);
	mkdir(folderName);
	strcpy(forFJ,folderName); strcat(forFJ,"\\finalj.txt");
	strcpy(forCat,folderName); strcat(forCat,"\\categories.txt");
	strcpy(forQues1,folderName); strcat(forQues1,"\\column1-questions.txt"); strcpy(forAns1,folderName); strcat(forAns1,"\\column1-answers.txt");
	strcpy(forQues2,folderName); strcat(forQues2,"\\column2-questions.txt"); strcpy(forAns2,folderName); strcat(forAns2,"\\column2-answers.txt");
	strcpy(forQues3,folderName); strcat(forQues3,"\\column3-questions.txt"); strcpy(forAns3,folderName); strcat(forAns3,"\\column3-answers.txt");
	strcpy(forQues4,folderName); strcat(forQues4,"\\column4-questions.txt"); strcpy(forAns4,folderName); strcat(forAns4,"\\column4-answers.txt");
	//saving the final jeopardy data
	fp1 = fopen(forFJ,"w");
	fprintf(fp1,pNode->fj.sFinalQuestion);
	fprintf(fp1,pNode->fj.sFinalAnswer);
	fclose(fp1);
	//saving the categories
	fp2 = fopen(forCat,"w");
	for(i=0;i<pNode->nNumOfCat-1;i++)
		fprintf(fp2,pNode->sGCQA[i].sCategoryName);
	newLineChk = strlen(pNode->sGCQA[pNode->nNumOfCat-1].sCategoryName);
	if(pNode->sGCQA[pNode->nNumOfCat-1].sCategoryName[newLineChk-1] == '\n')
		pNode->sGCQA[pNode->nNumOfCat-1].sCategoryName[newLineChk-1] = '\0';
	fprintf(fp2,pNode->sGCQA[pNode->nNumOfCat-1].sCategoryName);
	fclose(fp2);
	//saving the questions and answers
	if(pNode->nNumOfCat>=1){
		fp3 = fopen(forQues1, "w");
		fp4 = fopen(forAns1, "w");
		for(j=0;j<NUM_OF_QandA;j++){
			fprintf(fp3,pNode->sGCQA[0].s[j].sQuestion);
			fprintf(fp4,pNode->sGCQA[0].s[j].sAnswer);
		}
		fclose(fp3);
		fclose(fp4);
		if(pNode->nNumOfCat>=2){
			fp5 = fopen(forQues2, "w");
			fp6 = fopen(forAns2, "w");
			for(j=0;j<NUM_OF_QandA;j++){
				fprintf(fp5,pNode->sGCQA[1].s[j].sQuestion);
				fprintf(fp6,pNode->sGCQA[1].s[j].sAnswer);
			}
			fclose(fp5);
			fclose(fp6);
			if(pNode->nNumOfCat>=3){
				fp7 = fopen(forQues3, "w");
				fp8 = fopen(forAns3, "w");
				for(j=0;j<NUM_OF_QandA;j++){
					fprintf(fp7,pNode->sGCQA[2].s[j].sQuestion);
					fprintf(fp8,pNode->sGCQA[2].s[j].sAnswer);
				}
				fclose(fp7);
				fclose(fp8);
				if(pNode->nNumOfCat==4){
					fp9 = fopen(forQues4, "w");
					fp10 = fopen(forAns4, "w");
					for(j=0;j<NUM_OF_QandA;j++){
						fprintf(fp9,pNode->sGCQA[3].s[j].sQuestion);
						fprintf(fp10,pNode->sGCQA[3].s[j].sAnswer);
					}
					fclose(fp9);
					fclose(fp10);	
				}
			}
		}
	}
}

//this function allows the user to load a saved game
int loadGame(gameTypePtr *pFirst){
	char c, folderName[NAMES], forFJ[DIRECTORY_LENGTH], forCat[DIRECTORY_LENGTH], forQues1[DIRECTORY_LENGTH], forAns1[DIRECTORY_LENGTH], forQues2[DIRECTORY_LENGTH], forAns2[DIRECTORY_LENGTH], forQues3[DIRECTORY_LENGTH], forAns3[DIRECTORY_LENGTH], forQues4[DIRECTORY_LENGTH], forAns4[DIRECTORY_LENGTH];
	FILE *fp1, *fp2, *fp3, *fp4, *fp5, *fp6, *fp7, *fp8, *fp9, *fp10; 
	int i, j, categoryCtr = 0;
	printf("\nEnter The Game's Folder Name: ");
	gets(folderName); strupr(folderName);
	strcpy(forFJ,folderName); strcat(forFJ,"\\finalj.txt");
	strcpy(forCat,folderName); strcat(forCat,"\\categories.txt");
	strcpy(forQues1,folderName); strcat(forQues1,"\\column1-questions.txt"); strcpy(forAns1,folderName); strcat(forAns1,"\\column1-answers.txt");
	strcpy(forQues2,folderName); strcat(forQues2,"\\column2-questions.txt"); strcpy(forAns2,folderName); strcat(forAns2,"\\column2-answers.txt");
	strcpy(forQues3,folderName); strcat(forQues3,"\\column3-questions.txt"); strcpy(forAns3,folderName); strcat(forAns3,"\\column3-answers.txt");
	strcpy(forQues4,folderName); strcat(forQues4,"\\column4-questions.txt"); strcpy(forAns4,folderName); strcat(forAns4,"\\column4-answers.txt");
	if(strcmp(folderName,"FINISH")==0)
		return -1;
	else{
		fp1 = fopen(forFJ,"r");
		if(fp1==NULL){
			printf("\n\tNo Such Folder Found!\n");
			fclose(fp1);
		}
		else{
			gameTypePtr pNew;
			pNew = malloc(sizeof(gT));
			strcpy(pNew->gameName,folderName); //getting the game name
			//getting the final jeopardy stuff
			fgets(pNew->fj.sFinalQuestion,QUESTION_LENGTH,fp1);
			fgets(pNew->fj.sFinalAnswer,ANSWER_LENGTH,fp1);
			fclose(fp1);
			//loading category/ies stuff
			fp2 = fopen(forCat,"r");
			do{
				c = fgetc(fp2);
				if ((c == '\n')||(c == EOF))
					categoryCtr++; //counting number of categories
			}while(c != EOF);
			fclose(fp2);
			pNew->nNumOfCat = categoryCtr;
			fp2 = fopen(forCat,"r");
			for(i=0;i<pNew->nNumOfCat;i++)
				fgets(pNew->sGCQA[i].sCategoryName,30,fp2);
			strcat(pNew->sGCQA[pNew->nNumOfCat-1].sCategoryName,"\n");
			fclose(fp2);
			//loading questions and answers
			if(pNew->nNumOfCat>=1){
				fp3 = fopen(forQues1, "r");
				fp4 = fopen(forAns1, "r");
				for(j=0;j<NUM_OF_QandA;j++){
					fgets(pNew->sGCQA[0].s[j].sQuestion,QUESTION_LENGTH,fp3);
					fgets(pNew->sGCQA[0].s[j].sAnswer,ANSWER_LENGTH,fp4);
				}
				fclose(fp3);
				fclose(fp4);
				if(pNew->nNumOfCat>=2){
					fp5 = fopen(forQues2, "r");
					fp6 = fopen(forAns2, "r");
					for(j=0;j<NUM_OF_QandA;j++){
						fgets(pNew->sGCQA[1].s[j].sQuestion,QUESTION_LENGTH,fp5);
						fgets(pNew->sGCQA[1].s[j].sAnswer,ANSWER_LENGTH,fp6);
					}
					fclose(fp5);
					fclose(fp6);
					if(pNew->nNumOfCat>=3){
						fp7 = fopen(forQues3, "r");
						fp8 = fopen(forAns3, "r");
						for(j=0;j<NUM_OF_QandA;j++){
							fgets(pNew->sGCQA[2].s[j].sQuestion,QUESTION_LENGTH,fp7);
							fgets(pNew->sGCQA[2].s[j].sAnswer,ANSWER_LENGTH,fp8);
						}
						fclose(fp7);
						fclose(fp8);
						if(pNew->nNumOfCat==4){
							fp9 = fopen(forQues4, "r");
							fp10 = fopen(forAns4, "r");
							for(j=0;j<NUM_OF_QandA;j++){
								fgets(pNew->sGCQA[3].s[j].sQuestion,QUESTION_LENGTH,fp9);
								fgets(pNew->sGCQA[3].s[j].sAnswer,ANSWER_LENGTH,fp10);
							}
							fclose(fp9);
							fclose(fp10);	
						}
					}
				}
			}
			getUppercase(pNew);
			pNew->pLink = *pFirst;
			*pFirst = pNew;
		}
		return 0;
	}
}

//this function shows the phase one functions as a menu
void phaseOneFcns(gameTypePtr pNode){
	char sChoice[sChoiceLEN];
	int checkFJQ = 0, checkFJA = 0;
	getUppercase(pNode);
	printf("\n***************************************************************************************************************************************\n1. Add Category\n2. Delete Category\n3. Edit Category\n4. Edit Final Jeopardy\n5. View by category\n6. View by value\n7. Search\n8. Exit to Game Menu\n\nEnter Choice (1 - 8): ");
	gets(sChoice); printf("\n");
	int nVal = getVal(sChoice);
	while(nVal<1||nVal>8){
		printf("Sorry, Invalid Input. Please Select Again.\nEnter Choice (1 - 8)): ");
		gets(sChoice);
		nVal = getVal(sChoice);
	}
	if(nVal!=8){
		switch(nVal){
			case 1: pNode->nNumOfCat = addCQA(pNode); break;
			case 2: pNode->nNumOfCat = deleteCQA(pNode); break;
			case 3: editCQA(pNode); break;
			case 4: editFJ(pNode); break;
			case 5: viewByCat(pNode); break;
			case 6: viewByVal(pNode); break;
			case 7: search(pNode); break;
		}
		phaseOneFcns(pNode);
	}
	if(nVal==8){
		printf("Save Changes To Current Game? (Enter \"Yes\" or \"No\")\nChoice: ");
		gets(sChoice); strupr(sChoice);
		while((strcmp(sChoice,"YES")!=0)&&(strcmp(sChoice,"NO")!=0)){
			printf("Sorry, Invalid Input. Please Enter Choice Again.\n Choice: ");
			gets(sChoice); strupr(sChoice);
		}
		if(strcmp(sChoice,"YES")==0){
			checkFJQ = strlen(pNode->fj.sFinalQuestion);
			checkFJA = strlen(pNode->fj.sFinalAnswer);
			if((pNode->nNumOfCat>=1)&&(checkFJQ!=0)&&(checkFJA!=0))
				saveGame(pNode);
			else
				printf("Save Failed. \nPlease Make Sure That There Is A Category, A Final Jeopardy Question, And A Final Jeopardy Answer.\n");
		}
	}
}

//this function shows the phase two functions as a menu
void phaseTwoFcns(gameTypePtr pFirst, char sCurrentGame[]){
	char sChoice[sChoiceLEN];
	printf("\n**********************************************************************************************************************\nGame Menu\n\n[A]dd Game\n[D]elete Game\n[S]elect Game\n[V]iew Games\n[P]hase One (1) Functions\n[E]xit\n");
	printf(">>>Current Game Selected: %s\n", sCurrentGame);
	printf("\nEnter Choice: ");
	gets(sChoice); printf("\n");
	int nVal = getValPHASE2(sChoice);
	while(nVal>5){
		printf("Sorry, Invalid Input. Please Select Again.\nEnter Choice: ");
		gets(sChoice);
		nVal = getValPHASE2(sChoice);
	}
	if(nVal<4){
		switch(nVal){
			case 0: addGame(&pFirst); break;
			case 1: strcpy(sCurrentGame,deleteGame(&pFirst,sCurrentGame)); break;
			case 2: strcpy(sCurrentGame,selectGame(pFirst,sCurrentGame)); break;
			case 3: viewGames(pFirst); break;
		}
		phaseTwoFcns(pFirst,sCurrentGame);
	}
	if(nVal==4){
		if((pFirst==NULL)||(strcmp(sCurrentGame,"No Game Selected")==0))
			printf("Sorry, Please Select A Game First.\n");
		if((pFirst!=NULL)&&(strcmp(sCurrentGame,"No Game Selected")!=0)){
			gameTypePtr pNode = pFirst;
			while((strcmp(sCurrentGame,pNode->gameName)!=0)&&pNode!=NULL){
				pNode = pNode->pLink;
			}
			phaseOneFcns(pNode);
		}
		phaseTwoFcns(pFirst,sCurrentGame);
	}
	if(nVal==5)
		printf("Press Any Key To Exit. Have a nice day!\n");
}

int main(){
	gameTypePtr pFirst = NULL;
	char sChoice[sChoiceLEN], sCurrentGame[NAMES] = "No Game Selected";
	int nVal = 0;
	printf("Would You Like To Load A Game? (Enter \"Yes\" or \"No\")\nChoice: ");
	gets(sChoice); strupr(sChoice);
	while((strcmp(sChoice,"YES")!=0)&&(strcmp(sChoice,"NO")!=0)){
		printf("Sorry, Invalid Input. Please Enter Choice Again.\n Choice: ");
		gets(sChoice); strupr(sChoice);
	}
	if((strcmp(sChoice,"YES")==0)){
		printf("\nEnter \"Finish\" To Stop Loading Games.\n");
		do{ if(nVal!=-1) nVal = loadGame(&pFirst);
		}while(nVal!=-1);
	}
	phaseTwoFcns(pFirst,sCurrentGame);
	return 0;
}
