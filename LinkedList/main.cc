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
} LinkedList;

LinkedList* list;

int cnt;

void Init() {
	list = (LinkedList*)malloc(sizeof(LinkedList));
	list->head = (Node*)malloc(sizeof(Node));
	list->tail = (Node*)malloc(sizeof(Node));

	list->head->prev = NULL;
	list->tail->next = NULL;

	list->head->next = list->tail;
	list->tail->prev = list->head;
}

void Print() {
	std::cout << "List count " << cnt << " element: ";
	Node* pos = list->head->next;
	
	for (int i = 0; i < cnt; i++) {
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

	cnt++;
}

void Insert(int position, int data) {
	if (position >= cnt) {
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

		cnt++;
	}
}

int Delete(int position, int* value) {
	if (position <= cnt) {
		Node* pos = list->head->next;
		for (int i = 0; i < position; i++) {
			pos = pos->next;
		}
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;
		*value = pos->data;
		free(pos);
		cnt--;
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
	cnt = 0;
}

int main(void) {
	Init();

	int value;

	std::cout << "Just after initialize" << std::endl;
	Print();

	Append(-3);
	Print();
	Append(-19);
	Print();
	Append(1);
	Print();
	Insert(1, -5);
	Print();

	Append(4);
	Print();

	Insert(2, 10);
	Print();

	if (Delete(2, &value)) {
		Print();
		std::cout << "Deleted value: " << value << std::endl;
	}

	Free();

	return 0;
}