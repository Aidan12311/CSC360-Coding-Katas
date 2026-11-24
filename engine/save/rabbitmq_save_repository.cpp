#include <format>

#include <spdlog/spdlog.h>

#include "engine/save/rabbitmq_save_repository.hpp"
#include "SimpleAmqpClient/BasicMessage.h"

namespace et_game {

RabbitMqSaveRepository::RabbitMqSaveRepository(
    std::string host,
    std::uint16_t port,
    std::string username,
    std::string password,
    std::string queue_name
):
    _host(std::move(host)),
    _port(port),
    _username(std::move(username)),
    _password(std::move(password)),
    _queue_name(std::move(queue_name))
{}

void RabbitMqSaveRepository::connect() {
    if(_channel) {
        return;
    }

    try {
        _channel = AmqpClient::Channel::Create(_host, _port, _username, _password);

        _channel->DeclareQueue(
            _queue_name,
            /* passive     */ false,
            /* durable     */ true,
            /* exclusive   */ false,
            /* auto_delete */ false
        );
    }
    catch(const std::exception& e) {
        _channel.reset();
        
        throw SaveRepositoryError(std::format(
            "AMQP error while connecting to {}:{}: {}",
            _host, _port, e.what()
        ));
    }

    spdlog::info("RabbitMqSaveRepository connected to {}:{} (queue='{}')!", _host, _port, _queue_name);
}

void RabbitMqSaveRepository::disconnect() {
    if(!_channel) {
        return;
    }

    _channel.reset();
    spdlog::info("RabbitMqSaveRepository disconnected!");
}

bool RabbitMqSaveRepository::add(const SaveEvent& save_event) {
    if(!_channel) {
        spdlog::warn("Failed to publish message! RabbitMqSaveRepository not connected!");
        return false;
    }

    spdlog::info("Publishing save event (trigger={}) to amqp server {}:{}!", save_event.trigger, _host, _port);

    try {
        auto msg = AmqpClient::BasicMessage::Create(save_event.body);
        msg->ContentType("application/json");
        msg->DeliveryMode(AmqpClient::BasicMessage::dm_persistent);

        _channel->BasicPublish(
            "",
            _queue_name,
            msg
        );

        return true;
    }
    catch(const std::exception& e) {
        spdlog::warn("Failed to publish message! Unexpected error: {}", e.what());
        _channel.reset();

        return false;
    }
}

} // namespace et_game
