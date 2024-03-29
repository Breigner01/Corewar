/*
** EPITECH PROJECT, 2020
** lldi.c
** File description:
** Coline SEGURET's lldi.c made the 05/15/2020
*/

#include "vm_prototypes.h"

int lldi(vm_t *vm, elem_t *champs)
{
    unsigned char params[4] = {0};
    int value_one = 0;
    int value_two = 0;
    int ind = 0;

    skip_coding_byte(champs, vm, params, 50);
    get_param(params[0], &value_one, vm, champs);
    get_param(params[1], &value_two, vm, champs);
    ind = (int)retrieve_short(vm->mem, (champs->pc + value_one) % IDX_MOD);
    ind += value_two;
    set_carry_flag(ind, champs);
    champs->reg[get_index_reg(vm, champs)] =
    retrieve_int(vm->mem, (champs->pc + ind));
    champs->pc = champs->index_actual;
    return (0);
}
