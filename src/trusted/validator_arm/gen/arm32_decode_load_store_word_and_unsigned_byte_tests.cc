/*
 * Copyright 2013 The Native Client Authors.  All rights reserved.
 * Use of this source code is governed by a BSD-style license that can
 * be found in the LICENSE file.
 */

// DO NOT EDIT: GENERATED CODE

#ifndef NACL_TRUSTED_BUT_NOT_TCB
#error This file is not meant for use in the TCB
#endif


#include "gtest/gtest.h"
#include "native_client/src/trusted/validator_arm/actual_vs_baseline.h"
#include "native_client/src/trusted/validator_arm/baseline_vs_baseline.h"
#include "native_client/src/trusted/validator_arm/actual_classes.h"
#include "native_client/src/trusted/validator_arm/baseline_classes.h"
#include "native_client/src/trusted/validator_arm/inst_classes_testers.h"
#include "native_client/src/trusted/validator_arm/arm_helpers.h"
#include "native_client/src/trusted/validator_arm/gen/arm32_decode_named_bases.h"

using nacl_arm_dec::Instruction;
using nacl_arm_dec::ClassDecoder;
using nacl_arm_dec::Register;
using nacl_arm_dec::RegisterList;

namespace nacl_arm_test {

// The following classes are derived class decoder testers that
// add row pattern constraints and decoder restrictions to each tester.
// This is done so that it can be used to make sure that the
// corresponding pattern is not tested for cases that would be excluded
//  due to row checks, or restrictions specified by the row restrictions.


// A(25)=0 & op1(24:20)=0x010
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0100u010nnnnttttiiiiiiiiiiii,
//       rule: STRT_A1}
class ForbiddenCondDecoderTesterCase0
    : public UnsafeCondDecoderTester {
 public:
  ForbiddenCondDecoderTesterCase0(const NamedClassDecoder& decoder)
    : UnsafeCondDecoderTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool ForbiddenCondDecoderTesterCase0
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~0
  if ((inst.Bits() & 0x02000000)  !=
          0x00000000) return false;
  // op1(24:20)=~0x010
  if ((inst.Bits() & 0x01700000)  !=
          0x00200000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return UnsafeCondDecoderTester::
      PassesParsePreconditions(inst, decoder);
}

// A(25)=0 & op1(24:20)=0x011
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0100u011nnnnttttiiiiiiiiiiii,
//       rule: LDRT_A1}
class ForbiddenCondDecoderTesterCase1
    : public UnsafeCondDecoderTester {
 public:
  ForbiddenCondDecoderTesterCase1(const NamedClassDecoder& decoder)
    : UnsafeCondDecoderTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool ForbiddenCondDecoderTesterCase1
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~0
  if ((inst.Bits() & 0x02000000)  !=
          0x00000000) return false;
  // op1(24:20)=~0x011
  if ((inst.Bits() & 0x01700000)  !=
          0x00300000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return UnsafeCondDecoderTester::
      PassesParsePreconditions(inst, decoder);
}

// A(25)=0 & op1(24:20)=0x110
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0100u110nnnnttttiiiiiiiiiiii,
//       rule: STRBT_A1}
class ForbiddenCondDecoderTesterCase2
    : public UnsafeCondDecoderTester {
 public:
  ForbiddenCondDecoderTesterCase2(const NamedClassDecoder& decoder)
    : UnsafeCondDecoderTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool ForbiddenCondDecoderTesterCase2
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~0
  if ((inst.Bits() & 0x02000000)  !=
          0x00000000) return false;
  // op1(24:20)=~0x110
  if ((inst.Bits() & 0x01700000)  !=
          0x00600000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return UnsafeCondDecoderTester::
      PassesParsePreconditions(inst, decoder);
}

// A(25)=0 & op1(24:20)=0x111
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0100u111nnnnttttiiiiiiiiiiii,
//       rule: LDRBT_A1}
class ForbiddenCondDecoderTesterCase3
    : public UnsafeCondDecoderTester {
 public:
  ForbiddenCondDecoderTesterCase3(const NamedClassDecoder& decoder)
    : UnsafeCondDecoderTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool ForbiddenCondDecoderTesterCase3
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~0
  if ((inst.Bits() & 0x02000000)  !=
          0x00000000) return false;
  // op1(24:20)=~0x111
  if ((inst.Bits() & 0x01700000)  !=
          0x00700000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return UnsafeCondDecoderTester::
      PassesParsePreconditions(inst, decoder);
}

// A(25)=0 & op1(24:20)=xx0x0 & op1_repeated(24:20)=~0x010
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_STR_immediate_cccc010pu0w0nnnnttttiiiiiiiiiiii_case_1,
//       base: Rn,
//       baseline: Store2RegisterImm12Op,
//       constraints: ,
//       defs: {base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12)],
//       generated_baseline: STR_immediate_cccc010pu0w0nnnnttttiiiiiiiiiiii_case_0,
//       pattern: cccc010pu0w0nnnnttttiiiiiiiiiiii,
//       rule: STR_immediate,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE],
//       small_imm_base_wb: wback,
//       uses: {Rn, Rt},
//       wback: P(24)=0 ||
//            W(21)=1}
class Store2RegisterImm12OpTesterCase4
    : public LoadStore2RegisterImm12OpTester {
 public:
  Store2RegisterImm12OpTesterCase4(const NamedClassDecoder& decoder)
    : LoadStore2RegisterImm12OpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
  virtual bool ApplySanityChecks(nacl_arm_dec::Instruction inst,
                                 const NamedClassDecoder& decoder);
};

bool Store2RegisterImm12OpTesterCase4
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~0
  if ((inst.Bits() & 0x02000000)  !=
          0x00000000) return false;
  // op1(24:20)=~xx0x0
  if ((inst.Bits() & 0x00500000)  !=
          0x00000000) return false;
  // op1_repeated(24:20)=0x010
  if ((inst.Bits() & 0x01700000)  ==
          0x00200000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return LoadStore2RegisterImm12OpTester::
      PassesParsePreconditions(inst, decoder);
}

bool Store2RegisterImm12OpTesterCase4
::ApplySanityChecks(nacl_arm_dec::Instruction inst,
                    const NamedClassDecoder& decoder) {
  NC_PRECOND(LoadStore2RegisterImm12OpTester::
               ApplySanityChecks(inst, decoder));

  // safety: P(24)=0 &&
  //       W(21)=1 => DECODER_ERROR
  EXPECT_TRUE(!(((inst.Bits() & 0x01000000)  ==
          0x00000000) &&
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)));

  // safety: wback &&
  //       (Rn  ==
  //          Pc ||
  //       Rn  ==
  //          Rt) => UNPREDICTABLE
  EXPECT_TRUE(!((((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)) &&
       (((((((inst.Bits() & 0x000F0000) >> 16)) == (15))) ||
       (((((inst.Bits() & 0x000F0000) >> 16)) == (((inst.Bits() & 0x0000F000) >> 12))))))));

  // defs: {base
  //       if wback
  //       else None};
  EXPECT_TRUE(decoder.defs(inst).IsSame(RegisterList().
   Add(Register((((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)
       ? ((inst.Bits() & 0x000F0000) >> 16)
       : 32)))));

  return true;
}

// A(25)=0 & op1(24:20)=xx0x1 & Rn(19:16)=~1111 & op1_repeated(24:20)=~0x011
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       Tp: 9,
//       U: U(23),
//       W: W(21),
//       actual: Actual_LDR_immediate_cccc010pu0w1nnnnttttiiiiiiiiiiii_case_1,
//       add: U(23)=1,
//       base: Rn,
//       baseline: LdrImmediateOp,
//       constraints: ,
//       defs: {Rt, base
//            if wback
//            else None},
//       fields: [P(24), U(23), W(21), Rn(19:16), Rt(15:12), imm12(11:0)],
//       generated_baseline: LDR_immediate_cccc010pu0w1nnnnttttiiiiiiiiiiii_case_0,
//       imm12: imm12(11:0),
//       index: P(24)=1,
//       is_load_tp: Rn  ==
//               Tp &&
//            index &&
//            not wback &&
//            add &&
//            imm12 in {0, 4},
//       pattern: cccc010pu0w1nnnnttttiiiiiiiiiiii,
//       rule: LDR_immediate,
//       safety: [Rn  ==
//               Pc => DECODER_ERROR,
//         P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         wback &&
//            Rn  ==
//               Rt => UNPREDICTABLE,
//         Rt  ==
//               Pc => FORBIDDEN_OPERANDS],
//       small_imm_base_wb: wback,
//       uses: {Rn},
//       wback: P(24)=0 ||
//            W(21)=1}
class LdrImmediateOpTesterCase5
    : public LoadStore2RegisterImm12OpTester {
 public:
  LdrImmediateOpTesterCase5(const NamedClassDecoder& decoder)
    : LoadStore2RegisterImm12OpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
  virtual bool ApplySanityChecks(nacl_arm_dec::Instruction inst,
                                 const NamedClassDecoder& decoder);
};

bool LdrImmediateOpTesterCase5
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~0
  if ((inst.Bits() & 0x02000000)  !=
          0x00000000) return false;
  // op1(24:20)=~xx0x1
  if ((inst.Bits() & 0x00500000)  !=
          0x00100000) return false;
  // Rn(19:16)=1111
  if ((inst.Bits() & 0x000F0000)  ==
          0x000F0000) return false;
  // op1_repeated(24:20)=0x011
  if ((inst.Bits() & 0x01700000)  ==
          0x00300000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return LoadStore2RegisterImm12OpTester::
      PassesParsePreconditions(inst, decoder);
}

bool LdrImmediateOpTesterCase5
::ApplySanityChecks(nacl_arm_dec::Instruction inst,
                    const NamedClassDecoder& decoder) {
  NC_PRECOND(LoadStore2RegisterImm12OpTester::
               ApplySanityChecks(inst, decoder));

  // safety: Rn  ==
  //          Pc => DECODER_ERROR
  EXPECT_TRUE(((((inst.Bits() & 0x000F0000) >> 16)) != (15)));

  // safety: P(24)=0 &&
  //       W(21)=1 => DECODER_ERROR
  EXPECT_TRUE(!(((inst.Bits() & 0x01000000)  ==
          0x00000000) &&
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)));

  // safety: wback &&
  //       Rn  ==
  //          Rt => UNPREDICTABLE
  EXPECT_TRUE(!((((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)) &&
       (((((inst.Bits() & 0x000F0000) >> 16)) == (((inst.Bits() & 0x0000F000) >> 12))))));

  // safety: Rt  ==
  //          Pc => FORBIDDEN_OPERANDS
  EXPECT_TRUE(((((inst.Bits() & 0x0000F000) >> 12)) != (15)));

  // defs: {Rt, base
  //       if wback
  //       else None};
  EXPECT_TRUE(decoder.defs(inst).IsSame(RegisterList().
   Add(Register(((inst.Bits() & 0x0000F000) >> 12))).
   Add(Register((((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)
       ? ((inst.Bits() & 0x000F0000) >> 16)
       : 32)))));

  return true;
}

// A(25)=0 & op1(24:20)=xx0x1 & Rn(19:16)=1111 & op1_repeated(24:20)=~0x011 & $pattern(31:0)=xxxxxxx1xx0xxxxxxxxxxxxxxxxxxxxx
//    = {Pc: 15,
//       Rt: Rt(15:12),
//       actual: Actual_LDR_literal_cccc0101u0011111ttttiiiiiiiiiiii_case_1,
//       base: Pc,
//       baseline: Load2RegisterImm12Op,
//       constraints: ,
//       defs: {Rt},
//       fields: [Rt(15:12)],
//       generated_baseline: LDR_literal_cccc0101u0011111ttttiiiiiiiiiiii_case_0,
//       is_literal_load: true,
//       pattern: cccc0101u0011111ttttiiiiiiiiiiii,
//       rule: LDR_literal,
//       safety: [Rt  ==
//               Pc => FORBIDDEN_OPERANDS],
//       true: true,
//       uses: {Pc}}
class Load2RegisterImm12OpTesterCase6
    : public LoadStore2RegisterImm12OpTester {
 public:
  Load2RegisterImm12OpTesterCase6(const NamedClassDecoder& decoder)
    : LoadStore2RegisterImm12OpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
  virtual bool ApplySanityChecks(nacl_arm_dec::Instruction inst,
                                 const NamedClassDecoder& decoder);
};

bool Load2RegisterImm12OpTesterCase6
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~0
  if ((inst.Bits() & 0x02000000)  !=
          0x00000000) return false;
  // op1(24:20)=~xx0x1
  if ((inst.Bits() & 0x00500000)  !=
          0x00100000) return false;
  // Rn(19:16)=~1111
  if ((inst.Bits() & 0x000F0000)  !=
          0x000F0000) return false;
  // op1_repeated(24:20)=0x011
  if ((inst.Bits() & 0x01700000)  ==
          0x00300000) return false;
  // $pattern(31:0)=~xxxxxxx1xx0xxxxxxxxxxxxxxxxxxxxx
  if ((inst.Bits() & 0x01200000)  !=
          0x01000000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return LoadStore2RegisterImm12OpTester::
      PassesParsePreconditions(inst, decoder);
}

bool Load2RegisterImm12OpTesterCase6
::ApplySanityChecks(nacl_arm_dec::Instruction inst,
                    const NamedClassDecoder& decoder) {
  NC_PRECOND(LoadStore2RegisterImm12OpTester::
               ApplySanityChecks(inst, decoder));

  // safety: Rt  ==
  //          Pc => FORBIDDEN_OPERANDS
  EXPECT_TRUE(((((inst.Bits() & 0x0000F000) >> 12)) != (15)));

  // defs: {Rt};
  EXPECT_TRUE(decoder.defs(inst).IsSame(RegisterList().
   Add(Register(((inst.Bits() & 0x0000F000) >> 12)))));

  return true;
}

// A(25)=0 & op1(24:20)=xx1x0 & op1_repeated(24:20)=~0x110
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_STRB_immediate_cccc010pu1w0nnnnttttiiiiiiiiiiii_case_1,
//       base: Rn,
//       baseline: Store2RegisterImm12Op,
//       constraints: ,
//       defs: {base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12)],
//       generated_baseline: STRB_immediate_cccc010pu1w0nnnnttttiiiiiiiiiiii_case_0,
//       pattern: cccc010pu1w0nnnnttttiiiiiiiiiiii,
//       rule: STRB_immediate,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Rt  ==
//               Pc => UNPREDICTABLE,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE],
//       small_imm_base_wb: wback,
//       uses: {Rn, Rt},
//       wback: P(24)=0 ||
//            W(21)=1}
class Store2RegisterImm12OpTesterCase7
    : public LoadStore2RegisterImm12OpTester {
 public:
  Store2RegisterImm12OpTesterCase7(const NamedClassDecoder& decoder)
    : LoadStore2RegisterImm12OpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
  virtual bool ApplySanityChecks(nacl_arm_dec::Instruction inst,
                                 const NamedClassDecoder& decoder);
};

bool Store2RegisterImm12OpTesterCase7
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~0
  if ((inst.Bits() & 0x02000000)  !=
          0x00000000) return false;
  // op1(24:20)=~xx1x0
  if ((inst.Bits() & 0x00500000)  !=
          0x00400000) return false;
  // op1_repeated(24:20)=0x110
  if ((inst.Bits() & 0x01700000)  ==
          0x00600000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return LoadStore2RegisterImm12OpTester::
      PassesParsePreconditions(inst, decoder);
}

bool Store2RegisterImm12OpTesterCase7
::ApplySanityChecks(nacl_arm_dec::Instruction inst,
                    const NamedClassDecoder& decoder) {
  NC_PRECOND(LoadStore2RegisterImm12OpTester::
               ApplySanityChecks(inst, decoder));

  // safety: P(24)=0 &&
  //       W(21)=1 => DECODER_ERROR
  EXPECT_TRUE(!(((inst.Bits() & 0x01000000)  ==
          0x00000000) &&
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)));

  // safety: Rt  ==
  //          Pc => UNPREDICTABLE
  EXPECT_TRUE(((((inst.Bits() & 0x0000F000) >> 12)) != (15)));

  // safety: wback &&
  //       (Rn  ==
  //          Pc ||
  //       Rn  ==
  //          Rt) => UNPREDICTABLE
  EXPECT_TRUE(!((((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)) &&
       (((((((inst.Bits() & 0x000F0000) >> 16)) == (15))) ||
       (((((inst.Bits() & 0x000F0000) >> 16)) == (((inst.Bits() & 0x0000F000) >> 12))))))));

  // defs: {base
  //       if wback
  //       else None};
  EXPECT_TRUE(decoder.defs(inst).IsSame(RegisterList().
   Add(Register((((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)
       ? ((inst.Bits() & 0x000F0000) >> 16)
       : 32)))));

  return true;
}

// A(25)=0 & op1(24:20)=xx1x1 & Rn(19:16)=~1111 & op1_repeated(24:20)=~0x111
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_LDRB_immediate_cccc010pu1w1nnnnttttiiiiiiiiiiii_case_1,
//       base: Rn,
//       baseline: Load2RegisterImm12Op,
//       constraints: ,
//       defs: {Rt, base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12)],
//       generated_baseline: LDRB_immediate_cccc010pu1w1nnnnttttiiiiiiiiiiii_case_0,
//       pattern: cccc010pu1w1nnnnttttiiiiiiiiiiii,
//       rule: LDRB_immediate,
//       safety: [Rn  ==
//               Pc => DECODER_ERROR,
//         P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Rt  ==
//               Pc => UNPREDICTABLE,
//         wback &&
//            Rn  ==
//               Rt => UNPREDICTABLE],
//       small_imm_base_wb: wback,
//       uses: {Rn},
//       wback: P(24)=0 ||
//            W(21)=1}
class Load2RegisterImm12OpTesterCase8
    : public LoadStore2RegisterImm12OpTester {
 public:
  Load2RegisterImm12OpTesterCase8(const NamedClassDecoder& decoder)
    : LoadStore2RegisterImm12OpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
  virtual bool ApplySanityChecks(nacl_arm_dec::Instruction inst,
                                 const NamedClassDecoder& decoder);
};

bool Load2RegisterImm12OpTesterCase8
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~0
  if ((inst.Bits() & 0x02000000)  !=
          0x00000000) return false;
  // op1(24:20)=~xx1x1
  if ((inst.Bits() & 0x00500000)  !=
          0x00500000) return false;
  // Rn(19:16)=1111
  if ((inst.Bits() & 0x000F0000)  ==
          0x000F0000) return false;
  // op1_repeated(24:20)=0x111
  if ((inst.Bits() & 0x01700000)  ==
          0x00700000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return LoadStore2RegisterImm12OpTester::
      PassesParsePreconditions(inst, decoder);
}

bool Load2RegisterImm12OpTesterCase8
::ApplySanityChecks(nacl_arm_dec::Instruction inst,
                    const NamedClassDecoder& decoder) {
  NC_PRECOND(LoadStore2RegisterImm12OpTester::
               ApplySanityChecks(inst, decoder));

  // safety: Rn  ==
  //          Pc => DECODER_ERROR
  EXPECT_TRUE(((((inst.Bits() & 0x000F0000) >> 16)) != (15)));

  // safety: P(24)=0 &&
  //       W(21)=1 => DECODER_ERROR
  EXPECT_TRUE(!(((inst.Bits() & 0x01000000)  ==
          0x00000000) &&
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)));

  // safety: Rt  ==
  //          Pc => UNPREDICTABLE
  EXPECT_TRUE(((((inst.Bits() & 0x0000F000) >> 12)) != (15)));

  // safety: wback &&
  //       Rn  ==
  //          Rt => UNPREDICTABLE
  EXPECT_TRUE(!((((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)) &&
       (((((inst.Bits() & 0x000F0000) >> 16)) == (((inst.Bits() & 0x0000F000) >> 12))))));

  // defs: {Rt, base
  //       if wback
  //       else None};
  EXPECT_TRUE(decoder.defs(inst).IsSame(RegisterList().
   Add(Register(((inst.Bits() & 0x0000F000) >> 12))).
   Add(Register((((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)
       ? ((inst.Bits() & 0x000F0000) >> 16)
       : 32)))));

  return true;
}

// A(25)=0 & op1(24:20)=xx1x1 & Rn(19:16)=1111 & op1_repeated(24:20)=~0x111 & $pattern(31:0)=xxxxxxx1xx0xxxxxxxxxxxxxxxxxxxxx
//    = {Pc: 15,
//       Rt: Rt(15:12),
//       actual: Actual_LDRB_literal_cccc0101u1011111ttttiiiiiiiiiiii_case_1,
//       base: Pc,
//       baseline: Load2RegisterImm12Op,
//       constraints: ,
//       defs: {Rt},
//       fields: [Rt(15:12)],
//       generated_baseline: LDRB_literal_cccc0101u1011111ttttiiiiiiiiiiii_case_0,
//       is_literal_load: true,
//       pattern: cccc0101u1011111ttttiiiiiiiiiiii,
//       rule: LDRB_literal,
//       safety: [Rt  ==
//               Pc => UNPREDICTABLE],
//       true: true,
//       uses: {Pc}}
class Load2RegisterImm12OpTesterCase9
    : public LoadStore2RegisterImm12OpTester {
 public:
  Load2RegisterImm12OpTesterCase9(const NamedClassDecoder& decoder)
    : LoadStore2RegisterImm12OpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
  virtual bool ApplySanityChecks(nacl_arm_dec::Instruction inst,
                                 const NamedClassDecoder& decoder);
};

bool Load2RegisterImm12OpTesterCase9
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~0
  if ((inst.Bits() & 0x02000000)  !=
          0x00000000) return false;
  // op1(24:20)=~xx1x1
  if ((inst.Bits() & 0x00500000)  !=
          0x00500000) return false;
  // Rn(19:16)=~1111
  if ((inst.Bits() & 0x000F0000)  !=
          0x000F0000) return false;
  // op1_repeated(24:20)=0x111
  if ((inst.Bits() & 0x01700000)  ==
          0x00700000) return false;
  // $pattern(31:0)=~xxxxxxx1xx0xxxxxxxxxxxxxxxxxxxxx
  if ((inst.Bits() & 0x01200000)  !=
          0x01000000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return LoadStore2RegisterImm12OpTester::
      PassesParsePreconditions(inst, decoder);
}

bool Load2RegisterImm12OpTesterCase9
::ApplySanityChecks(nacl_arm_dec::Instruction inst,
                    const NamedClassDecoder& decoder) {
  NC_PRECOND(LoadStore2RegisterImm12OpTester::
               ApplySanityChecks(inst, decoder));

  // safety: Rt  ==
  //          Pc => UNPREDICTABLE
  EXPECT_TRUE(((((inst.Bits() & 0x0000F000) >> 12)) != (15)));

  // defs: {Rt};
  EXPECT_TRUE(decoder.defs(inst).IsSame(RegisterList().
   Add(Register(((inst.Bits() & 0x0000F000) >> 12)))));

  return true;
}

// A(25)=1 & op1(24:20)=0x010 & B(4)=0
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0110u010nnnnttttiiiiitt0mmmm,
//       rule: STRT_A2}
class ForbiddenCondDecoderTesterCase10
    : public UnsafeCondDecoderTester {
 public:
  ForbiddenCondDecoderTesterCase10(const NamedClassDecoder& decoder)
    : UnsafeCondDecoderTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool ForbiddenCondDecoderTesterCase10
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~1
  if ((inst.Bits() & 0x02000000)  !=
          0x02000000) return false;
  // op1(24:20)=~0x010
  if ((inst.Bits() & 0x01700000)  !=
          0x00200000) return false;
  // B(4)=~0
  if ((inst.Bits() & 0x00000010)  !=
          0x00000000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return UnsafeCondDecoderTester::
      PassesParsePreconditions(inst, decoder);
}

// A(25)=1 & op1(24:20)=0x011 & B(4)=0
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0110u011nnnnttttiiiiitt0mmmm,
//       rule: LDRT_A2}
class ForbiddenCondDecoderTesterCase11
    : public UnsafeCondDecoderTester {
 public:
  ForbiddenCondDecoderTesterCase11(const NamedClassDecoder& decoder)
    : UnsafeCondDecoderTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool ForbiddenCondDecoderTesterCase11
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~1
  if ((inst.Bits() & 0x02000000)  !=
          0x02000000) return false;
  // op1(24:20)=~0x011
  if ((inst.Bits() & 0x01700000)  !=
          0x00300000) return false;
  // B(4)=~0
  if ((inst.Bits() & 0x00000010)  !=
          0x00000000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return UnsafeCondDecoderTester::
      PassesParsePreconditions(inst, decoder);
}

// A(25)=1 & op1(24:20)=0x110 & B(4)=0
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0110u110nnnnttttiiiiitt0mmmm,
//       rule: STRBT_A2}
class ForbiddenCondDecoderTesterCase12
    : public UnsafeCondDecoderTester {
 public:
  ForbiddenCondDecoderTesterCase12(const NamedClassDecoder& decoder)
    : UnsafeCondDecoderTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool ForbiddenCondDecoderTesterCase12
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~1
  if ((inst.Bits() & 0x02000000)  !=
          0x02000000) return false;
  // op1(24:20)=~0x110
  if ((inst.Bits() & 0x01700000)  !=
          0x00600000) return false;
  // B(4)=~0
  if ((inst.Bits() & 0x00000010)  !=
          0x00000000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return UnsafeCondDecoderTester::
      PassesParsePreconditions(inst, decoder);
}

// A(25)=1 & op1(24:20)=0x111 & B(4)=0
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0110u111nnnnttttiiiiitt0mmmm,
//       rule: LDRBT_A2}
class ForbiddenCondDecoderTesterCase13
    : public UnsafeCondDecoderTester {
 public:
  ForbiddenCondDecoderTesterCase13(const NamedClassDecoder& decoder)
    : UnsafeCondDecoderTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool ForbiddenCondDecoderTesterCase13
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~1
  if ((inst.Bits() & 0x02000000)  !=
          0x02000000) return false;
  // op1(24:20)=~0x111
  if ((inst.Bits() & 0x01700000)  !=
          0x00700000) return false;
  // B(4)=~0
  if ((inst.Bits() & 0x00000010)  !=
          0x00000000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return UnsafeCondDecoderTester::
      PassesParsePreconditions(inst, decoder);
}

// A(25)=1 & op1(24:20)=xx0x0 & B(4)=0 & op1_repeated(24:20)=~0x010
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rm: Rm(3:0),
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_STR_register_cccc011pd0w0nnnnttttiiiiitt0mmmm_case_1,
//       base: Rn,
//       baseline: Store3RegisterImm5Op,
//       constraints: ,
//       defs: {base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12), Rm(3:0)],
//       generated_baseline: STR_register_cccc011pd0w0nnnnttttiiiiitt0mmmm_case_0,
//       index: P(24)=1,
//       pattern: cccc011pd0w0nnnnttttiiiiitt0mmmm,
//       rule: STR_register,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Rm  ==
//               Pc => UNPREDICTABLE,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE,
//         ArchVersion()  <
//               6 &&
//            wback &&
//            Rn  ==
//               Rm => UNPREDICTABLE,
//         index => FORBIDDEN],
//       uses: {Rm, Rn, Rt},
//       wback: P(24)=0 ||
//            W(21)=1}
class Store3RegisterImm5OpTesterCase14
    : public LoadStore3RegisterImm5OpTester {
 public:
  Store3RegisterImm5OpTesterCase14(const NamedClassDecoder& decoder)
    : LoadStore3RegisterImm5OpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
  virtual bool ApplySanityChecks(nacl_arm_dec::Instruction inst,
                                 const NamedClassDecoder& decoder);
};

bool Store3RegisterImm5OpTesterCase14
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~1
  if ((inst.Bits() & 0x02000000)  !=
          0x02000000) return false;
  // op1(24:20)=~xx0x0
  if ((inst.Bits() & 0x00500000)  !=
          0x00000000) return false;
  // B(4)=~0
  if ((inst.Bits() & 0x00000010)  !=
          0x00000000) return false;
  // op1_repeated(24:20)=0x010
  if ((inst.Bits() & 0x01700000)  ==
          0x00200000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return LoadStore3RegisterImm5OpTester::
      PassesParsePreconditions(inst, decoder);
}

bool Store3RegisterImm5OpTesterCase14
::ApplySanityChecks(nacl_arm_dec::Instruction inst,
                    const NamedClassDecoder& decoder) {
  NC_PRECOND(LoadStore3RegisterImm5OpTester::
               ApplySanityChecks(inst, decoder));

  // safety: P(24)=0 &&
  //       W(21)=1 => DECODER_ERROR
  EXPECT_TRUE(!(((inst.Bits() & 0x01000000)  ==
          0x00000000) &&
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)));

  // safety: Rm  ==
  //          Pc => UNPREDICTABLE
  EXPECT_TRUE((((inst.Bits() & 0x0000000F)) != (15)));

  // safety: wback &&
  //       (Rn  ==
  //          Pc ||
  //       Rn  ==
  //          Rt) => UNPREDICTABLE
  EXPECT_TRUE(!((((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)) &&
       (((((((inst.Bits() & 0x000F0000) >> 16)) == (15))) ||
       (((((inst.Bits() & 0x000F0000) >> 16)) == (((inst.Bits() & 0x0000F000) >> 12))))))));

  // safety: ArchVersion()  <
  //          6 &&
  //       wback &&
  //       Rn  ==
  //          Rm => UNPREDICTABLE
  EXPECT_TRUE(!((((nacl_arm_dec::ArchVersion()) < (6))) &&
       (((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)) &&
       (((((inst.Bits() & 0x000F0000) >> 16)) == ((inst.Bits() & 0x0000000F))))));

  // safety: index => FORBIDDEN
  EXPECT_TRUE(!((inst.Bits() & 0x01000000)  ==
          0x01000000));

  // defs: {base
  //       if wback
  //       else None};
  EXPECT_TRUE(decoder.defs(inst).IsSame(RegisterList().
   Add(Register((((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)
       ? ((inst.Bits() & 0x000F0000) >> 16)
       : 32)))));

  return true;
}

// A(25)=1 & op1(24:20)=xx0x1 & B(4)=0 & op1_repeated(24:20)=~0x011
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rm: Rm(3:0),
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_LDR_register_cccc011pu0w1nnnnttttiiiiitt0mmmm_case_1,
//       base: Rn,
//       baseline: Load3RegisterImm5Op,
//       constraints: ,
//       defs: {Rt, base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12), Rm(3:0)],
//       generated_baseline: LDR_register_cccc011pu0w1nnnnttttiiiiitt0mmmm_case_0,
//       index: P(24)=1,
//       pattern: cccc011pu0w1nnnnttttiiiiitt0mmmm,
//       rule: LDR_register,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Rm  ==
//               Pc => UNPREDICTABLE,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE,
//         ArchVersion()  <
//               6 &&
//            wback &&
//            Rn  ==
//               Rm => UNPREDICTABLE,
//         index => FORBIDDEN,
//         Rt  ==
//               Pc => FORBIDDEN_OPERANDS],
//       uses: {Rm, Rn},
//       wback: P(24)=0 ||
//            W(21)=1}
class Load3RegisterImm5OpTesterCase15
    : public LoadStore3RegisterImm5OpTester {
 public:
  Load3RegisterImm5OpTesterCase15(const NamedClassDecoder& decoder)
    : LoadStore3RegisterImm5OpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
  virtual bool ApplySanityChecks(nacl_arm_dec::Instruction inst,
                                 const NamedClassDecoder& decoder);
};

bool Load3RegisterImm5OpTesterCase15
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~1
  if ((inst.Bits() & 0x02000000)  !=
          0x02000000) return false;
  // op1(24:20)=~xx0x1
  if ((inst.Bits() & 0x00500000)  !=
          0x00100000) return false;
  // B(4)=~0
  if ((inst.Bits() & 0x00000010)  !=
          0x00000000) return false;
  // op1_repeated(24:20)=0x011
  if ((inst.Bits() & 0x01700000)  ==
          0x00300000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return LoadStore3RegisterImm5OpTester::
      PassesParsePreconditions(inst, decoder);
}

bool Load3RegisterImm5OpTesterCase15
::ApplySanityChecks(nacl_arm_dec::Instruction inst,
                    const NamedClassDecoder& decoder) {
  NC_PRECOND(LoadStore3RegisterImm5OpTester::
               ApplySanityChecks(inst, decoder));

  // safety: P(24)=0 &&
  //       W(21)=1 => DECODER_ERROR
  EXPECT_TRUE(!(((inst.Bits() & 0x01000000)  ==
          0x00000000) &&
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)));

  // safety: Rm  ==
  //          Pc => UNPREDICTABLE
  EXPECT_TRUE((((inst.Bits() & 0x0000000F)) != (15)));

  // safety: wback &&
  //       (Rn  ==
  //          Pc ||
  //       Rn  ==
  //          Rt) => UNPREDICTABLE
  EXPECT_TRUE(!((((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)) &&
       (((((((inst.Bits() & 0x000F0000) >> 16)) == (15))) ||
       (((((inst.Bits() & 0x000F0000) >> 16)) == (((inst.Bits() & 0x0000F000) >> 12))))))));

  // safety: ArchVersion()  <
  //          6 &&
  //       wback &&
  //       Rn  ==
  //          Rm => UNPREDICTABLE
  EXPECT_TRUE(!((((nacl_arm_dec::ArchVersion()) < (6))) &&
       (((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)) &&
       (((((inst.Bits() & 0x000F0000) >> 16)) == ((inst.Bits() & 0x0000000F))))));

  // safety: index => FORBIDDEN
  EXPECT_TRUE(!((inst.Bits() & 0x01000000)  ==
          0x01000000));

  // safety: Rt  ==
  //          Pc => FORBIDDEN_OPERANDS
  EXPECT_TRUE(((((inst.Bits() & 0x0000F000) >> 12)) != (15)));

  // defs: {Rt, base
  //       if wback
  //       else None};
  EXPECT_TRUE(decoder.defs(inst).IsSame(RegisterList().
   Add(Register(((inst.Bits() & 0x0000F000) >> 12))).
   Add(Register((((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)
       ? ((inst.Bits() & 0x000F0000) >> 16)
       : 32)))));

  return true;
}

// A(25)=1 & op1(24:20)=xx1x0 & B(4)=0 & op1_repeated(24:20)=~0x110
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rm: Rm(3:0),
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_STRB_register_cccc011pu1w0nnnnttttiiiiitt0mmmm_case_1,
//       base: Rn,
//       baseline: Store3RegisterImm5Op,
//       constraints: ,
//       defs: {base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12), Rm(3:0)],
//       generated_baseline: STRB_register_cccc011pu1w0nnnnttttiiiiitt0mmmm_case_0,
//       index: P(24)=1,
//       pattern: cccc011pu1w0nnnnttttiiiiitt0mmmm,
//       rule: STRB_register,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Pc in {Rm, Rt} => UNPREDICTABLE,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE,
//         ArchVersion()  <
//               6 &&
//            wback &&
//            Rn  ==
//               Rm => UNPREDICTABLE,
//         index => FORBIDDEN],
//       uses: {Rm, Rn, Rt},
//       wback: P(24)=0 ||
//            W(21)=1}
class Store3RegisterImm5OpTesterCase16
    : public LoadStore3RegisterImm5OpTester {
 public:
  Store3RegisterImm5OpTesterCase16(const NamedClassDecoder& decoder)
    : LoadStore3RegisterImm5OpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
  virtual bool ApplySanityChecks(nacl_arm_dec::Instruction inst,
                                 const NamedClassDecoder& decoder);
};

bool Store3RegisterImm5OpTesterCase16
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~1
  if ((inst.Bits() & 0x02000000)  !=
          0x02000000) return false;
  // op1(24:20)=~xx1x0
  if ((inst.Bits() & 0x00500000)  !=
          0x00400000) return false;
  // B(4)=~0
  if ((inst.Bits() & 0x00000010)  !=
          0x00000000) return false;
  // op1_repeated(24:20)=0x110
  if ((inst.Bits() & 0x01700000)  ==
          0x00600000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return LoadStore3RegisterImm5OpTester::
      PassesParsePreconditions(inst, decoder);
}

bool Store3RegisterImm5OpTesterCase16
::ApplySanityChecks(nacl_arm_dec::Instruction inst,
                    const NamedClassDecoder& decoder) {
  NC_PRECOND(LoadStore3RegisterImm5OpTester::
               ApplySanityChecks(inst, decoder));

  // safety: P(24)=0 &&
  //       W(21)=1 => DECODER_ERROR
  EXPECT_TRUE(!(((inst.Bits() & 0x01000000)  ==
          0x00000000) &&
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)));

  // safety: Pc in {Rm, Rt} => UNPREDICTABLE
  EXPECT_TRUE(!((((15) == ((inst.Bits() & 0x0000000F)))) ||
       (((15) == (((inst.Bits() & 0x0000F000) >> 12))))));

  // safety: wback &&
  //       (Rn  ==
  //          Pc ||
  //       Rn  ==
  //          Rt) => UNPREDICTABLE
  EXPECT_TRUE(!((((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)) &&
       (((((((inst.Bits() & 0x000F0000) >> 16)) == (15))) ||
       (((((inst.Bits() & 0x000F0000) >> 16)) == (((inst.Bits() & 0x0000F000) >> 12))))))));

  // safety: ArchVersion()  <
  //          6 &&
  //       wback &&
  //       Rn  ==
  //          Rm => UNPREDICTABLE
  EXPECT_TRUE(!((((nacl_arm_dec::ArchVersion()) < (6))) &&
       (((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)) &&
       (((((inst.Bits() & 0x000F0000) >> 16)) == ((inst.Bits() & 0x0000000F))))));

  // safety: index => FORBIDDEN
  EXPECT_TRUE(!((inst.Bits() & 0x01000000)  ==
          0x01000000));

  // defs: {base
  //       if wback
  //       else None};
  EXPECT_TRUE(decoder.defs(inst).IsSame(RegisterList().
   Add(Register((((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)
       ? ((inst.Bits() & 0x000F0000) >> 16)
       : 32)))));

  return true;
}

// A(25)=1 & op1(24:20)=xx1x1 & B(4)=0 & op1_repeated(24:20)=~0x111
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rm: Rm(3:0),
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_LDRB_register_cccc011pu1w1nnnnttttiiiiitt0mmmm_case_1,
//       base: Rn,
//       baseline: Load3RegisterImm5Op,
//       constraints: ,
//       defs: {Rt, base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12), Rm(3:0)],
//       generated_baseline: LDRB_register_cccc011pu1w1nnnnttttiiiiitt0mmmm_case_0,
//       index: P(24)=1,
//       pattern: cccc011pu1w1nnnnttttiiiiitt0mmmm,
//       rule: LDRB_register,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Pc in {Rt, Rm} => UNPREDICTABLE,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE,
//         ArchVersion()  <
//               6 &&
//            wback &&
//            Rn  ==
//               Rm => UNPREDICTABLE,
//         index => FORBIDDEN],
//       uses: {Rm, Rn},
//       wback: P(24)=0 ||
//            W(21)=1}
class Load3RegisterImm5OpTesterCase17
    : public LoadStore3RegisterImm5OpTester {
 public:
  Load3RegisterImm5OpTesterCase17(const NamedClassDecoder& decoder)
    : LoadStore3RegisterImm5OpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
  virtual bool ApplySanityChecks(nacl_arm_dec::Instruction inst,
                                 const NamedClassDecoder& decoder);
};

bool Load3RegisterImm5OpTesterCase17
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  // A(25)=~1
  if ((inst.Bits() & 0x02000000)  !=
          0x02000000) return false;
  // op1(24:20)=~xx1x1
  if ((inst.Bits() & 0x00500000)  !=
          0x00500000) return false;
  // B(4)=~0
  if ((inst.Bits() & 0x00000010)  !=
          0x00000000) return false;
  // op1_repeated(24:20)=0x111
  if ((inst.Bits() & 0x01700000)  ==
          0x00700000) return false;

  // if cond(31:28)=1111, don't test instruction.
  if ((inst.Bits() & 0xF0000000) == 0xF0000000) return false;

  // Check other preconditions defined for the base decoder.
  return LoadStore3RegisterImm5OpTester::
      PassesParsePreconditions(inst, decoder);
}

bool Load3RegisterImm5OpTesterCase17
::ApplySanityChecks(nacl_arm_dec::Instruction inst,
                    const NamedClassDecoder& decoder) {
  NC_PRECOND(LoadStore3RegisterImm5OpTester::
               ApplySanityChecks(inst, decoder));

  // safety: P(24)=0 &&
  //       W(21)=1 => DECODER_ERROR
  EXPECT_TRUE(!(((inst.Bits() & 0x01000000)  ==
          0x00000000) &&
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)));

  // safety: Pc in {Rt, Rm} => UNPREDICTABLE
  EXPECT_TRUE(!((((15) == (((inst.Bits() & 0x0000F000) >> 12)))) ||
       (((15) == ((inst.Bits() & 0x0000000F))))));

  // safety: wback &&
  //       (Rn  ==
  //          Pc ||
  //       Rn  ==
  //          Rt) => UNPREDICTABLE
  EXPECT_TRUE(!((((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)) &&
       (((((((inst.Bits() & 0x000F0000) >> 16)) == (15))) ||
       (((((inst.Bits() & 0x000F0000) >> 16)) == (((inst.Bits() & 0x0000F000) >> 12))))))));

  // safety: ArchVersion()  <
  //          6 &&
  //       wback &&
  //       Rn  ==
  //          Rm => UNPREDICTABLE
  EXPECT_TRUE(!((((nacl_arm_dec::ArchVersion()) < (6))) &&
       (((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)) &&
       (((((inst.Bits() & 0x000F0000) >> 16)) == ((inst.Bits() & 0x0000000F))))));

  // safety: index => FORBIDDEN
  EXPECT_TRUE(!((inst.Bits() & 0x01000000)  ==
          0x01000000));

  // defs: {Rt, base
  //       if wback
  //       else None};
  EXPECT_TRUE(decoder.defs(inst).IsSame(RegisterList().
   Add(Register(((inst.Bits() & 0x0000F000) >> 12))).
   Add(Register((((inst.Bits() & 0x01000000)  ==
          0x00000000) ||
       ((inst.Bits() & 0x00200000)  ==
          0x00200000)
       ? ((inst.Bits() & 0x000F0000) >> 16)
       : 32)))));

  return true;
}

// The following are derived class decoder testers for decoder actions
// associated with a pattern of an action. These derived classes introduce
// a default constructor that automatically initializes the expected decoder
// to the corresponding instance in the generated DecoderState.

// A(25)=0 & op1(24:20)=0x010
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0100u010nnnnttttiiiiiiiiiiii,
//       rule: STRT_A1}
class ForbiddenCondDecoderTester_Case0
    : public ForbiddenCondDecoderTesterCase0 {
 public:
  ForbiddenCondDecoderTester_Case0()
    : ForbiddenCondDecoderTesterCase0(
      state_.ForbiddenCondDecoder_STRT_A1_instance_)
  {}
};

// A(25)=0 & op1(24:20)=0x011
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0100u011nnnnttttiiiiiiiiiiii,
//       rule: LDRT_A1}
class ForbiddenCondDecoderTester_Case1
    : public ForbiddenCondDecoderTesterCase1 {
 public:
  ForbiddenCondDecoderTester_Case1()
    : ForbiddenCondDecoderTesterCase1(
      state_.ForbiddenCondDecoder_LDRT_A1_instance_)
  {}
};

// A(25)=0 & op1(24:20)=0x110
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0100u110nnnnttttiiiiiiiiiiii,
//       rule: STRBT_A1}
class ForbiddenCondDecoderTester_Case2
    : public ForbiddenCondDecoderTesterCase2 {
 public:
  ForbiddenCondDecoderTester_Case2()
    : ForbiddenCondDecoderTesterCase2(
      state_.ForbiddenCondDecoder_STRBT_A1_instance_)
  {}
};

// A(25)=0 & op1(24:20)=0x111
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0100u111nnnnttttiiiiiiiiiiii,
//       rule: LDRBT_A1}
class ForbiddenCondDecoderTester_Case3
    : public ForbiddenCondDecoderTesterCase3 {
 public:
  ForbiddenCondDecoderTester_Case3()
    : ForbiddenCondDecoderTesterCase3(
      state_.ForbiddenCondDecoder_LDRBT_A1_instance_)
  {}
};

// A(25)=0 & op1(24:20)=xx0x0 & op1_repeated(24:20)=~0x010
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_STR_immediate_cccc010pu0w0nnnnttttiiiiiiiiiiii_case_1,
//       base: Rn,
//       baseline: Store2RegisterImm12Op,
//       constraints: ,
//       defs: {base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12)],
//       generated_baseline: STR_immediate_cccc010pu0w0nnnnttttiiiiiiiiiiii_case_0,
//       pattern: cccc010pu0w0nnnnttttiiiiiiiiiiii,
//       rule: STR_immediate,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE],
//       small_imm_base_wb: wback,
//       uses: {Rn, Rt},
//       wback: P(24)=0 ||
//            W(21)=1}
class Store2RegisterImm12OpTester_Case4
    : public Store2RegisterImm12OpTesterCase4 {
 public:
  Store2RegisterImm12OpTester_Case4()
    : Store2RegisterImm12OpTesterCase4(
      state_.Store2RegisterImm12Op_STR_immediate_instance_)
  {}
};

// A(25)=0 & op1(24:20)=xx0x1 & Rn(19:16)=~1111 & op1_repeated(24:20)=~0x011
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       Tp: 9,
//       U: U(23),
//       W: W(21),
//       actual: Actual_LDR_immediate_cccc010pu0w1nnnnttttiiiiiiiiiiii_case_1,
//       add: U(23)=1,
//       base: Rn,
//       baseline: LdrImmediateOp,
//       constraints: ,
//       defs: {Rt, base
//            if wback
//            else None},
//       fields: [P(24), U(23), W(21), Rn(19:16), Rt(15:12), imm12(11:0)],
//       generated_baseline: LDR_immediate_cccc010pu0w1nnnnttttiiiiiiiiiiii_case_0,
//       imm12: imm12(11:0),
//       index: P(24)=1,
//       is_load_tp: Rn  ==
//               Tp &&
//            index &&
//            not wback &&
//            add &&
//            imm12 in {0, 4},
//       pattern: cccc010pu0w1nnnnttttiiiiiiiiiiii,
//       rule: LDR_immediate,
//       safety: [Rn  ==
//               Pc => DECODER_ERROR,
//         P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         wback &&
//            Rn  ==
//               Rt => UNPREDICTABLE,
//         Rt  ==
//               Pc => FORBIDDEN_OPERANDS],
//       small_imm_base_wb: wback,
//       uses: {Rn},
//       wback: P(24)=0 ||
//            W(21)=1}
class LdrImmediateOpTester_Case5
    : public LdrImmediateOpTesterCase5 {
 public:
  LdrImmediateOpTester_Case5()
    : LdrImmediateOpTesterCase5(
      state_.LdrImmediateOp_LDR_immediate_instance_)
  {}
};

// A(25)=0 & op1(24:20)=xx0x1 & Rn(19:16)=1111 & op1_repeated(24:20)=~0x011 & $pattern(31:0)=xxxxxxx1xx0xxxxxxxxxxxxxxxxxxxxx
//    = {Pc: 15,
//       Rt: Rt(15:12),
//       actual: Actual_LDR_literal_cccc0101u0011111ttttiiiiiiiiiiii_case_1,
//       base: Pc,
//       baseline: Load2RegisterImm12Op,
//       constraints: ,
//       defs: {Rt},
//       fields: [Rt(15:12)],
//       generated_baseline: LDR_literal_cccc0101u0011111ttttiiiiiiiiiiii_case_0,
//       is_literal_load: true,
//       pattern: cccc0101u0011111ttttiiiiiiiiiiii,
//       rule: LDR_literal,
//       safety: [Rt  ==
//               Pc => FORBIDDEN_OPERANDS],
//       true: true,
//       uses: {Pc}}
class Load2RegisterImm12OpTester_Case6
    : public Load2RegisterImm12OpTesterCase6 {
 public:
  Load2RegisterImm12OpTester_Case6()
    : Load2RegisterImm12OpTesterCase6(
      state_.Load2RegisterImm12Op_LDR_literal_instance_)
  {}
};

// A(25)=0 & op1(24:20)=xx1x0 & op1_repeated(24:20)=~0x110
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_STRB_immediate_cccc010pu1w0nnnnttttiiiiiiiiiiii_case_1,
//       base: Rn,
//       baseline: Store2RegisterImm12Op,
//       constraints: ,
//       defs: {base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12)],
//       generated_baseline: STRB_immediate_cccc010pu1w0nnnnttttiiiiiiiiiiii_case_0,
//       pattern: cccc010pu1w0nnnnttttiiiiiiiiiiii,
//       rule: STRB_immediate,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Rt  ==
//               Pc => UNPREDICTABLE,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE],
//       small_imm_base_wb: wback,
//       uses: {Rn, Rt},
//       wback: P(24)=0 ||
//            W(21)=1}
class Store2RegisterImm12OpTester_Case7
    : public Store2RegisterImm12OpTesterCase7 {
 public:
  Store2RegisterImm12OpTester_Case7()
    : Store2RegisterImm12OpTesterCase7(
      state_.Store2RegisterImm12Op_STRB_immediate_instance_)
  {}
};

// A(25)=0 & op1(24:20)=xx1x1 & Rn(19:16)=~1111 & op1_repeated(24:20)=~0x111
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_LDRB_immediate_cccc010pu1w1nnnnttttiiiiiiiiiiii_case_1,
//       base: Rn,
//       baseline: Load2RegisterImm12Op,
//       constraints: ,
//       defs: {Rt, base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12)],
//       generated_baseline: LDRB_immediate_cccc010pu1w1nnnnttttiiiiiiiiiiii_case_0,
//       pattern: cccc010pu1w1nnnnttttiiiiiiiiiiii,
//       rule: LDRB_immediate,
//       safety: [Rn  ==
//               Pc => DECODER_ERROR,
//         P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Rt  ==
//               Pc => UNPREDICTABLE,
//         wback &&
//            Rn  ==
//               Rt => UNPREDICTABLE],
//       small_imm_base_wb: wback,
//       uses: {Rn},
//       wback: P(24)=0 ||
//            W(21)=1}
class Load2RegisterImm12OpTester_Case8
    : public Load2RegisterImm12OpTesterCase8 {
 public:
  Load2RegisterImm12OpTester_Case8()
    : Load2RegisterImm12OpTesterCase8(
      state_.Load2RegisterImm12Op_LDRB_immediate_instance_)
  {}
};

// A(25)=0 & op1(24:20)=xx1x1 & Rn(19:16)=1111 & op1_repeated(24:20)=~0x111 & $pattern(31:0)=xxxxxxx1xx0xxxxxxxxxxxxxxxxxxxxx
//    = {Pc: 15,
//       Rt: Rt(15:12),
//       actual: Actual_LDRB_literal_cccc0101u1011111ttttiiiiiiiiiiii_case_1,
//       base: Pc,
//       baseline: Load2RegisterImm12Op,
//       constraints: ,
//       defs: {Rt},
//       fields: [Rt(15:12)],
//       generated_baseline: LDRB_literal_cccc0101u1011111ttttiiiiiiiiiiii_case_0,
//       is_literal_load: true,
//       pattern: cccc0101u1011111ttttiiiiiiiiiiii,
//       rule: LDRB_literal,
//       safety: [Rt  ==
//               Pc => UNPREDICTABLE],
//       true: true,
//       uses: {Pc}}
class Load2RegisterImm12OpTester_Case9
    : public Load2RegisterImm12OpTesterCase9 {
 public:
  Load2RegisterImm12OpTester_Case9()
    : Load2RegisterImm12OpTesterCase9(
      state_.Load2RegisterImm12Op_LDRB_literal_instance_)
  {}
};

// A(25)=1 & op1(24:20)=0x010 & B(4)=0
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0110u010nnnnttttiiiiitt0mmmm,
//       rule: STRT_A2}
class ForbiddenCondDecoderTester_Case10
    : public ForbiddenCondDecoderTesterCase10 {
 public:
  ForbiddenCondDecoderTester_Case10()
    : ForbiddenCondDecoderTesterCase10(
      state_.ForbiddenCondDecoder_STRT_A2_instance_)
  {}
};

// A(25)=1 & op1(24:20)=0x011 & B(4)=0
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0110u011nnnnttttiiiiitt0mmmm,
//       rule: LDRT_A2}
class ForbiddenCondDecoderTester_Case11
    : public ForbiddenCondDecoderTesterCase11 {
 public:
  ForbiddenCondDecoderTester_Case11()
    : ForbiddenCondDecoderTesterCase11(
      state_.ForbiddenCondDecoder_LDRT_A2_instance_)
  {}
};

// A(25)=1 & op1(24:20)=0x110 & B(4)=0
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0110u110nnnnttttiiiiitt0mmmm,
//       rule: STRBT_A2}
class ForbiddenCondDecoderTester_Case12
    : public ForbiddenCondDecoderTesterCase12 {
 public:
  ForbiddenCondDecoderTester_Case12()
    : ForbiddenCondDecoderTesterCase12(
      state_.ForbiddenCondDecoder_STRBT_A2_instance_)
  {}
};

// A(25)=1 & op1(24:20)=0x111 & B(4)=0
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0110u111nnnnttttiiiiitt0mmmm,
//       rule: LDRBT_A2}
class ForbiddenCondDecoderTester_Case13
    : public ForbiddenCondDecoderTesterCase13 {
 public:
  ForbiddenCondDecoderTester_Case13()
    : ForbiddenCondDecoderTesterCase13(
      state_.ForbiddenCondDecoder_LDRBT_A2_instance_)
  {}
};

// A(25)=1 & op1(24:20)=xx0x0 & B(4)=0 & op1_repeated(24:20)=~0x010
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rm: Rm(3:0),
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_STR_register_cccc011pd0w0nnnnttttiiiiitt0mmmm_case_1,
//       base: Rn,
//       baseline: Store3RegisterImm5Op,
//       constraints: ,
//       defs: {base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12), Rm(3:0)],
//       generated_baseline: STR_register_cccc011pd0w0nnnnttttiiiiitt0mmmm_case_0,
//       index: P(24)=1,
//       pattern: cccc011pd0w0nnnnttttiiiiitt0mmmm,
//       rule: STR_register,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Rm  ==
//               Pc => UNPREDICTABLE,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE,
//         ArchVersion()  <
//               6 &&
//            wback &&
//            Rn  ==
//               Rm => UNPREDICTABLE,
//         index => FORBIDDEN],
//       uses: {Rm, Rn, Rt},
//       wback: P(24)=0 ||
//            W(21)=1}
class Store3RegisterImm5OpTester_Case14
    : public Store3RegisterImm5OpTesterCase14 {
 public:
  Store3RegisterImm5OpTester_Case14()
    : Store3RegisterImm5OpTesterCase14(
      state_.Store3RegisterImm5Op_STR_register_instance_)
  {}
};

// A(25)=1 & op1(24:20)=xx0x1 & B(4)=0 & op1_repeated(24:20)=~0x011
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rm: Rm(3:0),
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_LDR_register_cccc011pu0w1nnnnttttiiiiitt0mmmm_case_1,
//       base: Rn,
//       baseline: Load3RegisterImm5Op,
//       constraints: ,
//       defs: {Rt, base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12), Rm(3:0)],
//       generated_baseline: LDR_register_cccc011pu0w1nnnnttttiiiiitt0mmmm_case_0,
//       index: P(24)=1,
//       pattern: cccc011pu0w1nnnnttttiiiiitt0mmmm,
//       rule: LDR_register,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Rm  ==
//               Pc => UNPREDICTABLE,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE,
//         ArchVersion()  <
//               6 &&
//            wback &&
//            Rn  ==
//               Rm => UNPREDICTABLE,
//         index => FORBIDDEN,
//         Rt  ==
//               Pc => FORBIDDEN_OPERANDS],
//       uses: {Rm, Rn},
//       wback: P(24)=0 ||
//            W(21)=1}
class Load3RegisterImm5OpTester_Case15
    : public Load3RegisterImm5OpTesterCase15 {
 public:
  Load3RegisterImm5OpTester_Case15()
    : Load3RegisterImm5OpTesterCase15(
      state_.Load3RegisterImm5Op_LDR_register_instance_)
  {}
};

// A(25)=1 & op1(24:20)=xx1x0 & B(4)=0 & op1_repeated(24:20)=~0x110
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rm: Rm(3:0),
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_STRB_register_cccc011pu1w0nnnnttttiiiiitt0mmmm_case_1,
//       base: Rn,
//       baseline: Store3RegisterImm5Op,
//       constraints: ,
//       defs: {base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12), Rm(3:0)],
//       generated_baseline: STRB_register_cccc011pu1w0nnnnttttiiiiitt0mmmm_case_0,
//       index: P(24)=1,
//       pattern: cccc011pu1w0nnnnttttiiiiitt0mmmm,
//       rule: STRB_register,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Pc in {Rm, Rt} => UNPREDICTABLE,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE,
//         ArchVersion()  <
//               6 &&
//            wback &&
//            Rn  ==
//               Rm => UNPREDICTABLE,
//         index => FORBIDDEN],
//       uses: {Rm, Rn, Rt},
//       wback: P(24)=0 ||
//            W(21)=1}
class Store3RegisterImm5OpTester_Case16
    : public Store3RegisterImm5OpTesterCase16 {
 public:
  Store3RegisterImm5OpTester_Case16()
    : Store3RegisterImm5OpTesterCase16(
      state_.Store3RegisterImm5Op_STRB_register_instance_)
  {}
};

// A(25)=1 & op1(24:20)=xx1x1 & B(4)=0 & op1_repeated(24:20)=~0x111
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rm: Rm(3:0),
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_LDRB_register_cccc011pu1w1nnnnttttiiiiitt0mmmm_case_1,
//       base: Rn,
//       baseline: Load3RegisterImm5Op,
//       constraints: ,
//       defs: {Rt, base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12), Rm(3:0)],
//       generated_baseline: LDRB_register_cccc011pu1w1nnnnttttiiiiitt0mmmm_case_0,
//       index: P(24)=1,
//       pattern: cccc011pu1w1nnnnttttiiiiitt0mmmm,
//       rule: LDRB_register,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Pc in {Rt, Rm} => UNPREDICTABLE,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE,
//         ArchVersion()  <
//               6 &&
//            wback &&
//            Rn  ==
//               Rm => UNPREDICTABLE,
//         index => FORBIDDEN],
//       uses: {Rm, Rn},
//       wback: P(24)=0 ||
//            W(21)=1}
class Load3RegisterImm5OpTester_Case17
    : public Load3RegisterImm5OpTesterCase17 {
 public:
  Load3RegisterImm5OpTester_Case17()
    : Load3RegisterImm5OpTesterCase17(
      state_.Load3RegisterImm5Op_LDRB_register_instance_)
  {}
};

// Defines a gtest testing harness for tests.
class Arm32DecoderStateTests : public ::testing::Test {
 protected:
  Arm32DecoderStateTests() {}
};

// The following functions test each pattern specified in parse
// decoder tables.

// A(25)=0 & op1(24:20)=0x010
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0100u010nnnnttttiiiiiiiiiiii,
//       rule: STRT_A1}
TEST_F(Arm32DecoderStateTests,
       ForbiddenCondDecoderTester_Case0_TestCase0) {
  ForbiddenCondDecoderTester_Case0 tester;
  tester.Test("cccc0100u010nnnnttttiiiiiiiiiiii");
}

// A(25)=0 & op1(24:20)=0x011
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0100u011nnnnttttiiiiiiiiiiii,
//       rule: LDRT_A1}
TEST_F(Arm32DecoderStateTests,
       ForbiddenCondDecoderTester_Case1_TestCase1) {
  ForbiddenCondDecoderTester_Case1 tester;
  tester.Test("cccc0100u011nnnnttttiiiiiiiiiiii");
}

// A(25)=0 & op1(24:20)=0x110
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0100u110nnnnttttiiiiiiiiiiii,
//       rule: STRBT_A1}
TEST_F(Arm32DecoderStateTests,
       ForbiddenCondDecoderTester_Case2_TestCase2) {
  ForbiddenCondDecoderTester_Case2 tester;
  tester.Test("cccc0100u110nnnnttttiiiiiiiiiiii");
}

// A(25)=0 & op1(24:20)=0x111
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0100u111nnnnttttiiiiiiiiiiii,
//       rule: LDRBT_A1}
TEST_F(Arm32DecoderStateTests,
       ForbiddenCondDecoderTester_Case3_TestCase3) {
  ForbiddenCondDecoderTester_Case3 tester;
  tester.Test("cccc0100u111nnnnttttiiiiiiiiiiii");
}

// A(25)=0 & op1(24:20)=xx0x0 & op1_repeated(24:20)=~0x010
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_STR_immediate_cccc010pu0w0nnnnttttiiiiiiiiiiii_case_1,
//       base: Rn,
//       baseline: Store2RegisterImm12Op,
//       constraints: ,
//       defs: {base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12)],
//       generated_baseline: STR_immediate_cccc010pu0w0nnnnttttiiiiiiiiiiii_case_0,
//       pattern: cccc010pu0w0nnnnttttiiiiiiiiiiii,
//       rule: STR_immediate,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE],
//       small_imm_base_wb: wback,
//       uses: {Rn, Rt},
//       wback: P(24)=0 ||
//            W(21)=1}
TEST_F(Arm32DecoderStateTests,
       Store2RegisterImm12OpTester_Case4_TestCase4) {
  Store2RegisterImm12OpTester_Case4 baseline_tester;
  NamedActual_STR_immediate_cccc010pu0w0nnnnttttiiiiiiiiiiii_case_1_STR_immediate actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc010pu0w0nnnnttttiiiiiiiiiiii");
}

// A(25)=0 & op1(24:20)=xx0x1 & Rn(19:16)=~1111 & op1_repeated(24:20)=~0x011
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       Tp: 9,
//       U: U(23),
//       W: W(21),
//       actual: Actual_LDR_immediate_cccc010pu0w1nnnnttttiiiiiiiiiiii_case_1,
//       add: U(23)=1,
//       base: Rn,
//       baseline: LdrImmediateOp,
//       constraints: ,
//       defs: {Rt, base
//            if wback
//            else None},
//       fields: [P(24), U(23), W(21), Rn(19:16), Rt(15:12), imm12(11:0)],
//       generated_baseline: LDR_immediate_cccc010pu0w1nnnnttttiiiiiiiiiiii_case_0,
//       imm12: imm12(11:0),
//       index: P(24)=1,
//       is_load_tp: Rn  ==
//               Tp &&
//            index &&
//            not wback &&
//            add &&
//            imm12 in {0, 4},
//       pattern: cccc010pu0w1nnnnttttiiiiiiiiiiii,
//       rule: LDR_immediate,
//       safety: [Rn  ==
//               Pc => DECODER_ERROR,
//         P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         wback &&
//            Rn  ==
//               Rt => UNPREDICTABLE,
//         Rt  ==
//               Pc => FORBIDDEN_OPERANDS],
//       small_imm_base_wb: wback,
//       uses: {Rn},
//       wback: P(24)=0 ||
//            W(21)=1}
TEST_F(Arm32DecoderStateTests,
       LdrImmediateOpTester_Case5_TestCase5) {
  LdrImmediateOpTester_Case5 baseline_tester;
  NamedActual_LDR_immediate_cccc010pu0w1nnnnttttiiiiiiiiiiii_case_1_LDR_immediate actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc010pu0w1nnnnttttiiiiiiiiiiii");
}

// A(25)=0 & op1(24:20)=xx0x1 & Rn(19:16)=1111 & op1_repeated(24:20)=~0x011 & $pattern(31:0)=xxxxxxx1xx0xxxxxxxxxxxxxxxxxxxxx
//    = {Pc: 15,
//       Rt: Rt(15:12),
//       actual: Actual_LDR_literal_cccc0101u0011111ttttiiiiiiiiiiii_case_1,
//       base: Pc,
//       baseline: Load2RegisterImm12Op,
//       constraints: ,
//       defs: {Rt},
//       fields: [Rt(15:12)],
//       generated_baseline: LDR_literal_cccc0101u0011111ttttiiiiiiiiiiii_case_0,
//       is_literal_load: true,
//       pattern: cccc0101u0011111ttttiiiiiiiiiiii,
//       rule: LDR_literal,
//       safety: [Rt  ==
//               Pc => FORBIDDEN_OPERANDS],
//       true: true,
//       uses: {Pc}}
TEST_F(Arm32DecoderStateTests,
       Load2RegisterImm12OpTester_Case6_TestCase6) {
  Load2RegisterImm12OpTester_Case6 baseline_tester;
  NamedActual_LDR_literal_cccc0101u0011111ttttiiiiiiiiiiii_case_1_LDR_literal actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc0101u0011111ttttiiiiiiiiiiii");
}

// A(25)=0 & op1(24:20)=xx1x0 & op1_repeated(24:20)=~0x110
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_STRB_immediate_cccc010pu1w0nnnnttttiiiiiiiiiiii_case_1,
//       base: Rn,
//       baseline: Store2RegisterImm12Op,
//       constraints: ,
//       defs: {base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12)],
//       generated_baseline: STRB_immediate_cccc010pu1w0nnnnttttiiiiiiiiiiii_case_0,
//       pattern: cccc010pu1w0nnnnttttiiiiiiiiiiii,
//       rule: STRB_immediate,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Rt  ==
//               Pc => UNPREDICTABLE,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE],
//       small_imm_base_wb: wback,
//       uses: {Rn, Rt},
//       wback: P(24)=0 ||
//            W(21)=1}
TEST_F(Arm32DecoderStateTests,
       Store2RegisterImm12OpTester_Case7_TestCase7) {
  Store2RegisterImm12OpTester_Case7 baseline_tester;
  NamedActual_STRB_immediate_cccc010pu1w0nnnnttttiiiiiiiiiiii_case_1_STRB_immediate actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc010pu1w0nnnnttttiiiiiiiiiiii");
}

// A(25)=0 & op1(24:20)=xx1x1 & Rn(19:16)=~1111 & op1_repeated(24:20)=~0x111
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_LDRB_immediate_cccc010pu1w1nnnnttttiiiiiiiiiiii_case_1,
//       base: Rn,
//       baseline: Load2RegisterImm12Op,
//       constraints: ,
//       defs: {Rt, base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12)],
//       generated_baseline: LDRB_immediate_cccc010pu1w1nnnnttttiiiiiiiiiiii_case_0,
//       pattern: cccc010pu1w1nnnnttttiiiiiiiiiiii,
//       rule: LDRB_immediate,
//       safety: [Rn  ==
//               Pc => DECODER_ERROR,
//         P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Rt  ==
//               Pc => UNPREDICTABLE,
//         wback &&
//            Rn  ==
//               Rt => UNPREDICTABLE],
//       small_imm_base_wb: wback,
//       uses: {Rn},
//       wback: P(24)=0 ||
//            W(21)=1}
TEST_F(Arm32DecoderStateTests,
       Load2RegisterImm12OpTester_Case8_TestCase8) {
  Load2RegisterImm12OpTester_Case8 baseline_tester;
  NamedActual_LDRB_immediate_cccc010pu1w1nnnnttttiiiiiiiiiiii_case_1_LDRB_immediate actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc010pu1w1nnnnttttiiiiiiiiiiii");
}

// A(25)=0 & op1(24:20)=xx1x1 & Rn(19:16)=1111 & op1_repeated(24:20)=~0x111 & $pattern(31:0)=xxxxxxx1xx0xxxxxxxxxxxxxxxxxxxxx
//    = {Pc: 15,
//       Rt: Rt(15:12),
//       actual: Actual_LDRB_literal_cccc0101u1011111ttttiiiiiiiiiiii_case_1,
//       base: Pc,
//       baseline: Load2RegisterImm12Op,
//       constraints: ,
//       defs: {Rt},
//       fields: [Rt(15:12)],
//       generated_baseline: LDRB_literal_cccc0101u1011111ttttiiiiiiiiiiii_case_0,
//       is_literal_load: true,
//       pattern: cccc0101u1011111ttttiiiiiiiiiiii,
//       rule: LDRB_literal,
//       safety: [Rt  ==
//               Pc => UNPREDICTABLE],
//       true: true,
//       uses: {Pc}}
TEST_F(Arm32DecoderStateTests,
       Load2RegisterImm12OpTester_Case9_TestCase9) {
  Load2RegisterImm12OpTester_Case9 baseline_tester;
  NamedActual_LDRB_literal_cccc0101u1011111ttttiiiiiiiiiiii_case_1_LDRB_literal actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc0101u1011111ttttiiiiiiiiiiii");
}

// A(25)=1 & op1(24:20)=0x010 & B(4)=0
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0110u010nnnnttttiiiiitt0mmmm,
//       rule: STRT_A2}
TEST_F(Arm32DecoderStateTests,
       ForbiddenCondDecoderTester_Case10_TestCase10) {
  ForbiddenCondDecoderTester_Case10 tester;
  tester.Test("cccc0110u010nnnnttttiiiiitt0mmmm");
}

// A(25)=1 & op1(24:20)=0x011 & B(4)=0
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0110u011nnnnttttiiiiitt0mmmm,
//       rule: LDRT_A2}
TEST_F(Arm32DecoderStateTests,
       ForbiddenCondDecoderTester_Case11_TestCase11) {
  ForbiddenCondDecoderTester_Case11 tester;
  tester.Test("cccc0110u011nnnnttttiiiiitt0mmmm");
}

// A(25)=1 & op1(24:20)=0x110 & B(4)=0
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0110u110nnnnttttiiiiitt0mmmm,
//       rule: STRBT_A2}
TEST_F(Arm32DecoderStateTests,
       ForbiddenCondDecoderTester_Case12_TestCase12) {
  ForbiddenCondDecoderTester_Case12 tester;
  tester.Test("cccc0110u110nnnnttttiiiiitt0mmmm");
}

// A(25)=1 & op1(24:20)=0x111 & B(4)=0
//    = {actual: ForbiddenCondDecoder,
//       baseline: ForbiddenCondDecoder,
//       constraints: ,
//       pattern: cccc0110u111nnnnttttiiiiitt0mmmm,
//       rule: LDRBT_A2}
TEST_F(Arm32DecoderStateTests,
       ForbiddenCondDecoderTester_Case13_TestCase13) {
  ForbiddenCondDecoderTester_Case13 tester;
  tester.Test("cccc0110u111nnnnttttiiiiitt0mmmm");
}

// A(25)=1 & op1(24:20)=xx0x0 & B(4)=0 & op1_repeated(24:20)=~0x010
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rm: Rm(3:0),
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_STR_register_cccc011pd0w0nnnnttttiiiiitt0mmmm_case_1,
//       base: Rn,
//       baseline: Store3RegisterImm5Op,
//       constraints: ,
//       defs: {base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12), Rm(3:0)],
//       generated_baseline: STR_register_cccc011pd0w0nnnnttttiiiiitt0mmmm_case_0,
//       index: P(24)=1,
//       pattern: cccc011pd0w0nnnnttttiiiiitt0mmmm,
//       rule: STR_register,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Rm  ==
//               Pc => UNPREDICTABLE,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE,
//         ArchVersion()  <
//               6 &&
//            wback &&
//            Rn  ==
//               Rm => UNPREDICTABLE,
//         index => FORBIDDEN],
//       uses: {Rm, Rn, Rt},
//       wback: P(24)=0 ||
//            W(21)=1}
TEST_F(Arm32DecoderStateTests,
       Store3RegisterImm5OpTester_Case14_TestCase14) {
  Store3RegisterImm5OpTester_Case14 baseline_tester;
  NamedActual_STR_register_cccc011pd0w0nnnnttttiiiiitt0mmmm_case_1_STR_register actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc011pd0w0nnnnttttiiiiitt0mmmm");
}

// A(25)=1 & op1(24:20)=xx0x1 & B(4)=0 & op1_repeated(24:20)=~0x011
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rm: Rm(3:0),
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_LDR_register_cccc011pu0w1nnnnttttiiiiitt0mmmm_case_1,
//       base: Rn,
//       baseline: Load3RegisterImm5Op,
//       constraints: ,
//       defs: {Rt, base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12), Rm(3:0)],
//       generated_baseline: LDR_register_cccc011pu0w1nnnnttttiiiiitt0mmmm_case_0,
//       index: P(24)=1,
//       pattern: cccc011pu0w1nnnnttttiiiiitt0mmmm,
//       rule: LDR_register,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Rm  ==
//               Pc => UNPREDICTABLE,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE,
//         ArchVersion()  <
//               6 &&
//            wback &&
//            Rn  ==
//               Rm => UNPREDICTABLE,
//         index => FORBIDDEN,
//         Rt  ==
//               Pc => FORBIDDEN_OPERANDS],
//       uses: {Rm, Rn},
//       wback: P(24)=0 ||
//            W(21)=1}
TEST_F(Arm32DecoderStateTests,
       Load3RegisterImm5OpTester_Case15_TestCase15) {
  Load3RegisterImm5OpTester_Case15 baseline_tester;
  NamedActual_LDR_register_cccc011pu0w1nnnnttttiiiiitt0mmmm_case_1_LDR_register actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc011pu0w1nnnnttttiiiiitt0mmmm");
}

// A(25)=1 & op1(24:20)=xx1x0 & B(4)=0 & op1_repeated(24:20)=~0x110
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rm: Rm(3:0),
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_STRB_register_cccc011pu1w0nnnnttttiiiiitt0mmmm_case_1,
//       base: Rn,
//       baseline: Store3RegisterImm5Op,
//       constraints: ,
//       defs: {base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12), Rm(3:0)],
//       generated_baseline: STRB_register_cccc011pu1w0nnnnttttiiiiitt0mmmm_case_0,
//       index: P(24)=1,
//       pattern: cccc011pu1w0nnnnttttiiiiitt0mmmm,
//       rule: STRB_register,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Pc in {Rm, Rt} => UNPREDICTABLE,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE,
//         ArchVersion()  <
//               6 &&
//            wback &&
//            Rn  ==
//               Rm => UNPREDICTABLE,
//         index => FORBIDDEN],
//       uses: {Rm, Rn, Rt},
//       wback: P(24)=0 ||
//            W(21)=1}
TEST_F(Arm32DecoderStateTests,
       Store3RegisterImm5OpTester_Case16_TestCase16) {
  Store3RegisterImm5OpTester_Case16 baseline_tester;
  NamedActual_STRB_register_cccc011pu1w0nnnnttttiiiiitt0mmmm_case_1_STRB_register actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc011pu1w0nnnnttttiiiiitt0mmmm");
}

// A(25)=1 & op1(24:20)=xx1x1 & B(4)=0 & op1_repeated(24:20)=~0x111
//    = {None: 32,
//       P: P(24),
//       Pc: 15,
//       Rm: Rm(3:0),
//       Rn: Rn(19:16),
//       Rt: Rt(15:12),
//       W: W(21),
//       actual: Actual_LDRB_register_cccc011pu1w1nnnnttttiiiiitt0mmmm_case_1,
//       base: Rn,
//       baseline: Load3RegisterImm5Op,
//       constraints: ,
//       defs: {Rt, base
//            if wback
//            else None},
//       fields: [P(24), W(21), Rn(19:16), Rt(15:12), Rm(3:0)],
//       generated_baseline: LDRB_register_cccc011pu1w1nnnnttttiiiiitt0mmmm_case_0,
//       index: P(24)=1,
//       pattern: cccc011pu1w1nnnnttttiiiiitt0mmmm,
//       rule: LDRB_register,
//       safety: [P(24)=0 &&
//            W(21)=1 => DECODER_ERROR,
//         Pc in {Rt, Rm} => UNPREDICTABLE,
//         wback &&
//            (Rn  ==
//               Pc ||
//            Rn  ==
//               Rt) => UNPREDICTABLE,
//         ArchVersion()  <
//               6 &&
//            wback &&
//            Rn  ==
//               Rm => UNPREDICTABLE,
//         index => FORBIDDEN],
//       uses: {Rm, Rn},
//       wback: P(24)=0 ||
//            W(21)=1}
TEST_F(Arm32DecoderStateTests,
       Load3RegisterImm5OpTester_Case17_TestCase17) {
  Load3RegisterImm5OpTester_Case17 baseline_tester;
  NamedActual_LDRB_register_cccc011pu1w1nnnnttttiiiiitt0mmmm_case_1_LDRB_register actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc011pu1w1nnnnttttiiiiitt0mmmm");
}

}  // namespace nacl_arm_test

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
