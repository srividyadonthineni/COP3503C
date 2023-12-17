#include <vector>
#include <iostream>
using namespace std;

template<typename T>
class LinkedList{
  public:
    struct Node{
      T data;
      Node* next;
      Node* prev;
    };
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    ~LinkedList();
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);
    unsigned int NodeCount() const;
    void PrintForward() const;
    void PrintReverse() const;
    Node *GetNode(unsigned int index);
    const Node *GetNode(unsigned int index) const;
    Node *Find(const T &data);
    const Node *Find(const T &data) const;
    void FindAll(vector<Node *> &outData, const T &value) const;
    const T &operator[](unsigned int index) const;
    T &operator[](unsigned int index);
    bool operator==(const LinkedList<T> &rhs) const;
    LinkedList<T>& operator=(const LinkedList<T>& rhs);
    void InsertBefore(Node* node, const T& data);
    void InsertAfter(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);
    void PrintaForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T& data);
    bool RemoveAt(unsigned int index);
    void Clear();
    Node* Head(){
      return head;
    }
    const Node* Head() const{
      return head;
    }
    Node* Tail(){
      return tail;
    }
    const Node* Tail() const{
      return tail;
    }
  private:
    Node* head;
    Node* tail;
    unsigned int numNodes;

};

template <typename T>
LinkedList<T>::LinkedList(){
  head = nullptr;
  tail = nullptr;
  numNodes = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list){
  numNodes = 0;
  head = nullptr;
  tail = nullptr;

  Node* copy = list.head;
  while(copy != nullptr){
    AddTail(copy->data);
    copy = copy->next;
  }
}

template <typename T>
LinkedList<T>::~LinkedList(){
  while(head != nullptr){
    Node* temp = head;
    head = head->next;
    delete temp;
  }
  numNodes = 0;
  tail = nullptr;
}

template <typename T>
void LinkedList<T>::AddHead(const T& data){
  Node* newNode = new Node();
  newNode->data = data;
  if(head == nullptr){
    head = newNode;
    tail = newNode;
  }
  else{
    newNode->next = head;
    head->prev= newNode;
    head = newNode;
  }
  numNodes++;
}

template <typename T>
void LinkedList<T>::AddTail(const T& data){
  Node* newNode = new Node();
  newNode->data = data;
  newNode->prev = nullptr;

  if(tail == nullptr){
    head = newNode;
    tail = newNode;
  }
  else{
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
  }
  numNodes++;
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count){
  for(unsigned int i = 0; i < count; i++){
    T addData = data[i];
    AddHead(addData);
  }
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count){
  for(unsigned int i = 0; i < count; i++){
    T addData = data[i];
    AddTail(addData);
  }
}

template <typename T>
unsigned int LinkedList<T>::NodeCount() const{
  return numNodes;
}


template <typename T>
void LinkedList<T>::PrintForward() const{
  Node* forward = head;
  while (forward != nullptr){
    cout << forward->data << endl;
    forward = forward->next;
  }
}

template <typename T>
void LinkedList<T>::PrintReverse() const{
  Node* reverse = tail;
  while(reverse != nullptr){
    cout << reverse->data << endl;
    reverse = reverse->prev;
  }
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const{
  if(index >= numNodes){
    throw out_of_range("Index out of range.");
  }
  Node* temp = head;
  unsigned int i = 0;
  while(i < index){
    temp = temp->next;
    i++;
  }
  return temp;
}

template <typename T> 
typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index){
  if(index >= numNodes){
    throw out_of_range("Index out of range.");
  }
  Node* temp = head;
  unsigned int i = 0;
  while(i < index){
    temp = temp->next;
    i++;
  }
  return temp;
}

template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const{
  if(index >= numNodes){
    throw out_of_range("Out of range exception.");
  }
  Node* temp = head;
  unsigned int i = 0;
  while(i < index){
    temp = temp->next;
    i++;
  }
  return temp;
}


template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
  if(index >= numNodes){
    throw out_of_range("Out of range exception.");
  }
  Node* temp = head;
  unsigned int i = 0;
  while(i < index){
    temp = temp->next;
    i++;
  }
  return temp->data;
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &rhs) const{
  if(numNodes != rhs.numNodes){
    return false;
  }
  Node* temp = head;
  Node* rhstemp = rhs.head;

  while(temp != nullptr && rhstemp != nullptr){
    if(temp->data != rhstemp->data){
      return false;
    }
    temp = temp->next;
    rhstemp = rhstemp->next;
  }
  return true;
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs){
  Node *current = head;
  Node *temp2 = rhs.head;
  while(current != nullptr){
    Node *temp = current->next;
    delete current;
    current = temp;
  }
  tail = nullptr;
  head = nullptr;
  numNodes = 0;
  while(temp2 != nullptr){
    AddTail(temp2->data);
    temp2 = temp2->next;
  }
  return *this;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::Find(const T& data){
  Node* temp = head;
  for(unsigned int i = 0; i < numNodes; i++){
    if(data == temp->data){
      return temp;
    }
    temp = temp->next;
  }
  return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Find(const T& data) const{
  Node* temp = head;
  for(unsigned int i = 0; i < numNodes; i++){
    if(data == temp->data){
      return temp;
    }
    temp = temp->next;
  }
  return nullptr;
}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const{
  Node *temp = head;
  while(temp != nullptr){
    if(temp->data == value){
      outData.push_back(temp);
    }
    temp = temp->next;
  }
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data){
  Node* lastNode = node->prev;
  Node* current = new Node();
  current->data = data;
  current->next = node;
  current->prev = lastNode;
  if(node != head){
    lastNode->next = current;
  }
  else{
    head = current;
  }
  node->prev = current;
  numNodes++;
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data){
  Node* after = node->next;
  Node* current = new Node();
  current->data = data;
  current->next = after;
  current->prev = node;
  if(node != tail){
    after->prev = current;
  }
  else{
    tail = current;
  }
  node->next = current;
  numNodes++;
}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index){
  if(index > numNodes){
    throw out_of_range("Out of range.");
  }
  else if(index == numNodes){
    AddTail(data);
  }
  else if(index == 0){
    AddHead(data);
  }
  else{
    Node *current = GetNode(index);
    InsertBefore(current, data);
  }
}

template <typename T>
bool LinkedList<T>::RemoveHead(){
  if(numNodes == 0){
    return false;
  }
  else if(numNodes == 1){
    delete head;
    head = nullptr;
    tail = nullptr;
    numNodes--;
    return true;
  }
  else{
    Node *temp = head->next;
    delete head;
    head = temp;
    numNodes--;
    head->prev = nullptr;
    return true;
  }
}

template <typename T>
bool LinkedList<T>::RemoveTail(){
  if(numNodes == 0){
    return false;
  }
  else if(numNodes == 1){
    delete tail;
    head = nullptr;
    tail = nullptr;
    numNodes--;
    return true;
  }
  else{
    Node* temp = tail->prev;
    delete tail;
    tail = temp;
    tail->next = nullptr;
    numNodes--;
    return true;
  }
}

template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index){
  if(index < 0 || index >= numNodes){
    return false;
  }
  else{
    Node* temp = GetNode(index);
    Node* nextNode = temp->next;
    Node* lastNode = temp->prev;
    delete temp;
    lastNode->next = nextNode;
    nextNode->prev = lastNode;
    numNodes--;
    return true;
  }
}

template<typename T>
unsigned int LinkedList<T>::Remove(const T &data){
  unsigned int i = 0;
  Node* temp = head;
  Node* prevNode = nullptr;
  Node* nextNode = nullptr;
  while(temp->next != nullptr){
    if(temp->data == data){
      prevNode = temp->prev;
      nextNode = temp->next;
      delete temp;
      prevNode->next = nextNode;
      nextNode->prev = prevNode;
      temp = nextNode;
      numNodes--;
      i++;
    }
    else{
      temp = temp->next;
    }
  }
  return i;
}

template<typename T>
void LinkedList<T>::Clear(){
  unsigned int i = 0;
  while(head != nullptr){
    Node *temp = head;
    head = head->next;
    temp->prev = nullptr;
    temp->next = nullptr;
    delete temp;
    temp = nullptr;
    i++;
  }
  tail = nullptr;
  numNodes = 0;
}

template<typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const{
  if(node->next == nullptr){
    cout << node->data << endl;
  }
  else{
    cout << node->data <<endl;
    PrintForwardRecursive(node->next);
  }
}

template<typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const{
  if(node == head){
    cout << node-> data << endl;
  }
  else{
    cout << node->data << endl;
    PrintReverseRecursive(node->prev);
  }
}
