//*******************************************************//
//	FWD-Embedded Systems Professional					 //
//	Augest Court										 //
//	Author:Hesahm Ellethy								 //
//	Mail:Hesham.ellethy@gmail.com						 //
//	File:server.c											 //
//														 //
//														 //
//-------------------------------------------------------//

#include"server.h"

ST_accountsDB_t acctountsDB_t[255]={{ 1000.0, RUNNING, "8989374615436851" },
                                    { 2000.0, RUNNING, "8989374615436852" },                              
                                    { 3000.0, RUNNING, "8989374615436853" }, 
                                    { 4000.0, RUNNING, "8989374615436854" }, 
                                    { 5000.0, RUNNING, "8989374615436855"},
                                    { 100000.0, BLOCKED, "5807007076043875" },
                                    { 6000.0, RUNNING, "8989374615436857" }, 
                                    { 7000.0, RUNNING, "8989374615436858" }, 
                                    { 8000.0, RUNNING, "8989374615436859" }, 
                                    { 9000.0, RUNNING, "8989374615436850" }
                                    };

ST_transaction_t transaction_t[255] = { {{0,0,0} ,{0,0,0} ,0,0} };
ST_transaction_t transDataReference;

ST_accountsDB_t* accountRefrence2;
uint32_t transactionSequenceCounter = 0;






EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
    if (isValidAccount(&transData->cardHolderData, &accountRefrence2) == ACCOUNT_NOT_FOUND) {//transData  debug
        transData->transState = FRAUD_CARD;
        return FRAUD_CARD;
    }
    else if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE) {
        transData->transState= DECLINED_INSUFFECIENT_FUND;
        return DECLINED_INSUFFECIENT_FUND;
    }
    else if (isBlockedAccount(accountRefrence2) == BLOCKED_ACCOUNT) {
        transData->transState = DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD;

    }
    else if (saveTransaction(transData) == SAVING_FAILED) {//transData debug
        
        return INTERNAL_SERVER_ERROR;

    }
    else {
        accountRefrence2->balance = accountRefrence2->balance - transData->terminalData.transAmount;
        //printf("%f   -   %s\n", accountRefrence2->balance,accountRefrence2->primaryAccountNumber);//for testing
        
        return APPROVED;
    }
        

        
   
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t** accountRefrence) {
    for (int i = 0; i < 255; i++) {
        if ((strcmp(cardData->primaryAccountNumber , acctountsDB_t[i].primaryAccountNumber)==0)) {
            
            *accountRefrence = &acctountsDB_t[i];
            
            return SERVER_OK;
        }
    }
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
    if (accountRefrence->state == BLOCKED) {
        return BLOCKED_ACCOUNT;
    }
    else {
        return SERVER_OK;
    }

    
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
    if (termData->transAmount <= accountRefrence2->balance) {
        return SERVER_OK;
    }
    else {
        return LOW_BALANCE;
    }
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
    transactionSequenceCounter += 1;
    if (transactionSequenceCounter <= 255) {
        transData->transactionSequenceNumber = transactionSequenceCounter;
        transaction_t[transactionSequenceCounter-1] = *transData;
    }
    if (getTransaction(transactionSequenceCounter,&transDataReference)== TRANSACTION_NOT_FOUND) {

        return SAVING_FAILED;
    }
    else {
        return SERVER_OK;
    }
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData) {
    for (int i = 0; i < 255; i++) {
        if (transactionSequenceNumber==transaction_t[i].transactionSequenceNumber) {

            *transData = transaction_t[i];//check debug
            return SERVER_OK;
        }
    }
    return TRANSACTION_NOT_FOUND;
}
