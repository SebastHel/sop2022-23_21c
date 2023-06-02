#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int data;
	struct Node* Node_prev;
	struct Node* Node_next;

};

void Wprowadz(Node** list, int numb) {
	Node* NewNode = (Node*)malloc(sizeof(Node));
	if (NewNode == NULL) {
		printf("błąd\n");
		return 1;
	}
	Node* beginning = *list;

	NewNode->Node_prev = NULL;
	NewNode->Node_next = *list;
	NewNode->data = numb;

	if (beginning == NULL) {
		*list = NewNode;
	}
	else {
		beginning->Node_prev = NewNode;
		*list = NewNode;
	}
}
void Wprowadz_koniec(Node** list,int numb) {
	Node* NewNode = (Node*)malloc(sizeof(Node));
	if (NewNode == NULL) {
		printf("błąd\n");
		return 2;
	}

	NewNode->Node_prev = NULL;
	NewNode->Node_next = NULL;
	NewNode->data = numb;

	if (*list == NULL) {
		*list = NewNode;

	}
	else {
		Node* Last_node = *list;
		while (Last_node->Node_next != NULL) {
			Last_node = Last_node->Node_next;
		}
		Last_node->Node_next = NewNode;
		NewNode->Node_prev = Last_node;
	}
}

void wyswietldane(Node* list) {
	Node* Last_node = list;
	while (Last_node != NULL) {
		printf("%d\n", Last_node->data);
		Last_node = Last_node->Node_next;

	}


}

int main() {
	Node* list = NULL;
	Wprowadz(&list, 4);
	Wprowadz_koniec(&list,4);
	Wprowadz(&list, 7);
	printf("Data: \n");
	wyswietldane(list);

	wyswietldane(list);
	return 0;

}
