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

    Node(const Node<T> &other) {
        data = other.data;
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
    
    CustomStack(const CustomStack<T> &other) {
        head = NULL;
        Node<T> *otherCurrent = other.head;
        while (otherCurrent != NULL) {
            push(otherCurrent->getData());
            otherCurrent = otherCurrent->getNext();
        }
    }


    bool isempty(){
        return head == NULL;
    }

    T top(){
        try {
            if (isempty()) {
                throw runtime_error("Error: Stack UnderFlow");
            }
            return head->getData();
        } catch (const exception& e) {
            cout << e.what()<<" -- Default Value : ";;
            return T();
        }
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
    
    ~CustomStack() {
        while (head != NULL) {
            Node<T> *temp = head;
            head = head->getNext();
            delete temp;
        }
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
    stk.push(4);
    cout<<"---------------------"<<endl;
    CustomStack<long long > obj(stk);
    obj.push(5);
    cout<<obj.top()<<endl;
    cout<<stk.top()<<endl;

}