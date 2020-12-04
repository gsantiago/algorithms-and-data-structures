#ifndef CLI_H
#define CLI_H

#include "bool.h"

int cli_get_index(int argc, char **argv, char *command);
bool cli_contains(int argc, char **argv, char *command);
char *cli_get_command_value(int argc, char **argv, char *command);

#endif
