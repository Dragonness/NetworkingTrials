#include "accepter.h"
#include "receiver.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <thread>

Accepter::Accepter(Queue<std::string>& q, List<std::shared_ptr<sf::TcpSocket>>& s):
    queue_(q),
    socket_(s)
{}

using namespace sf;

void Accepter::operator()()
{
    sf::TcpListener listener;
    
    // TODO the listener has to listen.
    listener.listen(PORT);


    std::cout << "Bound to port\n";
    while (true)
    {
        std::shared_ptr<sf::TcpSocket> socket = std::make_shared<sf::TcpSocket>();

        // TODO accept a connection on socket
        TcpSocket client;
        if(listener.accept(client) == Socket::Done)
        {
            std::cout << "New connection established with " << client.getRemoteAddress() << std::endl;
            //time to do something with it
        }


        socket_.push(socket);
        std::stringstream ss;
        ss << "Accepted a connection from: "
            << socket->getRemoteAddress()
            << ":"
            << socket->getRemotePort()
            << std::endl;
        std::cout << ss.str();
        std::shared_ptr<Receiver> receiver = std::make_shared<Receiver>(socket, queue_);

        // TODO launch a thread to receive with the receiver
        /// Imma need help w this...
    }
}