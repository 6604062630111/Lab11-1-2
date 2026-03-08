#include <stdio.h>
#include <stdlib.h>

#define NO_SCORE 5
#define NO_STD 10

typedef struct {
    char name[16];
    char surname[20];
    int score[NO_SCORE];
    float total;
} Student;

void readStudentData(Student *pStd);
void processAndDisplay(Student *pStd);
void findTotalScore(Student *pStd);
float findAverage(Student s);
void findLessThanTen(Student s);

int main() {
    Student std[NO_STD];
    FILE *fp;
    int i;

    for(i = 0; i < NO_STD; i++) {
        printf("\n--- Enter Student %d Data ---\n", i + 1);
        readStudentData(&std[i]);
    }

    fp = fopen("std10.dat", "wb");
    if (fp != NULL) {
        fwrite(std, sizeof(Student), NO_STD, fp);
        fclose(fp);
    }

    fp = fopen("std10.dat", "rb");
    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }
    fread(std, sizeof(Student), NO_STD, fp);
    fclose(fp);

    printf("\n================ RESULT ================\n");
    for(i = 0; i < NO_STD; i++) {
        processAndDisplay(&std[i]);
    }

    return 0;
}

void processAndDisplay(Student *pStd) {
    findTotalScore(pStd);
    printf("\nAverage score is %.2f", findAverage(*pStd));
    findLessThanTen(*pStd);
    printf("\n----------------------------------------\n");
}

void readStudentData(Student *pStd) {
    printf("Name    : "); scanf("%s", pStd->name);
    printf("Surname : "); scanf("%s", pStd->surname);
    
    for(int i = 0; i < NO_SCORE; i++) {
        printf("Score %d : ", i + 1);
        scanf("%d", &pStd->score[i]);
    }
}

void findTotalScore(Student *pStd) {
    pStd->total = 0;
    printf("\n%s %s got score:", pStd->name, pStd->surname);
    
    for(int i = 0; i < NO_SCORE; i++) {
        printf("%5d", pStd->score[i]);
        pStd->total += pStd->score[i];
    }
    printf("\nTotal score = %.2f", pStd->total);
}

float findAverage(Student s) {
    return s.total / NO_SCORE;
}

void findLessThanTen(Student s) {
    int count = 0;
    printf("\nScore less than 10:");
    
    for(int i = 0; i < NO_SCORE; i++) {
        if(s.score[i] < 10) {
            printf("\n  > Test %d : %d", i + 1, s.score[i]);
            count++;
        }
    }
    
    if(count == 0) printf(" None");
}
