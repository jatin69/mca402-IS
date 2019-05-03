#include "./des.hpp"

/* key HEX is : 133457799bbcdff1 */
int key[64] = {0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1,
               1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1,
               1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1};


void test_ECB();

int main(){
  test_ECB();    

  cout << "Press Enter to exit ... ";
  cin.ignore();
  return 0;
}