#include <stdio.h>
int main(){
 int a = 0xDDCCAABB;
 int* ptr = &a;
 printf("first byte = %x\n",*ptr & 0xff);
 printf("second byte = %x\n",*ptr>>8 & 0xff);
 printf("third byte = %x\n",*ptr>>16 & 0xff);
 printf("fourth byte = %x\n",*ptr>>24 & 0xff);
 *ptr = *ptr & 0xff88ffff; 
 printf("changed a = %x\n",a);
}
