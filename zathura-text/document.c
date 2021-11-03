/* SPDX-License-Identifier: Zlib */

#include <string.h>
#include <girara/datastructures.h>
#include <glib.h>

#include "plugin.h"
#include "internal.h"

static bool read_text(text_document_t* text_document, const char* text);

zathura_error_t
text_document_open(zathura_document_t* document)
{
  zathura_error_t error = ZATHURA_ERROR_OK;
  if (document == NULL) {
    error = ZATHURA_ERROR_UNKNOWN;
    goto error_ret;
  }

  text_document_t* text_document = g_malloc0(sizeof(text_document_t));

  /* archive path */
  const char *path = zathura_document_get_path(document);

  /* create list of supported files (pages) */
  text_document->pages = girara_list_new2((girara_free_function_t) text_page_clear);
  if (text_document->pages == NULL) {
    goto error_free;
  }

  /* read text */
  if (read_text(text_document, path) == false) {
    goto error_free;
  }

  zathura_document_set_number_of_pages(document, girara_list_size(text_document->pages));
  zathura_document_set_data(document, text_document);

  return error;

error_free:

  text_document_free(document, text_document);

  return ZATHURA_ERROR_UNKNOWN;

error_ret:

  return error;
}

zathura_error_t
text_document_free(zathura_document_t* document, void* data)
{
  text_document_t *text_document = data;
  if (document == NULL) {
    return ZATHURA_ERROR_INVALID_ARGUMENTS;
  }
  
  /* remove page list */
  if (text_document->pages != NULL) {
    girara_list_free(text_document->pages);
  }

  g_free(text_document);

  return ZATHURA_ERROR_OK;
}

static bool
read_text(text_document_t* text_document, const char* path)
{
  FILE* r= fopen(path, "r");
  if (r == NULL) {
    return false;
  }

  char page_content[PAGE_LINE_SIZE][LINE_BUFFER_SIZE];
  int c;
  unsigned int i = 0, j = 0;
  while (1) {
    c = fgetc(r);
    if (c != EOF) {
      if (c == '\n') {
        page_content[i++][j] = '\0';
        j = 0;
        if (i >= PAGE_LINE_SIZE) {
          text_page_t *page = g_malloc0(sizeof(text_page_t));
          page->file = g_malloc0(sizeof(char*) * PAGE_LINE_SIZE);
          for (unsigned int k = 0; k < PAGE_LINE_SIZE; k++) {
            page->file[k] = strdup(page_content[k]);
          }
          page->n_lines = PAGE_LINE_SIZE;
          girara_list_append(text_document->pages, page);
          memset(page_content, 0, sizeof(page_content));
          i = 0;
        }
      } else {
        page_content[i][j++] = c;
      }
    } else if (feof(r)) {
      page_content[i][j] = '\0';
      text_page_t *page = g_malloc0(sizeof(text_page_t));
      page->file = g_malloc0(sizeof(char*) * (i + 1));
      for (unsigned int k = 0; k <= i; k++) {
        page->file[k] = strdup(page_content[k]);
      }
      page->n_lines = i + 1;
      girara_list_append(text_document->pages, page);
      break;
    } else if (ferror(r)) {
      fclose(r);
      return false;
    }
  }

  if (fclose(r)) {
    perror("fclose error");
    return false;
  } else {
    return true;
  }
}
