#include <iostream>
#include <boost/asio.hpp>

void handleRead(const boost::system::error_code& error, std::size_t /*bytes_transferred*/)
{
    if (!error)
    {
        std::cout << "Read completed successfully!" << std::endl;
    }
    else
    {
        std::cout << "Error: " << error.message() << std::endl;
    }
}

int main()
{
    // 创建boost::asio::io_context对象
    boost::asio::io_context ioContext;

    // 创建socket对象
    boost::asio::ip::tcp::socket socket(ioContext);

    try
    {
        // 连接到一个地址和端口
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234);
        socket.async_connect(endpoint, [](const boost::system::error_code& error) {
            if (!error)
            {
                std::cout << "Connected successfully!" << std::endl;
            }
            else
            {
                std::cout << "Connect error: " << error.message() << std::endl;
            }
        });

        // 协程主要包装客户端的网络请求
        // 异步读取数据
        //TODO（shenglish）包装wirte 和read
        // 以及客户端的connect close按照python的方式
        boost::asio::streambuf receiveBuffer;
        boost::asio::async_read(socket, receiveBuffer, handleRead);

        // 运行io_context，处理异步操作
        ioContext.run();
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}