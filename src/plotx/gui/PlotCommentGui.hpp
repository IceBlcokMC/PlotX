#pragma once
#include "plotx/core/model/StorageModel.hpp"


#include <memory>
#include <optional>


class Player;
namespace plotx {
class PlotHandle;

struct PlotCommentGUI {
    PlotCommentGUI() = delete;

    static void sendTo(Player& player, std::shared_ptr<PlotHandle> handle);

    static void writeComment(Player& player, std::shared_ptr<PlotHandle> handle);

    static void showComment(Player& player, std::shared_ptr<PlotHandle> handle, CommentID id);

    static void editComment(Player& player, std::shared_ptr<PlotHandle> handle, CommentID id);

    static void deleteComment(Player& player, std::shared_ptr<PlotHandle> handle, CommentID id);

    static bool ensureCommentExists(Player& player, std::optional<CommentModel> const& model);
};

} // namespace plotx
