/* SPDX-License-Identifier: Zlib */

#ifndef INTERNAL_H
#define INTERNAL_H

#define TEXT_BUFFER_SIZE 8192

struct text_document_s {
  // unsigned int n_pages;
  // struct text_page_s *page;
  // struct text_page_s *page_tail;
  girara_list_t* pages;
};

struct text_page_s {
  char *file;
  // unsigned int width;
  // unsigned int height;
  // struct text_page_s *next;
};

#endif // INTERNAL_H
