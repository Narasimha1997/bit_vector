#ifndef __BIT_VECTOR_H
#define __BIT_VECTOR_H

#include<bit.h>

#include<stdlib.h>
#include<stdint.h>


bit_group_t * create_bit_vector(unsigned int size) {
    unsigned int n_bit_group_size = (size / 8 + (!! (size % 8)));
    bit_group_t * n_bit_group = (bit_group_t *)calloc(n_bit_group_size, sizeof(unsigned char));

    return n_bit_group;
}

void set_bit(bit_group_t * bit_vector, unsigned int position) {
    unsigned int bit_group_number = position / 8;
    uint8_t bit_position = position % 8;

    set_bit_in_group(&bit_vector[bit_group_number], bit_position);
}

void reset_bit(bit_group_t * bit_vector, unsigned int position) {
     unsigned int bit_group_number = position / 8;
     uint8_t bit_position = position % 8;

     reset_bit_in_group(&bit_vector[bit_group_number], bit_position);
}

uint8_t check_is_set(bit_group_t * bit_vector, unsigned int position) {
    return is_set_in_group(
        &bit_vector[position / 8],
        position % 8
    );
}

unsigned int get_n_bits_set(bit_group_t * bit_vector, unsigned int size) {
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

void free_bit_vector(bit_group_t * bit_vector) {
    free(bit_vector);
}

#endif