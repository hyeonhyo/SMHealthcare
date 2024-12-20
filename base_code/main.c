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
    FILE *dietFile = fopen(DIETFILEPATH, "r");
    FILE *exerciseFile = fopen(EXERCISEFILEPATH, "r"); //24.12.13.

    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    do {//섭취 칼로리 -기초 대사량 - 소모 칼로리 = 0 이거나 4.Exit 옵션 선택 시 종료 
    	if (health_data.total_calories_intake - BASAL_METABOLIC_RATE - health_data.total_calories_burned == 0){
            printf("You have consumed all your calories for today! \n");
		} 
		else{
			printf("\n=======================================================================\n");
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
            	inputExercise(&health_data); //exercise 선택  후 calories 소모를 healthdata에 추가 // &를 이용해서 참조함 
                break;
                
            case 2:
            	inputDiet(&health_data); // diest 선택 후 칼로리를 healthdata에 추가 
                break;
                
            case 3:
            	printHealthData(&health_data); // health_data 출력 
                break;
                
            case 4:
            	
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                break;
                
            default:
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
    } while (choice != 4); //4.Exit 옵션 선택 시 종료 

    return 0;
}

