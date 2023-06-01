#include<stdio.h>
#include<stdlib.h>
int max(int a, int b) {
	return a > b ? a : b;
}
int min(int a, int b) {
	return a < b ? a : b;
}
int sum(int a, int b) {
	return a + b;
}


int main() {
	int(*fun[3])(int, int) = { max,min,sum };
	int i = 0,int functionId, int elementCount, int z, int p;

	scanf("%d%d%d", &functionId, &elementCount, &z);
	while (i < elementCount - 1) {
		scanf("%d", &p);
		z = fun[functionId](z, p);
		i++;
	}
	printf("%d", z);
	return 0;

}
