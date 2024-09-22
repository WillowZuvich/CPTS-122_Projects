/*Willow Zuvich
PA3 Test
Cpts 122
2/12/23
Desc: Tests commands insert, delete, and shuffle from PA3
*/

#include "PA3test.h"

//function tests insert 
/*
expected result:
Memory allocated
"Perry, Katy",Witness,Chained to the Rhythm,4:36,0,5
Head pointer Updated Successfully
Invalid input caught and corrected
Data: "Perry, Katy",Witness,Chained to the Rhythm,4:36,0,5
*/
void testInsert(void)
{
	Record testPoint = { "Perry, Katy", "Witness", "Chained to the Rhythm", "pop", {4, 36}, -1, 6 };
	Node* pList = NULL;

	int success = insertFront(&pList, testPoint);

	printf("***Results of testInsert***\n\n");

	if (success == 1)
	{
		printf("Memory Allocated.\n");

		if (pList != NULL)
		{
			printf("Head pointer Updated successfully\n");

			if (pList->data.timesPlayed != testPoint.timesPlayed)
			{
				printf("Invalid input caught and corrected\nData:");
				printList(pList);
			}
			else
			{
				printf("Failed to catch invalid input.\n");
				printList(pList);
			}
		}
		else
		{
			printf("Failed to update Head pointer successfully\nData:");
		}
	}
	else
	{
		printf("Insert failed\n");
	}
}

//function tests delete 
/*
expected result:
Node found
Memory Released successfully
Head pointer updated
*/
void testDelete(void)
{
	Record testPoint = { "Perry, Katy", "Witness", "Chained to the Rhythm", "pop", {4, 36}, 3, 5 };
	Node* pList = NULL;
	Node* pMem = NULL;

	pMem = (Node*) malloc(sizeof(Node)); //innit pMem

	printf("\n***Results of testDelete***\n\n");

	if (pMem != NULL)
	{
		strcpy(pMem->data.artist, testPoint.artist);
		strcpy(pMem->data.albumTitle, testPoint.albumTitle);
		strcpy(pMem->data.songTitle, testPoint.songTitle);
		strcpy(pMem->data.genre, testPoint.genre);
		pMem->data.songLength.minutes = testPoint.songLength.minutes;
		pMem->data.songLength.seconds = testPoint.songLength.seconds;
		pMem->data.timesPlayed = testPoint.timesPlayed;
		pMem->data.rating = testPoint.rating;


		pMem->pNext = NULL;
		pMem->pPrev = NULL;

		pList = pMem;

		int success = deleteNode(&pList, testPoint);

		if (success == 1)
		{
			printf("Node found\n");

			if (strcmp(pMem->data.artist, "Perry, Katy") != 0)
			{
				printf("Memory released successfully\n");

				if (pList == NULL)
				{
					printf("Head pointer updated\n");
				}
				else
				{
					printf("Failed to update head pointer\n");
				}
			}
			else
			{
				printf("Failed to release memory\n");
			}
		}
		else
		{
			printf("Node not found\n");
		}
	}

	else
	{
		printf("Could not allocate memory\n");
	}
}

//function tests shuffle
/*
expected result:
Play First: SZA,SOS,Kill Bill,R&B,2:33,8,5 //for 1.5 seconds each
Play Second: "Perry, Katy",Witness,Chained to the Rhythm,pop,4:36,3,5 
Play Third: Drake,YOU WELCOME,The Motto,Rap,4:13,7,4
(order 3, 1, 2)
*/
void testShuffle(void)
{
	RandNode* oHead = NULL;
	Node* pHead = NULL, * pMem = pHead;
	Record song1 = { "Perry, Katy", "Witness", "Chained to the Rhythm", "pop", {4, 36}, 3, 5 },
		song2 = { "Drake", "YOU WELCOME", "The Motto", "Rap", {4, 13}, 7, 4 },
		song3 = { "SZA", "SOS", "Kill Bill", "R&B", {2, 33}, 8, 5 };


	oHead = malloc(sizeof(RandNode));
	oHead->num = 3;
	oHead->pNext = malloc(sizeof(RandNode));
	oHead->pNext->num = 1;
	oHead->pNext->pNext = malloc(sizeof(RandNode));
	oHead->pNext->pNext->num = 2;
	oHead->pNext->pNext->pNext = NULL; //innit order list

	pMem = malloc(sizeof(Node));
	strcpy(pMem->data.artist, song1.artist);
	strcpy(pMem->data.albumTitle, song1.albumTitle);
	strcpy(pMem->data.songTitle, song1.songTitle);
	strcpy(pMem->data.genre, song1.genre);
	pMem->data.songLength.minutes = song1.songLength.minutes;
	pMem->data.songLength.seconds = song1.songLength.seconds;
	pMem->data.timesPlayed = song1.timesPlayed;
	pMem->data.rating = song1.rating;
	pMem->pNext = NULL;
	pMem->pPrev = NULL; //innit first song in list

	pHead = pMem;

	Node* temp = pMem;
	pMem = pMem->pNext;

	pMem = malloc(sizeof(Node));
	strcpy(pMem->data.artist, song2.artist);
	strcpy(pMem->data.albumTitle, song2.albumTitle);
	strcpy(pMem->data.songTitle, song2.songTitle);
	strcpy(pMem->data.genre, song2.genre);
	pMem->data.songLength.minutes = song2.songLength.minutes;
	pMem->data.songLength.seconds = song2.songLength.seconds;
	pMem->data.timesPlayed = song2.timesPlayed;
	pMem->data.rating = song2.rating;
	pMem->pNext = NULL;
	pMem->pPrev = temp; //innit second song in list

	temp->pNext = pMem;
	temp = pMem;
	pMem = pMem->pNext;

	pMem = malloc(sizeof(Node));
	strcpy(pMem->data.artist, song3.artist);
	strcpy(pMem->data.albumTitle, song3.albumTitle);
	strcpy(pMem->data.songTitle, song3.songTitle);
	strcpy(pMem->data.genre, song3.genre);
	pMem->data.songLength.minutes = song3.songLength.minutes;
	pMem->data.songLength.seconds = song3.songLength.seconds;
	pMem->data.timesPlayed = song3.timesPlayed;
	pMem->data.rating = song3.rating;
	pMem->pNext = NULL;
	pMem->pPrev = temp; //innit third song in list

	temp->pNext = pMem;

	playShuffle(oHead, pHead); //call to shuffle w/ specified order
	

}