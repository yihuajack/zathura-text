/* SPDX-License-Identifier: Zlib */

#include <glib.h>
#include <stdlib.h>

#include <cairo.h>

#include "plugin.h"
#include "internal.h"

zathura_error_t
text_page_render_cairo(zathura_page_t* page, void* data,
    cairo_t* cairo, bool UNUSED(printing))
{
  text_page_t* text_page = data;
  if (page == NULL || text_page == NULL || cairo == NULL) {
    return ZATHURA_ERROR_INVALID_ARGUMENTS;
  }

  zathura_document_t* document = zathura_page_get_document(page);
  if (document == NULL) {
    return ZATHURA_ERROR_UNKNOWN;
  }

  cairo_set_source_rgb(cairo, 0.1, 0.1, 0.1);

  cairo_select_font_face(cairo,"Times New Roman",
      CAIRO_FONT_SLANT_NORMAL,
      CAIRO_FONT_WEIGHT_BOLD);
 
  cairo_set_font_size(cairo, 13);

  for (unsigned int i = 0; i < text_page->n_lines; i++) {
    cairo_move_to(cairo, 40, 40 + i * 40);
    cairo_show_text(cairo, (const char *)(text_page->file[i]));
  }

  return ZATHURA_ERROR_OK;
}
