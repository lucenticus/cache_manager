#ifndef CACHE_MANAGER_H
#define CACHE_MANAGER_H
 
#define NHASH (9973)

struct hash_node {
  char *name;
  struct hash_node *next;
};
struct cache_manager {
  char *cache_destination;
  struct hash_node *cache_tab[HASHTAB_SIZE];
  FILE *index_file;
};

unsigned int hash (char *name);
struct hash_node * lookup(struct hash_node *hash_tab, char *name);
int add_to_hash_tab(struct hash_node *hash_tab, char *name);

int open_cache(struct cache_manager *cache, char *cache_dest);
int add_to_cache(struct cache_manager *cache, char *name);
int remove_from_cache(struct cache_manager *cache, char *name);
int is_exist_in_cache(struct cache_manager *cache, char *name);
int close_cache(struct cache_manager *cache);
#endif /*CACHE_MANAGER*/
