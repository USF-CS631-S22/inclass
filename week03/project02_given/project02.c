/* project02.c - initial parsing implemenation */

#include "ntlang.h"

int main(int argc, char **argv) {
    struct config_st config;
    struct scan_table_st scan_table;
    struct parse_table_st parse_table;
    struct parse_node_st *parse_tree;
    uint32_t value;
    
    if (argc != 2) {
        printf("Usage: project02 <expression>\n");
        printf("  Example: project02 \"1 + 2\"\n");
        exit(-1);
    }

    strncpy(config.input, argv[1], SCAN_INPUT_LEN);

    scan_table_init(&scan_table);
    scan_table_scan(&scan_table, config.input);
    scan_table_print(&scan_table);
    printf("\n");
    
    parse_table_init(&parse_table);
    parse_tree = parse_program(&parse_table, &scan_table);
    parse_tree_print(parse_tree);
    printf("\n");

    value = eval(parse_tree);
    eval_print(&config, value);

    return 0;
}
