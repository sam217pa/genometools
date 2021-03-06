/*
  Copyright (c) 2007-2008 Gordon Gremme <gordon@gremme.org>
  Copyright (c) 2007-2008 Center for Bioinformatics, University of Hamburg

  Permission to use, copy, modify, and distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef STR_ARRAY_H
#define STR_ARRAY_H

#include "core/str_api.h"
#include "core/str_array_api.h"

/* Returns an array of strings read from fila at <path>. Each line resulting in
   one <GtStr> within the <GtStrArray>. */
GtStrArray* gt_str_array_new_file(const char *path);

/* Returns an internal GtStr pointer (i.e., _not_ a new reference!). */
GtStr*      gt_str_array_get_str(const GtStrArray*, GtUword strnum);

#endif
