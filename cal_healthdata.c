//
//  cal_healthdata.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"


/*
    description : enter the exercise and diet history in "health_data.txt" 
    input parameters : health_data - data object in which the selected exercise and diet is stored
    return value : No
    
    operation : 1. save the chosen exercise and total calories burned 
    			2. save the chosen diet and total calories intake 
    			3. save the total remaining calrories
*/

void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	int i;
    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
        printf("There is no file for health data.\n");
        return;
    }

    // ToCode: to save the chosen exercise and total calories burned 
    fprintf(file, "[Exercises] \n");
    
    for (i = 0; i < health_data->exercise_count; i++) {   //exercise Listed on File: Outputting Exercise Name and Calorie Burnout  by haeun
        fprintf(file, "%d. %s, Calories burned: %d kcal\n",
                i + 1,
                health_data->exercises[i].exercise_name,
                health_data->exercises[i].calories_burned_per_minute);
    }  // // Output exercise history to a file by haeun

    
    
    // ToCode: to save the chosen diet and total calories intake 
    fprintf(file, "\n[Diets] \n");
    
    for (i = 0; i < health_data->diet_count; i++) {   // Record Diet List on File: Print Food Name and Calorie Intake by haeun
        fprintf(file, "%d. %s, Calories intake: %d kcal\n",
                i + 1,
                health_data->diet[i].food_name,
                health_data->diet[i].calories_intake);
    } //// Output Diet History to a File by haeun




    // ToCode: to save the total remaining calrories
    fprintf(file, "\n[Total] \n");
    
    int remaining_calories = health_data->total_calories_intake -
                             (BASAL_METABOLIC_RATE + health_data->total_calories_burned);  // difference between basal metabolism and calories consumed by haeun
    fprintf(file, "Basic Metabolic Rate: %d kcal\n", BASAL_METABOLIC_RATE);  // print Basic Metabolic Output by haeun
    fprintf(file, "Total Calories Burned: %d kcal\n", health_data->total_calories_burned); // print Total Calories burned by haeun
    fprintf(file, "Total Calories Intake: %d kcal\n", health_data->total_calories_intake); // print Total Calories intake by haeun
    fprintf(file, "Remaining Calories: %d kcal\n", remaining_calories); // print Remaining Calories by haeun

    fclose(file); // close file by haeun
} // savaData close by haeun
    
    


/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
*/

	
void printHealthData(const HealthData* health_data) {
    int i;
    int remaining_calories = health_data->total_calories_intake - (BASAL_METABOLIC_RATE + health_data->total_calories_burned); // calculating remain cal by haeun
    
	
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
	
	
    if (health_data->exercise_count == 0) {
        printf("No exercise data available.\n");  // print if there is no exercise data by haeun
    } else {
         for (i = 0; i < health_data->exercise_count; i++) {
            printf("Exercise: %s, Calories burned: %d kcal\n",
                   health_data->exercises[i].exercise_name,  //print exercise name by haeun
                   health_data->exercises[i].calories_burned_per_minute); // print cal_burned by haeun
        }
    }  //Exercise Record Output Ends by haeun
 
	
	 
  
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");
    
    if (health_data->diet_count == 0) {
        printf("No diet data available.\n");   // print if no diet data by haeun
    } else {
        for (i = 0; i < health_data->diet_count; i++) {   // print diet by haeun
            printf("Food: %s, Calories intake: %d kcal\n",  
                   health_data->diet[i].food_name,  // food name print by haeun 
                   health_data->diet[i].calories_intake);  // cal_intake print by haeun
        }  //by haeun
  

    printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
	
	int remaining_calories = health_data->total_calories_intake - (BASAL_METABOLIC_RATE + health_data->total_calories_burned);
    printf("Basic Metabolic Rate: %d kcal\n", BASAL_METABOLIC_RATE);    // basic meta rate print by haeun 
    printf("Total Calories Burned: %d kcal\n", health_data->total_calories_burned); // total cal_burned print by haeun 
    printf("Total Calories Intake: %d kcal\n", health_data->total_calories_intake); // total cal_intake print by haeun 
    printf("Remaining Calories: %d kcal\n", remaining_calories); // remaining cal print by haeun

 
 
    printf("=======================================================================\n \n");
    
}
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake 
	

	 if (remaining_calories == 0) {  
        printf("You have consumed all your calories for today!\n");  
        printf("=======================================================================\n");
        return;  // Print a message for system shutdown and then exit the function by haeun
    } else if (remaining_calories < 0) {
        printf("[Warning] Too few calories!\n"); // cal<0 by haeun
    if (health_data->total_calories_intake >= DAILY_CALORIE_GOAL) {
            printf("Your total calorie intake for today has reached your goal!\n"); // print message when caloric goal is achieved by haeun 
        } else if (health_data->total_calories_intake < DAILY_CALORIE_GOAL) {
            printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n"); //Output message when caloric goal is less achieved
        } else {
            printf("You have eaten more calories than planned today, but you have exercised too much!\n"); // Output message when caloric goal is more achieved
        }
    } else {  // if exercise less
        printf("Please exercise for your health!\n");
        if (health_data->total_calories_intake >= DAILY_CALORIE_GOAL) {
            printf("Your total calorie intake for today has reached your goal!\n");  // print message when caloric goal is achieved by haeun 
        } else if (health_data->total_calories_intake < DAILY_CALORIE_GOAL) {
            printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n");  // print message when caloric goal is not achieved by haeun
        } 
    }    
   
    
    
	 printf("=======================================================================\n");   
	 
}

