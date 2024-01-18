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

         
        CustomStack(const CustomStack& other) {
          size = other.size;
          index = other.index;
          data = new T[size];
          for (int i = 0; i <= index; ++i) {
              data[i] = other.data[i];
          }
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
          if(index+1==size){
            cout<<"Error : Stack OverFlow"<<endl;
            return;
           }
          index++;
          data[index] = val;
        }

        void pop(){
        if(index == -1){
           cout<<"Stack UnderFlow"<<endl;
           return;
          }
        index--;
        }
        
        ~CustomStack() {
        delete[] data;
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
    cout<<obj.top()<<endl;

}
