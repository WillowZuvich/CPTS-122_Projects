/*Willow Zuvich
PA3
Cpts 122
2/12/23
Desc: Doubly linked list operations on a music playlist
-Basic Digital Music Manager
*/

#define _CRT_SECURE_NO_WARNINGS

#ifndef PA2_H
#define PA2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TEST 2
#define RUNPROGRAM 1

#define PRINTALL 1
#define PRINTARTIST 2

#define ARTIST 1
#define ALBUM 2
#define RATING 3
#define TIMESPLAYED 4

#define LOAD 1
#define STORE 2
#define DISPLAY 3
#define INSERT 4
#define DELETE 5
#define EDIT 6
#define SORT 7
#define RATE 8
#define PLAY 9
#define SHUFFLE 10 
#define EXIT 11


typedef struct duration
{
	int minutes;
	int seconds;
}Duration;

typedef struct record
{
	char artist[30];
	char albumTitle[30];
	char songTitle[50];
	char genre[20];
	Duration songLength;
	int timesPlayed;
	int rating;
}Record;

typedef struct node
{
	Record data;
	struct node* pPrev;
	struct node* pNext;
}Node;

typedef struct randNode
{
	int num;
	struct randNode* pNext;
}RandNode;

//function allocates memory for and initializes a Node
//Return: pointer to new node
Node* makeNode(Record newData);

//function inserts new node at the head position in the list
//returns: 0 for failure, 1 for success
int insertFront(Node** pList, Record newData);

//Function prints menu
void printMenu(void);

//function obtains users selection from menu
//returns: user selection
int menuOption(void);

//function removes \n char from string - replaces with null char
void removeNewline(char* str);

//function reads all record from a csv file and places them into a doubly linked list
int load(Node** pHead, FILE* infile);

//function writes all records in the current list to musicPlayList.csv
void store(Node* pHead, FILE* outfile);

//function prints all records
void printList(Node* pHead);

//function prints all records from artist
void printFromArtist(Node* pHead, char* artist);

//function either displays all records to the screen or all records from one artist
void display(Node* pHead, int userinput);

//function find record user wishes to edit or rate
Node* findRecord(Node* pHead);

//function gets yes or no from user
char getYorN();

//function allows user to rate chosen record
void rate(Node* pEdit);

//function edits record pointed to
void edit(Node* pEdit);

//function displays a record for a short period of time 
void play(Node* pStart);

//function gets information for new record from user
void getNewRecord(Record* newRecord);

//function deletes searchdata from the list - if it exists
int deleteNode(Node** pHead, Record SearchData);

//Node swaps position of two Nodes
void swapNodes(Node** pHead, Node** pOne, Node** pTwo);

//function sorts the playlist by artist (A-Z)
void sortArtist(Node** pHead);

//function sorts playlist by album title (A-Z)
void sortAlbumTitle(Node** pHead);

//function sorts playlist by rating(low-high)
void sortRating(Node** pHead);

//function sorts playlist by times played (high- low)
void sortTimesPlayed(Node** pHead);

//function generates a node containing a unique randomly generated number
RandNode* makeRandNode(int rand);

//function generates a unique random num for list 'order'
int UniqueNum(RandNode* pHead, int num_records);

//function inserts a new RandNode at the front of list 'order'
void insertRandNodeFront(RandNode** pHead, int num_records);

//function plays songs in order dictated by order list
void playShuffle(RandNode* oHead, Node* pHead);

#endif