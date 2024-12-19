//
//  main.c
//  Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define EXERCISEFILEPATH "exercises.txt"
#define DIETFILEPATH "diets.txt"
#define HEALTHFILEPATH "health_data.txt"

static int choice;



int main() {
	// To initialize the health data object
    HealthData health_data = {0};
    
    // Tocode: to read the list of the exercises and diets
    
    loadExercises(EXERCISEFILEPATH);  // Calling a function that reads the exercise list from a file by haeun
    loadDiets(DIETFILEPATH);  // Calling a function that reads a list of diet from a file by haeun
    
    

    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    do {
    	if (health_data.total_calories_intake >= 2000){  //  // If the total number of calories consumed is 2000 or more, no more calories can be added by haeun
            printf("You have consumed all your calories for today! \n"); // Notify that you have exhausted all your calories by haeun
		} 
		else{
			printf("\n=======================================================================\n");  // print system options for users to choose from by haeun
        	printf("[Healthcare Management Systems] \n");
        	printf("1. Exercise \n");
        	printf("2. Diet \n");
        	printf("3. Show logged information \n");
        	printf("4. Exit \n");
        	printf("Select the desired number: ");
        	scanf("%d", &choice);
        	printf("=======================================================================\n");
        }
        
		// ToCode: to run the sysmtem based on the user's choice
        switch (choice) {
            case 1:
            	
            	inputExercise(&health_data);  //structure for exercise by haeun
            	
                break;
                
            case 2:
            	
            	inputDiet(&health_data); //structure for diet by haeun

            	
                break;
                
            case 3:
            	
            	printHealthData(&health_data); //print for healthdata by haeun

            	
                break;
                
            case 4:
            	
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                break;
                
            default:
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        } 
    } while (health_data.total_calories_intake < 2000 && choice != 4);  //Repeat until 2000 calories are exceeded or the user shuts down by haeun

    return 0;  // program end by haeun
}

