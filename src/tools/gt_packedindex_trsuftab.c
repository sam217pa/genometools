/*
  Copyright (c) 2007 Thomas Jahns <Thomas.Jahns@gmx.net>

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

#include <stdio.h>
#include <string.h>
#include "libgtcore/ensure.h"
#include "libgtcore/error.h"
#include "libgtcore/option.h"
#include "libgtcore/str.h"
#include "libgtcore/versionfunc.h"
#include "libgtmatch/eis-bwtseq.h"
#include "libgtmatch/encseq-def.h"
#include "libgtmatch/sarr-def.h"
#include "libgtmatch/eis-bwtconstruct_params.h"
#include "tools/gt_packedindex_trsuftab.h"

#define DEFAULT_PROGRESS_INTERVAL  100000UL

struct trSufTabOptions
{
  struct bwtOptions idx;
};

static OPrval
parseTrSufTabOptions(int *parsed_args, int argc, const char **argv,
                     struct trSufTabOptions *params, const Str *projectName,
                     Error *err);

extern int
gt_packedindex_trsuftab(int argc, const char *argv[], Error *err)
{
  struct trSufTabOptions params;
  BWTSeq *bwtSeq = NULL;
  Str *inputProject = NULL;
  int parsedArgs;
  bool had_err = false;
  inputProject = str_new();

  do {
    error_check(err);
    {
      bool exitNow = false;
      switch (parseTrSufTabOptions(&parsedArgs, argc, argv, &params,
                                   inputProject, err))
      {
      case OPTIONPARSER_OK:
        break;
      case OPTIONPARSER_ERROR:
        had_err = true;
        exitNow = true;
        break;
      case OPTIONPARSER_REQUESTS_EXIT:
        exitNow = true;
        break;
      }
      if (exitNow)
        break;
    }
    str_set(inputProject, argv[parsedArgs]);
    {
      bwtSeq = trSuftab2BWTSeq(&params.idx.final, err);
    }
    ensure(had_err, bwtSeq);
    if (had_err)
      break;
  } while (0);
  if (bwtSeq) deleteBWTSeq(bwtSeq);
  if (inputProject) str_delete(inputProject);
  return had_err?-1:0;
}

static OPrval
parseTrSufTabOptions(int *parsed_args, int argc, const char **argv,
                   struct trSufTabOptions *params, const Str *projectName,
                   Error *err)
{
  OptionParser *op;
  OPrval oprval;

  error_check(err);
  op = option_parser_new("indexname",
                         "Build BWT packedindex for project <indexname>.");

  registerPackedIndexOptions(op, &params->idx, BWTDEFOPT_MULTI_QUERY,
                             projectName);

  option_parser_set_min_max_args(op, 1, 1);
  oprval = option_parser_parse(op, parsed_args, argc, argv, versionfunc, err);
  /* compute parameters currently not set from command-line or
   * determined indirectly */
  computePackedIndexDefaults(&params->idx,
                             BWTBaseFeatures & ~BWTProperlySorted);

  option_parser_delete(op);

  return oprval;
}
