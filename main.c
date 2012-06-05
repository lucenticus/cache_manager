//
//  main.c
//  test_project
//
//  Created by Pavlov Evgeny on 06.06.12.
//  Copyright (c) 2012. All rights reserved.
//

#include <stdio.h>
#include "cache_manager.h"
int main (int argc, const char * argv[])
{
    cache = (struct cache_manager*) malloc(sizeof(struct cache_manager));
    open_cache("index.cache");
    add_to_cache("tile_0_2.png");
    add_to_cache("tile_1_2.png");
    close_cache();
    return 0;
}

