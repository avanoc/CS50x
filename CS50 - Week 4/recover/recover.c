#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int BLOCK_SIZE = 512;
int main(int argc, char *argv[])
{
    // Check if user typed command line correctly:
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }
    // Open the file
    FILE *file = fopen(argv[1], "r");
    // Check that file is not empty
    if (file == NULL)
    {
        printf("No file available\n");
        return 1;
    }
    // Allocate memory to read/write data
    unsigned char *buffer = malloc(BLOCK_SIZE);
    // Initialize the new file to be written
    char filename[8];
    FILE *new_file = NULL;
    // Set a counter
    int i = 0;
    while (fread(buffer, 1, BLOCK_SIZE, file) != 0)
    {
        // When header of JPEG is found, create a .jpg file and start writing on it
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (new_file != NULL)
            {
                // Close the new file
                fclose(new_file);
            }
            sprintf(filename, "%03i.jpg", i);
            new_file = fopen(filename, "w");
            fwrite(buffer, 1, BLOCK_SIZE, new_file);
            i++;
        }
        // When no header is found, after finding the first JPEG header, keep writing in the existing file until new header is found.
        else if (new_file != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, new_file);
        }
    }
    // Close the last file encountered
    fclose(new_file);
    // Release the allocated memory
    free(buffer);
    // Close the original file
    fclose(file);
}