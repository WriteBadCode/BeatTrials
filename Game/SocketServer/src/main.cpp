#include <iostream>
#include <./websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

int main() {
    // Create a WebSocket server endpoint
    using server_t = websocketpp::server<websocketpp::config::asio>;
    server_t server;

    // Initialize the server
    server.init_asio();

    // Set up a callback to handle incoming messages
    server.set_message_handler([](server_t::connection_ptr connection, server_t::message_ptr message) {
        if (message->get_opcode() == websocketpp::frame::opcode::text) {
            std::cout << "Received message: " << message->get_payload() << std::endl;

            // Echo the message back to the client
            connection->send(message->get_payload(), message->get_opcode());
        }
    });

    // Listen on port 9002
    server.listen(9002);

    // Start the server accept loop
    server.start_accept();

    // Start the ASIO io_service run loop
    server.run();

    return 0;
}
