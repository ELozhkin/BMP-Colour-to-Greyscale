#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "bmp.h"
#include <string>

using namespace std;

int searchDirectory(char* path);
int isImg(char* path);
int convertGrey(char* bmpPath, int count);
int createNewBmp(BmpFileHeader fhead, BmoInfoHeader ihead, rgbTriple *data, int size, char* name);

int test(char* name);

int main(int argc, char** argv) {

	int count = searchDirectory(argv[1]);

	if (count == 0) {
		printf("Did not find any pngs in the specified directory.\n");
	}

	printf("Created %d new bmp files.\n", count);
	return 0;
}

int test(char* name) {
	// char filename[] = "test";

	char* name2 = strtok(name, ".");
	// string n = to_string(num);
	// strcpy(&n[0], n.c_str());
	
	// strcat(filename, &n[0]);
	strcat(name2, "-greyscale.bmp");
	printf("%s\n", name2);
	return 0;
}

// searchDirectory searches through the directory specified by the user. Returns error if directory is equal 
// to NULL. Returns the number of converted bmp files.
// Skip first two entries in the directory. Returns if any files in the directory are not bmp files (ie this 
// script should only be used for 'bmp folders').
int searchDirectory(char* path) {
	int count = 0;

	struct dirent *pathDirent;
	DIR *dir = opendir(path); //dir contains a pointer to manage the directory
	if (dir == NULL) {
		printf("couldn't open %s\n", path);
		return 1;
	}

	int numSkip = 2;

	while((pathDirent = readdir(dir)) != NULL) {
		if (numSkip > 0) {
			numSkip--;
			continue;
		}
		count++;

		if (isImg(pathDirent->d_name) != 0) {
			printf("%s is not a bmp. All files in the directory must be a .bmp file format\n", pathDirent->d_name);
			return 1;
		}

		if (convertGrey(pathDirent->d_name, count) != 0) {
			printf("Couldn't convert %s to greyscale.\n", pathDirent->d_name);
		} else {
			printf("Converted %s to greyscale.\n\t New file name: %s\n", pathDirent->d_name, pathDirent->d_name);
		}
	}

	closedir(dir);
	return count;
}

int isImg(char* path) {
	char correctBMP[16] = {0x42, 0x4D, 0x36, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00};
	char buffer[16];

	FILE *fp = fopen(path, "r");
	if (fp == NULL) {
		printf("could not open %s.\n", path);
		return 1;
	}
	fseek(fp, 0, SEEK_SET);

	fread(buffer, sizeof(char), 16, fp);
	
	for (int i = 0; i< 16; i++) {
		if (buffer[i] != correctBMP[i]) {
			printf( &buffer[i], correctBMP[i], i);
			return 1;
		}
	}

	fclose(fp);
	return 0;
}

int convertGrey(char* bmpPath, int count) {

	FILE* bmp = fopen(bmpPath, "r");
	if (bmp == NULL) {
		printf("could not open %s.\n", bmpPath);
		return 1;
	}

	fseek(bmp, 0, SEEK_SET);
	BmpFileHeader fhead;
	fread(&fhead, sizeof(fhead)-2, 1, bmp);

	if(fhead.type != 0x4D42) {
		printf("Error! Unrecognized file format.");
		return 1;
	}

	fseek(bmp, 14, SEEK_SET);
	BmoInfoHeader ihead;
	fread(&ihead, sizeof(ihead), 1, bmp);
	
	int size = 3 * ihead.width * ihead.height;

	rgbTriple* data2 = new rgbTriple[size/3];

	fseek(bmp, 54, SEEK_SET);
	for (int i = 0; i < size/3; i++) {
		fread(&data2[i], sizeof(unsigned char), 3, bmp);
	}

	for(int i =0; i < size/3; i++) {
		int scale = (0.3 * data2[i].red) + (0.59 * data2[i].green) + (0.11 * data2[i].blue); // weighted method from https://www.tutorialspoint.com/dip/grayscale_to_rgb_conversion.htm
		
		if (scale < 110) {
			data2[i].red = data2[i].green = data2[i].blue = 0;
		} else {
			data2[i].red = data2[i].green = data2[i].blue = 500;
		}
	}

	createNewBmp(fhead, ihead, data2, size, bmpPath);

	delete[](data2);
	fclose(bmp);

	return 0;
}

int createNewBmp(BmpFileHeader fhead, BmoInfoHeader ihead, rgbTriple *data, int size, char* filename) {
	//copy everything over to a new file

	char* name = strtok(filename, ".");

	strcat(name, "-greyscale.bmp");

	FILE* final = fopen(name, "w");
	if (final == NULL) {
		printf("could not open .\n");
		return 1;
	}
	
	fseek(final, 0, SEEK_SET);
	fwrite(&fhead, 14, 1, final);
	fwrite(&ihead, sizeof(ihead), 1, final);
	fwrite(data, size, 1, final);

	fclose(final);
	return 0;
}