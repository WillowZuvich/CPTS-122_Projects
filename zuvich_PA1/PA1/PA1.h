/*
Willow Zuvich
CPTS 122
PA1
Desc: Program intakes data from an input file, cleanses it, and parses into an array of structs.
Some calculations are performed, and the results are outputted to an output file, along with the now clean data
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#ifndef PA1_H
#define PA1_H

typedef enum sleep
{

	NONE, ASLEEP, AWAKE, REALLYAWAKE
}Sleep;

typedef struct fitbit
{
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;

}FitbitData;

//function inserts placeholder value into the string where data is missing
//inputs: one record(line) from the file
//output: edited string
//precondition: record must have been successfully read in
void Cleansing(char* record);

//function reads in and processes each string and parses data into the array
//inputs: pointer to the infile, pointer to the array of structs, and a pointer to the number of records
//outputs: The parsed and cleansed data, and the number of records that were taken in
//precondition: file must have been opened successfully
void recordIntake(FILE* infile, FitbitData* data, int* recordCount);

//function calculates total burned calories
//inputs: A pointer to the array of structs and the number of records taken in
//outputs: the total calories burned in 24 hours
double TotalCals(FitbitData* data, int recordCount);

//function calculates total distance walked in miles
//inputs: A pointer to the array of structs and the number of records taken in
//outputs:the total distance traveled in 24 hours
double TotalDistance(FitbitData* data, int recordCount);

//function calculates total floors walked
//inputs: A pointer to the array of structs and the number of records taken in
//outputs:the total floors walked in 24 hours
unsigned int TotalFloors(FitbitData* data, int recordCount);

//function calculates total steps taken
//inputs: A pointer to the array of structs and the number of records taken in
//outputs:the total steps taken in 24 hours
unsigned int TotalSteps(FitbitData* data, int recordCount);

//function calculates the average heartrate over the 24 hour period
//inputs: A pointer to the array of structs and the number of records taken in
//outputs:the average heartrate in 24 hours
double AverageHeartRate(FitbitData* data, int recordCount);

//function finds max steps taken in 1 minute
//inputs: A pointer to the array of structs and the number of records taken in
//outputs:the maximum steps taken in 1 minute in 24 hours
unsigned int MaximumSteps(FitbitData* data, int recordCount);

//function finds longest range of poor sleep
//inputs: pointer to the start and end time of the maximum range, and a
//pointer to the array of structs and the number of records taken in
//outputs: the start and end times to the longest range of poor sleep
void PoorSleep(char* start, char* end, FitbitData* data, int recordCount);

//function outputs dedupes, filtered, and cleansed data to Results.csv
//inputs: pointer to the outfile, pointer to array of structs, and number of records taken in
void OutputCleanData(FILE* outfile, FitbitData* data, int recordCount);


#endif
