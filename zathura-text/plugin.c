/* SPDX-License-Identifier: Zlib */

#include "plugin.h"

ZATHURA_PLUGIN_REGISTER_WITH_FUNCTIONS(
  "text",
  VERSION_MAJOR, VERSION_MINOR, VERSION_REV,
  ZATHURA_PLUGIN_FUNCTIONS({
    .document_open            = text_document_open,
    .document_free            = text_document_free,
    .page_init                = text_page_init,
    .page_clear               = text_page_clear,
    .page_render_cairo        = text_page_render_cairo,
  }),
  // https://en.wikipedia.org/wiki/Media_type
  ZATHURA_PLUGIN_MIMETYPES({
    "text/plain"
  })
)
