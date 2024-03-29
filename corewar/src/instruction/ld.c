/*
** EPITECH PROJECT, 2020
** ld.c
** File description:
** Coline SEGURET's ld.c made the 05/15/2020
*/

#include "vm_prototypes.h"

int ld(vm_t *vm, elem_t *champs)
{
    unsigned char params[4] = {0};
    int value = 0;

    skip_coding_byte(champs, vm, params, 5);
    get_param(params[0], &value, vm, champs);
    if (params[0] == REG)
        champs->reg[get_index_reg(vm, champs)] = value;
    else if (params[0] == DIR)
        champs->reg[get_index_reg(vm, champs)] = retrieve_int(vm->mem,
        (champs->pc + value) % IDX_MOD);
    set_carry_flag(value, champs);
    champs->pc = champs->index_actual;
    return (0);
}
