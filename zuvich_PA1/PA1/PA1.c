/*
Willow Zuvich
CPTS 122
PA1
Desc: Program intakes data from an input file, cleanses it, and parses into an array of structs.
Some calculations are performed, and the results are outputted to an output file, along with the now clean data
*/

#include "PA1.h"

//function inserts placeholder value into the string where data is missing
//inputs: one record(line) from the file
//output: edited string
//precondition: record must have been successfully read in
void Cleansing(char* record)
{
	int index = 0;
	int length = (int) strlen(record);
	

	for (; record[index] != '\0'; ++index)
	{
		//locate missing data feilds
		if ((record[index] == ',' && record[index +1] == ',') || (record[index] == ',' && record[index + 1] == '\n'))
		{
			//shift two spaces over
			for (int end = length + 2;end > index ; length += 2, --end) 
			{
				record[end] = record[end - 2];
			}

			//insert -1 at record[index + 1] / record[index + 1]
			record[index + 1] = '-';
			record[index + 2] = '1';
		}
	}
}


//function reads in and processes each string and parses data into the array
//inputs: pointer to the infile, pointer to the array of structs, and a pointer to the number of records
//outputs: The parsed and cleansed data, and the number of records that were taken in
//precondition: file must have been opened successfully
void recordIntake(FILE* infile, FitbitData* data, int* recordCount)
{
	char record[100] = "";
	char previous[100] = {'\0'};


	for (int index = 0; fgets(record, 100, infile) != NULL;) //read strings until end of file
	{
	
	
		//discard duplicate and non-target data
		if (strncmp(record, "12cx7", 5) == 0 && strcmp(record, previous) != 0)
		{

			//record previous string for deduping
			strcpy(previous, record);

			
			//call to cleanse function
			Cleansing(record);
			

			//tokenize record
			strcpy(data[index].patient, strtok(record, ","));
			strcpy(data[index].minute, strtok(NULL, ","));
			data[index].calories = atof(strtok(NULL, ","));
			data[index].distance = atof(strtok(NULL, ","));
			data[index].floors = atoi(strtok(NULL, ","));
			data[index].heartRate = atoi(strtok(NULL, ","));
			data[index].steps = atoi(strtok(NULL, ","));
			data[index].sleepLevel = (Sleep)atoi(strtok(NULL, "\n"));


			//update record count
			*recordCount = *recordCount + 1;

			//update index 
			++index;
		}

	}
}


//function calculates total burned calories
//inputs: A pointer to the array of structs and the number of records taken in
//outputs: the total calories burned in 24 hours
double TotalCals(FitbitData* data, int recordCount)
{
	double calories = 0.0;

	for (int index = 0; index < recordCount; ++index)
	{
		
			calories += data[index].calories;
		
	}

	return calories;

}

//function calculates total distance walked in miles
//inputs: A pointer to the array of structs and the number of records taken in
//outputs:the total distance traveled in 24 hours
double TotalDistance(FitbitData* data, int recordCount)
{
	double distance = 0.0;

	for (int index = 0; index < recordCount; ++index)
	{
		
			distance += data[index].distance;
		
	}

	return distance;

}

//function calculates total floors walked
//inputs: A pointer to the array of structs and the number of records taken in
//outputs:the total floors walked in 24 hours
unsigned int TotalFloors(FitbitData* data, int recordCount)
{
	int floors = 0;

	for (int index = 0; index < recordCount; ++index)
	{
		if (data[index].floors != -1) //ignore invalid data
		{
			floors += data[index].floors;
		}
	}

	return floors;
}

//function calculates total steps taken
//inputs: A pointer to the array of structs and the number of records taken in
//outputs:the total steps taken in 24 hours
unsigned int TotalSteps(FitbitData* data, int recordCount)
{
	int steps = 0;

	for (int index = 0; index < recordCount; ++index)
	{
		if (data[index].steps != -1) //ignore invalid data
		{
			steps += data[index].steps;
		}
	}

	return steps;
}

//function calculates the average heartrate over the 24 hour period
//inputs: A pointer to the array of structs and the number of records taken in
//outputs:the average heartrate in 24 hours
double AverageHeartRate(FitbitData* data, int recordCount)
{
	double sum = 0.0;

	for (int index = 0; index < recordCount; ++index)
	{
		if (data[index].heartRate != -1) //ignore invalid data
		{
			sum += data[index].heartRate; //find sum of all heartrates
		}
	}

	return (sum / recordCount);
}


//function finds max steps taken in 1 minute
//inputs: A pointer to the array of structs and the number of records taken in
//outputs:the maximum steps taken in 1 minute in 24 hours
unsigned int MaximumSteps(FitbitData* data, int recordCount)
{
	unsigned int max = 0;

	for (int index = 0; index < recordCount; ++index)
	{
		if (data[index].steps >= max && data[index].steps != -1) //check for new max
		{
			max = data[index].steps; //update max
		}
	}

	return max;
}


//function finds longest range of poor sleep
//inputs: pointer to the start and end time of the maximum range, and a
//pointer to the array of structs and the number of records taken in
//outputs: the start and end times to the longest range of poor sleep
void PoorSleep(char* start, char* end, FitbitData* data, int recordCount) 
{
	int maxRange = 0;
	int tempRange = 0;
	char tempStart[9] = "", tempEnd[9] = "";

	for (int index = 0; index < recordCount; ++index) //iterate through entire array
	{
		if (data[index].sleepLevel > 1) //if range is found
		{
			strncpy(tempStart, data[index].minute, 9); //copy start of range

			for (tempRange = 0; data[index].sleepLevel > 1; ++index) //iterate till end of range
			{
				tempRange += data[index].sleepLevel; //add up values in range
			}

			strncpy(tempEnd, data[index - 1].minute, 9); //copy end of range

			if (tempRange > maxRange) //if new max range is found
			{
				maxRange = tempRange; //update maxRange
				strncpy(start, tempStart, 9); //copy new start time
				strncpy(end, tempEnd, 9); //copy new end time
			}
		}
	}
}

//function outputs dedupes, filtered, and cleansed data to Results.csv
//inputs: pointer to the outfile, pointer to array of structs, and number of records taken in
void OutputCleanData(FILE* outfile, FitbitData* data, int recordCount)
{
	//heading
	fprintf(outfile, "\nTarget: ,12cx7,,,,,,\nPatient, minute, calories, distance, floors, heart, steps, sleep_level\n");

	//printing all data
	for (int index = 0; index < recordCount; ++index) //iterate through entire array
	{
		fprintf(outfile, "%s,%s,%lf,%lf,%d,%d,%d,%d\n", data[index].patient, data[index].minute, data[index].calories,
			data[index].distance, data[index].floors, data[index].heartRate, data[index].steps, data[index].sleepLevel);
	}
}