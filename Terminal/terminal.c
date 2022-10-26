
//*******************************************************//
//	FWD-Embedded Systems Professional					 //
//	Augest Court										 //
//	Author:Hesahm Ellethy								 //
//	Mail:Hesham.ellethy@gmail.com						 //
//	File:terminal.c											 //
//														 //
//														 //
//-------------------------------------------------------//

#include"terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	sprintf(termData->transactionDate, "%02d/%02d/%04d\n", (tm.tm_mday), (tm.tm_mon + 1), (tm.tm_year + 1900));
	//printf( "%s  test os date\n", termData->transactionDate);//for testing
	
	return TERMINAL_OK;
	

}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {

	uint8_t curren_Month[3] = { termData->transactionDate[3],termData->transactionDate[4],'\0' };
	uint8_t curren_Year[3] = { termData->transactionDate[8],termData->transactionDate[9],'\0' };
	uint8_t Expire_Month[3] = { cardData->cardExpirationDate[0],cardData->cardExpirationDate[1],'\0'};
	uint8_t Expire_Year[3] = { cardData->cardExpirationDate[3],cardData->cardExpirationDate[4],'\0' };
	
	if (atoi(curren_Year) < atoi(Expire_Year)) {
		return TERMINAL_OK;
	}
	else if(atoi(curren_Year) == atoi(Expire_Year)) {
			if (atoi(curren_Month) <= atoi(Expire_Month)) {
				return TERMINAL_OK;
			}
			else {
				return EXPIRED_CARD;
			}
		
	}
	else {
		return EXPIRED_CARD;
	}


}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {

}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("Please Enter transaction Amount :\n");
	scanf_s("%f",&termData->transAmount);
	if (termData->transAmount > 0) {
		return TERMINAL_OK;
	}
	else {
		return INVALID_AMOUNT;
	}
	
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if ((termData->transAmount) > (termData->maxTransAmount)) {
		return EXCEED_MAX_AMOUNT;
	}
	else {
		return TERMINAL_OK;
	}
	
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	printf("Please Enter Max transaction Amount :\n");
	scanf_s("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount > 0) {
		return TERMINAL_OK;
	}
	else {
		return INVALID_MAX_AMOUNT;
	}
}