#include <stdint.h>

typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} BmpFileHeader;

typedef struct 
{
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitcount;
    uint32_t compression;
    uint32_t sizeimage;
    //unused
    int32_t xpixperm; //horizontal resolution (pixels/metre)
    int32_t ypixperm;
    uint32_t coloursused;
    uint32_t importantcolours;
} BmoInfoHeader;

typedef struct
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} rgbTriple;
