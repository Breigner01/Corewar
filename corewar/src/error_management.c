/*
** EPITECH PROJECT, 2020
** error_management.c
** File description:
** Coline SEGURET's error_management.c made the 05/09/2020
*/

#include "corewar.h"
#include "vm_struct.h"
#include "vm_prototypes.h"
#include <string.h> //2 strdup

int is_num(char *str);
int display_error(char *str);
void attribute_prognumber(param_t *param);

elem_t *add_elem(int n, int a, elem_t *actual);
elem_t *param_list(int n, int a);

static int error_progNumber(char *av, int *index, param_t *param)
{
    int nbProg = 0;

    if (param->values[PROGNUMBER] == 0) {
        if (!av || is_num(av))
            return (display_error(err[ERR_PROGNUMBER]));
        nbProg = getnbr(av);
        if (!(1 <= nbProg && nbProg <= 4))
            return (display_error(err[ERR_PROGNUMBER]));
        if (param->prog[nbProg - 1])
            return (display_error(err[ASS_PROGNUMBER]));
        param->values[PROGNUMBER] = nbProg;
        param->prog[nbProg - 1] = true;
        *index += 1;
        return (0);
    } else
        return (display_error(err[TM_PROGNUMBER]));
}

static int error_address(char *av, int *index, param_t *param)
{
    int address = 0;

    if (param->values[ADDRESS] == -1) {
        if (!av || is_num(av))
            return (display_error(err[POS_ADRESS]));
        address = getnbr(av);
        param->values[ADDRESS] = address;
        *index += 1;
        return (0);
    } else
        return (display_error(err[TM_ADRESS]));
}

static int error_dump(char *av, int *index, param_t *param)
{
    int dump = 0;

    if (param->values[DUMP] == 0) {
        if (!av || is_num(av))
            return (display_error(err[POS_DUMP]));
        dump = getnbr(av);
        param->values[DUMP] = dump;
        *index += 1;
        return (0);
    } else
        return (display_error(err[TM_DUMP]));
}

static int is_champs(char *av, param_t *param, elem_t **ch)
{
    int fd = open(av, O_RDONLY);
    char *buffer = 0;
    size_t len = 0;
    vm_t vm = init_vm();

    if (fd < 0)
        return (display_error(err[NOP_OPEN]));
    if (param->values[PROGNUMBER] == 0)
        attribute_prognumber(param);
    if (*ch == NULL)
        *ch = param_list(param->values[0], param->values[1]);
    else
        *ch = add_elem(param->values[0], param->values[1], *ch);
    (*ch)->fd = fd;
    set_address(*ch);
    if (header_handling(*ch, fd))
        return (1);
    param->values[ADDRESS] = -1;
    param->values[PROGNUMBER] = 0;
    return (0);
}

int loop_error(char **av, param_t *param, elem_t **champs)
{
    for (int i = 1; av[i]; i += 1) {
        if (tabequals(av[i], "-n", sizeof(char))) {
            if (error_progNumber(av[i + 1], &i, param))
                return (1);
            continue;
        }
        if (tabequals(av[i], "-a", sizeof(char))) {
            if (error_address(av[i + 1], &i, param))
                return (1);
            continue;
        }
        if (tabequals(av[i], "-dump", sizeof(char))) {
            if (error_dump(av[i + 1], &i, param))
                return (1);
            continue;
        }
        if (is_champs(av[i], param, champs))
            return (1);
    }
    return (0);
}
