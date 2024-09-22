/*Willow Zuvich
PA3
Cpts 122
2/12/23
Desc: Doubly linked list operations on a music playlist
-Basic Digital Music Manager
*/

#include "PA3.h"
#include "PA3test.h"

int main(void)
{
	

	Node* pHead = NULL;

	int choice = 0;
	int success = 0;
	clock_t timeC = clock();

	srand((unsigned int)time(NULL));

	//run tests or run program
	do
	{
		printf("**************\n");
		printf("1. Run program\n2. Run Tests\nEnter Selection: ");
		(int) scanf("%d", &choice);
		system("cls");

	} while (choice != RUNPROGRAM && choice != TEST);


	if(choice == RUNPROGRAM) //run program
	{
		printf("*********************************************\n");
		printf("********* Welcome to Music Manager! *********\n");
		printf("*********************************************\n"); //welcome message

		timeC = clock();
		while (clock() < timeC + 1200); //pause program
		system("cls");


		do
		{

			//menu
			choice = menuOption();

			//choices
			if (choice == LOAD)
			{
				success = 0;

				FILE* infile = fopen("musicPlayList.csv", "r"); //open .csv for mode read

				if (infile == NULL)
				{
					printf("Unable to Access Playlist\n"); //check file opened successfully

				}
				else // if file opened correctly
				{

					success = load(&pHead, infile); //call to load
					printf("Loading...\n");

					timeC = clock();
					while (clock() < timeC + 500); //pause program

					if (success == 0)
					{
						printf("Failed to Load Playlist.\n"); //if unable to load playlist
					}
					else
					{
						printf("Playlist Loaded successfully."); //if playlist loaded successfully
					}

					fclose(infile); //close infile
				}



			}
			if (choice == STORE)
			{
				FILE* outfile = fopen("musicPlayList.csv", "w"); //open .csv for mode write
				store(pHead, outfile); //call to store
				printf("Storing...\n");
				fclose(outfile); //close file
			}
			if (choice == DISPLAY)
			{
				int userinput = 0;

				do //get valid user input
				{
					printf("1. Display all Records\n2. Display all Records from one Artist\n");
					scanf("%d", &userinput);
				} while (userinput != PRINTALL && userinput != PRINTARTIST);
				system("cls");


				display(pHead, userinput); //call to display

			}
			if (choice == INSERT)
			{
				success = 0;
				Record newRecord = { "", "", "", "", {0,0}, 0, 0 };
				getNewRecord(&newRecord);
				success = insertFront(&pHead, newRecord);

				if (success == 0)
				{
					printf("Failed to Add Record"); //if memory couldnt be allocated
				}
				else
				{
					printf("Record Added Successfully"); //if node was add successfully
				}

			}
			if (choice == DELETE)
			{
				Record searchRecord = { "", "", "", "", {0,0} , 0, 0 };
				printf("Enter Song Title to Delete: ");
				fgets(searchRecord.songTitle, 50, stdin);
				fgets(searchRecord.songTitle, 50, stdin);
				removeNewline(searchRecord.songTitle);   //get song title user wished to delete

				//call delete
				success = deleteNode(&pHead, searchRecord);

				if (success == 0)
				{
					printf("Record Not Found\n"); //if list is empty or title is not in list
				}
				else
				{
					printf("Record Deleted Successfully.\n"); // if record was found and successfully removed
				}

			}
			if (choice == EDIT)
			{
				Node* pCur = findRecord(pHead); //locate record user wishes to edit
				edit(pCur); //call to edit
				printf("Record Updated.\n");

			}
			if (choice == SORT)
			{
				int sort = 0;
				//input val loop
				do
				{
					printf("1. Artist Name (A-Z)\n2. Album Title (A-Z)\n3. Rating (low-high)\n4. TimesPlayed (low-high)\n");
					printf("Choose Method of Sorting: ");
					scanf("%d", &sort);
					system("cls");

				} while (sort != ARTIST && sort != ALBUM && sort != RATING && sort != TIMESPLAYED);

				if (sort == ARTIST)
				{
					sortArtist(&pHead); //sort by artist
				}
				else if (sort == ALBUM)
				{
					sortAlbumTitle(&pHead); //sort by album
				}
				else if (sort == RATING)
				{
					sortRating(&pHead); //sort by rating
				}
				else
				{
					sortTimesPlayed(&pHead); //sort by times played
				}

				printf("Playlist sorted.\n");
			}
			if (choice == RATE)
			{
				Node* pCur = findRecord(pHead); //find record user wishes to rate
				rate(pCur); //call rate
				printf("Rating Updated.\n");
			}
			if (choice == PLAY)
			{
				printf("Play From...\n");
				Node* pStart = findRecord(pHead); //locate starting point
				for (; pStart != NULL; pStart = pStart->pNext) //play all songs until the end of the playlist
				{
					play(pStart); //call to play
				}
				printf("End of Playlist.\n");
			}
			if (choice == SHUFFLE)
			{
				RandNode* OrderHead = NULL;
				int count = 0, position = 0;
				Node* pCur = pHead;

				for (pCur = pHead; pCur != NULL; pCur = pCur->pNext, ++count); //find number of records

				for (; position < count; ++position) //generate a Randnode for each record
				{
					insertRandNodeFront(&OrderHead, count); //call to insert randnode front to generate order
				}
			
				playShuffle(OrderHead, pHead); //play songs in order specified 

				printf("End of Playlist.\n");

			}
			if (choice == EXIT)
			{
				FILE* outfile = fopen("musicPlayList.csv", "w"); //open .csv for mode write
				//write current playlist to file
				store(pHead, outfile); //call to store - save changes


				printf("Exiting...");
				fclose(outfile);
				return 0; //end of program
			}

			//clearscreen
			timeC = clock();
			while (clock() < timeC + 1500);
			system("cls"); //add buffer before returning to menu

		} while (choice != EXIT && choice != 0);
	}

	else
	{
	/*
	expected result:
	Memory allocated
	"Perry, Katy",Witness,Chained to the Rhythm,4:36,0,5
	Head pointer Updated Successfully
	Invalid input caught and corrected
	Data: "Perry, Katy",Witness,Chained to the Rhythm,4:36,0,*/
		testInsert();

		/*
	expected result:
	Node found
	Memory Released successfully
	Head pointer updated*/
		testDelete();

		char answer = 'n';
		printf("\nTest Shuffle? (y/n): \n");
		answer = getYorN();

		if(answer == 'y')
		{

			/*
			expected result:
			Play First: SZA,SOS,Kill Bill,R&B,2:33,8,5 //for 1.5 seconds each
			Play Second: "Perry, Katy",Witness,Chained to the Rhythm,pop,4:36,3,5
			Play Third: Drake,YOU WELCOME,The Motto,Rap,4:13,7,4
			(order 3, 1, 2)*/
			testShuffle();
		}

		printf("End of Test.\nExiting...\n");

		return 0;
	}
	
}
