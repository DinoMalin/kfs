#pragma once

#include "cursor.h"
#include "io.h"
#include "shell.h"

#define NB_WS 2

typedef struct {
	u8 vmem[4000];
	u8 *cursor;
} workspace;

void auto_switch_workspace();
void switch_workspace(int nb);
