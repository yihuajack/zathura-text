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
  // text_document->n_pages = 0;
  // text_document->page_head = NULL;

  /* archive path */
  const char *path = zathura_document_get_path(document);

  /* text_document->page_head = g_malloc0(sizeof(text_page_t));
  text_document->page_head->file = NULL;
  text_document->page_head->next = NULL;

  if (fgets(content, 400, ifile)) {
    text_document->page_head->file = strdup(content);
    text_document->page_tail = text_document->page_head; 
  }  */

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

  /* if (text_document != NULL) {
    for (unsigned int i = 0; i < zathura_document_get_number_of_pages(document); i++) {
      g_free(text_document->pages[i].file);
    }
    g_free(text_document->pages);
    g_free(text_document);
    zathura_document_set_data(document, NULL);
  }  */

  g_free(text_document);

  return ZATHURA_ERROR_OK;
}

/* static void
text_document_page_free(text_page_t* text_page)
{
  if (text_page == NULL) {
    return;
  }

  if (text_page->file != NULL) {
    g_free(text_page->file);
  }
  g_free(text_page);
}  */

static bool
read_text(text_document_t* text_document, const char* path)
{
  FILE* r= fopen(path, "r");
  if (r == NULL) {
    return false;
  }

  char content[400];
  while (1) {
    if (fgets(content, 400, r)) {
      text_page_t *page = g_malloc0(sizeof(text_page_t));
      page->file = strdup(content);
      /* page.next = NULL;
      text_document->page_tail->next = page;
      text_document->page_tail = text_document->page_tail->next;
      text_document->n_pages++;  */
      girara_list_append(text_document->pages, page);
    } else {
      return false;
    }
  }

  fclose(r);
  return true;
}
