#include<iostream>
using namespace std;

template<typename T>
class CustomStack{
	      T *data;
        int size;
        int index;
    public:

        CustomStack(int size=10){
          this->size = size;
          data = new T[size];
          this->index = -1;
        }

         ~CustomStack() {
        delete[] data;
        }

        bool isempty(){
          return index == -1;
        }

        T top(){
         if(isempty()){
            cout<<"Warning : Stack is Empty ";
            return T();
          }
         return data[index];
        }

        void push(T val){
          if(index+1==size){
            cout<<"Error : Stack Is Full"<<endl;
            return;
           }
          index++;
          data[index] = val;
        }

        void pop(){
        if(index == -1){
           cout<<"Stack Is Empty"<<endl;
           return;
          }
        index--;
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
