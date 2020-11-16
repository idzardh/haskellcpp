#include <iostream>
#include <boost/asio.hpp>

#include "calc_stub.h"

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;


int read_(tcp::socket& socket) {
    streambuf buf;
    read_until(socket, buf, "\n");
    string data = buffer_cast<const char*>(buf.data());
    try {
        return std::stoi(data);
    }
    catch ([[gnu::unused]] std::exception& e) {
        return 0;
    }
}


void send_(tcp::socket& socket, const string& message) {
    const string msg = message + '\n';
    write(socket, buffer(message));
}


int main(int argc, char *argv[]) {
    hs_init(&argc, &argv);
    io_service io_service;
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234));
    tcp::socket socket_(io_service);

    acceptor_.accept(socket_);

    int number = read_(socket_);

    std::stringstream ss;
    ss << "Here are the  fibs to (" << number << "): [";
    for (int i = 1; i < number; i++) {
        ss << fibonacci_hs(i) << ", ";
    }
    ss << fibonacci_hs(number) << "].\n";

    send_(socket_, ss.str());
    cout << "Server send Hello message to Client!\n";
    hs_exit();
    return 0;
}
