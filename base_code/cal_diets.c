//
//  cal_diets.c
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

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
    while (fscanf(file, "%s %d", diet_list[diet_list_size].food_name, diet_list[diet_list_size].calories_intake )!= EOF){
    	//food, calories 읽어서 diet list에 저장하기 
        if (diet_list_size >= MAX_DIETS){
        	break;
		}
    }
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, i;
    
    // ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");
    //for 문을 이용해서 
	//for(i=0; i<diet_list_size; i++) diet_list에 있는 food_name과 calories_intake를 출력함 
    
   
    
	// ToCode: to enter the diet to be chosen with exit option
	printf("choose a diet (4: exit):\n"); //사용자로부터 choice 입력받기 
	scanf("%d", &choice); // 2024.12.14 (main.c도 고치기)
	
	if (choice ==4){
		return; // exit option
	}
    

    // ToCode: to enter the selected diet in the health data
    //selected diet를 diet_list 애서 가져와서 health_data 에 복사하기..
	

    

    // ToCode: to enter the total calories intake in the health data
    //selected diet의 칼로리를 total_calories_intake에 더해서 총 칼로리를 구함 
    //health_data에 있는 toal_calories_intake 를 health_data -> total_calories_intake으로 구조체 포인터로 멤버 접근함 
    



}

