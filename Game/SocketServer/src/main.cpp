#include <iostream>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

// Define the type of the message handler function
using message_handler_t = std::function<void(websocketpp::connection_hdl, websocketpp::server<websocketpp::config::asio>::message_ptr)>;

int main() {
    std::cout << "hello this is websocket" << std::endl;
    // Create a WebSocket server endpoint
    using server_t = websocketpp::server<websocketpp::config::asio>;
    server_t server;

    // Initialize the server
    server.init_asio();

    // Define the message handler function
    message_handler_t message_handler = [&server](websocketpp::connection_hdl hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg) {
        if (msg->get_opcode() == websocketpp::frame::opcode::text) {
            std::cout << "Received message: " << msg->get_payload() << std::endl;

            // Echo the message back to the client
            server.send(hdl, msg->get_payload(), msg->get_opcode());
        }
    };

    // Set up a callback to handle incoming messages
    server.set_message_handler(message_handler);

    // Listen on port 9002
    server.listen(9002);

    // Start the server accept loop
    server.start_accept();

    // Start the ASIO io_service run loop
    server.run();

    return 0;
}
