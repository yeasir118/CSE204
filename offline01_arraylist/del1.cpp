#include <bits/stdc++.h>
using namespace std;

void swap(int& a, int& b){
  int temp = a;
  a = b;
  b = temp;
}

int main(){
  vector<int> nums = {2, 0, 2, 1, 1, 0};
  swap(nums[0], nums[1]);
  for(int i=0;i<6;i++){
    cout<<nums[i]<<endl;
  }
  return 0;
}