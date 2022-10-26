
//*******************************************************//
//	FWD-Embedded Systems Professional					 //
//	Augest Court										 //
//	Author:Hesahm Ellethy								 //
//	Mail:Hesham.ellethy@gmail.com						 //
//	File:app.c											 //
//														 //
//														 //
//-------------------------------------------------------//

#include"app.h"

ST_transaction_t transData1={{"","",""},{0,0,""},APPROVED,0};
ST_accountsDB_t* accountRefrence1;
uint8_t CheckTerminal=15;
uint8_t CheckServer = 15;
void getCard(void) {
	uint8_t Check=10;
	for (int i = 0;Check!=0; i++) {
		
		Check = getCardHolderName(&transData1.cardHolderData);
		switch (Check) {
		case 0:printf("%s\n", "CARD_OK(CardName)");
			break;
		case 1:printf("%s\n", "WRONG_NAME(CardName)");
			break;
		case 2:printf("%s\n", "WRONG_EXP_DATE(CardName)");
			break;
		case 3:printf("%s\n", "WRONG_PAN(CardName)");
			break;
		
		default:printf("%s\n", "error(CardName)");
			break;
		}
	}

	 Check = 10;
	for (int i = 0; Check != 0; i++) {

		Check = getCardExpiryDate(&transData1.cardHolderData);
		switch (Check) {
		case 0:printf("%s\n", "CARD_OK(CardExpDate)");
			break;
		case 1:printf("%s\n", "WRONG_NAME(CardExpDate)");
			break;
		case 2:printf("%s\n", "WRONG_EXP_DATE(CardExpDate)");
			break;
		case 3:printf("%s\n", "WRONG_PAN(CardExpDate)");
			break;

		default:printf("%s\n", "error(CardExpDate)");
			break;
		}
	}

	 Check = 10;
	for (int i = 0; Check != 0; i++) {

		Check = getCardPAN(&transData1.cardHolderData);
		switch (Check) {
		case 0:printf("%s\n", "CARD_OK(CardPAN)");
			break;
		case 1:printf("%s\n", "WRONG_NAME(CardPAN)");
			break;
		case 2:printf("%s\n", "WRONG_EXP_DATE(CardPAN)");
			break;
		case 3:printf("%s\n", "WRONG_PAN(CardPAN)");
			break;

		default:printf("%s\n", "error(CardPAN)");
			break;
		}
	}

	

}


void getTerminal(void) {
	uint8_t Check = 10;
	for (int i = 0; Check != TERMINAL_OK; i++) {

		Check = getTransactionDate(&transData1.terminalData);
		switch (Check) {
		case 0:printf("%s\n", "TERMINAL_OK(TraDate)");
			break;
		case 1:printf("%s\n", "WRONG_DATE(TraDate)");
			break;
		case 2:printf("%s\n", "EXPIRED_CARD(TraDate)");
			break;
		case 3:printf("%s\n", "INVALID_CARD(TraDate)");
			break;
		case 4:printf("%s\n", "INVALID_AMOUNT(TraDate)");
			break;
		case 5:printf("%s\n", "EXCEED_MAX_AMOUNT(TraDate)");
			break;
		case 6:printf("%s\n", "INVALID_MAX_AMOUNT(TraDate)");
			break;
		default:printf("%s\n", "error(TraDate)");
			break;
		}
	}
	if (isCardExpired(&transData1.cardHolderData, &transData1.terminalData) == EXPIRED_CARD) {
		CheckTerminal = EXPIRED_CARD;
		printf("%s\n", "EXPIRED_CARD");
		return;
	}

	Check = 10;
	for (int i = 0; Check != TERMINAL_OK; i++) {

		Check = getTransactionAmount(&transData1.terminalData);
		switch (Check) {
		case 0:printf("%s\n", "TERMINAL_OK(Amount)");
			break;
		case 1:printf("%s\n", "WRONG_DATE(Amount)");
			break;
		case 2:printf("%s\n", "EXPIRED_CARD(Amount)");
			break;
		case 3:printf("%s\n", "INVALID_CARD(Amount)");
			break;
		case 4:printf("%s\n", "INVALID_AMOUNT(Amount)");
			break;
		case 5:printf("%s\n", "EXCEED_MAX_AMOUNT(Amount)");
			break;
		case 6:printf("%s\n", "INVALID_MAX_AMOUNT(Amount)");
			break;
		default:printf("%s\n", "error(Amount)");
			break;
		}
	}

	Check = 10;
	for (int i = 0; Check != TERMINAL_OK; i++) {

		Check = setMaxAmount(&transData1.terminalData);
		switch (Check) {
		case 0:printf("%s\n", "TERMINAL_OK(MXAmount)");
			break;
		case 1:printf("%s\n", "WRONG_DATE(MXAmount)");
			break;
		case 2:printf("%s\n", "EXPIRED_CARD(MXAmount)");
			break;
		case 3:printf("%s\n", "INVALID_CARD(MXAmount)");
			break;
		case 4:printf("%s\n", "INVALID_AMOUNT(MXAmount)");
			break;
		case 5:printf("%s\n", "EXCEED_MAX_AMOUNT(MXAmount)");
			break;
		case 6:printf("%s\n", "INVALID_MAX_AMOUNT(MXAmount)");
			break;
		default:printf("%s\n", "error(MXAmount)");
			break;
		}
	}


	if (isBelowMaxAmount( &transData1.terminalData) == EXCEED_MAX_AMOUNT) {
		CheckTerminal = EXCEED_MAX_AMOUNT;
		printf("%s\n", "EXCEED_MAX_AMOUNT");
		return;
	}
	

	CheckTerminal = TERMINAL_OK;
}

void appStart(void) {
	getCard();
	getTerminal();
}


int main() {
	while (1) {
		CheckTerminal = 15;
		CheckServer = 15;
		
		appStart();
		if (CheckTerminal!=TERMINAL_OK) {
			continue;
		}
		
		
		CheckServer = recieveTransactionData(&transData1);
		switch (CheckServer) {
		case 0:printf("%s\n", "APPROVED");
			break;
		case 1:printf("%s\n", "DECLINED_INSUFFECIENT_FUND");
			break;
		case 2:printf("%s\n", "DECLINED_STOLEN_CARD");
			break;
		case 3:printf("%s\n", "FRAUD_CARD");
			break;
		case 4:printf("%s\n", "INTERNAL_SERVER_ERROR");
			break;
		
		default:printf("%s\n", "error");
			break;
		}
		
	}
}