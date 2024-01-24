#include "bitFields.h"
#include <assert.h>

int getBit(int bn,unsigned long val) {
	// TODO:
	//		check to make sure bn is a valid bit position in long (you may assert this is true)

	assert(bn >= 0 && bn < (sizeof(unsigned long) * 8)); //bn is a position mus be greater than one.
														// and it must be smaller than the bit size
	//		If the bit in val at position bn is 1, return 1
	if (val & (1UL << bn)) // sifts left 1 by bn and than and opertor with val. If its sth other than 0  its true.
	{
        return 1;
    }
	
	//		otherwise return 0.
	return 0; 
}

void setBit(int bn,int new,unsigned long *val) {
	// TODO:
	//		check to make sure bn is a valid bit position in long (you may assert this is true)
	assert(bn >= 0 && bn < (sizeof(unsigned long) * 8));
	
	//		if new is true, set the bit in val at bn to 1
	// 		Bitwise OR is used when you want to set a specific 
	//		bit or bits to 1 while leaving the other bits unchanged. 
	if (new!=0) 
	{
		*val |= (1UL << bn);
	}
	//     otherwise, set the bit in val at bn to 0
	//     Bitwise AND, is used 
	//	   when you want to clear a specific bit or 
	//	   bits to 0 while leaving the other bits unchanged. 
	else 
	{
		*val &= ~(1UL << bn);
	}
}

long getBitFld(int bs,int len,unsigned long val) {
	// TODO:
	//		check to make sure bs is a valid bit position in long (you may assert this is true)
	assert(bs >= 0 && bs < (sizeof(unsigned long) * 8));
	//		check to make sure len is a valid length for a subfield that starts at bs (you may assert this is true)
	assert(len>0);
	assert(len<=bs+1);

	//i//nt max_len = sizeof(unsigned long) * 8 -bs;
	//if(len> max_len)
	//{
	//	len= max_len;
	//}
	
	//assert(len >= 0 && bs +len <= (sizeof(unsigned long)*8));
	// 		perform an unsigned getBitFldU to extract the unsigned version of the field
	unsigned long unsignedField = getBitFldU(bs, len, val);
	//		get the high order bit of the result... that's the "sign" bit
	unsigned long signBit = 1UL << (len - 1);
	//		if the sign bit not zero, replace the 0 padding with 1 padding
	if(signBit != 0)
	{
		unsigned long mask = (1UL << len) - 1;	// To get a bit field that contains `n` bits, 
												// right justified, you can use the bit-twiddle: `(1L<<n)-1`.
		unsignedField |= ~(mask);
	}
	return (long) unsignedField; // replace this with the correct code
}
unsigned long getBitFldU(int bs,int len,unsigned long val) {
	// TODO:
	// Check to make sure bs is a valid bit position in long
	assert(bs >= 0 && bs < (sizeof(unsigned long) * 8));
	// Check to make sure len is a valid length for a subfield that starts at bs
	assert(len>0);
	assert(len<=bs+1);
	//int max_len = sizeof(unsigned long) * 8 - bs;
	//if(len> max_len)
	//{
	//	len= max_len;
	//}
	
	// 		make a mask that has len 1's
	//unsigned long mask = (1UL << len) - 1;

	unsigned long mask = ((1UL << len) - 1); 
	// 		Shift that mask left so it's leftmost 1 starts at bs
	mask <<= (bs-len+1);
	//      bitwise and the mask and val to isolate the bit field bits
	unsigned long field = val & mask;
	//		Shift the result to the right so that the rightmost bit of the bit field is bit 0
	field >>= (bs-len+1);
	//			Note that shift right pads to the left with the sign bit if the field is signed, but
	//			for unsigned, it will pad to the left with 0
	return field; // replace this with the correct code
}

void setBitFld(int bs,int len,unsigned long new,unsigned long *val) {
	// TODO:
	//		check to make sure bs is a valid bit position in long (you may assert this is true)
	 assert(bs >= 0 && bs < (sizeof(unsigned long) * 8));

	//		check to make sure len is a valid length for a subfield that starts at bs (you may assert this is true)
	int max_len = sizeof(unsigned long) * 8 -bs ;
	if(len> max_len)
	{
		len= max_len;
	}
	assert(len>=0);
	//assert(len >= 0 && len <= (sizeof(unsigned long) * 8 - bs));
	//      Make a mask that has len bits, right justified

	//unsigned long mask = ((1UL << len) - 1) << bs;
	unsigned long mask = ((1UL << len) - 1);

	//		Use mask to turn off any bits to the left of the bitField values in new
	 new &= mask;
	// 		Shift both the new value and the mask to the correct bit position
    mask <<= (bs-len+1);
	new <<= (bs-len+1);
	//		Turn off all bits in *val under the mask by bitwise anding with ~mask
	*val &= ~mask;
	//		Or *val with new.  (new has zeros for all non bit field positions, so won't affect val)
	*val |= new;
}
