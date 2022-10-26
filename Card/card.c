


//*******************************************************//
//	FWD-Embedded Systems Professional					 //
//	Augest Court										 //
//	Author:Hesahm Ellethy								 //
//	Mail:Hesham.ellethy@gmail.com						 //
//	File:Card.c											 //
//														 //
//														 //
//-------------------------------------------------------//


#include"card.h"



EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	uint8_t input[100]={0};			//local array of char to get input data and validates it before storing in global transData1 structure
	printf("Please Enter Card Name :\n"); //ask user for input
	
	gets( input);//get user input
	
	
	if (strlen(input) > 24 || strlen(input)<20) {
		//validate Card holder name is 24 alphabetic characters string max and 20 min 
		return WRONG_NAME;
	}
	else {
		//validate all Chars that belong to A:Z and a:z and apace char
		for (int i = 0; input[i] != '\0'; i++) {
			if ((input[i] == ' ') || (input[i] >= 'A' & input[i] <= 'Z') || (input[i] >= 'a' & input[i] <= 'z')) {
				//char is correct
			}
			else { 
				return WRONG_NAME;
				//wrong char
			}
		}
		//card name is correct and fill global transData1
		for (int i = 0; i <= strlen(input); i++) {
			cardData->cardHolderName[i] = input[i];
		}
		return CARD_OK;
	}

}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	uint8_t input[100]={ 0 };;
	printf("Please Enter Expiration Date in Format MM/YY :\n");
	gets(input);
	

	if (strlen(input)!=5 ) {
		
		return WRONG_NAME;
	}
	else {
		for (int i = 0; i <= strlen(input); i++) {
			if (i == 5 ) {
				cardData->cardExpirationDate[i] = input[i];
			}
			else if (i==2 && (input[i] == '/')) {
				cardData->cardExpirationDate[i] = input[i];
				}
			else if(i != 2 && (input[i] >= '0' & input[i] <= '9')) {
				cardData->cardExpirationDate[i] = input[i];
			}
			else{
				return WRONG_EXP_DATE;
			}
			
		}
		return CARD_OK;
	}


}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	uint8_t input[100]= { 0 };
	printf("Please Enter Card PAN Number :\n");
	gets(input);


	if (strlen(input) > 19 || strlen(input) < 16) {

		return WRONG_PAN;
	}
	else {
		for (int i = 0; input[i] != '\0'; i++) {
			if ((input[i] >= '0' & input[i] <= '9')) {

			}
			else {
				return WRONG_PAN;
			}
		}

		for (int i = 0; i <= strlen(input); i++) {
			cardData->primaryAccountNumber[i] = input[i];
		}
		return CARD_OK;
	}

}
