#ifndef ET_GAME_SERVICE_TILESET_HPP
#define ET_GAME_SERVICE_TILESET_HPP

#include <format>
#include <memory>
#include <string>
#include <stdexcept>
#include <unordered_map>

#include "types.hpp"
#include "walkability_strategy.hpp"

namespace et_game {

struct TilesetError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct Tileset {
    TilesetName name{};

    int tile_size{};
    int tiles_per_row{};

    std::unordered_map<TileId, TileDef> tile_defs{};
    std::shared_ptr<const WalkabilityStrategy> walkability{std::make_shared<TileDefWalkability>()};

public:
    const TileDef& get_tiledef_by_id(TileId id) const {
        auto it = tile_defs.find(id);
        if (it == tile_defs.end()) {
            throw TilesetError(std::format("Tile ID {} not found in tileset '{}'", id, name));
        }

        return it->second;
    }

    void set_walkability_strategy(std::shared_ptr<const WalkabilityStrategy> strategy) {
        if(!strategy) {
            throw TilesetError(std::format("Tileset '{}' was given a null walkability strategy", name));
        }

        walkability = std::move(strategy);
    }

    bool is_walkable(TileId id) const {
        return walkability->is_walkable(get_tiledef_by_id(id));
    }
};

} // namespace et_game

#endif
