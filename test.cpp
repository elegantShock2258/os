#include <bits/stdc++.h>
using namespace std;


void setNthBit(unsigned int *data, int n, bool value) {
  if (value) {
    *data |= (1 << n);
  } else {
    *data &= ~(1 << n);
  }
}

int main() {
  unsigned int n = 0x00000000;
  // print the binary representation of n
  for (int i = 0; i < 32; i++) {
    cout << bitset<32>(n) << endl;
    cout << findFirstUnSetBit(n) << endl;
    setNthBit(&n, 31 - i, true);
  }
  cout << bitset<32>(n) << endl;
  cout << findFirstUnSetBit(n) << endl;
}