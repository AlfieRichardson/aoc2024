#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* leftList;
int* rightList;
int size = 0;

void printArr(int* ptr, int size) {
  for (int i = 0; i < size; i++) {
    printf("element - %d : %d\n", i, ptr[i]);
  }
}

int compare (const void * a, const void * b) {
  return (*(int*)a - *(int*)b);
}

void createArrays() {
  char filename[] = "day01-input.txt";
  FILE* fp = fopen(filename, "r");

  // check file exists
  if (fp == NULL) {
    printf("!! no file found with name %s\n", filename);
    exit(1);
  }

  // while char is not EOF check next line
  int ch = 0;
  size = 0;
  while ((ch = fgetc(fp)) != EOF) {
    if (ch == '\n') {
      size++;
    }
  }

  rewind(fp);

  // create arrays
  leftList = (int*) malloc(size * sizeof(int));
  rightList = (int*) malloc(size * sizeof(int));
  if (leftList == NULL || rightList == NULL) {
    printf ("malloc failed\n");
    exit(1);
  } else {
    bool wasNum = false;
    int c = 0;
    int sum = 0;
    int count = 0;

    while ((c = fgetc(fp)) != EOF) {
      if (c != ' ' && c != '\n') {
	int trueNum = c - 48;
        if (!wasNum) {
	  sum = 0;
	  sum = trueNum;
	  wasNum = true;
	} else if (wasNum) {
	  sum = 10 * sum;
	  sum += trueNum;
        }
      } else if (c == ' ' && sum != 0) {
	*(leftList + count) = sum;
	sum = 0;
	wasNum = false;
      } else if (c == '\n') {
	*(rightList + count) = sum;
	sum = 0;
	wasNum = false;
	count++;
      }
    }
  }

  // close file
  fclose(fp);
}

void sortArrays() {
  qsort(leftList, size, sizeof(int), compare);
  qsort(rightList, size, sizeof(int), compare);
}

// with my data answer should be: 1830467
void partOne() {
  int totalDiff = 0;
  for (int i = 0; i < size; i++) {
    totalDiff += abs(leftList[i] - rightList[i]);
  }

  printf("Total Difference: %d\n", totalDiff);
}

// with my data answer should be: 26674158
void partTwo() {
  int currValue = 0;
  int totalSimilarity = 0;
  for (int i = 0; i < size; i++) {
    currValue = leftList[i];
    int occurrences = 0;
    for (int j = 0; j < size; j++) {
      if (rightList[j] == currValue) {
	occurrences++;
      }
    }
    totalSimilarity += currValue * occurrences;
  }
  printf("Total Similarity: %d\n", totalSimilarity);
}

int main() {
  createArrays();
  sortArrays();
  partOne();
  partTwo();
  return 0;
}
