/**
 * IPROPS (stands for InputPROPerties System)
 * require C99
 * require following header files:
 * stdio.h stdlib.h string.h assert.h stdbool.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "iprops.h"

/**
 * IPROPS load function
 */
extern iprops_t *IPROPS_load(const char * const filename) {
  printf("\n### IPROPS Load Begin\n");
  iprops_t *iprops = NULL;

  // file open
  printf("# file = %s\n", filename);
  FILE* file = fopen(filename, "r");

  if (file != NULL) {
    char buff[MAX_READ_BUFFER_SIZE];
    char key[MAX_READ_BUFFER_SIZE];
    char value[MAX_READ_BUFFER_SIZE];
    bool headerflag = false;
    double ipropsversion = 0.0;
    int nProps = 0;
    char **keys;
    char **values;
    while (fgets(buff, sizeof(buff), file) != NULL) {

      // buff check
      if (strlen(buff) == (sizeof(buff) - 1)) {
        fprintf(stderr, "# string buffer is too small !!\n");
        continue;
      }

      // header chars check
      if (!headerflag
          && !strncmp(buff, IPROPS_HEADER_VERSION_CHARS_WITHOUT_FORMAT,
              strlen(IPROPS_HEADER_VERSION_CHARS_WITHOUT_FORMAT))) {
        sscanf(buff, IPROPS_HEADER_VERSION_CHARS, &ipropsversion);
        // IPROPS Version check
        printf("# IPROPS Version (prog) = %1.1f\n", IPROPS_VERSION);
        printf("# IPROPS Version (text) = %1.1f\n", ipropsversion);
        assert(ipropsversion == IPROPS_VERSION);
        headerflag = true;
        // NPROPS check
        assert(fgets(buff, sizeof(buff), file) != NULL);
        if (!strncmp(buff, IPROPS_HEADER_NPROPS_CHARS_WITHOUT_FORMAT,
            strlen(IPROPS_HEADER_NPROPS_CHARS_WITHOUT_FORMAT))) {
          sscanf(buff, IPROPS_HEADER_NPROPS_CHARS, &nProps);
          printf("# nProps = %d\n", nProps);
          iprops = (iprops_t *) calloc((size_t) 1, sizeof(iprops_t));
          keys = (char **) calloc((size_t) nProps, sizeof(char *));
          values = (char **) calloc((size_t) nProps, sizeof(char *));
          iprops->nProps = nProps;
          iprops->keys = keys;
          iprops->values = values;
        }
      }

      // property chars check
      if (headerflag && nProps > 0) {
        if (!strncmp(buff, IPROPS_COMMENT_LINE, strlen(IPROPS_COMMENT_LINE))
            || !strcmp(buff, IPROPS_BLANK_LINE))
          continue;
        if (sscanf(buff, IPROPS_PROPERTY_LINE, key, value)) {
          printf("# %d (key, value) = (\"%s\", \"%s\")\n",
              (iprops->nProps - nProps), key, value);
          iprops->keys[iprops->nProps - nProps] = (char *) calloc(
              (size_t) strlen(key), sizeof(char));
          strncpy(iprops->keys[iprops->nProps - nProps], key, strlen(key));
          iprops->values[iprops->nProps - nProps] = (char *) calloc(
              (size_t) strlen(value), sizeof(char));
          strncpy(iprops->values[iprops->nProps - nProps], value,
              strlen(value));
        }
        nProps--;
      }

    }
  }

  fclose(file);
  printf("### IPROPS Load Finish\n\n");
  return iprops;
}

/**
 * IPROPS free function
 * !!! required to be called after end of use IPROPS !!!
 */
extern void IPROPS_free(iprops_t *iprops) {
  printf("\n### IPROPS Free Begin\n");
  free(iprops->values);
  printf("# free iprops->values\n");
  free(iprops->keys);
  printf("# free iprops->keys\n");
  free(iprops);
  printf("# free iprops-self\n");
  printf("### IPROPS Free Finish\n\n");
}

/**
 * IPROPS read function
 */
extern char *IPROPS_read(const iprops_t * const iprops, const char * const key) {
  char* value = NULL;
  for (int i = 0; i < iprops->nProps; i++) {
    if (!strncmp(key, iprops->keys[i], strlen(key))) {
      value = iprops->values[i];
      break;
    }
  }
  return value;
}

/**
 * IPROPS read as double function
 */
extern double IPROPS_readf(const iprops_t * const iprops,
    const char * const key) {
  char *tvalue = NULL;
  double value = 0.0;
  tvalue = IPROPS_read(iprops, key);
  if (tvalue != NULL) {
    value = atof(tvalue);
  }
  return value;
}

/**
 * IPROPS read as int function
 */
extern int IPROPS_readi(const iprops_t * const iprops, const char * const key) {
  char *tvalue = NULL;
  int value = 0;
  tvalue = IPROPS_read(iprops, key);
  if (tvalue != NULL) {
    value = atoi(tvalue);
  }
  return value;
}
