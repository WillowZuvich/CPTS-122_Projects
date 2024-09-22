/*
Willow Zuvich
CPTS 122
PA1
Desc: Program intakes data from an input file, cleanses it, and parses into an array of structs.
Some calculations are performed, and the results are outputted to an output file, along with the now clean data
*/



#include "PA1.h"


int main(void)
{
	
	//open file
	FILE* infile = fopen("FitbitData.csv", "r");


	//data
	FitbitData fibData[1440] = { {"", "", 0.0, 0.0, 0, 0, 0, NONE} };
	int recordCount = 0;

	double caloriesBurned = 0.0;
	double distanceWalked = 0.0;
	unsigned int floorsWalked = 0;
	unsigned int StepsTaken = 0;
	double AvgHeartRate = 0;
	unsigned int MaxSteps = 0;
	char SleepStart[9] = "";
	char SleepEnd[9] = "";



	//check if file opened successfully
	if (infile != NULL)
	{
		//file opened successfully 
		
		//call to record intake 
		recordIntake(infile, fibData, &recordCount);

		//call to calculation functions
		caloriesBurned = TotalCals(fibData, recordCount);
		
		distanceWalked = TotalDistance(fibData, recordCount);
		
		floorsWalked = TotalFloors(fibData, recordCount);

		StepsTaken = TotalSteps(fibData, recordCount);

		AvgHeartRate = AverageHeartRate(fibData, recordCount);

		MaxSteps = MaximumSteps(fibData, recordCount);

		PoorSleep(SleepStart, SleepEnd, fibData, recordCount);

		//output data
		FILE* outfile = fopen("Results.csv", "w");

		fprintf(outfile, "Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n"); //header line
		
		fprintf(outfile, "%lf,%lf,%d,%d,%.2lf,%d,%s:%s\n", caloriesBurned, distanceWalked, floorsWalked, StepsTaken, AvgHeartRate,
			MaxSteps, SleepStart, SleepEnd); //values

		//call to output cleaned data function
		OutputCleanData(outfile, fibData, recordCount);

		//close input and output files
		fclose(infile);
		fclose(outfile);
		
	}
	else 
	{
		//file did not open successfully
		printf("Could not open Fitbit.csv\n");
	}



	return 0;
}