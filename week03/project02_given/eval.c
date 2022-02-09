/* eval.c - tree evaluation and value printing */

#include "ntlang.h"

void eval_error(char *err) {
    printf("eval_error: %s\n", err);
    exit(-1);
}

uint32_t eval(struct parse_node_st *pt) {
    uint32_t v1, v2;

    if (pt->type == EX_INTVAL) {
        v1 = pt->intval.value;
    } else if (pt->type == EX_OPER1) {
        v1 = eval(pt->oper1.operand);
        if (pt->oper1.oper == OP_MINUS) {
            v1 = -v1;
        } else {
            eval_error("Bad operator");
        }
    } else if (pt->type == EX_OPER2) {
        v1 = eval(pt->oper2.left);
        v2 = eval(pt->oper2.right);
        if (pt->oper2.oper == OP_PLUS) {
            v1 = v1 + v2;
        } else if (pt->oper2.oper == OP_MINUS) {
            v1 = v1 - v2;
        } else {
            eval_error("Bad operator");            
        }
    }

    return v1;
}

void eval_print(struct config_st *cp, uint32_t value) {
    /*
     * Handle -b -w -u
     *
     * Use your own conversion functions for uint32_t to string.
     */

    printf("%d\n", value);
}
