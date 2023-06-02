#include <stdio.h>
#include<stdlib.h>

struct node {
	int dane;
	struct node* node2;

};
void wprowadz(node** list, int i) {
	int liczba;
	struct node* noweDane = (node*)malloc(sizeof(node));
	if (noweDane == NULL) {
		printf("Błąd");
		return 1;
	}
	noweDane->dane = i;
	noweDane->node2 = *list;
	*list = noweDane;
};
void wyswietldane(node* list) {
	struct node* last = list;

	while (last != NULL) {
		printf("%d\n", last->dane);
		last = last->node2;
	}
}
void usun(node** list, int dane) {
	struct node* del = *list;
	struct node* previous = NULL;

	while (del->dane != dane && del != NULL) {
		previous = del;
		del = del->node2;
	}

	if (previous == NULL) {
		*list = del->node2;
	}
	else {
		previous->node2 = del->node2;
	}
	free(del);

}
int main() {
	struct node* list = NULL;
	wprowadz(&list, 4);
	wprowadz(&list, 7);
	wprowadz(&list, 8);
	printf("Dane: \n");

	wyswietldane(list);
	scanf("%d", 7);
	usun(&list, 7);
	wyswietldane(list);
	return 0;

}
