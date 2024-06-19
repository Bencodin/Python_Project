#include <unistd.h>
#include <stdio.h>
int main() {
	for (int i = 1; i < 11; i++) {
		char c[2];
		sprintf(c, "%d", i);
		write(1, &c, sizeof c);
		write(1, "\n", 1);
	}
	return 0;
}
