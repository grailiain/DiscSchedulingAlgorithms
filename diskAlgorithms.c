/* 
This program implements the following disck-scheduling algorithms:
FCFS, SSTF, SCAN, C-SCAN, LOOK, and C-LOOK
The program services a disk of 5,000 cylinders numbered 0 to 4999.
It generates a random series of 1000 cylinder requests and services 
them according to each of he algorithms listed above. The program
will be passed the initial position of the disk head (as a parameter
on the command line) and report the total amount of head movement 
required by each algorithm.
*/

#include <stdio.h>
#include <stdlib.h>

#define CYLINDERS 5000
#define REQUESTS 11
#define ARRAYSIZE 11


int arr[10][REQUESTS];

int determineAlgorithm(int * ranArray, int ranAlgorithm);

int fcfs(int * ranArray);
int sstf(int * ranArray);
int scan(int * ranArray);
int cscan(int * ranArray);
int look(int * ranArray);
int clook(int * ranArray);

int* sort(int * ranArray);

int start;

// THE GIVEN ARRAY IS FOR TESTING, 
// IT IS USED TO MAKE SURE THE HEADVALUES ARE THE SAME AS THE HOMEWORK SOLUTIONS
int ranArray[ARRAYSIZE]; // = {2150, 2069, 1212, 2296, 2800, 544, 1618, 356, 1523, 4965, 3681};


int main (int argc, char *argv[]) {

	start = atoi(argv[1]); 
	printf("START Index: %d\n",start);

	int i, j;
	int requestCount = 0;
		

	// THIS IS FOR RANDOM SERIES OF 1000 CYLINDERS 
	// COMMENT OUT FOR TESTING WITH HOMEWORK PROBLEMS
	for(i = 0; i < ARRAYSIZE; i++) {
		ranArray[i] = 0;
	}
	printf("RANDOM ARRAY\n");
	for(i = 0; i < ARRAYSIZE; i++) {
		int ran = rand() % 5000;
		ranArray[i] = ran;
		if(i == start) {
			printf("START: %d\n",ranArray[i]);
		}
		else {
			printf("%d\n",ranArray[i]);
		}
	}
	// END  ----  THIS NEEDS TO BE UNCOMMENTED

	

	for(i = 0; i < 10; i++) {
		for(j = 0; j < ARRAYSIZE; j++) {
			arr[i][j] = 0;
		}
	}

	while(requestCount < REQUESTS) {

		int ranAlgorithm = rand() % 10;
		//int ranAlgorithm = 3;
		int headMovement = determineAlgorithm(ranArray, ranAlgorithm);
		arr[ranAlgorithm][requestCount] = headMovement;
		printf("Head Movement: %d\n",arr[ranAlgorithm][requestCount]);
		requestCount++;
		printf("COUNT: %d\n",requestCount);
	}
	printf("\nQUEUE Index and Head Value:\n0=FCFS\n1=SSTF\n2=SCAN\n3=C-SCAN\n4=LOOK\n5=C-LOOK\n");
	for(i = 0; i < 6; i++) {
		for(j = 0; j < REQUESTS; j++) {
			if(arr[i][j] > 0) {
				printf("Index: %d, Head Value: %d\n",i ,arr[i][j]);
			}
		}
	}

	
	return 0;
}

int determineAlgorithm(int * ranArray, int ranAlgorithm) {
	int headCount;
	if(ranAlgorithm == 0) {
		printf("\nFCFS\n");
		headCount = fcfs(ranArray);
		printf("FCFS %d\n",headCount);
	}
	else if(ranAlgorithm == 1) {
		printf("\nSSTF\n");
		headCount = sstf(ranArray);
		printf("SSTF %d\n",headCount);
	}
	
	else if(ranAlgorithm == 2) {
		printf("\nSCAN\n");
		headCount = scan(ranArray);
		printf("SCAN %d\n",headCount);
	}
	else if(ranAlgorithm == 3) {
		printf("\nC-SCAN\n");
		headCount = cscan(ranArray);
		printf("C-SCAN %d\n",headCount);
	}
	
	else if(ranAlgorithm == 4) {
		printf("\nLOOK\n");
		headCount = look(ranArray);
		printf("LOOK %d\n",headCount);
	}
	
	else if(ranAlgorithm == 5) {
		printf("\nC-LOOK\n");
		headCount = clook(ranArray);
		printf("C-LOOK %d\n",headCount);
	}
	
	else {
		return -1;
	}

	return headCount;
}

int fcfs(int * ranArray) {

	int i;
	int head_movement;
    for(i=start; i < ARRAYSIZE; i++) {
    	if(i+1 < ARRAYSIZE) {
    		if(ranArray[i+1] > ranArray[i]) {
	    		int num = ranArray[i+1] - ranArray[i];
	    		//printf("num: %d\n",num);
	    		head_movement = head_movement+ num;
	    		//printf("Head1: %d\n",head_movement);
    		}
    		else {
    			int num = ranArray[i] - ranArray[i+1];
	    		//printf("num: %d\n",num);
	    		head_movement = head_movement+ num;
	    		//printf("Head1: %d\n",head_movement);
    		}
    	}
    	else {
    		break;
    	}
    }
    for(i=0; i < start; i++) {
    	if(i == 0) {
    		if(ranArray[9] > ranArray[0]) {
	    		int num2 = ranArray[ARRAYSIZE-1] - ranArray[0];
	    		//printf("num2: %d\n",num2);
	    		head_movement = head_movement + num2;
	    		//printf("Head2: %d\n",head_movement);
    		}
    		else {
    			int num2 = ranArray[0] - ranArray[ARRAYSIZE-1];
	    		//printf("num2: %d\n",num2);
	    		head_movement = head_movement + num2;
	    		//printf("Head2: %d\n",head_movement);
    		}
    	}
    	else {
    		if(ranArray[i] > ranArray[i-1]) {
    			int num3 = ranArray[i] - ranArray[i-1];
    			//printf("num3: %d\n",num3);
    			head_movement = head_movement+ num3;
    			//printf("Head3: %d\n",head_movement);
    		}
    		else {
    			int num3 = ranArray[i-1] - ranArray[i];
    			//printf("num3: %d\n",num3);
    			head_movement = head_movement+ num3;
    			//printf("Head3: %d\n",head_movement);
    		}
    	}
    }
        
    return head_movement;
}


int sstf(int * ranArray) {

	int shortest = 5001;
	int j;
	int hey = ARRAYSIZE;
	int newStart = ranArray[start];
	int newHead = 0;
	int saveCurrent;
	int arrTest[ARRAYSIZE];
	int saveLocation;
	int i = 0;

	for(i = 0; i < ARRAYSIZE; i++) {
		arrTest[i] = 0;
	}
	arrTest[start]++;

	while(hey > 0) {

		int distance;
		
		for(j = 0; j< ARRAYSIZE; j++) {

			int current = ranArray[j];
			int used = arrTest[j];

			if(used < 1 && newStart > current) {
				distance = newStart - current;
			}
			else if(used < 1 && newStart < current) {
				distance = current - newStart;
			}
			if(used < 1 && distance < shortest) {
				shortest = distance;
				saveCurrent = current;
				saveLocation = j;
			}
		}

		distance = 0;
		arrTest[saveLocation]++;
		int num = arrTest[saveLocation];
		int difference = 0;

		if(num < 2 && saveCurrent < newStart) {
			difference = newStart - saveCurrent;
			newHead += difference;
		}
		else if(num < 2 && saveCurrent > newStart) {
			difference = saveCurrent - newStart;
			newHead += difference;
		}

		printf("NEW HEAD FINAL: %d\n",newHead);
		newStart = saveCurrent;
		saveCurrent = 0;
		shortest = 5001;
		--hey;
	}
	return newHead;
}

int scan(int * ranArray) {

	int i = 0;
	int j = 0;
	int* aTest = malloc(sizeof(int) * sizeof(ranArray)/ranArray[0]);  

	for(i = 0; i < ARRAYSIZE; i++) {
		aTest[i] = 0;
	}
	for(i = 0; i < ARRAYSIZE; i++) {
		aTest[i] = ranArray[i];
	}

	int origStart = ranArray[start];
	int arrFinal[ARRAYSIZE];

	ranArray = sort(aTest);

	//for(i = 0; i < ARRAYSIZE; i++) {
	//	printf("RETURNED %d\n",ranArray[i]);
	//}

	int posit;
	int saveNum;
	int headTotal = 0;

	for(i = 0; i < ARRAYSIZE; i++) {
		arrFinal[i] = 0;
		int num = ranArray[i];
		if(num == origStart) {
			posit = i;
			saveNum = num;
			printf("START: %d, Index: %d\n",saveNum, posit);
		}
	}

	int thisOne;
	//if(posit == 0) {
	//	posit = ARRAYSIZE-1;
	//}
	for(i = posit-1; i >= 0; --i) {
		thisOne = ranArray[i];
		//printf("This One: %d\n",thisOne);
		int difference = saveNum - thisOne;
		//printf("S Diff1 %d\n",difference);
		arrFinal[j] = difference;
		saveNum = thisOne;
		headTotal += difference;
		printf("Total: %d\n",headTotal);
		j++;
	}
	int thisDif = thisOne - 0;
	//printf("End diff: %d\n",thisDif);
	headTotal += thisDif - 0;
	printf("Total End: %d\n",headTotal);
	saveNum = 0;

	for(i = posit+1; i < ARRAYSIZE; i++) {
		thisOne = ranArray[i];
		int difference = thisOne - saveNum;
		//printf("L Diff2 %d\n",difference);
		arrFinal[j] = difference;
		headTotal += difference;
		printf("Total: %d\n",headTotal);
		saveNum = thisOne;
		j++;
	}

	free(aTest);

	return headTotal;
}


int cscan(int * ranArray) {

	int i = 0;
	int j = 0;
	int* aTest = malloc(sizeof(int) * sizeof(ranArray)/ranArray[0]);  

	for(i = 0; i < ARRAYSIZE; i++) {
		aTest[i] = 0;
	}
	for(i = 0; i < ARRAYSIZE; i++) {
		aTest[i] = ranArray[i];
	}

	int origStart = ranArray[start];
	int arrFinal[ARRAYSIZE];

	ranArray = sort(aTest);

	//for(i = 0; i < ARRAYSIZE; i++) {
	//	printf("RETURNED %d\n",ranArray[i]);
	//}

	int posit;
	int saveNum;
	int headTotal = 0;

	for(i = 0; i < ARRAYSIZE; i++) {
		arrFinal[i] = 0;
		int num = ranArray[i];
		if(num == origStart) {
			posit = i;
			saveNum = num;
			printf("START: %d, Index: %d\n",saveNum, posit);
		}
	}

	int thisOne;

	for(i = posit+1; i < ARRAYSIZE; i++) {
		thisOne = ranArray[i];
		int difference = thisOne - saveNum;
		//printf("L Diff2 %d\n",difference);
		arrFinal[j] = difference;
		headTotal += difference;
		printf("Total: %d\n",headTotal);
		saveNum = thisOne;
		j++;
	}

	int thisDif = 4999 - saveNum;
	//printf("End diff: %d\n",thisDif);
	headTotal += thisDif;
	printf("Total End1: %d\n",headTotal);
	saveNum = 0;
	headTotal += 4999;
	printf("Total End2: %d\n",headTotal);

	for(i = 0; i < posit; i++) {
		thisOne = ranArray[i];
		//printf("This One: %d\n",thisOne);
		int difference;
		difference = thisOne - saveNum;
		//printf("S Diff1 %d\n",difference);
		arrFinal[j] = difference;
		saveNum = thisOne;
		headTotal += difference;
		printf("Total: %d\n",headTotal);
		j++;
	}
	
	free(aTest);

	return headTotal;
}



int look(int* ranArray) {

	int i = 0;
	int j = 0;
	int* aTest = malloc(sizeof(int) * sizeof(ranArray)/ranArray[0]);  

	for(i = 0; i < ARRAYSIZE; i++) {
		aTest[i] = 0;
	}
	for(i = 0; i < ARRAYSIZE; i++) {
		aTest[i] = ranArray[i];
	}

	int origStart = ranArray[start];
	int arrFinal[ARRAYSIZE];

	ranArray = sort(aTest);

	//for(i = 0; i < ARRAYSIZE; i++) {
	//	printf("RETURNED %d\n",ranArray[i]);
	//}

	int posit;
	int saveNum;
	int headTotal = 0;

	for(i = 0; i < ARRAYSIZE; i++) {
		arrFinal[i] = 0;
		int num = ranArray[i];
		if(num == origStart) {
			posit = i;
			saveNum = num;
		}
	}

	int thisOne;

	for(i = posit+1; i < ARRAYSIZE; i++) {
		thisOne = ranArray[i];
		int difference = thisOne - saveNum;
		//printf("L Diff2 %d\n",difference);
		arrFinal[j] = difference;
		headTotal += difference;
		printf("Total: %d\n",headTotal);
		saveNum = thisOne;
		j++;
	}

	for(i = posit-1; i >= 0; --i) {
		thisOne = ranArray[i];
		int difference = saveNum - thisOne;
		//printf("L Diff1 %d\n",difference);
		arrFinal[j] = difference;
		saveNum = thisOne;
		headTotal += difference;
		printf("Total: %d\n",headTotal);
		j++;
	}

	free(aTest);

	return headTotal;
}

int clook(int* ranArray) {

	int i = 0;
	int j = 0;
	int* aTest = malloc(sizeof(int) * sizeof(ranArray)/ranArray[0]);  

	for(i = 0; i < ARRAYSIZE; i++) {
		aTest[i] = 0;
	}
	for(i = 0; i < ARRAYSIZE; i++) {
		aTest[i] = ranArray[i];
		//printf("TEST: %d\n",aTest[i]);
	}

	int arrFinal[ARRAYSIZE];
	int origStart = ranArray[start];

	ranArray = sort(aTest);

	//for(i = 0; i < 10; i++) {
	//	printf("RETURNED %d\n",ranArray[i]);
	//}

	int posit;
	int saveNum;
	int headTotal = 0;

	for(i = 0; i < ARRAYSIZE; i++) {
		arrFinal[i] = 0;
		int num = ranArray[i];
		if(num == origStart) {
			posit = i;
			saveNum = num;
		}
	}

	int thisOne;
	for(i = posit+1; i < ARRAYSIZE; i++) {
		thisOne = ranArray[i];
		int difference = thisOne - saveNum;
		//printf("Diff1 %d\n",difference);
		arrFinal[j] = difference;
		headTotal += difference;
		printf("Total: %d\n",headTotal);
		saveNum = thisOne;
		j++;
	}

	for(i = 0; i < posit; i++) {
		thisOne = ranArray[i];
		int difference;
		if(i == 0) {
			difference = saveNum - thisOne;
			//printf("Diff2 %d\n",difference);
		}
		else {
			difference = thisOne - saveNum;
			//printf("Diff3 %d\n",difference);
		}
		arrFinal[j] = difference;
		saveNum = thisOne;
		headTotal += difference;
		printf("Total: %d\n",headTotal);
		j++;
	}	

	free(aTest);

	return headTotal;
}

int* sort(int * aTest) {

	int a;
	int i = 0;
	int j = 0;
	for (i = 0; i < ARRAYSIZE; ++i) {
       	for (j = i + 1; j < ARRAYSIZE; ++j) {
            if (aTest[i] > aTest[j]) {
                a =  aTest[i];
                aTest[i] = 	aTest[j];
                aTest[j] = a;
            }
        }
    }

	return aTest;
}




