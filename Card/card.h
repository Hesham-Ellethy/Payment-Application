

//*******************************************************//
//	FWD-Embedded Systems Professional					 //
//	Augest Court										 //
//	Author:Hesahm Ellethy								 //
//	Mail:Hesham.ellethy@gmail.com						 //
//	File:Card.h											 //
//														 //
//														 //
//-------------------------------------------------------//
/*****************header file Guard********************/
#ifndef CARD_H		
#define CARD_H
/*****************Header contents********************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"../common Libs/types.h"
#define _CTR_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#pragma warning(disable : 4996)
/*******************Types declaration*********************/
//card data structure
typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;
//card expected errers
typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;
/*******************Functions dec decleration*********************/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);//fn to get card name 

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);//fn to get card name

EN_cardError_t getCardPAN(ST_cardData_t* cardData);//fn to get card name

#endif
