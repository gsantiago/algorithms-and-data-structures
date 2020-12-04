#include <string.h>
#include "cli.h"

int cli_get_index(int argc, char **argv, char *command) {
  int i;

  for (i = 0; i < argc; i++) {
    if (strcmp(argv[i], command) == 0) {
      return i;
    }
  }

  return -1;
}

bool cli_contains(int argc, char **argv, char *command) {
  return cli_get_index(argc, argv, command) != -1;
}

char *cli_get_command_value(int argc, char **argv, char *command) {
  int index = cli_get_index(argc, argv, command) + 1;

  if (index > argc) {
    return NULL;
  }

  return argv[index];
}
