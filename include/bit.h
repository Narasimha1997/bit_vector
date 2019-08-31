#ifndef __BIT_H
#define __BIT_H

#include<stdint.h>

typedef unsigned char bit_group_t; 

static inline void set_bit_in_group(bit_group_t * group, uint8_t position) {
    bit_group_t group_ =  * group;
    //set bit at position positon 
    * group =  ( (group_) | (1 <<  position) );
}

static inline void reset_bit_in_group(bit_group_t * group, uint8_t positon) {
    bit_group_t group_ = * group;
    * group = ( (group_ ) & ( ~ (1 << positon) ) );
}

static inline uint8_t n_bits_set_in_group(bit_group_t * group) {
    bit_group_t  group_ = *group;
    uint8_t count = 0;
    while(group_ != 0) {
        if((group_ & 1) == 1) count ++;
        group_ = group_ >> 1;
    }
    return count;
}

static inline uint8_t is_set_in_group(bit_group_t * group, uint8_t position) {
    bit_group_t group_ = * group;
    return ( group_ & (1 << position) );
}

static inline void toggle_bit_in_group(bit_group_t * group, uint8_t position) {
    bit_group_t group_ = * group;
    * group = ( group_ ^ (1 << position));
}

#endif