#include <assert.h>
#include <getopt.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cachelab.h"

#define address_bits 64

typedef cache_line* data_t;
typedef struct linklist_node {
    struct linklist_node* prev;
    struct linklist_node* next;
    data_t data;
} linklist_node;

typedef struct linklist {
    linklist_node* head;
    linklist_node* tail;
} linklist;

void init_linklist(linklist* l);
void print_help_message(char* program_name);

typedef struct cache_line {
    char valid;  // valid bit is the lowest 1 bit

    // since addresses are 64 bits, tag bits won't be greater than 64 bits
    int64_t tag;

    // We just need to print a hit/miss result
    // So we don't need to actually store the data
    // char* block;
} cache_line;
typedef struct cache {
    linklist* sets;  // an array of lisklists
    int line_num;
    int set_index_bits;
    int associativity;
    int block_bits;
} cache;

int set_index_bits = 0, associativity = 0, block_bits = 0, verbose = 0;
int tag_bits = 0;
int set_num = 0;
int hit_cnt = 0, miss_cnt = 0, eviction_cnt = 0;
cache c;

void init_cache();

int main(int argc, char** argv) {
    int option;
    char* tracefile = NULL;

    while ((option = getopt(argc, argv, "s:E:b:t:hv")) != -1) {
        switch (option) {
            case 'h':
                print_help_message(argv[0]);
                break;
            case 's':
                // optarg is a pointer points to somewhere in argv
                // so it's safe to reassign this variable
                set_index_bits = atoi(optarg);
                break;
            case 'E':
                associativity = atoi(optarg);
                break;
            case 'b':
                block_bits = atoi(optarg);
                break;
            case 't':
                tracefile = optarg;
                break;
            case 'v':
                verbose = 1;
                break;

            default:
                abort();
        }
    }

    if (!tracefile || !associativity || !set_index_bits || !block_bits) {
        printf("%s: Missing required command line argument\n", argv[0]);
        return -1;
    }

    printf("%d %d %d %s\n", set_index_bits, associativity, block_bits,
           tracefile);

    tag_bits = address_bits - (block_bits + set_index_bits);
    assert(tag_bits > 0);
    set_num = (int)pow(2, set_index_bits);
    cache* c = init_cache();

    printSummary(0, 0, 0);
    return 0;
}

void print_help_message(char* program_name) {
    printf(
        "Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n"
        "Options:\n"
        "  -h         Print this help message.\n"
        "  -v         Optional verbose flag.\n"
        "  -s <num>   Number of set index bits.\n"
        "  -E <num>   Number of lines per set.\n"
        "  -b <num>   Number of block offset bits.\n"
        "  -t <file>  Trace file."
        "\n"
        "Examples:\n"
        "  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n"
        "  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n",
        program_name, program_name, program_name);
}

void init_linklist(linklist* l) {
    l->head = malloc(sizeof(linklist_node));
    l->tail = malloc(sizeof(linklist_node));
    *(l->head) = (linklist_node){.next = l->tail, .prev = NULL, .data = NULL};
    *(l->tail) = (linklist_node){.next = NULL, .prev = l->head, .data = NULL};
}

void init_cache() {
    c.sets = malloc(sizeof(linklist) * set_num);
    for (int i = 0; i < set_num; i++) {
        linklist* set = &(c.sets[i]);
        init_linklist(set);

        for (int j = 0; j < associativity; j++) {
            linklist_node* node = malloc(sizeof(linklist_node));

            // insert a new node to the beginning of the linklist
            node->next = set->head->next;
            node->prev = set->head;
            set->head->next->prev = node;
            set->head->next = node;

            // init cache line
            node->data = malloc(sizeof(cache_line));
            *(node->data) = (cache_line){.valid = 0, .tag = 0};
        }
    }
}

cache_line* read_cache(int64_t address, int size) {
    int64_t set_index = (address >> c.block_bits) & (1 << c.set_index_bits - 1);
}

void search_lines(linklist* set) {
    linklist_node* cur = set->head->next;
    int miss = 0, hit = 0, eviction = 0;
    while (cur != set->tail) {
        cache_line* line = cur->data;
        // it is not possible that a valid line is located after an invalid line
        if (!line->valid) {
            miss = 1;
        }
    }
