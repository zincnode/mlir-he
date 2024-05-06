
#include "Conversion/ArithToHe/ArithToHe.h"
#include "Dialect/He/IR/He.h"

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Support/LogicalResult.h"
#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

#include <utility>

namespace mlir_he {

#define GEN_PASS_DEF_CONVERTARITHTOHE
#include "Conversion/Passes.h.inc"

} // namespace mlir_he

namespace {
// This pattern converts an arith::AddIOp to a mlir_he::HeAddOp.
struct ConvertArithAddIOp: public mlir::OpRewritePattern<mlir::arith::AddIOp> {
  using mlir::OpRewritePattern<mlir::arith::AddIOp>::OpRewritePattern;

  mlir::LogicalResult matchAndRewrite(mlir::arith::AddIOp op,
   mlir::PatternRewriter &rewriter) const override {
    rewriter.replaceOpWithNewOp<mlir_he::HeAddOp>(op, op.getType(), op.getLhs(), op.getRhs());
    return mlir::success();
  }
};

// This pattern converts an arith::AddFOp to a mlir_he::HeAddOp.
struct ConvertArithAddFOp: public mlir::OpRewritePattern<mlir::arith::AddFOp> {
  using mlir::OpRewritePattern<mlir::arith::AddFOp>::OpRewritePattern;

  mlir::LogicalResult matchAndRewrite(mlir::arith::AddFOp op,
   mlir::PatternRewriter &rewriter) const override {
    rewriter.replaceOpWithNewOp<mlir_he::HeAddOp>(op, op.getType(), op.getLhs(), op.getRhs());
    return mlir::success();
  }
};

struct ArithToHe : public mlir_he::impl::ConvertArithToHeBase<ArithToHe> {
public:
  void runOnOperation() override;
};

void ArithToHe::runOnOperation() {
    mlir::MLIRContext &context = getContext();

    mlir::RewritePatternSet patterns(&context);
    patterns.add<ConvertArithAddIOp>(&getContext());
    patterns.add<ConvertArithAddFOp>(&getContext());

    if (failed(applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
    }
}

} // namespace

std::unique_ptr<mlir::Pass> mlir_he::createConvertArithToHePass() {
  return std::make_unique<ArithToHe>();
}
