#include <Communicating/BoostSocketSrv.h>
#include <System/Configurator.h>
#include <boost/bind.hpp>

using namespace communicating;
using namespace boost::asio;
using namespace boost;
using namespace boost::system;

BoostSocketSrv::BoostSocketSrv() :
	m_acceptor(m_ioService, ip::tcp::endpoint(ip::tcp::v4(), 2000)),
	m_socket(m_ioService),
	m_isNewMessage(false)
{

}

void BoostSocketSrv::exit()
{
	//m_doResetConnection = true; //TODO: Determine whether remove
	m_ioService.stop();
}

void BoostSocketSrv::run()
{
	// Accept next connection and block
	acceptNextConnection();
	m_ioService.run();
}

void BoostSocketSrv::acceptNextConnection()
{
	// Accept the next connection
	m_acceptor.async_accept(m_socket, bind(&BoostSocketSrv::handleAccept,
		this, asio::placeholders::error));
}

void BoostSocketSrv::handleAccept(const error_code& err)
{
	if (err)
		return;

	m_doResetConnection = false;

	// Repeat until the connection must be reset (client disconnect, ...)
	while (!m_doResetConnection)
	{
		const size_t BUFFER_SIZE = 128;
		char myBuffer[BUFFER_SIZE];
		system::error_code myError;

		// Get the next data (blocking)
		size_t bytesRead = m_socket.receive(
			asio::buffer(myBuffer, BUFFER_SIZE), 0, myError);

		if (myError == 0) // No error
		{
			// Fill the std::string buffer in a thread-safe way
			m_receiveBufferProtector.lock();
			m_receiveBuffer.append(myBuffer, bytesRead);
			m_receiveBufferProtector.unlock();
			m_isNewMessage = true;
		}
		else
			handleIfError(myError);
	}

	acceptNextConnection();
}

void BoostSocketSrv::send(const std::string& str)
{
	static auto handleSendProxy = boost::bind(
		&BoostSocketSrv::handleSend,
		this,
		asio::placeholders::error,
		asio::placeholders::bytes_transferred
	);

	m_socket.async_write_some(asio::buffer(str, str.size()), handleSendProxy);
}

bool BoostSocketSrv::receive(std::string& str)
{
	bool retValue = m_isNewMessage;

	if(m_isNewMessage)
	{
		m_receiveBufferProtector.lock();
		str = m_receiveBuffer;
		m_receiveBuffer.clear();
		m_receiveBufferProtector.unlock();
		m_isNewMessage = false;
	}

	return retValue;
}

void BoostSocketSrv::handleSend(
		const error_code& theError, size_t bytes_transferred)
{
	handleIfError(theError);
}

void BoostSocketSrv::handleIfError(const error_code& theError)
{
	if(theError == error::eof || theError == errc::connection_reset)
	{
		m_doResetConnection = true;
		m_isNewMessage = false;
		m_receiveBuffer.clear();
		m_socket.close();
	}
}
