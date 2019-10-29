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
	fread(&fhead, sizeof(fhead)-2, 1, bmp);
	printf("%d\n", sizeof(fhead));

	if(fhead.type != 0x4D42) {
		printf("Error! Unrecognized file format.");
		return 1;
	}


	fseek(bmp, 14, SEEK_SET);
	BmoInfoHeader ihead;
	fread(&ihead, sizeof(ihead), 1, bmp);
	
	int size = 3 * ihead.width * ihead.height;
	unsigned char* data = new unsigned char[size]; //allocate 3 bytes per pixel according to size

	fseek(bmp, 54, SEEK_SET);
	fread(data, sizeof(unsigned char), size, bmp); //data should now contain the rgb values of the pixels 

	for (int i = 0; i < size; i += 3) {
		unsigned char tmp = data[i];
		data[i+2] = data[i];
		data[i] = tmp;

		int R = data[i];
		int G = data[i+1];
		int B = data[i+2];

		int scale =(0.3 * R) + (0.59 * G) + (0.11 * B);

		data[i] = data[i+1] = data[i +2] = scale;

		// i = r, i + 1 = g, i + 2 = b
		// if (data[i] < 150) {
		// 	data[i] = 0;
		// } else {
		// 	data[i] = 250;
		// }

	}

	//copy everything over to a new file
	FILE* final = fopen("test.bmp", "w");
	if (final == NULL) {
		printf("could not open .\n");
		return 1;
	}
	
	fseek(final, 0, SEEK_SET);
	fwrite(&fhead, 14, 1, final);
	fwrite(&ihead, sizeof(ihead), 1, final);
	fwrite(data, size, 1, final);


	printf("%d\n", ihead.bitcount);
	printf("%d\n", ihead.coloursused);

	delete[](data);
	fclose(bmp);
	fclose(final);

	return 0;
}
