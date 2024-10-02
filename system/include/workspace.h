#pragma once

# include "dinio.h"
# include "cursor.h"

# define NB_WS 2

typedef struct {
    unsigned char   vmem[4000];
    unsigned char   *cursor;
} workspace;

void	auto_switch_workspace();
void	switch_workspace(int nb);
