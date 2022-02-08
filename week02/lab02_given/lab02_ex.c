/* lab02.c - initial parsing implemenation */

#include "ntlang.h"

int main(int argc, char **argv) {
    struct scan_table_st scan_table;
    char *input;

    /* This first part is from lab01_start/scan2.c */
    
    /* Parse tree construction manually */
    
    struct parse_node_st node1;
    struct parse_node_st node2;
    struct parse_node_st node3;

    node1.type = EX_INTVAL;
    node1.intval.value = 1;

    node2.type = EX_INTVAL;
    node2.intval.value = 2;

    node3.type = EX_OPER2;
    node3.oper2.oper = OP_PLUS;
    node3.oper2.left = &node1;
    node3.oper2.right = &node2;

    parse_tree_print(&node3);
    printf("\n");
    
    /* Parse tree construction from parse_table */
    struct parse_node_st *np1, *np2, *np3;
    struct parse_table_st parse_table;

    parse_table_init(&parse_table);

    np1 = parse_node_new(&parse_table);
    np1->type = EX_INTVAL;
    np1->intval.value = 3;

    np2 = parse_node_new(&parse_table);
    np2->type = EX_INTVAL;
    np2->intval.value = 4;

    np3 = parse_node_new(&parse_table);
    np3->type = EX_OPER2;
    np3->oper2.oper = OP_PLUS;
    np3->oper2.left = np1;
    np3->oper2.right = np2;

    parse_tree_print(np3);
    printf("\n");

    return 0;
}
