#ifndef SORBET_REWRITER_PACKAGE_H
#define SORBET_REWRITER_PACKAGE_H
#include "ast/ast.h"
#include "packager/VisibilityChecker.h"

namespace sorbet {
class WorkerPool;
}

namespace sorbet::packager {
// TODO(jez) Re-document this after you're done merging packager into namer.
class Packager final {
public:
    static void findPackages(core::GlobalState &gs, absl::Span<ast::ParsedFile> files);

    // Build the packageDB, and validate packaged files at the same time.
    static void run(core::GlobalState &gs, WorkerPool &workers, absl::Span<ast::ParsedFile> files);

    // Run packager incrementally. Note: `files` must contain all packages files. Does not support package changes.
    static std::vector<ast::ParsedFile> runIncremental(const core::GlobalState &gs, std::vector<ast::ParsedFile> files,
                                                       WorkerPool &workers);

    // Build the packageDB only. This requires that the `files` span only contains `__package.rb` files.
    static void buildPackageDB(core::GlobalState &gs, WorkerPool &workers, absl::Span<ast::ParsedFile> files);

    // Validate packaged files. This requires that hte `files` span does not contain any `__package.rb` files.
    static void validatePackagedFiles(core::GlobalState &gs, WorkerPool &workers, absl::Span<ast::ParsedFile> files);

    // For each file, set its package name.
    static void setPackageNameOnFiles(core::GlobalState &gs, absl::Span<const ast::ParsedFile> files);

    static core::SymbolRef getEnumClassForEnumValue(const core::GlobalState &gs, core::SymbolRef sym);

    Packager() = delete;
};
} // namespace sorbet::packager

#endif // SORBET_REWRITER_PACKAGE_H
