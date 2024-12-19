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
	int remaining_calories; // 남은 칼로리 변수 정의 
    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
        printf("There is no file for health data.\n");
        return;
    }

    // ToCode: to save the chosen exercise and total calories burned 
    fprintf(file, "[Exercises] \n");
    for(i = 0; i < health_data->exercise_count; i++) { //이떄까지 진행한 운동, 소모된 칼로리를 저장하기 위해  for 문을 이용함 
    //i 는 health_data를 참조하기 위한 변수 
	// health_data에 -> health_data -> exercise_count 를 이용해서 구조체 변수를 참조하며  기록된 health_data의 총 개수를 나타내줌. 
        fprintf(file, "%s - %d kcal\n", health_data -> exercises[i].exercise_name, //%s는 운동 이름(문자열), %d는 소모 칼로리(정수)표시함 
                health_data -> exercises[i].calories_burned_per_minute); //현재 운동 이름, 해당 운동으로 소모된 칼로리 
    fprintf(file, "Total calories burned: %d kcal\n", health_data->total_calories_burned); //누적된 소모 칼로리 출력 
    
    // ToCode: to save the chosen diet and total calories intake 
    fprintf(file, "\n[Diets] \n");
    for (i=0; i< health_data->diet_count; i++){ //이때까지 먹은 식사 종류, 섭취한 칼로리를 저장하기  위해 for 문을 이용함 
    	fprintf(file, "%s - %d kcal\n", health_data -> diet[i].food_name, health_data -> diet[i].calories_intake);
    	//음식 이름, 섭취 칼로리를 출력하며 %s는 음식이름(문자열), %d는 섭취 칼로리(정수)를 나타냄 
	}
	fprintf(file, "Total calories intake: %d kcal\n", health_data -> total_calories_intake); //모든 총 섭취 칼로리를 출력함 
	//health_data -> total_calories_intake 로 구조체 변수에서 이때까지 먹은 칼로리 값을 출력함 


    // ToCode: to save the total remaining calrories
    remaining_calories = health_data->total_calories_intake - BASAL_METABOLIC_RATE - health_data->total_calories_burned;
    // 남은 칼로리(섭취 칼로리 - 기초 대사량- 소모된 칼로리 )
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
	int remaining_calories; // 남은 칼로리 정의
	
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
	for ( i=0; i < health_data -> exercise_count; i++){
		printf("Exercise: %s, Calories burned: %d kcal\n", health_data -> exercises[i].exercise_name, health_data -> exercises[i].calories_burned_per_minute);
		//Exercise 이름과 소모 칼로리 출력 
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
    // health_data 의 구조체 멤버에 -> 를 이용해서 참조함 
    printf("=======================================================================\n \n");
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
     if (remaining_calories == 0) {
        printf("You have consumed all your calories for today!"); // 남은 칼로리 =0인 경우 
    } else if (remaining_calories < 0) { //남은 칼로리<0인 경우 
        printf("[Warning] Too few calories!");
    } else if (health_data->total_calories_intake < DAILY_CALORIE_GOAL) {//섭취 칼로리가 일일 권장 칼로리보다 적은 경우 
        printf("Your total calorie intake for today has not reached your goal. Remember to eat more!\n");}
      else if (health_data -> total_calories_intake > DAILY_CALORIE_GOAL){//섭취 칼로리가 권장 칼로리보다 많은 경우 
      	printf("You have eaten more calories than planned today, but you have exercised too much!");
	  }
	  else if (health_data -> total_calories_intake >= DAILY_CALORIE_GOAL){//섭취칼로리가 일일 권장 칼로리에 도달한 경우 
    	printf("Your total calorie intake for today has reached your goal!");
    }
    
    if (remaining_calories >0){ // 남은 칼로리 >0인 경우 
      	printf("Please exercise for your health!");
	  }	else if (health_data -> total_calories_intake >= DAILY_CALORIE_GOAL){ //섭취 칼로리가 일일 권장 칼로리에 도달한 경우
	  printf("Your total calorie intake for today has reached your goal!");
	}
	else if (health_data -> total_calories_intake < DAILY_CALORIE_GOAL){//섭취 칼로리가 일일 권장 칼로리보다 적은 경우 
		printf("Your total calorie intake for today has not reached yout goal, remember to eat more!!"); 
	}
    
	printf("=======================================================================\n");
}
