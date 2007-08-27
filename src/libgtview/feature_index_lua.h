/*
  Copyright (c) 2007 Gordon Gremme <gremme@zbh.uni-hamburg.de>
  Copyright (c) 2007 Center for Bioinformatics, University of Hamburg
  See LICENSE file or http://genometools.org/license.html for license details.
*/

#ifndef FEATURE_INDEX_LUA_H
#define FEATURE_INDEX_LUA_H

#include "lua.h"

/* exports the FeatureIndex class to Lua:

   feature_index    = gt.feature_index_new()
   -- returns the genome features (of type genome_node) in a table
   table            = feature_index:get_features_for_seqid(string)
   table            = feature_index:get_features_for_range(seqid,
                                                           startpos, endpos)
   seqid            = feature_index:get_first_seqid()
   startpos, endpos = feature_index:get_range_for_seqid(seqid)
*/
int luaopen_feature_index(lua_State*);

#define FEATURE_INDEX_METATABLE  "GenomeTools.feature_index"
#define check_feature_index(L, POS) \
          (FeatureIndex**) luaL_checkudata(L, POS, FEATURE_INDEX_METATABLE);

#endif
