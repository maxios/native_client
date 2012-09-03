/*
 * Copyright (c) 2011 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* DFA for instruction generators. */

%%{
  machine one_instruction_x86_32;
  alphtype unsigned char;

  include byte_machine "byte_machines.rl";

  include prefix_actions
    "native_client/src/trusted/validator_ragel/unreviewed/parse_instruction.rl";
  include prefixes_parsing
    "native_client/src/trusted/validator_ragel/unreviewed/parse_instruction.rl";
  include vex_actions_ia32
    "native_client/src/trusted/validator_ragel/unreviewed/parse_instruction.rl";
  include vex_parsing_ia32
    "native_client/src/trusted/validator_ragel/unreviewed/parse_instruction.rl";
  include modrm_actions_ia32
    "native_client/src/trusted/validator_ragel/unreviewed/parse_instruction.rl";
  include modrm_parsing_ia32
    "native_client/src/trusted/validator_ragel/unreviewed/parse_instruction.rl";
  include displacement_fields_mark
    "native_client/src/trusted/validator_ragel/unreviewed/parse_instruction.rl";
  include immediate_fields_mark
    "native_client/src/trusted/validator_ragel/unreviewed/parse_instruction.rl";
  include relative_fields_mark_ia32
    "native_client/src/trusted/validator_ragel/unreviewed/parse_instruction.rl";
  include cpuid_actions
    "native_client/src/trusted/validator_ragel/unreviewed/parse_instruction.rl";

  action last_byte_is_not_immediate { }

  include decode_x86_32 "one_valid_instruction_x86_32.rl";

  main := one_instruction;

}%%
