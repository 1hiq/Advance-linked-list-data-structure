#include <iostream>
using namespace std;



template <class type> class Advance_Linked_list {
private:
	struct Node {
		type data;
		Node* next;
		Node* before;
	};

	Node* head;
	Node* tail;
	int elementsNumber;

	Node* getNodeOfThisIndex(int index) {
		if (isEmpty()) {
			cout << "This linked-list is empty.\n";
		}
		else if (index > getSize() || index < 0) {
			cout << "Error, index of node should be LESS or EQUAL to the length of the linked-list and MORE or EQUAL to 0.\n";
		}
		else {
			if (index == 0) {
				return head;
			}
			else if (index == getSize() - 1) {
				return tail;
			} 
			else {
				Node* mover = new Node;
				if (index < getSize() / 2) {
					mover = head;

					for (int i = 1; i < index; i++) {
						mover = mover->next;
					}

					return mover;
				}
				else {
					mover = tail;

					for (int i = index; i < getSize() - 2; i++) {
						mover = mover->before;
					}

					return mover;
				}
			}
		}
	}


public:
	Advance_Linked_list();
	bool isEmpty();
	void addNodeAtTheBeginning(type value);
	void addNodeAtTheEnd(type value);
	void addNodeAt_a_CertainIndex(type value, int index);
	type removeNodeAtTheEnd();
	type removeNodeAtTheBeginning();
	void removeNode(type value);
	void showElements();
	void showElementsViceVersa();
	type getElements(); // You should use with it (for loop) using (getSize) function.
	type getElementsViceVersa(); // == == == == == == == == == == == == == == == == ==
	//int search(type value); //(Linear search): get/return index of node that contains this value.
	int search(type value); // (Binary serach): get/return index of node that contains this value.
	bool isExist(type value);
	int getSize();
	type getFirstValue();
	type getLastValue();
	type getValueOfIndex(int index);
	void sortAscending();
	void sortDescending();
	type getMax();
	type getMin();
	void editValue(int indexOfNode, type newValue);
	void swapNode(int indexOfFirstNode, int indexOfSecondNode);
	void reverse();
	void clear();

};



int main(void){
  



  return 0;
}






template <class type> Advance_Linked_list<type>::Advance_Linked_list() {
	head = NULL;
	tail = NULL;
	elementsNumber = 0;
}

template <class type> bool Advance_Linked_list<type>::isEmpty() {
	if (head == NULL) {
		return true;
	}
	else {
		return false;
	}
}

template <class type> void Advance_Linked_list<type>::addNodeAtTheBeginning(type value) {
	Node* firstNode = new Node;
	firstNode->data = value;
	firstNode->before = NULL;
	elementsNumber++;

		if (head == NULL) {
			head = firstNode;
			tail = firstNode;
			firstNode->next = NULL;
		}
		else {
			head->before = firstNode;
			firstNode->next = head;
			head = firstNode;
		}
}

template <class type> void Advance_Linked_list<type>::addNodeAtTheEnd(type value) {
	Node* newNode = new Node;
	newNode->data = value;
	newNode->next = NULL;
	elementsNumber++;

		if (head == NULL) {
			head = tail = newNode;
			newNode->before = NULL; // may head instead of NULL
		}
		else {
			newNode->before = tail;
			tail->next = newNode;
			tail = newNode;
		}
}

template <class type> void Advance_Linked_list<type>::addNodeAt_a_CertainIndex(type value, int index) {
	if (index > getSize() || index < 0) { // getSize() - index < 0
		cout << "Error, index can not be GREATER than size of linked-list OR LESS than 0.\n";
	}
	else {
		Node* newNode = new Node;
		newNode->data = value;

		if (index == 0) {
			if (head == NULL) {
				head = newNode;
				tail = newNode;
				newNode->next = NULL;
				newNode->before = NULL;

				elementsNumber++;
			}
			else {
				head->before = newNode;

				newNode->next = head;
				head = newNode;
				newNode->before = NULL;

				elementsNumber++;
			}
		}
		else if (index == getSize()) {
			newNode->before = tail;
			newNode->next = NULL;

			tail->next = newNode;
			tail = newNode;

			elementsNumber++;
		}
		else {
			Node* nodeOfThisIndex = getNodeOfThisIndex(index);
			Node* before_nodeOfThisIndex = nodeOfThisIndex->before;

			newNode->next = nodeOfThisIndex;
			newNode->before = nodeOfThisIndex->before;
			nodeOfThisIndex->before = newNode;

			before_nodeOfThisIndex->next = newNode;

			elementsNumber++;
		}
	}
}

template <class type> type Advance_Linked_list<type>::removeNodeAtTheEnd() {
	if (isEmpty()) {
		cout << "This linked-list is empty, so I can't remove any element.\n";
		return false;
	}
	else {
		if (head->next == NULL){
			type value = head->data;
			
			free(head->next);
			head = NULL;
			tail = NULL;
			
			return value;
		}
			
		Node* lastNode = tail;
		type dataInTheLastNode = lastNode->data;
		tail = tail->before;
		tail->next = NULL;
		free(lastNode);
		elementsNumber--;
		return dataInTheLastNode;
	}
}

template <class type> type Advance_Linked_list<type>::removeNodeAtTheBeginning() {
	if (isEmpty()) {
		cout << "This linked-list is empty, so I can't remove any element.\n";
		return false;
	}
	else {
		Node* firstNode = head;
		type dataInTheFirstNode = firstNode->data;
		head = firstNode->next;
		head->before = NULL;
		free(firstNode);
		elementsNumber--;
		return dataInTheFirstNode;
	}
}

template <class type> void Advance_Linked_list<type>::removeNode(type value) {
	if (isEmpty()) {
		cout << "This linked-list is empty, so I can't remove any element.\n";
		return;
	}

	Node* checker = head;
	checker->before = NULL;
	while (checker->data != value) {
		if (checker == tail) {
			cout << "This value is not found in the linked-list.\n";
			return;
		}
		checker = checker->next;
	}

	if (isEmpty()) {
		cout << "This linked-list is empty, so I can't remove any element.\n";
	}
	else {
		elementsNumber--;

		Node* current = head;
		Node* previous = head;

		while (current->data != value) {
			previous = current;
			current = current->next;
		}

		if (head->data == value) {
			if (head->next == NULL) {
				head = NULL;
				tail = NULL;
				free(current);
			}
			else {
				head = current->next;
				head->before = NULL;
				free(current);
			}
		}
		else if (current->data == tail->data) {
			tail = previous; // tail = tail->before;
			tail->next = NULL; // tail->next = current->next;
			free(current); 
		}
		else {
			Node* afterCurrent = current->next;
			afterCurrent->before = previous;

			previous->next = current->next;
			free(current);
		}
	}
}

template <class type> void Advance_Linked_list<type>::showElements() {
	if (isEmpty()) {
		cout << "This linked-list is empty, so I can't print any element.\n";
	}
	else {
		Node* shower = head;
		while (shower != NULL) {
			cout << shower->data << endl;
			shower = shower->next;
		}
	}
}

template <class type> void Advance_Linked_list<type>::showElementsViceVersa() {
	if (isEmpty()) {
		cout << "This linked-list is empty, so I can't print any element.\n";
	}
	else {
		Node* shower = tail;
		while (shower != NULL) {
			cout << shower->data << endl;
			shower = shower->before;
		}
	}
}

template <class type> type Advance_Linked_list<type>::getElements() {
	if (isEmpty()) {
		cout << "This linked-list is empty, so I can't return any element.\n";
		return false;
	}
	else {
		static Node* turner = head;

		while (turner->next != NULL) {
			type data = turner->data;
			turner = turner->next;
			return data;

		}

		return turner->data;
	}
}

template<class type> type Advance_Linked_list<type>::getElementsViceVersa(){
	if (isEmpty()) {
		cout << "This linked-list is empty, so I can't return any element.\n";
		return false;
	}
	else {
		static Node* turner = tail;

		while (turner->before != NULL) {
			type data = turner->data;
			turner = turner->before;
			return data;
		}

		return turner->data;
	}
}

/*template <class type> int Advance_Linked_list<type>::search(type value) {
	Node* checker = head;
	checker->before = NULL;
	while (checker->data != value) {
		if (checker == tail) {
			cout << "This value is not found in the linked-list.\n";
			return -1; // Or maybe 0 (false)
		}
		checker = checker->next;
	}

	if (isEmpty()) {
		cout << "This linked-list is empty, so I can't search about any element.\n";
		return -1;
	}
	else {
		Node* turner = head;
		int counter = 1;
		while (turner->data != value) {
			counter++;
			turner = turner->next;
		}

		//cout << "This value is found in the Node Number " << return counter << " .\n";
		return counter - 1;
	}
}*/

template <class type> int Advance_Linked_list<type>::search(type value) {
	if (isEmpty()) {
		cout << "This linked-list is empty, so I can't search about any element.\n";
		return -1;
	}

	Node* checker = head;
	checker->before = NULL;
	while (checker->data != value) {
		if (checker == tail) {
			cout << "This value is not found in the linked-list.\n";
			return -1; // Or maybe 0 (false)
		}
		checker = checker->next;
	}


	if (isEmpty()) {
		cout << "This linked-list is empty, so I can't search about any element.\n";
		return -1;
	}
	else if (head->data == value) {
		return 0;
	}
	else if (tail->data == value) {
		return getSize() - 1;
	}
	else {
		int start = 0, end = getSize(), middle;

		while (start <= end) {
			middle = (start + end) / 2;
			if (getValueOfIndex(middle) == value) {
				return middle;
			}
			else if (getValueOfIndex(middle) < value) {
				start = middle;
			}
			else if (getValueOfIndex(middle) > value) {
				end = middle;
			}
		}
	}
}

template <class type> bool Advance_Linked_list<type>::isExist(type value) {
	Node* checker = head;
	checker->before = NULL;
	while (checker->data != value) {
		if (checker == tail) {
			cout << "This value is not found in the linked-list.\n";
			return false;
		}
		checker = checker->next;
	}


	if (isEmpty()) {
		cout << "This linked-list is empty.\n";
		return false;
	}
	else {
		return true;
	}
}

template <class type> int Advance_Linked_list<type>::getSize() {
	
	return elementsNumber;

	/*if (isEmpty()) {
		cout << "This linked-list is empty.\n";
		return false;
	}
	else {
		return elementsNumber;
	}*/
}

template <class type> type Advance_Linked_list<type>::getFirstValue() {
	if (isEmpty()) {
		cout << "This linked-list is empty.\n";
		return false;
	}
	else {
		return head->data;
	}
}

template <class type> type Advance_Linked_list<type>::getLastValue() {
	if (isEmpty()) {
		cout << "This linked-list is empty.\n";
		return false;
	}
	else {
		return tail->data;
	}
}

template <class type> type Advance_Linked_list<type>::getValueOfIndex(int index) {
	if (isEmpty()) {
		cout << "This linked-list is empty.\n";
		return -1;
	}
	else if (index >= getSize() || index < 0) {
		cout << "Error, index should be LESS than the size of the linked-list AND MORE than -1.\n";
		return -1;
	}
	else {
		if (index <= getSize() / 2) {
			Node* turner = head;
			int counter = 0;

			while (counter != index) {
				turner = turner->next;
				counter++;
			}

			return turner->data;
		}
		else {
			Node* turner = tail;
			int counter = getSize() - 1;

			while (counter != index) {
				turner = turner->before;
				counter--;

			}

			return turner->data;
		}
	}
}

template <class type> void Advance_Linked_list<type>::sortAscending() {
	if (isEmpty()) {
		cout << "This linked-list is empty.\n";
	}
	else {
		if (head->next == NULL) {
			cout << "This linked-list contains only one element, so it is already sorted (ascending).\n";
			return;
		}

		int counter = 0;
		for (int i = 1; i < getSize(); i++) {
			for (int j = 0; j < i; j++) {
				if (getValueOfIndex(i) < getValueOfIndex(j)) {
					counter++;
					swapNode(j, i);
				}
			}
		}

		if (counter == 0) {
			cout << "This linked-list has already sorted (ascending).\n";
		}
	}
}

template <class type> void Advance_Linked_list<type>::sortDescending() {
	if (isEmpty()) {
		cout << "This linked-list is empty.\n";
	}
	else {
		if (head->next == NULL) {
			cout << "This linked-list contains only one element, so it is already sorted (descending).\n";
			return;
		}

		int counter = 0;
		for (int i = 0; i < getSize(); i++) {
			for (int j = i + 1; j < getSize(); j++) {
				if (getValueOfIndex(i) < getValueOfIndex(j)) {
					counter++;
					swapNode(i, j);
				}
			}
		}

		if (counter == 0) {
			cout << "This linked-list has already sorted (descending).\n";
		}
	}
}

template <class type> type Advance_Linked_list<type>::getMax() {
	if (isEmpty()) {
		cout << "This linked-list is empty.\n";
		return -1;

	} else {
		if (head->next == NULL) {
			return head->data;
		}
		else {
			type max = getValueOfIndex(0);
			for (int i = 1; i < getSize(); i++) {
				if (max < getValueOfIndex(i)) {
					max = getValueOfIndex(i);
				}
			}

			return max;
		}
	}
}

template <class type> type Advance_Linked_list<type>::getMin() {
	if (isEmpty()) {
		cout << "This linked-list is empty.\n";
		return -1;

	}
	else {
		if (head->next == NULL) {
			return head->data;
		}
		else {
			type min = getValueOfIndex(0);
			for (int i = 1; i < getSize(); i++) {
				if (min > getValueOfIndex(i)) {
					min = getValueOfIndex(i);
				}
			}

			return min;
		}
	}
}

template <class type> void Advance_Linked_list<type>::editValue(int indexOfNode, type newValue) {
	if (isEmpty()) {
		cout << "This linked-list is empty.\n";
	}
	else if (indexOfNode >= getSize() || indexOfNode < 0) {
		cout << "Error, index of node should be LESS than the length of the linked-list AND MORE than -1.\n";
	}
	else {
		Node* mover = head;
		
		for (int i = 0; i < indexOfNode; i++) {
			mover = mover->next;
		}

		mover->data = newValue;
	}
}

template <class type> void Advance_Linked_list<type>::swapNode(int indexOfFirstNode, int indexOfSecondNode) {
	if (isEmpty()) {
		cout << "This linekd-list is empty.\n";
	}
	else if (head->next == NULL) {
		cout << "This linked-list contains only one node, so I can't swap.\n";
	}
	else if (indexOfFirstNode >= getSize() || indexOfFirstNode < 0 || indexOfSecondNode >= getSize() || indexOfFirstNode < 0) {
		cout << "Error, index should be LESS than the length of linked-list AND MORE than -1.\n";
	}
	else {
		type firstData = getNodeOfThisIndex(indexOfFirstNode)->data;
		getNodeOfThisIndex(indexOfFirstNode)->data = getNodeOfThisIndex(indexOfSecondNode)->data;
		getNodeOfThisIndex(indexOfSecondNode)->data = firstData;
	}
}

template <class type> void Advance_Linked_list<type>::reverse() {
	if (isEmpty()) {
		cout << "This linked-list is empty.\n";
	}
	else {
		type* arr = new type[getSize()];
		Node* fromLastToStart = tail;

		int counter = 0;
		while (fromLastToStart != NULL) {
			arr[counter] = fromLastToStart->data;
			fromLastToStart = fromLastToStart->before;
			counter++;
		}

		for (int i = 0; i < getSize(); i++) {
			getNodeOfThisIndex(i)->data = arr[i];
		}
	}
} // Contains Warnings :D

template <class type> void Advance_Linked_list<type>::clear() {
	if (isEmpty()) {
		cout << "This linked-list is empty.\n";
	}
	else {
		int orginalSize = elementsNumber;
		for (int i = 0; i < orginalSize; i++)
			removeNodeAtTheEnd();
	}
}
