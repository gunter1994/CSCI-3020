// check if rows contain numbers 1-9
void *checkRows(void *t) {
    int thread = (int)t;
    int numTest[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //defaults values to false
    
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) { //checks each row for every number
            if(puzzle[i][j] != 0) {
                numTest[puzzle[i][j] -1] ++;
            }
        }
        for(int k = 0; k < 9; k++) {
            if(numTest[k] > 1) {  //if one num occurs twice, sets result
                results[thread] = 0;
                printf("Rows failed"); //DELETE THIS
                pthread_exit(NULL);
            } else { //sets rest to false again
                numTest[k] = 0;
            }
        }
    }
    results[thread] = 1;
    pthread_exit(NULL);
}

// check if columns contain numbers 1-9
void *checkCols(void *t) {
    int thread = (int)t;
    int numTest[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //defaults values to false
    
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) { //checks each row for every number
            if(puzzle[j][i] != 0) {
                numTest[puzzle[j][i] -1] ++;
            }
        }
        for(int k = 0; k < 9; k++) {
            if(numTest[k] > 1) {  //if one num occurs twice, sets result
                results[thread] = 0;
                printf("Columns failed"); //DELETE THIS
                pthread_exit(NULL);
            } else { //sets rest to false again
                numTest[k] = 0;
            }
        }
    }
    results[thread] = 1;
    pthread_exit(NULL);
}

// check if box contains numbers 1-9
void *checkBoxes(void *arguments) {
	struct thread_args *args = (struct thread_args *)arguments;
    int numTest[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //defaults values to false
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) { //checks each box for every number
            if(puzzle[i * args->row][j * args->col] != 0) {
                numTest[puzzle[i * args->row][j * args->col] -1] ++;
            }
        }
        
    }
    for(int k = 0; k < 9; k++) {
            if(numTest[k] > 1) {  //if one num occurs twice, sets result
                results[args->thread] = 0;
                printf("Boxes failed"); //DELETE THIS
                pthread_exit(NULL);
            }
        }
    results[args->thread] = 1;
    pthread_exit(NULL);
}

