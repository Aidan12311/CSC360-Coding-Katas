#ifndef ET_GAME_RABBITMQ_SAVE_REPOSITORY_HPP
#define ET_GAME_RABBITMQ_SAVE_REPOSITORY_HPP

#include <string>
#include <cstdint>

#include <SimpleAmqpClient/SimpleAmqpClient.h>

#include "engine/save/save_repository.hpp"

namespace et_game {

class RabbitMqSaveRepository final : public SaveRepository {
public:
    RabbitMqSaveRepository(
        std::string host,
        std::uint16_t port,
        std::string username,
        std::string password,
        std::string queue_name
    );

    ~RabbitMqSaveRepository() override { disconnect(); }

    RabbitMqSaveRepository(const RabbitMqSaveRepository&) = delete;
    RabbitMqSaveRepository& operator=(const RabbitMqSaveRepository&) = delete;

    void connect() override;
    void disconnect() override;
    bool is_connected() const override { return _channel != nullptr; }

    bool add(const SaveEvent& save_event) override;

private:
    std::string _host{};
    std::uint16_t _port{};
    std::string _username{};
    std::string _password{};
    std::string _queue_name{};

    AmqpClient::Channel::ptr_t _channel{nullptr};
};

} // namespace et_game

#endif
