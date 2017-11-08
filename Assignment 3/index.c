#include <stdio.h>
#include <stdlib.h>

#include "index.h"
#include "other.h"
#include "structs.h"
/*
    The indexer function returns nothing, but takes two arguments as parameters: the absolute path of an input file to added to the supplied FILE * to the
    output file. This function reads data from outputFile, adds data to outputFile, sorts said data and rewrites is back to the outputFile. 
*/
void indexer(char * inputFilePath, char * outputFileName){
    //Note the outputFile has been opened for "a+" currently (appending and reading)
    //To open the outputFile for writing, that is, delete the file and start over use:
    //FILE *freopen(const char *filename, const char *mode, FILE *stream)

    FILE * tempFile;
    tempFile = fopen(outputFileName, "a+");

    //If the outputFile is empty
    if (fileSize(tempFile) == 0){
        printf("\tThe output, \"%s\", is empty!\n", outputFileName);
        printf("\t\tAdding first entry...\n");
        termList * inputList;
        termList * outputList;

        inputList = malloc(sizeof(termList));
        if (inputList == NULL){
            fprintf(stderr, "Could not allocate memory for inputList.");
        }

        outputList = malloc(sizeof(termList));
        if (outputList == NULL){
            fprintf(stderr, "Could not allocate memory for outputList.");
        }

        //readFromFile(inputFilePath);
        inputList = readFromFile(inputFilePath);

        termList * temp;
        temp = inputList;

        printf("\t\tCurrent list:\n");

        while(temp!=NULL)
        {
            fileCountList * tempFileCount;
            printf("\t\t\t\"%s\"", temp->term);
            tempFileCount = temp->filesAndCounts;
            while(tempFileCount != NULL){
                printf(" \"%s\" %d\n", tempFileCount->file, tempFileCount->count);
                tempFileCount = tempFileCount->next;
            }
            temp=temp->next;
        }

        free(temp);

        //Print sorted data to outputFile
        printSorted(inputList, outputFileName);

        if (inputList != NULL) deleteTermList(inputList);
        if (outputList != NULL) deleteTermList(outputList);
    }
    
    //If the outputFile is not empty
    else{
        printf("\tThe output file is NOT empty!\n");

        termList * inputList;
        termList * outputList;
        termList * newList;

        inputList = malloc(sizeof (termList));
        if (inputList == NULL){
            fprintf(stderr, "Could not allocate memory for inputList.");
        }

        outputList = malloc(sizeof (termList));
        if (outputList == NULL){
            fprintf(stderr, "Could not allocate memory for outputList.");
        }

        newList = malloc(sizeof (termList));
        if (newList == NULL){
            fprintf(stderr, "Could not allocate memory for newList.");
        }

        //Read sorted data into memory
        outputList = readFromIndex(outputFileName); //Reads terms in order
		
        //Read non-sorted data into memory
        //inputList = readFromFile(inputFilePath); //Reads terms in any order

        //Sort data in memory
        //inputList = sortTerms(inputList); //Sorts list by terms

        //MergeSort latter into former
        //newList = mergeSorted(inputList, outputList); //merges inputList and outputList, keeps terms in alphabetical order

        //Rewrite new merged list into outputFile
        //printSorted(newList, outputFile, outputFileName) //Prints sorted list in alphabetical order, keeping order of file counts descending

        fclose(tempFile);

        if (inputList != NULL) deleteTermList(inputList);
        if (outputList != NULL) deleteTermList(outputList);
        if (newList != NULL) deleteTermList(newList);
        if (inputList != NULL) free(inputList);
        if (outputList != NULL) free(outputList);
        if (newList != NULL) free(newList);


    }
}