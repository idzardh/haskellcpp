#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;


int main(int argc, char* argv[]) {

    if (argc != 2) {
        cout << "Need at least a number!\n";
        return -1;
    }

    int m = std::atoi(argv[1]);
    
    io_service io_service;
    tcp::socket socket(io_service);
    socket.connect(tcp::endpoint(ip::address::from_string("127.0.0.1"), 1234));

    const string msg = std::to_string(m) + '\n';
    boost::system::error_code error;
    write(socket, buffer(msg), error);

    if (!error) 
        cout << "Client sent hello message!\n";
    else
        cout << "Send failed: " << error.message() << '\n';

    streambuf receive_buffer;
    read(socket, receive_buffer, transfer_all(), error);
    if (error && error != error::eof)
        cout << "Receive failed: " << error.message() << '\n';
    else
        cout << buffer_cast<const char*>(receive_buffer.data()) << '\n';

    return 0;
}
