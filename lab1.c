#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){

	// make sure number of arguemnts is correct
	if (argc != 4){
		fprintf(stderr, "Incorrect number of arguments\n");
		return(-1);
	}

	// declare variables/open files
	FILE *file = fopen(argv[1], "rb");
	FILE *o_file = fopen(argv[3], "w");
	char *text = argv[2];
	int i, j;
	char *buffer, *buffer1, *buffer2;
	size_t result;
	long file_size;
	int count = 0;

	// make sure files opened properly
	if (!file){
		fprintf(stderr, "Error opening input file, be sure that file exists\n");
		return(-1);
	}
	if (!o_file){
		fprintf(stderr, "Error opening output file, not really sure why\n");
		return(-1);
	}


	// find size of file
	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	rewind(file);

	// initialize buffers
	buffer = (char*) malloc (sizeof(char)*100); 
	buffer1 = (char*) malloc (sizeof(char)*50);
	buffer2 = (char*) malloc (sizeof(char)*50);

	// set first buffer value
	result = fread(buffer1, 1, 50, file);
	if(result == 50){
		result = fread(buffer2, 1, 50, file) + 50;
	}
	strcpy(buffer, buffer1);
	strcat(buffer, buffer2);

	// print info
	printf("File: %s\n", argv[1]);
	printf("File size: %ld\n", file_size);
	fprintf(o_file, "File: %s\n", argv[1]);
	fprintf(o_file, "File size: %ld\n", file_size);

	// read file and find number of matching strings
	// very inefficient, but it works
	for( i = 0; i<result; i++){
		if (i+strlen(text) >= result && result == 100){
			strcpy(buffer, buffer2);
			result = fread(buffer2, 1, 50, file) + 50;
			strcat(buffer, buffer2);
			i -= 50;
		}
		if(buffer[i] == (text[0] & 0xff) && i+strlen(text) < result){
			for( j = 1; j<strlen(text); j++){
				if(buffer[i+j] != (text[j] & 0xff)){
					break;
				}
				if (j == strlen(text)-1){
					count++;
				}
			}
		}
	}
	
	// print count
	printf("%s appeared %d times\n", text, count);
	fprintf(o_file, "%s appeared %d times\n", text, count);

	// close streams/free memory
	fclose(file);
	fclose(o_file);
	free(buffer);
	free(buffer1);
	free(buffer2);
	return 0;
}