#include<bit_vector.h>
#include<stdio.h>

int main(int argc, char const *argv[])
{
    bit_group_t * bit_vector = create_bit_vector(64);
    set_bit(bit_vector, 15);
    set_bit(bit_vector, 10);
    set_bit(bit_vector, 0);
    set_bit(bit_vector, 20);
    set_bit(bit_vector, 33);
    set_bit(bit_vector, 63);

    printf("-------Tests---------\n");
    
    int count = get_n_bits_set(bit_vector, 64);
    printf("Count test :  %d\n", count);
    printf("is set test : %d\n", check_is_set(bit_vector, 32));
    printf("\nReset test\n");
    reset_bit(bit_vector, 20);
    printf("Bit at position 20 : %d\n", check_is_set(bit_vector, 20));

    return 0;
}
