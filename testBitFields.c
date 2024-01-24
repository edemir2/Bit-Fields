#include "bitFields.h"
#include <stdio.h>
#include <assert.h>

/*---------------------------------------------------------
Internal Function Declarations
-----------------------------------------------------------*/
char * char2bin(unsigned char in);
char * nibble2bin(unsigned char in);

/*---------------------------------------------------------
Global Variables 
----------------------------------------------------------*/
char * bits[]={"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};

int main(int argc, char **argv) {

	// Unit test for the bitFields functions

	unsigned long val=0xdeadbeefdeafc0de;

	printf("testing deadbeef bits...");
	for(int i=63;i>=0;i--) {
		printf("%c",getBit(i,val)?'1':'0');
		if (0==i%4) printf(" ");
	}

	printf("\nexpected deadbeef bits: ");
	for(int c=sizeof(val)-1;c>=0;c--) {
		printf("%s ",char2bin((unsigned char)(val>>(c*8)%256)));
	}
	printf("\n");

	unsigned long newBeef=0;
	for(int i=0;i<64;i++) setBit(i,getBit(i,val),&newBeef);
	printf("Setting deadbeef bits: %lx\n",newBeef);

	// Testing get/set fields using nibbles

	printf("setting deadbeef by nibbles...");
	for (int i=63;i>=0;i-=4) { printf("%lx ",getBitFldU(i,4,val)); }
	printf("\n");

	printf("getting signed deadbeef by nibbles...");
	for (int i=63;i>=0;i-=4) { printf("%x ",(unsigned char)getBitFld(i,4,val)); }
	printf("\n");

	newBeef=0;
	for (int s=63;s>=0;s-=4) setBitFld(s,4,getBitFldU(s,4,val),&newBeef);
	printf("deadbeef set by nibbles: %lx\n",newBeef);

	newBeef=0;
	for (int s=63;s>=0;s-=4) setBitFld(s,4,getBitFld(s,4,val),&newBeef);
	printf("deadbeef set by signed nibbles: %lx\n",newBeef);

	printf("getting/setting deadbeef by groups of 3 bits: \n");
	newBeef=0;
	for(int s=63;s>=0;s-=3) {
		unsigned char val3=0;
		if (s>1) val3=getBitFldU(s,3,val);
		else val3=getBitFldU(s,s+1,val);
		printf("%s ",nibble2bin(val3));
		if (s>1) setBitFld(s,3,val3,&newBeef);
		else setBitFld(s,s+1,val3,&newBeef);
	}
	printf("\n");
	printf("deadbeef set by 3 bit groups: %lx\n",newBeef);
	

	return 0;
}

char * char2bin(unsigned char in) {
	static char answer[10]={0x00};
	sprintf(answer,"%s %s",bits[in/16],bits[in%16]);
	return answer; // User warning... result will change next time char2bin is invoked!
}

char * nibble2bin(unsigned char in) {
	assert(0<=in && in<16);
	static char answer[5]={0x00};
	sprintf(answer,"%s",bits[in]); 
	return answer; // User warning... result will change next time nibble2bin is invoked!
}