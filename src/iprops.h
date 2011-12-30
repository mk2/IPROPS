/**
 * IPROPS (stands for InputPROPerties System)
 * require C99
 * require following header files:
 * stdio.h stdlib.h string.h assert.h stdbool.h
 */

#pragma once
#ifndef __IPROPS_H
#define __IPROPS_H

#define MAX_READ_BUFFER_SIZE 512

// IPROPS constants
#define IPROPS_VERSION 1.0
#define IPROPS_HEADER_VERSION_CHARS "#IPROPS Version %1.1f\n"
#define IPROPS_HEADER_VERSION_CHARS_WITHOUT_FORMAT "#IPROPS Version"
#define IPROPS_HEADER_NPROPS_CHARS "#NPROPS %d\n"
#define IPROPS_HEADER_NPROPS_CHARS_WITHOUT_FORMAT "#NPROPS"
#define IPROPS_COMMENT_LINE "#"
#define IPROPS_BLANK_LINE "\n"
#define IPROPS_PROPERTY_LINE "%s = %s\n"

typedef struct InputProperties {
  int nProps;
  char** keys;
  char** values;
} iprops_t;

extern iprops_t *IPROPS_load(const char * const);
extern void IPROPS_free(iprops_t *);
extern char *IPROPS_read(const iprops_t * const, const char * const);
extern double IPROPS_readf(const iprops_t * const, const char * const);
extern int IPROPS_readi(const iprops_t * const, const char * const);

#endif
