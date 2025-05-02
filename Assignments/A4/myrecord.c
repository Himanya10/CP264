/*
 --------------------------------------------------
 Project: a4q2
 File:    myrecord.c
 Author:  Himanya Verma, 169051154, Verm1154@mylaurier.ca
 Version: 2025-02-06
 --------------------------------------------------
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "myrecord.h"
#include "mysort.h"

GRADE grade(float score) {
	GRADE r = { "F" };
	// your code
	if (score >= 90) {
		strcpy(r.letter_grade, "A+");
	} else if (score >= 85) {
		strcpy(r.letter_grade, "A");
	} else if (score >= 80) {
		strcpy(r.letter_grade, "A-");
	} else if (score >= 77) {
		strcpy(r.letter_grade, "B+");
	} else if (score >= 73) {
		strcpy(r.letter_grade, "B");
	} else if (score >= 70) {
		strcpy(r.letter_grade, "B-");
	} else if (score >= 67) {
		strcpy(r.letter_grade, "C+");
	} else if (score >= 63) {
		strcpy(r.letter_grade, "C");
	} else if (score >= 60) {
		strcpy(r.letter_grade, "C-");
	} else if (score >= 57) {
		strcpy(r.letter_grade, "D+");
	} else if (score >= 53) {
		strcpy(r.letter_grade, "D");
	} else if (score >= 50) {
		strcpy(r.letter_grade, "D-");
	}
	return r;
}

int import_data(FILE *fp, RECORD *dataset) {
// your code

	char line[100];
	int i = 0;
	while (fgets(line, sizeof(line), fp) != NULL) {
		sscanf(line, "%[^, ],%f", dataset[i].name, &dataset[i].score);
		i++;
	}
	return i;

}

STATS process_data(RECORD *dataset, int count) {
// your code
	STATS stats = { count, 0, 0, 0 }; //count, mean, sttdv,median
	float sum = 0;
	for (int i = 0; i < count; i++) {
		sum = sum + dataset[i].score;
	}

	stats.mean = sum / count;

	float standard = 0;
	for (int i = 0; i < count; i++) {
		standard = standard
				+ ((dataset[i].score - stats.mean)
						* (dataset[i].score - stats.mean));
	}
	standard = sqrt(standard / count);
	stats.stddev = standard;

	float median = 0;
	void *medianList[count];
	for (int i = 0; i < count; i++) {
		medianList[i] = &dataset[i].score;
	}
	select_sort(medianList, 0, count - 1);
	if (count % 2 == 0) {
		median = (*(float*) medianList[count / 2 - 1]
				+ *(float*) medianList[count / 2]) / 2;

	} else {
		median = *(float*) medianList[count / 2];
	}
	stats.median = median;

	return stats;

}

int cmp2(void *x, void *y) {
	float b = ((RECORD*) x)->score;
	float a = ((RECORD*) y)->score;
	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}

int report_data(FILE *fp, RECORD *dataset, STATS stats) {

// your code

	int n = stats.count;
	if (n < 1) {
		return 0;
	}

	RECORD *p[n];

	for (int i = 0; i < n; i++) {
		p[i] = &dataset[i];

	}

	my_sort((void*) p, 0, n - 1, cmp2);
	fprintf(fp, "stats:value\n");
	fprintf(fp, "count:%.2d\n", stats.count);
	fprintf(fp, "mean:%.1f\n", stats.mean);
	fprintf(fp, "stddev:%.1f\n", stats.stddev);
	fprintf(fp, "median:%.1f\n\n", stats.median);
	fprintf(fp, "name:score,grade\n");
	for (int i = 0; i < n; i++) {
		fprintf(fp, "%s:%.1f,%s\n", p[i]->name, p[i]->score,
				grade(p[i]->score).letter_grade);
	}
	return 1;

}
