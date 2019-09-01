#ifndef __BIT_VECTOR_H
#define __BIT_VECTOR_H

#include<bit.h>

#include<stdlib.h>
#include<stdint.h>


static inline bit_group_t * create_bit_vector(unsigned int size) {
    unsigned int n_bit_group_size = (size / 8 + (!! (size % 8)));
    bit_group_t * n_bit_group = (bit_group_t *)calloc(n_bit_group_size, sizeof(unsigned char));

    return n_bit_group;
}

static inline void set_bit(bit_group_t * bit_vector, unsigned int position) {
    unsigned int bit_group_number = position / 8;
    uint8_t bit_position = position % 8;

    set_bit_in_group(&bit_vector[bit_group_number], bit_position);
}

static inline void reset_bit(bit_group_t * bit_vector, unsigned int position) {
     unsigned int bit_group_number = position / 8;
     uint8_t bit_position = position % 8;

     reset_bit_in_group(&bit_vector[bit_group_number], bit_position);
}

static inline uint8_t check_is_set(bit_group_t * bit_vector, unsigned int position) {
    return is_set_in_group(
        &bit_vector[position / 8],
        position % 8
    );
}

static inline unsigned int get_n_bits_set(bit_group_t * bit_vector, unsigned int size) {
    bit_group_t * vector_ptr = bit_vector;
    unsigned int count = 0, iter_ =  0 ;
    size = (size / 8 + (!! (size % 8)));
    while(iter_ < size) {
        count += n_bits_set_in_group(vector_ptr);
        vector_ptr ++;
        iter_ ++;
    }
    return count;
}

static inline void toggle_bit(bit_group_t * bit_vector, unsigned int position) {
    unsigned int bit_group_number = position / 8;
    uint8_t bit_position = position % 8;

    toggle_bit_in_group(&bit_vector[bit_group_number], bit_position);
}

static inline unsigned int compare_bit_vectors(
    bit_group_t * bit_vector_a,  
    bit_group_t * bit_vector_b, 
    unsigned int lower_bound, 
    unsigned int upper_bound) {

        //this routine checks whether the bit vectors a and b are same within the given region
        //bounded by upper and lower bounds
        //returns 0 if not equal, returns 1 constant if equal, -1 if there are bounding errors
        if(lower_bound > upper_bound) return -1;
        if(lower_bound % 8 != 0 || upper_bound % 8 != 0) return -1;
        unsigned int iter_ = 0, xor_sum = 0;
        int lower_group = lower_bound / 8, n_scan_groups = (upper_bound - lower_bound) / 8;
        for(iter_ = 0; iter_ < n_scan_groups; iter_++) 
            xor_sum += bit_vector_a[lower_bound + iter_] ^ bit_vector_b[lower_bound + iter_];
        
        return (xor_sum == 0) ? 1 : 0;
}

static inline void reset_all_bits(
    bit_group_t * bit_vector, 
    unsigned int lower_bound, 
    unsigned int upper_bound) {

        if(lower_bound > upper_bound) return -1;
        if(lower_bound % 8 != 0 || upper_bound % 8 != 0) return -1;
        unsigned int iter_ = 0;
        for(iter_ = (lower_bound) / 8; iter_ < (upper_bound - lower_bound) / 8; iter_ ++) bit_vector[iter_] &= 0x00;
}

static inline void set_all_bits(
    bit_group_t * bit_vector, 
    unsigned int lower_bound,
    unsigned int upper_bound) {
        if(lower_bound > upper_bound) return -1;
        if(lower_bound % 8 != 0 || upper_bound % 8 != 0) return -1;
        unsigned int iter_ = 0;
        for(iter_ = (lower_bound) / 8; iter_ < (upper_bound - lower_bound) / 8; iter_ ++) bit_vector[iter_] |= 0xff;
}

static inline unsigned int get_remaining_bits(bit_group_t * bit_vector, unsigned int length) {
    return (length - get_n_bits_set(bit_vector, length));
}

static inline unsigned int has_free_capacity(bit_group_t * bit_vector, unsigned int length) {
    return (
        (get_n_bits_set(bit_vector, length) >= length) ? 0 : 1
    );
}

static inline void free_bit_vector(bit_group_t * bit_vector) {
    free(bit_vector);
}

#endif