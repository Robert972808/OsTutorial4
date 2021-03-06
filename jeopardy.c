/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4



void show_results(player *players){
    for(int i = 0; i < 4; i++){
        printf("Name: %s\tScore:%d\n", players[i].name, players[i].score);
    }
}

void tokenize(char *input, char **tokens){

    char *token1 = strtok(input, " ");
    token1 = strtok(input, " ");

    for(int i = 0; token1 != NULL; i++){
        strcpy(tokens[i], token1);
        token1 = strtok(NULL, " ");
    }       
}

void run_game(char **token, player *players){
    // Execute the game until all questions are answered
    int questions_remaining = 12;
    bool correct;
    char category[512];  
    int value;
    char response[BUFFER_LEN] = {0};
    char dummy1[256];
    char dummy2[256];
    char real[256];
    for (int i=0; i < 4; i++)
    {
    	players[i].score = 0;
    }

    //category = (char *) calloc(BUFFER_LEN, sizeof(char));
    
    //token = (char *) calloc(256, sizeof(char));

    char name[20];
    while(questions_remaining > 0){
            printf("\nEnter name of player answering: ");
	    scanf("%s", name);
	    while (1)
	    {
	    	if (player_exists(players, NUM_PLAYERS, name) == true)
		{
			break;
		}
		printf("Invalid player name. Please try again");
		scanf("%s", name);
	    }
	    printf("%s's Turn\nPlease choose from the following questions\n<Type category, then press 'enter', then type value, then press 'enter':\n\n", name);
            display_categories();
            printf("\n\n");
            scanf("%s", category);
            scanf("%d", &value);
            printf("\n");
            
            if(already_answered(category, value)==true){
                printf("Question has already been answered. Please choose another");
            }
            else{
                display_question(category, value);
                scanf("%s %s %s", dummy1, dummy2, real);                                 //Takes response
                
                //tokenize(response, token);                               //extracts answer from response
                correct = valid_answer(category,value,&real);
                if(correct){
                    printf("Correct! You may now choose another question.\n\n");
		    for (int i=0; i < 4; i++)
		    {
			if (strcmp(players[i].name, name)==0)
			{
                    		players[i].score += value;
			}
		    }
                }
                else{
                    printf("Unfortunately, that is incorrect, or you forgot to say \"What is/Who is\".\n\n");
                }
                already_answered(category, value);
                questions_remaining--;
		printf("%d\n",questions_remaining);
                if(questions_remaining<=0){
                    break;
                }              
        }
    }
    
    // Display the final results and exit
    show_results(players);

}
int main(void)
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[4];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and prompt for players names
    // initialize each of the players in the array
    printf("Welcome to Jeopardy! Please Enter your Names:\n");
    for(int i=0; i<4; i++){
        scanf("%s", players[i].name);
    }
    printf("Thank you.\n");

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Call functions from the questions and players source files

        char token[4][BUFFER_LEN] = {{0}};

        
        initialize_game();
        run_game(token, players);
        //free(token);
        return 0;

    }

    
}

