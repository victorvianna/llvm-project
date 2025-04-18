//===- Passes.h - Pass Entrypoints ------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef MLIR_DIALECT_MATH_TRANSFORMS_PASSES_H_
#define MLIR_DIALECT_MATH_TRANSFORMS_PASSES_H_

#include "mlir/IR/PatternMatch.h"
#include "mlir/Pass/Pass.h"

namespace mlir {
namespace math {
#define GEN_PASS_DECL
#define GEN_PASS_REGISTRATION
#include "mlir/Dialect/Math/Transforms/Passes.h.inc"
} // namespace math

class ConversionTarget;
class RewritePatternSet;
class TypeConverter;

void populateExpandCtlzPattern(RewritePatternSet &patterns);
void populateExpandTanPattern(RewritePatternSet &patterns);
void populateExpandSinhPattern(RewritePatternSet &patterns);
void populateExpandCoshPattern(RewritePatternSet &patterns);
void populateExpandTanhPattern(RewritePatternSet &patterns);
void populateExpandAsinhPattern(RewritePatternSet &patterns);
void populateExpandAcoshPattern(RewritePatternSet &patterns);
void populateExpandAtanhPattern(RewritePatternSet &patterns);
void populateExpandFmaFPattern(RewritePatternSet &patterns);
void populateExpandCeilFPattern(RewritePatternSet &patterns);
void populateExpandExp2FPattern(RewritePatternSet &patterns);
void populateExpandPowFPattern(RewritePatternSet &patterns);
void populateExpandFPowIPattern(RewritePatternSet &patterns);
void populateExpandRoundFPattern(RewritePatternSet &patterns);
void populateExpandRoundEvenPattern(RewritePatternSet &patterns);
void populateExpandRsqrtPattern(RewritePatternSet &patterns);
void populateMathAlgebraicSimplificationPatterns(RewritePatternSet &patterns);

struct MathPolynomialApproximationOptions {
  // Enables the use of AVX2 intrinsics in some of the approximations.
  bool enableAvx2 = false;
};

void populatePolynomialApproximateTanhPattern(RewritePatternSet &patterns);
void populatePolynomialApproximateErfPattern(RewritePatternSet &patterns);
void populatePolynomialApproximateErfcPattern(RewritePatternSet &patterns);

// Adds patterns to convert to f32 around math functions for which `predicate`
// returns true.
void populateMathF32ExpansionPatterns(
    RewritePatternSet &patterns, llvm::function_ref<bool(StringRef)> predicate,
    PatternBenefit = 1);

// Adds patterns to enable polynomial approximations for math functions for
// which `predicate` returns true.
void populateMathPolynomialApproximationPatterns(
    RewritePatternSet &patterns, llvm::function_ref<bool(StringRef)> predicate,
    PatternBenefit = 1);

// Legacy. Calls both populateMathF32ExpansionPatterns and
// populateMathPolynomialApproximationPatterns with predicates enabling a
// certain set of math function rewrites, that probably can't be changed for
// compatibility reasons. Notice that unlike
// populateMathPolynomialApproximationPatterns(patterns, predicate), this
// overload also calls populateMathF32ExpansionPatterns.
// Prefer calling these functions directly:
// * populateMathF32ExpansionPatterns(patterns, predicate)
// * populateMathPolynomialApproximationPatterns(patterns, predicate)
void populateMathPolynomialApproximationPatterns(
    RewritePatternSet &patterns,
    const MathPolynomialApproximationOptions &options = {});

void populateUpliftToFMAPatterns(RewritePatternSet &patterns);

namespace math {
void populateExtendToSupportedTypesTypeConverter(
    TypeConverter &typeConverter, const SetVector<Type> &sourceTypes,
    Type targetType);
void populateExtendToSupportedTypesConversionTarget(
    ConversionTarget &target, TypeConverter &typeConverter);
void populateExtendToSupportedTypesPatterns(RewritePatternSet &patterns,
                                            const TypeConverter &typeConverter);
} // namespace math
} // namespace mlir

#endif // MLIR_DIALECT_MATH_TRANSFORMS_PASSES_H_
