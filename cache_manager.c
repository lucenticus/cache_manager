#include "cache_manager.h"

unsigned int hash (const char *name) 
{
    unsigned int hash = 0;
    unsigned int c;
    while (c = *name++) 
        hash = hash * 9 ^ c;
    return hash;
}

struct hash_node * lookup(struct hash_node **hash_tab, const char *name)
{
    struct hash_node *hn = hash_tab[hash(name) % NHASH];
  
    while (hn) {
        if (!strcmp(hn->name, name)) {
            return hn;
        }
        hn = hn->next;
    }
    return NULL;
}

int add_to_hash_tab(struct hash_node **hash_tab, const char *name)
{
    struct hash_node *hn;
    if ((hn = lookup(hash_tab, name)) == NULL) {
        hn = (struct hash_node *)malloc(sizeof(struct hash_node));
        if (hn == NULL)
            return 1;
        hn->name = strdup(name);
        hn->next = hash_tab[hash(name)];
        hash_tab[hash(name)] = hn;
    } 
    return 0;
}

int open_cache(struct cache_manager *cache, const char *cache_dest)
{
    cache = (struct cache_manager*) malloc(sizeof(struct cache_manager));
    for (int i = 0; i < NHASH; i++) {
        cache->cache_tab[i] = NULL;
    }
    if ((cache->index_file = fopen(cache_dest, "wr")) == NULL) {
        return 1;
    } 
    while (!feof(cache->index_file)) {
        char *name;
        fscanf(cache->index_file, "%s\n", name);
        add_to_hash_tab(cache->cache_tab, name);
    }
    return 0;
}

int add_to_cache(struct cache_manager *cache, const char *name)
{

    int retval = add_to_hash_tab(cache->cache_tab, name);
    if (retval != 0)
        return retval;
    fprintf(cache->index_file, "%s", name);
    return 0;
}


int is_exist_in_cache(struct cache_manager *cache, const char *name)
{
    if (lookup(cache->cache_tab, name) == NULL)
        return 0;
    return 1;
}

int close_cache(struct cache_manager *cache)
{
    fclose(cache->index_file);
    for (int i = 0; i < NHASH; i++) {
        while (cache->cache_tab[i]) {
            struct hash_node *temp = cache->cache_tab[i];
            cache->cache_tab[i] = cache->cache_tab[i]->next;
            free(temp);
        }
    }
    free(cache);
    return 0;
}
