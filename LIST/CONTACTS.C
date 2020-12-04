#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "../base.h"

#define APP_VERSION "0.0.1"
#define FILEPATH "CONTACTS.DAT"

/**
 * Globals and type definitions.
 */

typedef struct {
  char *name;
  char *email;
  char *phone;
} contact_t;

FILE *file;

/**
 * App's functions.
 */

void app_help();
void app_add_contact(int argc, char **argv);
void app_read_contacts();

/**
 * File manipulation.
 */

void file_open();
void file_close();
void file_write_string(char *string);
void file_write_contact(contact_t *contact);
int file_get_length();
int file_read_contact(contact_t *contact);

/**
 * Contact functions.
 */

void contact_print(contact_t *contact);
void contact_clear(contact_t *contact);

int main(int argc, char **argv) {
  contact_t c;

  if (argc == 1) {
    app_help();
    return 0;
  }

  if (cli_contains(argc, argv, "--add")) {
    app_add_contact(argc, argv);
  }

  if (cli_contains(argc, argv, "--read")) {
    app_read_contacts();
  }

  return 0;
}

void app_help() {
  printf("CONTACTS - v%s\n\n", APP_VERSION);
  printf("--add -n [name] -e [email] -p [phone]\tInserts a new contact\n");
  printf("--read\tRead all contacts from %s file", FILEPATH);
}

void app_add_contact(int argc, char **argv) {
  contact_t contact;

  contact.name = cli_get_command_value(argc, argv, "-n");
  contact.email = cli_get_command_value(argc, argv, "-e");
  contact.phone = cli_get_command_value(argc, argv, "-p");

  contact_print(&contact);

  file_open();
  file_write_contact(&contact);
  file_close();
}

void app_read_contacts() {
  contact_t c;
  int index = 0;

  file_open();

  while (file_read_contact(&c) != EOF) {
    contact_print(&c);
    contact_clear(&c);
  }

  file_close();
}

void file_open() {
  file = fopen(FILEPATH, "ab+");

  if (file == NULL) {
    printf("cannot open or create file\n");
    exit(1);
  }

  rewind(file);
}

void file_close() {
  fclose(file);
}

void file_write_string(char *string) {
  int length = strlen(string);
  size_t written_elements;

  written_elements = fwrite(
    &length,
    sizeof(int),
    1,
    file
  );

  if (written_elements != 1) {
    printf("Did not write the number of bytes for length\n");
    exit(1);
  }

  written_elements = fwrite(
    string,
    sizeof(char),
    length,
    file
  );

  if (written_elements != length) {
    printf("Did not write the number of bytes for string\n");
    exit(1);
  }
}

void file_write_contact(contact_t *contact) {
  file_write_string(contact->name);
  file_write_string(contact->email);
  file_write_string(contact->phone);
}

int file_get_length() {
  int length;

  fread(&length, sizeof(int), 1, file);
  return length;
}

int file_read_string(char **string) {
  int length = file_get_length();

  if (feof(file)) {
    return EOF;
  }

  *string = malloc(sizeof(char) * (length + 1));
  fread(*string, sizeof(char), length, file);
  (*string)[length] = '\0';

  return 0;
}

int file_read_contact(contact_t *contact) {
  if (file_read_string(&contact->name)) {
    return EOF;
  }

  if (file_read_string(&contact->email)) {
    return EOF;
  }

  if (file_read_string(&contact->phone)) {
    return EOF;
  }

  return 0;
}

void contact_print(contact_t *contact) {
  printf("Name: %s\n", contact->name);
  printf("Email: %s\n", contact->email);
  printf("Phone: %s\n", contact->phone);
}

void contact_clear(contact_t *contact) {
  free(contact->name);
  free(contact->email);
  free(contact->phone);
}
