/* SPDX-License-Identifier: Zlib */

#ifndef INTERNAL_H
#define INTERNAL_H

#define LINE_BUFFER_SIZE 1024
#define PAGE_LINE_SIZE 10

struct text_document_s {
  girara_list_t* pages;
};

struct text_page_s {
  char** file;
  unsigned int n_lines;
};

#endif // INTERNAL_H
