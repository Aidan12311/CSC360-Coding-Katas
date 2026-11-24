#ifndef ET_GAME_SAVE_REPOSITORY_HPP
#define ET_GAME_SAVE_REPOSITORY_HPP

#include <stdexcept>

#include "engine/save/save_event.hpp"

namespace et_game {

struct SaveRepositoryError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class SaveRepository {
public:
    virtual ~SaveRepository() = default;

    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual bool is_connected() const = 0;

    virtual bool add(const SaveEvent& save_event) = 0;
};

} // namespace et_game

#endif
