#include <iostream>
#include <malloc.h>

typedef struct node {
	int data;
	node* prev;
	node* next;
} Node;

typedef struct linked_list {
	Node* head;
	Node* tail;
	int cnt;
} LinkedList;

LinkedList* list;

void Init() {
	list = (LinkedList*)malloc(sizeof(LinkedList));
	list->head = (Node*)malloc(sizeof(Node));
	list->tail = (Node*)malloc(sizeof(Node));

	list->head->prev = NULL;
	list->tail->next = NULL;

	list->head->next = list->tail;
	list->tail->prev = list->head;

	list->cnt = 0;
}

void Print() {
	std::cout << "List count " << list->cnt << " elements: ";
	Node* pos = list->head->next;
	
	for (int i = 0; i < list->cnt; i++) {
		std::cout << pos->data << " ";
		pos = pos->next;
	}
	std::cout << std::endl;
}

void Append(int data) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	
	new_node->data = data;
	new_node->prev = list->tail->prev;
	
	list->tail->prev->next = new_node;
	list->tail->prev = new_node;
	
	new_node->next = list->tail;

	list->cnt++;
}

void Insert(int position, int data) {
	if (position >= list->cnt) {
		Append(data);
	}
	else {
		Node* pos = list->head->next;
		for (int i = 0; i < position; i++) {
			pos = pos->next;
		}

		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->data = data;

		new_node->next = pos->next;
		new_node->prev = pos;
		
		pos->next->prev = new_node;
		pos->next = new_node;

		list->cnt++;
	}
}

int Delete(int position, int* value) {
	if (position <= list->cnt) {
		Node* pos = list->head->next;
		for (int i = 0; i < position; i++) {
			pos = pos->next;
		}
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;
		*value = pos->data;
		free(pos);
		list->cnt--;
		return 1;
	}
	else {
		std::cout << "List out of range\n";
		return 0;
	}
}

void Free() {
	Node* pos = list->head->next;
	while (pos) {
		free(pos->prev);
		pos = pos->next;
	}
	free(list->tail);
	free(list);
	list->cnt = 0;
}

int main(void) {
	
	Init();

	int value;

	Print();

	Append(0);
	Print();
	Append(1);
	Print();
	Append(2);
	Print();
	Append(3);
	Append(4);
	Append(5);
	Append(6);
	Insert(4, 10);
	Print();
	
	Insert(3, 10);
	Print();

	if (Delete(2, &value)) {
		Print();
		std::cout << "Deleted value: " << value << std::endl;
	}

	Free();

	return 0;
}