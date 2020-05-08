//
// Created by Benjamin Lesieux on 01/05/2020.
//

#include "Date.h"

void makeDate(Date *targetDate) {

    int validEntry; // Valide le scanf

    do {
        printf("\nVeuillez entrer votre date sous la forme dd/mm/yyyy : ");
        validEntry = scanf("%d/%d/%d", &targetDate->day, &targetDate->month, &targetDate->year);
        getchar();
    } while (validEntry == 0);
}
