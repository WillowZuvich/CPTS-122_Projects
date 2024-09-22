/*Willow Zuvich
PA3
Cpts 122
2/12/23
Desc: Doubly linked list operations on a music playlist
-Basic Digital Music Manager
*/

#include "PA3.h"

Node* makeNode(Record newData)
{
	Node* pMem = NULL;

	pMem = (Node*)malloc(sizeof(Node));
	if (pMem != NULL) //memory was allocated for node
	{
		strncpy(pMem->data.artist, newData.artist, 30);
		strncpy(pMem->data.albumTitle, newData.albumTitle, 30);
		strncpy(pMem->data.songTitle, newData.songTitle, 50);
		strncpy(pMem->data.genre, newData.genre, 20);
		pMem->data.songLength.minutes = newData.songLength.minutes;
		pMem->data.songLength.seconds = newData.songLength.seconds;
		pMem->data.timesPlayed = newData.timesPlayed;
		if (pMem->data.timesPlayed < 0)
		{
			pMem->data.timesPlayed = 0; //if out of bounds, round up
		}
		pMem->data.rating = newData.rating;
		if (pMem->data.rating < 0)
		{
			pMem->data.rating = 0; //if out of bounds, round up
		}
		if (pMem->data.rating > 5)
		{
			pMem->data.rating = 5; //if out of bounds, round down
		}
		pMem->pNext = NULL;
		pMem->pPrev = NULL;
	}

	return pMem;
}

//function inserts new node at the head position in the list
//returns: 0 for failure, 1 for success
int insertFront(Node** pHead, Record newData)
{
	Node* pMem = NULL;
	int success = 0;

	pMem = makeNode(newData);

	if (pMem != NULL) //makeNode successfully allocated space for node
	{
		success = 1;
		if (*pHead == NULL) //list is empty
		{
			*pHead = pMem;
		}
		else //list is not empty
		{
			pMem->pNext = *pHead;
			(*pHead)->pPrev = pMem;
			*pHead = pMem;
		}
	}

	return success;
}

//Function prints menu
void printMenu(void)
{
	printf("**************\n*****MENU*****\n");
	printf("1. Load\n2. Store\n3. Display\n4. Insert\n5. Delete\n6. Edit\n7. Sort\n8. Rate\n9. Play\n10. Shuffle\n11. Exit\n");
}

//function obtains users selection from menu
int menuOption(void)
{
	int choice = 0;

	do
	{
		printMenu();
		printf("Enter Selection: ");
		scanf("%d", &choice);
		system("cls");

	} while (choice != LOAD && choice != STORE && choice != DISPLAY && choice != INSERT && choice != DELETE &&
		choice != EDIT && choice != SORT && choice != RATE && choice != PLAY && choice != SHUFFLE &&
		choice != EXIT); //get valid input

	return choice;
}


//function removes \n char from string - replaces with null char
void removeNewline(char* str)
{
	int len = (int)strlen(str);
	if (str[len - 1] == '\n')
	{
		str[len - 1] = '\0'; //if \n char is found, replace with null char
	}
}

//function reads all record from a csv file and places them into a doubly linked list
int load(Node** pHead, FILE* infile)
{
	char line0[100] = "";
	Record newData = { '\0', '\0', '\0', '\0', 0, 0, 0 }; 
	int success = 1;


	for (;success != 0 && fgets(line0, 100, infile) != NULL;) //loop to end of file
	{

		if (line0[0] == '"') //quotes are present
		{
			strncpy(newData.artist, strtok(&line0[1], "\""), 30); //if "" are present
		}
		else
		{
			strncpy(newData.artist, strtok(line0, ","), 30); 
		}
		strncpy(newData.albumTitle, strtok(NULL, ","), 30);
		strncpy(newData.songTitle, strtok(NULL, ","), 50);
		strncpy(newData.genre, strtok(NULL, ","), 20);
		newData.songLength.minutes = atoi(strtok(NULL, ":"));
		newData.songLength.seconds = atoi(strtok(NULL, ","));
		newData.timesPlayed = atoi(strtok(NULL, ","));
		newData.rating = atoi(strtok(NULL, "\n")); //copy all data values over

		success = insertFront(&*pHead, newData); //insert new data at front of list

	}

	return success;

}


//function writes all records in the current list to musicPlayList.csv
void store(Node* pHead, FILE* outfile)
{
	Node* pCur = pHead;

	for (; pCur != NULL; pCur = pCur->pNext)
	{
		int index = 0;

		for (index = 0; pCur->data.artist[index] != ',' && pCur->data.artist[index] != '\0'; ++index); //check format of data

		if (pCur->data.artist[index] == ',') // if "" are needed
		{
			fprintf(outfile, "\"%s\",%s,%s,%s,%d:%d,%d,%d\n", pCur->data.artist, pCur->data.albumTitle, pCur->data.songTitle,
				pCur->data.genre, pCur->data.songLength.minutes, pCur->data.songLength.seconds, pCur->data.timesPlayed,
				pCur->data.rating);
		}
		else
		{
			fprintf(outfile, "%s,%s,%s,%s,%d:%d,%d,%d\n", pCur->data.artist, pCur->data.albumTitle, pCur->data.songTitle,
				pCur->data.genre, pCur->data.songLength.minutes, pCur->data.songLength.seconds, pCur->data.timesPlayed,
				pCur->data.rating);
		}

	}



}

//function displays entire playlist to user
void printList(Node* pHead)
{
	Node* pCur = pHead;

	for (; pCur != NULL; pCur = pCur->pNext) //iterate till end - printf all records
	{
		int index = 0;

		for (index = 0; pCur->data.artist[index] != ',' && pCur->data.artist[index] != '\0'; ++index); //check format

		if (pCur->data.artist[index] == ',')
		{
			printf("\"%s\",%s,%s,%s,%d:%d,%d,%d\n", pCur->data.artist, pCur->data.albumTitle, pCur->data.songTitle,
				pCur->data.genre, pCur->data.songLength.minutes, pCur->data.songLength.seconds, pCur->data.timesPlayed,
				pCur->data.rating);
		}
		else
		{
			printf("%s,%s,%s,%s,%d:%d,%d,%d\n", pCur->data.artist, pCur->data.albumTitle, pCur->data.songTitle,
				pCur->data.genre, pCur->data.songLength.minutes, pCur->data.songLength.seconds, pCur->data.timesPlayed,
				pCur->data.rating);
		}
	}
}

//function displays all records from an artist
void printFromArtist(Node* pHead, char* artist)
{
	Node* pCur = pHead; 

	for (; pCur != NULL; pCur = pCur->pNext)
	{
		if (strcmp(artist, pCur->data.artist) == 0) //find records by artist
		{

			int index = 0;

			for (index = 0; pCur->data.artist[index] != ',' && pCur->data.artist[index] != '\0'; ++index); //check format

			if (pCur->data.artist[index] == ',')
			{
				printf("\"%s\",%s,%s,%s,%d:%d,%d,%d\n", pCur->data.artist, pCur->data.albumTitle, pCur->data.songTitle,
					pCur->data.genre, pCur->data.songLength.minutes, pCur->data.songLength.seconds, pCur->data.timesPlayed,
					pCur->data.rating);
			}
			else
			{
				printf("%s,%s,%s,%s,%d:%d,%d,%d\n", pCur->data.artist, pCur->data.albumTitle, pCur->data.songTitle,
					pCur->data.genre, pCur->data.songLength.minutes, pCur->data.songLength.seconds, pCur->data.timesPlayed,
					pCur->data.rating);
			}
		}
	}
}

//function either displays all records to the screen or all records from one artist
void display(Node* pHead, int userinput)
{
	char artist[30] = "";

	if (userinput == PRINTALL)
	{
		printList(pHead); //print all records
	}
	else
	{
		Node* pCur = pHead;
		int validate = 0;
		//print all from one artist
		do
		{
			char str[2] = "";
			printf("Enter Artist to Display: ");
			fgets(artist, 30, stdin);
			if(strncmp(artist, "\n", 1) == 0) //if \n char was in stream
			{
				fgets(artist, 30, stdin); //get user input after newline
			}
	
			removeNewline(artist); //remove \n char

			while (pCur != NULL) //verify input exists in list
			{
				if (strcmp(artist, pCur->data.artist) == 0)
				{
					validate = 1;
				}
				pCur = pCur->pNext;
			}

			system("cls");

		} while (validate != 1);

		printFromArtist(pHead, artist); //print all or artists records

	}

	char key[10] = "";

	printf("\nEnter Any Key to Return to Menu: ");
	scanf("%s", &key);
	system("cls");
	printf("Returning..."); //let user see display as long as they wish

}

//function allows user to edit all atrubutes of a record
Node* findRecord(Node* pHead)
{
	char artist[30] = "";
	char title[50] = "";
	Node* pCur = pHead;
	int count = 0;

	if (pHead == NULL) //if list has no elements to edit
	{
		printf("No Records in Playlist\n");
		
	}
	else //if list has elements to edit
	{
		//get artist from user
		do
		{

			printf("Search by Artist: ");
			
			fgets(artist, 30, stdin);
			
			if (strncmp(artist, "\n", 1) == 0)
			{
				fgets(artist, 30, stdin); //if newline was in stream
			}

			//remove \n
			removeNewline(artist);

			for (pCur = pHead; pCur != NULL; pCur = pCur->pNext)
			{
				if (strcmp(pCur->data.artist, artist) == 0)
				{
					++count; //verify if multiple records from artist exist
				}
			}
			system("cls");

			if (count == 0) //no records found
			{
				printf("No Records by Artist.\n");
				clock_t time = clock();
				while (clock() < time + 500);
				system("cls"); //let user know artist is not in list
			}
		} while (count == 0);

		//multiple records from artist
		if (count > 1)
		{
	
			do 	//verify user input 
			{
				//display record from artist
				printFromArtist(pHead, artist); //print record from arist
				
				printf("\nSelect Record\n");
				printf("Enter title: ");
				fgets(title, 50, stdin); //verify which user wishes to edit
				
				//remove \n
				removeNewline(title);

				//loop until song is found based on title or until pCUr == NULL
				for (pCur = pHead; pCur != NULL && strcmp(title, pCur->data.songTitle) != 0; pCur = pCur->pNext);
				
				system("cls");

			} while (pCur == NULL);
		}
		else
		{
			//loop until song is found based on title or until pCUr == NULL
			for (pCur = pHead; pCur != NULL && strcmp(artist, pCur->data.artist) != 0; pCur = pCur->pNext);
		}

		
	}
	return pCur;
}

//function gets yes or no from user
char getYorN()
{
	char choice = 'n';

	do
	{
		scanf(" %c", &choice);
		system("cls");

	} while (choice != 'y' && choice != 'n'); //get valid input 

	return choice;
}


//funtion allows user to rate chosen record
void rate(Node* pEdit)
{
	printf("Current Rating: %d\n", pEdit->data.rating);
	printf("Enter New Rating: ");
	scanf("%d", &(pEdit->data.rating)); //get rating

	if (pEdit->data.rating > 5)
	{
		pEdit->data.rating = 5; //round down if out of bounds
	}
	if (pEdit->data.rating < 0)
	{
		pEdit->data.rating = 0; //round up if out of bounds
	}

	system("cls");
}


//function edits record pointed to
void edit(Node* pEdit)
{
	char new[50] = "";
	char option = 'n';

	printf("Edit Artist Name? (y/n): ");
	option = getYorN();
	
	if(option == 'y')
	{
		printf("Current Artist Name: %s\n", pEdit->data.artist);
		printf("Enter New Name: ");
		fgets(new, 30, stdin); //get newline
		fgets(new, 30, stdin); //get input
		removeNewline(new); //remove \n
		system("cls");
		strncpy(pEdit->data.artist, new, 30);
	}

	printf("Edit Album Title? (y/n): ");
	option = getYorN();

	if (option == 'y')
	{
		printf("Current Album Title: %s\n", pEdit->data.albumTitle);
		printf("Enter New Album Title: ");
		fgets(new, 30, stdin);
		fgets(new, 30, stdin);
		removeNewline(new);
		system("cls");
		strncpy(pEdit->data.albumTitle, new, 30);
	}

	printf("Edit Song Title? (y/n): ");
	option = getYorN();

	if (option == 'y')
	{
		printf("Current Song Title: %s\n", pEdit->data.songTitle);
		printf("Enter Song Title: ");
		fgets(new, 30, stdin);
		fgets(new, 50, stdin);
		removeNewline(new);
		system("cls");
		strncpy(pEdit->data.songTitle, new, 50);
	}

	printf("Edit Genre? (y/n): ");
	option = getYorN();

	if (option == 'y')
	{
		printf("Current genre: %s\n", pEdit->data.genre);
		printf("Enter New Genre: ");
		fgets(new, 30, stdin);
		fgets(new, 20, stdin);
		removeNewline(new);
		system("cls");
		strncpy(pEdit->data.genre, new, 20);
	}

	printf("Edit Song Duration? (y/n): ");
	option = getYorN();
	if(option == 'y')
	{
		printf("Current Duration: %d:%d\n", pEdit->data.songLength.minutes, pEdit->data.songLength.seconds);
		printf("Enter New Seconds: ");
		scanf("%d", &(pEdit->data.songLength.seconds));
		printf("Enter New Minutes: ");
		scanf("%d", &(pEdit->data.songLength.minutes));
		system("cls");
	}

	printf("Edit Times Played? (y/n): ");
	option = getYorN();

	if (option == 'y')
	{
		printf("Current Times Played: %d\n", pEdit->data.timesPlayed);
		printf("Enter New Times Played: ");
		scanf("%d", &(pEdit->data.timesPlayed));
		system("cls");
	}

	printf("Edit Rating? (y/n): ");
	option = getYorN(); 

	if (option == 'y')
	{
		rate(pEdit); //call rate
	}

	
}

//function displays a record for a short period of time 
void play(Node* pStart)
{
		int index = 0;

		printf("Now Playing...\n");

		for (index = 0; pStart->data.artist[index] != ',' && pStart->data.artist[index] != '\0'; ++index); //check format

		if (pStart->data.artist[index] == ',')
		{
			printf("\"%s\",%s,%s,%s,%d:%d,%d,%d\n", pStart->data.artist, pStart->data.albumTitle, pStart->data.songTitle,
				pStart->data.genre, pStart->data.songLength.minutes, pStart->data.songLength.seconds, pStart->data.timesPlayed,
				pStart->data.rating);
		}
		else
		{
			printf("%s,%s,%s,%s,%d:%d,%d,%d\n", pStart->data.artist, pStart->data.albumTitle, pStart->data.songTitle,
				pStart->data.genre, pStart->data.songLength.minutes, pStart->data.songLength.seconds, pStart->data.timesPlayed,
				pStart->data.rating);
		}

		clock_t time = clock();
		while (clock() < time + 1500); //display each record for 1.5 seconds
		system("cls");

}

//function gets information for new record from user
void getNewRecord(Record* newRecord)
{
	printf("Provide Record Information Below: \n");
	printf("Enter Artist Name: ");
	fgets(newRecord->artist, 30, stdin); // get newline
	fgets(newRecord->artist, 30, stdin); //get input
	removeNewline(newRecord->artist); //remove newline
	system("cls");

	printf("Enter Album Title: ");
	fgets(newRecord->albumTitle, 30, stdin);
	removeNewline(newRecord->albumTitle);
	system("cls");

	printf("Enter Song Title: ");
	fgets(newRecord->songTitle, 50, stdin);
	removeNewline(newRecord->songTitle);
	system("cls");

	printf("Enter Genre: ");
	fgets(newRecord->genre, 20, stdin);
	removeNewline(newRecord->genre);
	system("cls");

	printf("Enter Duration (m s): ");
	scanf("%d %d", &(newRecord->songLength.minutes), &(newRecord->songLength.seconds));
	system("cls");

	printf("Enter Times Played: ");
	scanf("%d", &(newRecord->timesPlayed));
	system("cls");

	printf("Enter Rating: ");
	scanf("%d", &(newRecord->rating));
	system("cls");

}

//function deletes searchdata from the list - if it exists
int deleteNode(Node** pHead, Record SearchData)
{
	int success = 0;
	Node* pCur = *pHead;

	while (pCur != NULL && strcmp(pCur->data.songTitle, SearchData.songTitle) != 0) // find data to delete
	{
		pCur = pCur->pNext; // update pointer
	}

	if (pCur != NULL) //check for empty list / data not found
	{
		success = 1;

		if (pCur->pPrev == NULL) //deleting front node
		{
			if(pCur->pNext != NULL) //deleting front node
			{
				pCur->pNext->pPrev = NULL;
				*pHead = pCur->pNext; //update head pointer
				free(pCur);
			}
			else //deleting only node
			{
				*pHead = pCur->pNext;
				free(pCur);
			}
		}
		else if (pCur->pNext == NULL) //deleting back
		{
			pCur->pPrev->pNext = NULL;
			free(pCur);
		}
		else // deleting in the middle
		{
			pCur->pPrev->pNext = pCur->pNext;
			pCur->pNext->pPrev = pCur->pPrev;
			free(pCur);
		}
	}

	return success;
}

//Node swaps position of two Nodes
void swapNodes(Node** pHead, Node** pOne, Node** pTwo)
{

	Node* TempP = (*pOne)->pPrev;

	if (*pOne == *pHead && (*pTwo)->pNext == NULL) //case: only 2 nodes in list
	{
		(*pOne)->pNext = (*pTwo)->pNext; //4 //connection point 4
		(*pOne)->pPrev = *pTwo; //1
		(*pTwo)->pNext = *pOne; //2
		(*pTwo)->pPrev = TempP; //5
	}
	else if (*pOne == *pHead) //case: swapping first node
	{
		(*pOne)->pNext = (*pTwo)->pNext; //4
		(*pTwo)->pNext->pPrev = *pOne; //3
		(*pOne)->pPrev = *pTwo; //1
		(*pTwo)->pNext = *pOne; //2
		(*pTwo)->pPrev = TempP; //5
		*pHead = *pTwo; //update head
	}
	else if ((*pTwo)->pNext == NULL) //case: swapping last node
	{
		(*pOne)->pNext = (*pTwo)->pNext; //4
		(*pOne)->pPrev->pNext = *pTwo; //6
		(*pOne)->pPrev = *pTwo; //1
		(*pTwo)->pNext = *pOne; //2
		(*pTwo)->pPrev = TempP; //5
	}

	else // case: swapping middle nodes
	{
		(*pOne)->pNext = (*pTwo)->pNext; //4
		(*pTwo)->pNext->pPrev = *pOne; //3
		(*pOne)->pPrev->pNext = *pTwo; //6
		(*pOne)->pPrev = *pTwo; //1
		(*pTwo)->pNext = *pOne; //2
		(*pTwo)->pPrev = TempP; //5
	}
}

//function sorts the playlist by artist (A-Z)
void sortArtist(Node** pHead)
{
	Node* pCur = *pHead, * pNext = (*pHead)->pNext;
	int count = 0;

	for (; pCur != NULL; pCur = pCur->pNext, ++count);

	for (pCur = *pHead; count > 1; --count)
	{
		for (pCur = *pHead, pNext = (*pHead)->pNext; pNext != NULL; pCur = pNext, pNext = pNext->pNext)
		{
			if (strcmp(pCur->data.artist, pNext->data.artist) > 0)
			{
				swapNodes(&*pHead, &pCur, &pNext);
				Node* temp = pCur;
				pCur = pNext;
				pNext = temp;
			}
		}
	}
}

//function sorts playlist by album title (A-Z)
void sortAlbumTitle(Node** pHead)
{
	Node* pCur = *pHead, * pNext = (*pHead)->pNext;
	int count = 0;

	for (; pCur != NULL; pCur = pCur->pNext, ++count);

	for (pCur = *pHead; count > 1; --count)
	{
		for (pCur = *pHead, pNext = (*pHead)->pNext; pNext != NULL; pCur = pNext, pNext = pNext->pNext)
		{
			if (strcmp(pCur->data.albumTitle, pNext->data.albumTitle) > 0)
			{
				swapNodes(&*pHead, &pCur, &pNext);
				Node* temp = pCur;
				pCur = pNext;
				pNext = temp;
			}
		}
	}
}

//function sorts playlist by rating(low-high)
void sortRating(Node** pHead)
{
	Node* pCur = *pHead, * pNext = (*pHead)->pNext;
	int count = 0;

	for (; pCur != NULL; pCur = pCur->pNext, ++count);

	for (pCur = *pHead; count > 1; --count)
	{
		for (pCur = *pHead, pNext = (*pHead)->pNext; pNext != NULL; pCur = pNext, pNext = pNext->pNext)
		{
			if (pCur->data.rating > pNext->data.rating)
			{
				swapNodes(&*pHead, &pCur, &pNext);
				Node* temp = pCur;
				pCur = pNext;
				pNext = temp;
			}
		}
	}
}

//function sorts playlist by times played (high- low)
void sortTimesPlayed(Node** pHead)
{
	Node* pCur = *pHead, * pNext = (*pHead)->pNext;
	int count = 0;

	for (; pCur != NULL; pCur = pCur->pNext, ++count);

	for (pCur = *pHead; count > 1; --count)
	{
		for (pCur = *pHead, pNext = (*pHead)->pNext; pNext != NULL; pCur = pNext, pNext = pNext->pNext)
		{
			if (pCur->data.timesPlayed > pNext->data.timesPlayed)
			{
				swapNodes(&*pHead, &pCur, &pNext); //swap position of the nodes
				Node* temp = pCur;
				pCur = pNext;
				pNext = temp;
			}
		}
	}
}

//function generates a node containing a unique randomly generated number
RandNode* makeRandNode(int rand)
{
	RandNode* pMem = malloc(sizeof(RandNode));
	pMem->num = rand;
	pMem->pNext = NULL;
	return pMem; 
}

//function generates a unique random num for list 'order'
int UniqueNum(RandNode* pHead, int num_records)
{
	int num = 0, flag = 0;
	RandNode* pCur = pHead;


	num = (rand() % num_records) + 1; //generate 1- size of playlist

	if (pHead != NULL) //if list is not empty
	{
		while(flag == 0) //check for repeats
		{
			flag = 1;

			for (pCur = pHead; pCur != NULL; pCur = pCur->pNext)
			{
				if (pCur->num == num)
				{
					flag = 0; //flag repeat
				}
			}

			if (flag == 0)
			{
				num = num = (rand() % num_records) + 1; //generate 1- size of playlist
			}
		}
	}

	return num;
}

//function inserts a new RandNode at the front of list 'order'
void insertRandNodeFront(RandNode** pHead, int num_records)
{
	int num = UniqueNum(*pHead, num_records);
	RandNode* pMem = makeRandNode(num);
	int success = 0;

	if (pMem != NULL)
	{
		success = 1;

		pMem->pNext = *pHead; //insert link at front of list
		*pHead = pMem;

	}
}

//function plays songs in order dictated by order list
void playShuffle(RandNode* oHead, Node* pHead)
{
	RandNode* Pos = NULL;

	Node* pCur = pHead;

	int position = 0;

	pCur = pHead;

	for (position = 1, Pos = oHead; Pos != NULL; Pos = Pos->pNext) //iterate through list 'order' 
	{
		for (; position < Pos->num; ++position, pCur = pCur->pNext);
		for (; position > Pos->num; --position, pCur = pCur->pPrev); //locate song to play

		play(pCur);
	}
}



