/* Chapter 1. Basic cp file copy program. C library Implementation. */
/* cpC file1 file2: Copy file1 to file2. */

#include <stdio.h>
#include <errno.h>
#define BUF_SIZE 256

int main(int argc, char* argv[])
{
	FILE* inFile, * outFile;
	char rec[BUF_SIZE];
	size_t bytesIn, bytesOut;
	errno_t	err;

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
		return 1;
	}

	err = fopen_s(&inFile, argv[1], "rb");
	if (err)
	{
		perror(argv[1]);
		return 2;
	}
	err = fopen_s(&outFile, argv[2], "wb");
	if (err)
	{
		perror(argv[2]);
		fclose(inFile);
		return 3;
	}

	while ((bytesIn = fread(rec, 1, BUF_SIZE, inFile)) > 0)
	{
		bytesOut = fwrite(rec, 1, BUF_SIZE, outFile);
		if (bytesOut != bytesIn)
		{
			perror("Fatal write error.");
			fclose(inFile);
			fclose(outFile);
			return 4;
		}
	}

	fclose(inFile);
	fclose(outFile);
	return 0;
}