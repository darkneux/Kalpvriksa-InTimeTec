#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class CustomStack{
	    vector<T> data;
        int index;
    public:

        CustomStack(){  
          this->index = -1;
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
          index++;
          data.push_back(val);
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