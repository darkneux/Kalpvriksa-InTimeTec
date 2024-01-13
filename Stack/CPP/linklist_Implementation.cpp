#include<iostream>
using namespace std;

template<typename T>
class Node {
    T data;
    Node<T> *next;
public:
    
    Node(T data) {
        this->data = data;
        next = NULL;
    }

    T getData() {
        return data;
    }

    Node<T> *getNext(){
        return next;
    }
    void setNext(Node<T> *next){
        this->next = next;
    }
};

template <typename T>
class CustomStack{
    Node<T> *head;
  public:
    CustomStack(){
        head = NULL;
    }
    bool isempty(){
        return head == NULL;
    }
    T top(){
        if(isempty()){
            cout<<"Warning : Stack is Empty ";
            return T();
        }
        return head->getData();
    }
    void pop(){
        if(isempty())return;
        head = head->getNext();
    }
    void push(T value){
        Node<T> *container = new Node<T>(value);
        if(!isempty()){
            container->setNext(head);
        }
        head = container;
    }

};

int main(){
    CustomStack<long long> stk;
    stk.pop(); 
    cout<<stk.isempty()<<endl;
    stk.push(7);
    cout<<stk.isempty()<<endl;
    cout<<stk.top()<<endl;
    stk.pop();
    cout<<stk.top()<<endl;
    cout<<stk.isempty()<<endl;
}