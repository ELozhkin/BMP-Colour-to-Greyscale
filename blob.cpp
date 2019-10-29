#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

using namespace std;

int convertGrey(char* bmpPath);
int convertGrey2(char* bmpPath);

int main(int argc, char** argv) {

	int success = convertGrey2(argv[1]);

	if (success == 0) {
		printf("yAy\n");
	} else {
		printf("aw no\n");
	}

	return 0;

}

int convertGrey(char* bmpPath) {

	FILE *bmp = fopen(bmpPath, "r");
	if (bmp == NULL) {
		printf("could not open %s.\n", bmpPath);
		return 1;
	}

	FILE *final = fopen("test.bmp", "w");
	if (final == NULL) {
		printf("could not create test.bmp\n");
		return 1;
	}

	BmpFileHeader fhead;
	fread(&fhead, sizeof(fhead), 1, bmp);

	BmoInfoHeader ihead;
	fread(&ihead, sizeof(ihead), 1, bmp);



	fclose(final);
	fclose(bmp);

	return 0;
}

int convertGrey2(char* bmpPath) {

	FILE* bmp = fopen(bmpPath, "r");
	if (bmp == NULL) {
		printf("could not open %s.\n", bmpPath);
		return 1;
	}

	fseek(bmp, 0, SEEK_SET);
	BmpFileHeader fhead;
	fread(&fhead, sizeof(fhead), 1, bmp);
	printf("%d\n", fhead.size);


	fseek(bmp, 14, SEEK_SET);
	BmoInfoHeader ihead;
	fread(&ihead, sizeof(ihead), 1, bmp);
	printf("%d\n", ihead.height);

	int size = 3 * ihead.width * ihead.height;
	unsigned char* data = new unsigned char[size]; //allocate 3 bytes per pixel according to size

	fseek(bmp, 54, SEEK_SET);
	fread(data, sizeof(unsigned char), size, bmp); //data should now contain the rgb values of the pixels 

	for (int i = 0; i < size; i += 3) {
		unsigned char tmp = data[i];
		data[i+2] = data[i];
		data[i] = tmp;

		// printf("%d\n", data[i]);
	}

	printf("%d\n", ihead.bitcount);
	fclose(bmp);

	return 0;
}
