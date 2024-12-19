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
	int remaining_calories; // ���� Į�θ� ���� ���� 
    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
        printf("There is no file for health data.\n");
        return;
    }

    // ToCode: to save the chosen exercise and total calories burned 
    fprintf(file, "[Exercises] \n");
    for(i = 0; i < health_data->exercise_count; i++) { //�̋����� ������ �, �Ҹ�� Į�θ��� �����ϱ� ����  for ���� �̿��� 
    //i �� health_data�� �����ϱ� ���� ���� 
	// health_data�� -> health_data -> exercise_count �� �̿��ؼ� ����ü ������ �����ϸ�  ��ϵ� health_data�� �� ������ ��Ÿ����. 
        fprintf(file, "%s - %d kcal\n", health_data -> exercises[i].exercise_name, //%s�� � �̸�(���ڿ�), %d�� �Ҹ� Į�θ�(����)ǥ���� 
                health_data -> exercises[i].calories_burned_per_minute); //���� � �̸�, �ش� ����� �Ҹ�� Į�θ� 
    fprintf(file, "Total calories burned: %d kcal\n", health_data->total_calories_burned); //������ �Ҹ� Į�θ� ��� 
    
    // ToCode: to save the chosen diet and total calories intake 
    fprintf(file, "\n[Diets] \n");
    for (i=0; i< health_data->diet_count; i++){ //�̶����� ���� �Ļ� ����, ������ Į�θ��� �����ϱ�  ���� for ���� �̿��� 
    	fprintf(file, "%s - %d kcal\n", health_data -> diet[i].food_name, health_data -> diet[i].calories_intake);
    	//���� �̸�, ���� Į�θ��� ����ϸ� %s�� �����̸�(���ڿ�), %d�� ���� Į�θ�(����)�� ��Ÿ�� 
	}
	fprintf(file, "Total calories intake: %d kcal\n", health_data -> total_calories_intake); //��� �� ���� Į�θ��� ����� 
	//health_data -> total_calories_intake �� ����ü �������� �̶����� ���� Į�θ� ���� ����� 


    // ToCode: to save the total remaining calrories
    remaining_calories = health_data->total_calories_intake - BASAL_METABOLIC_RATE - health_data->total_calories_burned;
    // ���� Į�θ�(���� Į�θ� - ���� ��緮- �Ҹ�� Į�θ� )
    fprintf(file, "\n[Total] \n");
    fprintf(file, "Basal metabolic rate - %d kcal\n", BASAL_METABOLIC_RATE);
    fprintf(file, "The remaining calories - %d kcal\n", remaining_calories);
}
    
    
}

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
	int remaining_calories; // ���� Į�θ� ����
	
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
	for ( i=0; i < health_data -> exercise_count; i++){
		printf("Exercise: %s, Calories burned: %d kcal\n", health_data -> exercises[i].exercise_name, health_data -> exercises[i].calories_burned_per_minute);
		//Exercise �̸��� �Ҹ� Į�θ� ��� 
	}
  
  
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");
	for (i = 0; i < health_data -> diet_count; i++) {
        printf("Food: %s, Calories intake: %d kcal\n", health_data->diet[i].food_name, 
               health_data->diet[i].calories_intake);
}
    printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
 	printf("Basal Metabolic rate: %d kcal\n", BASAL_METABOLIC_RATE);
    printf("Total calories burned: %d kcal\n", health_data->total_calories_burned);
    printf("Total calories intake: %d kcal\n", health_data->total_calories_intake);
    printf("The remaining calories: %d kcal\n", remaining_calories);
    // health_data �� ����ü ����� -> �� �̿��ؼ� ������ 
    printf("=======================================================================\n \n");
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
     if (remaining_calories == 0) {
        printf("You have consumed all your calories for today!"); // ���� Į�θ� =0�� ��� 
    } else if (remaining_calories < 0) { //���� Į�θ�<0�� ��� 
        printf("[Warning] Too few calories!");
    } else if (health_data->total_calories_intake < DAILY_CALORIE_GOAL) {//���� Į�θ��� ���� ���� Į�θ����� ���� ��� 
        printf("Your total calorie intake for today has not reached your goal. Remember to eat more!\n");}
      else if (health_data -> total_calories_intake > DAILY_CALORIE_GOAL){//���� Į�θ��� ���� Į�θ����� ���� ��� 
      	printf("You have eaten more calories than planned today, but you have exercised too much!");
	  }
	  else if (health_data -> total_calories_intake >= DAILY_CALORIE_GOAL){//����Į�θ��� ���� ���� Į�θ��� ������ ��� 
    	printf("Your total calorie intake for today has reached your goal!");
    }
    
    if (remaining_calories >0){ // ���� Į�θ� >0�� ��� 
      	printf("Please exercise for your health!");
	  }	else if (health_data -> total_calories_intake >= DAILY_CALORIE_GOAL){ //���� Į�θ��� ���� ���� Į�θ��� ������ ���
	  printf("Your total calorie intake for today has reached your goal!");
	}
	else if (health_data -> total_calories_intake < DAILY_CALORIE_GOAL){//���� Į�θ��� ���� ���� Į�θ����� ���� ��� 
		printf("Your total calorie intake for today has not reached yout goal, remember to eat more!!"); 
	}
    
	printf("=======================================================================\n");
}
