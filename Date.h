//
// Created by Benjamin Lesieux on 01/05/2020.
//

#ifndef LABIBLIODEFRANCK_DATE_H
#define LABIBLIODEFRANCK_DATE_H
#include <stdlib.h>
#include <stdio.h>

typedef struct {

    unsigned int day;
    unsigned int month;
    unsigned int year;
} Date;

void makeDate(Date *targetDate);
void showDate(Date *targetDate);
int compareDate(Date *date1, Date *date2);
int coherentDate(int day, int month, int year); // Vérifie si une date est cohérente (empêche donc les 30 fevrier)

#endif //LABIBLIODEFRANCK_DATE_H