//
//  cache_manager.c
//  test_project
//
//  Created by Pavlov Evgeny on 06.06.12.
//  Copyright (c) 2012. All rights reserved.
//

#include "cache_manager.h"

unsigned int hash (const char *name) 
{
    unsigned int hash = 0;
    unsigned int c;
    while (c = *name++) 
        hash = hash * 9 ^ c;
    return hash;
}

struct hash_node * lookup(const char *name)
{
    unsigned int h = hash(name) % NHASH;
    struct hash_node *hn = cache->cache_tab[h];
  
    while (hn) {
        if (!strcmp(hn->name, name)) {
            return hn;
        }
        hn = hn->next;
    }
    return NULL;
}

int add_to_hash_tab(const char *name)
{
    struct hash_node *hn;
    if ((hn = lookup(name)) == NULL) {
        hn = (struct hash_node *)malloc(sizeof(struct hash_node));
        if (hn == NULL)
            return 1;
        hn->name = strdup(name);
        unsigned int h = hash(name) % NHASH;
        hn->next = cache->cache_tab[h];
        cache->cache_tab[h] = hn;
    } 
    return 0;
}

int open_cache(const char *cache_dest)
{
    int i;
    for (i = 0; i < NHASH; i++) {
        cache->cache_tab[i] = NULL;
    }
    if ((cache->index_file = fopen(cache_dest, "r+")) == NULL) {
        if ((cache->index_file = fopen(cache_dest, "w+")) == NULL) {
            return 1;
        } else 
            return 0;
    } 
    while (feof(cache->index_file) == 0) {
        char name[MAX_BUF];
        fscanf(cache->index_file, "%s\n", name);
        add_to_hash_tab(name);
    }
    return 0;
}

int add_to_cache(const char *name)
{
    if (is_exist_in_cache(name))
        return 1;
    
    int retval = add_to_hash_tab(name);
    if (retval != 0)
        return retval;
    fprintf(cache->index_file, "%s\n", name);
    return 0;
}


int is_exist_in_cache( const char *name)
{
    if (lookup(name) == NULL)
        return 0;
    return 1;
}

int close_cache()
{
    int i;
    fclose(cache->index_file);
    for (i = 0; i < NHASH; i++) {
        while (cache->cache_tab[i]) {
            struct hash_node *temp = cache->cache_tab[i];
            cache->cache_tab[i] = cache->cache_tab[i]->next;
            free(temp);
        }
    }
    free(cache);
    return 0;
}
