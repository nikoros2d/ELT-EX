#include <stdio.h>

int main(){

 int a = 0xDDCCAABB;
 unsigned char c;
 c = (a & 0x000000FF);
 printf("first byte = %x\n",c);
 c = ((a >> 8) & (0xFF));
 printf("second byte = %x\n",c);
 c = ((a >> 16) & (0xFF));
 printf("third byte = %x\n",c);
 c = ((a >> 24) & (0xFF));
 printf("fourth byte = %x\n",c);
 a = a & 0xFF99FFFF; 
 printf("changed a = %x\n",a);
}
