#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
	int k[2];
	memset(k, 0, sizeof(int) * 2);
	printf("%d%dkek", k[0], k[1]);
}
