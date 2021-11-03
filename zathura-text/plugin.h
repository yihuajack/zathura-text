/* SPDX-License-Identifier: Zlib */

#ifndef TEXT_H
#define TEXT_H

#include <stdbool.h>
#include <zathura/plugin-api.h>
#include <cairo.h>

typedef struct text_document_s text_document_t;
typedef struct text_page_s text_page_t;

/**
 * Open a PostScript document
 *
 * @param document Zathura document
 * @return ZATHURA_ERROR_OK if no error occurred otherwise see
 *   zathura_error_t
 */
GIRARA_HIDDEN zathura_error_t text_document_open(zathura_document_t* document);

/**
 * Closes and frees the internal document structure
 *
 * @param document Zathura document
 * @return ZATHURA_ERROR_OK if no error occurred otherwise see
 *   zathura_error_t
 */
GIRARA_HIDDEN zathura_error_t text_document_free(zathura_document_t* document, void* spectre_document);

/**
 * Returns a reference to a page
 *
 * @param page Page object
 * @return ZATHURA_ERROR_OK if no error occurred otherwise see
 *   zathura_error_t
 */
GIRARA_HIDDEN zathura_error_t text_page_init(zathura_page_t* page);

/**
 * Renders a page onto a cairo object
 *
 * @param page Page
 * @param cairo Cairo object
 * @param printing Set to true if page should be rendered for printing
 * @return ZATHURA_ERROR_OK if no error occurred otherwise see
 *   zathura_error_t
 */
GIRARA_HIDDEN zathura_error_t text_page_render_cairo(zathura_page_t* page, void* spectre_page, cairo_t* cairo, bool printing);

/**
 * Frees a PostScript page
 *
 * @param page Page
 * @return ZATHURA_ERROR_OK if no error occurred otherwise see
 *   zathura_error_t
 */
GIRARA_HIDDEN zathura_error_t text_page_clear(zathura_page_t* page, void* spectre_page);

#endif // TEXT_H
