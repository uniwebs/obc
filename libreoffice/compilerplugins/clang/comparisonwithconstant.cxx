/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <set>

#include "compat.hxx"
#include "plugin.hxx"

/**
  Look for comparisons where the constant is on the left, it should be on the right.
 */

namespace {

class ComparisonWithConstant :
    public RecursiveASTVisitor<ComparisonWithConstant>, public loplugin::RewritePlugin
{
public:
    explicit ComparisonWithConstant(InstantiationData const & data): RewritePlugin(data) {}

    virtual void run() override
    {
        TraverseDecl(compiler.getASTContext().getTranslationUnitDecl());
    }

    bool VisitBinaryOperator(const BinaryOperator *);
private:
    bool rewrite(const BinaryOperator *);
    std::string getExprAsString(SourceRange range);
    SourceRange ignoreMacroExpansions(SourceRange range);
};

bool ComparisonWithConstant::VisitBinaryOperator(const BinaryOperator* binaryOp)
{
    if (ignoreLocation(binaryOp)) {
        return true;
    }
    if (!(binaryOp->getOpcode() == BO_EQ || binaryOp->getOpcode() == BO_NE)) {
        return true;
    }
    // ignore logging macros
    if (compiler.getSourceManager().isMacroBodyExpansion(binaryOp->getSourceRange().getBegin())
        || compiler.getSourceManager().isMacroArgExpansion(binaryOp->getSourceRange().getBegin())) {
        return true;
    }
    // protect against clang assert
    if (binaryOp->getLHS()->isValueDependent() || binaryOp->getRHS()->isValueDependent()) {
        return true;
    }
    if (!binaryOp->getLHS()->isEvaluatable(compiler.getASTContext())) {
        return true;
    }
    if (binaryOp->getRHS()->isEvaluatable(compiler.getASTContext())) {
        return true;
    }
    if (!rewrite(binaryOp))
    {
        report(
            DiagnosticsEngine::Warning, "Rather put constant on right when comparing",
            binaryOp->getSourceRange().getBegin())
            << binaryOp->getSourceRange();
    }
    return true;
}


bool ComparisonWithConstant::rewrite(const BinaryOperator * binaryOp) {
    if (rewriter == nullptr) {
        return false;
    }

    auto lhsRange = ignoreMacroExpansions(binaryOp->getLHS()->getSourceRange());
    if (!lhsRange.isValid()) {
        return false;
    }
    auto rhsRange = ignoreMacroExpansions(binaryOp->getRHS()->getSourceRange());
    if (!rhsRange.isValid()) {
        return false;
    }

    const std::string lhsString = getExprAsString(lhsRange);
    const std::string rhsString = getExprAsString(rhsRange);

    /* we can't safely move around stuff containing comments, we mess up the resulting code */
    if ( lhsString.find("/*") != std::string::npos || lhsString.find("//") != std::string::npos ) {
        return false;
    }
    if ( rhsString.find("/*") != std::string::npos || rhsString.find("//") != std::string::npos ) {
        return false;
    }

    // switch LHS and RHS
    if (!replaceText(lhsRange, rhsString)) {
        return false;
    }
    if (!replaceText(rhsRange, lhsString)) {
        return false;
    }

    return true;
}

// get the expression contents
std::string ComparisonWithConstant::getExprAsString(SourceRange range)
{
    SourceManager& SM = compiler.getSourceManager();
    SourceLocation startLoc = range.getBegin();
    SourceLocation endLoc = range.getEnd();
    const char *p1 = SM.getCharacterData( startLoc );
    const char *p2 = SM.getCharacterData( endLoc );
    unsigned n = Lexer::MeasureTokenLength( endLoc, SM, compiler.getLangOpts());
    return std::string( p1, p2 - p1 + n);
}

SourceRange ComparisonWithConstant::ignoreMacroExpansions(SourceRange range) {
    if (range.getBegin().isMacroID()) {
        SourceLocation loc;
        if (Lexer::isAtStartOfMacroExpansion(
                range.getBegin(), compiler.getSourceManager(),
                compiler.getLangOpts(), &loc))
        {
            range.setBegin(loc);
        }
    }
    if (range.getEnd().isMacroID()) {
        SourceLocation loc;
        if (Lexer::isAtEndOfMacroExpansion(
                range.getEnd(), compiler.getSourceManager(),
                compiler.getLangOpts(), &loc))
        {
            range.setEnd(loc);
        }
    }
    return range.getBegin().isMacroID() || range.getEnd().isMacroID()
        ? SourceRange() : range;
}

loplugin::Plugin::Registration< ComparisonWithConstant > X("comparisonwithconstant", false);

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
