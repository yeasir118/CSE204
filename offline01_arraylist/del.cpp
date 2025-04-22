#include "iostream"
using namespace std;

class Array{
	int sz;
	int* root;
public:
	Array();
	Array(int);
	Array(int*, int);

	int* get_array();
	int get_an_element(int);
	void print();
	~Array();
};

Array::Array(){
	sz = 10;
	root = new int[sz];
	for(int i=0;i<sz;i++){
		root[i] = 0;
	}
}

Array::Array(int n){
	sz = n;
	root = new int[sz];
	for(int i=0;i<sz;i++){
		root[i] = 0;
	}
}

Array::Array(int* arr, int n){
	sz = n;
	root = new int[sz];
	for(int i=0;i<sz;i++){
		root[i] = arr[i];
	}
}

void Array::print(){
	for(int i=0;i<sz;i++){
		cout<<root[i]<<" ";
	}
	cout<<endl;
}

int* Array::get_array(){
	return root;
}

int Array::get_an_element(int i){
	if(i>=sz) return -33;
	return root[i];
}

Array::~Array(){
	delete[] root;
}

int main(){

	Array arr;
	arr.print();

	Array arr1(5);
	arr1.print();

	int nums[] = {1, 2, 3};
	Array arr2(nums, 3);
	arr2.print();

	int* arr_ptr = arr2.get_array();
	arr_ptr[1] = 33;
	arr2.print();

	cout<<arr2.get_an_element(1)<<endl;
	cout<<arr2.get_an_element(6)<<endl;

	return 0;
}
