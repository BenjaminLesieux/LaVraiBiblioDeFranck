//
// Created by Benjamin Lesieux on 01/05/2020.
//

#include "Date.h"

Date *makeDate() {

    Date *targetDate = NULL;
    targetDate = (Date*) malloc(sizeof(Date));

    if(targetDate == NULL) {
        printf("Erreur mémoire date");
        exit(1);
    }

    int validEntry; // Valide le scanf

    do {
        printf("\nVeuillez entrer votre date sous la forme dd/mm/yyyy : ");
        validEntry = scanf("%d/%d/%d", &targetDate->day, &targetDate->month, &targetDate->year);
        getchar();
    } while (validEntry == 0 || targetDate->day < 0 || targetDate->day > 31
            || targetDate->month < 0 || targetDate->month > 12 || targetDate->year < 2020);

    return targetDate;
}

Date *readFromString(char *string) {
    Date *date = (Date*) malloc(sizeof(Date));

    if (date == NULL) {
        printf("Erreur mémoire date");
        exit(1);
    }

    sscanf(string, "%d/%d/%d", &date->day, &date->month, &date->year);

    return date;
}

void showDate(Date **targetDate) {

    printf("\nDates de rendu attendues : ");

    for (int i = 0; i < 3; i++) {
        if (targetDate[i]->day > 0)
            printf("\n %d/%d/%d", targetDate[i]->day, targetDate[i]->month, targetDate[i]->year);
        else
            printf("\n Aucun emprunt - %d ", i);
    }
}

int compareDate(Date *date) {
    int day, month, year;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    day = local->tm_mday;
    month = local->tm_mon + 1;
    year = local->tm_year + 1900;
    if(year < date->year || (year==date->year && month <date->month) ||
        (year ==date->year && month == date->month && day < date->day))
        return 1;

    else return 0;
}