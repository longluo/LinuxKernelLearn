#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
	int testdev;
	int i, ret;
	char buf[15];

	testdev = open("/dev/mycdev", O_RDWR);

	if (-1 == testdev) {
		printf("cannot open file.\n");
		exit(1);
	}

	if (ret = read(testdev, buf, 15) < 15) {
		printf("read error!\n");
		exit(1);
	}

	printf("%s\n", buf);

	close(testdev);

	return 0;
}

