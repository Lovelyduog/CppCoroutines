#include <iostream>
#include <algorithm>
#include <memory>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
 
 
using  boost::asio::ip::tcp;
typedef std::shared_ptr<boost::asio::ip::tcp::socket> SOCKET_PTR;
 
void client_session(SOCKET_PTR socket_ptr)
{
 
	while (true)
	{
		char data[512] = "";
		size_t len = socket_ptr->read_some(boost::asio::buffer(data));// 阻塞
		printf(data);
		socket_ptr->write_some(boost::asio::buffer("ok", 2));
	}
}
 
int main(int argc, char * argv[])
{
	boost::asio::io_service ioService;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 2001);
	boost::asio::ip::tcp::acceptor acceptor(ioService, endpoint);
 
	while (true)
	{
		SOCKET_PTR socket_ptr(new boost::asio::ip::tcp::socket(ioService));
		acceptor.accept(*socket_ptr); // 阻塞
		char data[512] = "";
		size_t len = socket_ptr->read_some(boost::asio::buffer(data));// 阻塞
		printf(data);
		socket_ptr->write_some(boost::asio::buffer("ok", 2));
		// boost::thread(boost::bind(client_session, socket_ptr));
	}
	
 
	return 0;
}