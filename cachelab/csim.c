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

typedef struct cache_line {
    char valid;  // valid bit is the lowest 1 bit

    // since addresses are 64 bits, tag bits won't be greater than 64 bits
    int64_t tag;

    // We just need to print a hit/miss result
    // So we don't need to actually store the data
    // char* block;
} cache_line;

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

typedef struct cache {
    linklist* sets;  // an array of lisklists
    int line_num;
    int set_index_bits;
    int associativity;
    int block_bits;
    int tag_bits;
    int set_num;
} cache;

int verbose = 0;
int hit_cnt = 0, miss_cnt = 0, eviction_cnt = 0;
cache c;

void init_linklist(linklist* l);
void print_help_message(char* program_name);
void init_cache();
cache_line* read_cache(linklist* set, int64_t tag);
linklist_node* search_lines(linklist* set, int64_t tag);
void move_node_to_head(linklist* set, linklist_node* node);
linklist_node* load_address(linklist* set, int64_t tag);

int main(int argc, char** argv) {
    int option;
    char* tracefile = NULL;

    c = (cache){NULL, 0, 0, 0, 0, 0, 0};

    while ((option = getopt(argc, argv, "s:E:b:t:hv")) != -1) {
        switch (option) {
            case 'h':
                print_help_message(argv[0]);
                break;
            case 's':
                // optarg is a pointer points to somewhere in argv
                // so it's safe to reassign this variable
                c.set_index_bits = atoi(optarg);
                break;
            case 'E':
                c.associativity = atoi(optarg);
                break;
            case 'b':
                c.block_bits = atoi(optarg);
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

    if (!tracefile || !c.associativity || !c.set_index_bits || !c.block_bits) {
        printf("%s: Missing required command line argument\n", argv[0]);
        return -1;
    }

    c.tag_bits = address_bits - (c.block_bits + c.set_index_bits);
    assert(c.tag_bits > 0);
    c.set_num = (int)pow(2, c.set_index_bits);
    // printf(
    //     "set_index_bits: %d\n"
    //     "set_num: %d\n"
    //     "associativity: %d\n"
    //     "block_bits: %d\n"
    //     "tag_bits: %d\n",
    //     c.set_index_bits, c.set_num, c.associativity, c.block_bits,
    //     c.tag_bits);
    init_cache();

    FILE* fp;
    int ch;
    char buf[30];
    char action;
    int64_t address;
    int size;
    fp = fopen(tracefile, "r");
    // read 1 char, skip if not a space
    while ((ch = getc(fp)) != EOF) {
        fgets(buf, 30, fp);
        if (ch != ' ') {
            continue;
        }
        sscanf(buf, "%c %lx,%d", &action, &address, &size);
        int64_t set_index =
            (address >> c.block_bits) & ((1 << c.set_index_bits) - 1);
        int64_t tag = (address >> c.block_bits) >> c.set_index_bits;
        // printf("set_index: %ld, tag: %ld\n", set_index, tag);
        linklist* set = &(c.sets[set_index]);
        printf("%c %lx,%d", action, address, size);
        switch (action) {
            case 'L':
                read_cache(set, tag);
                break;
            case 'S':
                read_cache(set, tag);
                break;
            case 'M':
                read_cache(set, tag);
                // for now, write is equal to read
                read_cache(set, tag);
                break;

            default:
                abort();
        }
        printf(" \n");
    }

    printSummary(hit_cnt, miss_cnt, eviction_cnt);
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
    c.sets = malloc(sizeof(linklist) * c.set_num);
    for (int i = 0; i < c.set_num; i++) {
        linklist* set = &(c.sets[i]);
        init_linklist(set);

        for (int j = 0; j < c.associativity; j++) {
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

cache_line* read_cache(linklist* set, int64_t tag) {
    linklist_node* node = search_lines(set, tag);
    if (node == NULL) {
        node = load_address(set, tag);
    }
    move_node_to_head(set, node);
    return NULL;
}

linklist_node* search_lines(linklist* set, int64_t tag) {
    linklist_node* cur = set->head->next;
    // int miss = 0, hit = 0, eviction = 0;
    while (cur != set->tail) {
        cache_line* line = cur->data;
        // it is not possible that a valid line is located after an invalid line
        if (!line->valid) {
            if (verbose) printf(" miss");
            miss_cnt++;
            return NULL;
        }
        if (line->tag == tag) {
            if (verbose) printf(" hit");
            hit_cnt++;
            return cur;
        }
        cur = cur->next;
    }
    if (verbose) printf(" miss eviction");
    miss_cnt++;
    eviction_cnt++;
    return NULL;
}

// move a linklist node to its head
void move_node_to_head(linklist* set, linklist_node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = set->head;
    node->next = set->head->next;
    set->head->next->prev = node;
    set->head->next = node;
}

linklist_node* load_address(linklist* set, int64_t tag) {
    // get the LRU line (the last node in the linklist)
    linklist_node* node = set->tail->prev;
    cache_line* line = node->data;
    // overwrite this line with new tag
    if (!line->valid) line->valid = 1;
    line->tag = tag;

    return node;
}
