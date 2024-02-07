#include <iostream>
#include <algorithm>
#include <memory>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
 
 
using  boost::asio::ip::tcp;
 
boost::asio::io_service ioService;
std::shared_ptr<boost::asio::ip::tcp::socket> socketPtr;
 
void connect_handler(const boost::system::error_code &ec)
{
	if (!ec)
	{
		printf("connect\n");
		socketPtr->write_some(boost::asio::buffer("hello", 6));// 阻塞
 
		char data[512] = "";
		size_t len = socketPtr->read_some(boost::asio::buffer(data));// 阻塞
		printf("%s\n", data);
	}
}
 
void Connect(std::string ip, int port)
{
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip), port);
	socketPtr->async_connect(endpoint, connect_handler); // 异步
}
 
int main(int argc, char * argv[])
{
 
	socketPtr.reset(new boost::asio::ip::tcp::socket(ioService));
 
	Connect("127.0.0.1", 2001);
	ioService.run();
 
 
	return 0;
}