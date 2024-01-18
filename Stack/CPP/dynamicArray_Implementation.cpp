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

        CustomStack(const CustomStack& other) {
          data = other.data;  
          index = other.index;
        }

        bool isempty(){
          return index == -1;
        }

        T top(){
          try {
             if (isempty()) {
                  throw runtime_error("Error: Stack UnderFlow");
              }
              return data[index];
          }catch (const exception& e) {
              cout << e.what()<<" -- Default Value : ";;
              return T();
          }
        }

        void push(T val){
          index++;
          data.push_back(val);
        }

        void pop(){
        if(index == -1){
           cout<<"Stack UnderFlow"<<endl;
           return;
          }
        index--;
        }

        ~CustomStack() {
        // No need
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
    stk.push(6);
    cout<<"---------------------"<<endl;
    CustomStack<long long > obj(stk);
    cout<<obj.top()<<endl;
}