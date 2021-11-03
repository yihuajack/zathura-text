/* SPDX-License-Identifier: Zlib */

#include "plugin.h"
#include "internal.h"

zathura_error_t
text_page_init(zathura_page_t* page)
{
  if (page == NULL) {
    return ZATHURA_ERROR_INVALID_ARGUMENTS;
  }

  zathura_document_t* document   = zathura_page_get_document(page);
  text_document_t* text_document = zathura_document_get_data(document);

  if (document == NULL || text_document == NULL) {
    return ZATHURA_ERROR_UNKNOWN;
  }

  text_page_t* text_page = girara_list_nth(text_document->pages, zathura_page_get_index(page));
  if (text_page == NULL || text_page->file == NULL) {
    return ZATHURA_ERROR_UNKNOWN;
  }

  zathura_page_set_width(page, 500);
  zathura_page_set_height(page, 500);
  zathura_page_set_data(page, text_page);

  return ZATHURA_ERROR_OK;
}

zathura_error_t
text_page_clear(zathura_page_t* UNUSED(page), void* data)
{
  text_page_t* text_page = data;
  if (text_page != NULL) {
    for (unsigned int i = 0; i < text_page->n_lines; i++) {
      free(text_page->file[i]);
    }
    g_free(text_page->file);
    g_free(text_page);
  }

  return ZATHURA_ERROR_OK;
}
