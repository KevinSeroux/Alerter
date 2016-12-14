#ifndef BOOST_SOCKET_SRV
#define BOOST_SOCKET_SRV

#include <System/Thread.h>
#include <boost/asio.hpp>
#include <mutex>
#include <atomic>

namespace communicating
{
	class BoostSocketSrv : public Thread
	{
	public:
		BoostSocketSrv();
		void send(const std::string&);
		bool receive(std::string&);
		void exit();

	private:
		void run();
		void acceptNextConnection();
		void handleAccept(const boost::system::error_code&);
		void handleSend(const boost::system::error_code&, size_t);
		void handleIfError(const boost::system::error_code&);

		boost::asio::io_service m_ioService;
		boost::asio::ip::tcp::acceptor m_acceptor;
		boost::asio::ip::tcp::socket m_socket;
		std::string m_receiveBuffer;
		mutable std::mutex m_receiveBufferProtector;
		std::atomic<bool> m_doResetConnection;
		std::atomic<bool> m_isNewMessage;
	};
}

#endif // BOOST_SOCKET_SRV
