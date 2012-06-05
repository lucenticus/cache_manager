//
//  cache_manager.h
//  test_project
//
//  Created by Pavlov Evgeny on 06.06.12.
//  Copyright (c) 2012. All rights reserved.
//

#ifndef CACHE_MANAGER_H
#define CACHE_MANAGER_H
 
#define NHASH (9973)
#define MAX_BUF (1024)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
  
struct hash_node {
  char *name;
  struct hash_node *next;
};
struct cache_manager {
  char *cache_destination;
  struct hash_node *cache_tab[NHASH];
  FILE *index_file;
} *cache;

unsigned int hash (const char *name);
struct hash_node * lookup(const char *name);
int add_to_hash_tab(const char *name);

int open_cache(const char *cache_dest);
int add_to_cache(const char *name);
int is_exist_in_cache(const char *name);
int close_cache();
#endif /*CACHE_MANAGER*/
