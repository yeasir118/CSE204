#include <bits/stdc++.h>
using namespace std;

int DEFAULT_SIZE = 10;

class Array{
	int sz;
	int* root;
	int curr;
public:
	Array();
	Array(int);
	Array(int*, int);

	int* get_array();
	int get_curr();
	int get_sz();
	int get_an_element(int);
	void add_element(int);
	void add(int,int);
	vector<int> find_index(int);
	vector<int> sub_array(int,int);
	void remove(int);

	void print();
	~Array();
};

Array::Array(){
	sz = DEFAULT_SIZE;
	curr = 0;
	root = new int[sz];
	for(int i=0;i<sz;i++){
		root[i] = -1;
	}
}

Array::Array(int n){
	sz = n;
	curr = 0;
	root = new int[sz];
	for(;curr<sz;curr++){
		root[curr] = -1;
	}
}

Array::Array(int* arr, int n){
	sz = n;
	curr = 0;
	root = new int[sz];
	for(int i=0;i<sz;i++){
		root[curr++] = arr[i];
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

int Array::get_curr(){return curr;}
int Array::get_sz(){return sz;}

int Array::get_an_element(int i){
	if(i>=sz) return -33;
	return root[i];
}

void Array::add_element(int element){
	if(curr < sz){
		root[curr++] = element;
	}else{
		int temp_arr[sz];
		for(int i=0;i<sz;i++){
			temp_arr[i] = root[i];
		}
		delete[] root;

		sz += DEFAULT_SIZE;
		root = new int[sz];
		for(int i=0;i<sz;i++){
			if(i < sz-DEFAULT_SIZE) root[i] = temp_arr[i];
			else root[i] = -1;
		}
		root[curr++] = element;
	}
}

void Array::add(int pos, int element){
	if(curr == sz){
		int temp_arr[sz];
		for(int i=0;i<sz;i++){
			temp_arr[i] = root[i];
		}
		delete[] root;

		sz += DEFAULT_SIZE;
		root = new int[sz];
		for(int i=0;i<sz;i++){
			if(i < sz-DEFAULT_SIZE) root[i] = temp_arr[i];
			else root[i] = -1;
		}
	}

	for(int i=curr;i>pos;i--){
		root[i] = root[i-1];
	}
	root[pos] = element;
	curr++;
}

vector<int> Array::find_index(int element){
	vector<int> ret;
	for(int i=0;i<curr;i++){
		if(root[i] == element){
			ret.push_back(i);
		}
	}
	return ret;
}

vector<int> Array::sub_array(int start, int end){
	vector<int> ret(end-start);
	for(int i=start;i<end;i++){
		ret[i-start] = root[i];
	}
	return ret;
}

void Array::remove(int element){
	for(int i=0;i<curr;i++){
		if(root[i] == element){
			int j = i;
			for(;j<curr-1;j++){
				root[j] = root[j+1];
			}
			root[j] = -1;
			curr--;
		}
	}
}

// doesn't work
// gives double free error
// probably because roots inside a1, a2 gets deleted once out of function scope
// and then again at the end of the main function
vector<int> merge(Array a1, Array a2){
	vector<int> res(a1.get_curr() + a2.get_curr());
	int p1 = 0, p2 = 0;
	for(int i=0;i<res.size();i++){
		if(p1 == a1.get_curr()){
			while(p2 < a2.get_curr()){
				res[i++] = a2.get_array()[p2++]; 
			}
		}else if(p2 == a2.get_curr()){
			while(p1 < a1.get_curr()){
				res[i++] = a1.get_array()[p1++];
			}
		}else if(a1.get_array()[p1] < a2.get_array()[p2]){
			res[i] = a1.get_array()[p1++];
		}else{
			res[i] = a2.get_array()[p2++];
		}
	}
	return res;
}

Array::~Array(){
	delete[] root;
}

int main(){

	Array arr;
	arr.print();

	Array arr1(5);
	arr1.print();

	int nums[] = {1, 32, 2, 33, 3};
	Array arr2(nums, 5);
	arr2.print();

	int* arr_ptr = arr2.get_array();
	arr_ptr[1] = 33;
	arr2.print();

	cout<<arr2.get_an_element(1)<<endl;
	cout<<arr2.get_an_element(6)<<endl;

	for(int i=0;i<20;i++){
		arr2.add(1, i * 10);
		arr2.print();
	}

	vector<int> indices = arr2.find_index(33);
	for(int i=0;i<indices.size();i++){
		cout<<indices[i]<<" ";
	}
	cout<<endl;

	vector<int> sub_array = arr2.sub_array(5, 12);
	for(int i=0;i<sub_array.size();i++){
		cout<<sub_array[i]<<" ";
	}
	cout<<endl;

	// int sorted1[] = {1, 2, 3, 4, 5};
	// Array sorted1_arr(sorted1, 5);
	// int sorted2[] = {6, 7, 8, 9, 10};
	// Array sorted2_arr(sorted2, 5);

	// vector<int> sorted = merge(sorted1_arr, sorted2_arr);
	// for(int i=0;i<sorted.size();i++){
	// 	cout<<sorted[i]<<" ";
	// }
	// cout<<endl;

	arr2.remove(33);
	arr2.print();

	return 0;
}
