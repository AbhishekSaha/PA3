#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "tokenize.c"
#include "recurse.h"

SortedListPtr rust;
char *getNewPath(char *dirName,char *newItemName)
{
    
	strcat(dirName,"/");
    strcat(dirName,newItemName);
    
    return dirName;
}

char *testRemove(char *curPath)
{
	char *ptr;

	ptr = strrchr(curPath,'/');
	
	if(ptr != NULL)
	{
		*ptr = '\0';
	}
	
	return curPath;
}


int checkIndex(char * file, char *path) // returns 1 if a file with the same name as the index file exists
{
	DIR *dirPtr;
	dirPtr = opendir(path);

	struct dirent *direntPtr = readdir(dirPtr);

	while(direntPtr != NULL)
	{
		if(strcmp(direntPtr->d_name,file) == 0)
			return 1;
	
		direntPtr = readdir(dirPtr);
	}

	return 0;
}
void recurse(char *path, FILE *bufferPtr)
{
    
	
	DIR *dirPtr;
	dirPtr = opendir(path); 
    
	FILE *filePtr = fopen(path,"r");
    
    
	if(dirPtr != NULL) // Non-null value means success
	{
		struct dirent *direntPtr = readdir(dirPtr);
        
		while(direntPtr != NULL)
		{
			if(strcmp(direntPtr->d_name,".") == 0)
			{
				direntPtr = readdir(dirPtr);
			}
			else if(strcmp(direntPtr->d_name,"..") == 0)
			{
				direntPtr = readdir(dirPtr);
			}
			else
			{
				char *newPath = getNewPath(path,direntPtr->d_name);
				recurse(newPath,bufferPtr);
                
				// remove the last part of the path so that the next element doesn't get it
				path = testRemove(newPath);
				direntPtr = readdir(dirPtr);
			}
		}
        
	}
	else if(filePtr != NULL)
	{
		processFile(path,bufferPtr);
		return;
	}
	else
	{
		printf("\nThere's an error\n");
	}
	
	return;
}

int checkFile(char *file)
{
        char temp[25];
        strcpy(temp,file);

        

        char bob[4];

        int length = strlen(temp);

        


        bob[3] = temp[length];
        bob[2] = temp[length -1];
        bob[1] = temp[length - 2];
        bob[0] = temp[length - 3];

        

        return strcmp(bob,"txt");
}


int main(int argc, char **argv)
{
	if((argv[2] == NULL) || (argv[1] == NULL))
	{
		printf("Not enough arguments. Please enter your input in the form ./index index.txt file/directory. Exiting...\n");
		return 0;
	}
	else if(argv[3] != NULL)
	{
		printf("Too many arguments. Please enter your input in the form ./index index.txt file/directory. Exiting...\n");
		return 0;
	}


	int holder;
	holder = checkIndex(argv[1],".");
	
	if(holder == 1)
	{
		char decision;
		printf("Would you like to override the existing file (y/n)? \n");
		scanf("%c",&decision);

		while((decision != 'y') && (decision != 'n'))
		{
			if(decision == 'y')
			{		
				printf("Overwriting file with same name as %s...\n",argv[1]);
				remove(argv[1]);

			}
			else if(decision == 'n')
			{
				printf("Existing file not overridden. Exiting program...\n");
				return 0;
			}
			else
			{
				printf("Invalid choice. Would you like to override the existing file (y/n)? \n");
				scanf("%c",&decision);
			}
		}
		
		
	}



	char *indexFile;
	indexFile = argv[1];
    
	FILE *bufferPtr = fopen("aux.txt","w");
	
	if(checkFile(indexFile) != 0)
	{
		printf("Not a valid file name. Please enter a file with a .txt extension\n");
		return 0;
	}
    
	DIR *dirPtr;
	dirPtr = opendir(argv[2]);
	FILE *filePtr = fopen(argv[2],"r");
	
	if(dirPtr != NULL)
	{
		recurse(argv[2],bufferPtr);
		
	}
	else if(filePtr != NULL)
	{
		processFile(argv[2],bufferPtr);
		
	}
	else
		printf("There is an error in your input. Please make sure that the input is the path to an existing file or directory. Exiting...\n");
    fclose(bufferPtr);
	process("bill", "rondo");
    

	holder = printAll(indexFile);
	
	remove("aux.txt");

return 0;
}







































