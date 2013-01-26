/// Client.cpp
///
/// Implements the Client class.
///
/// LAST UPDATED:
/// 22/11/12 11:51PM
///
/// PROGRAMMERS:
/// Miguel Martin
///
/// LEGAL NOTICE:
/// This software is provided 'as-is',
/// without any express or implied warranty.
/// In no even will the authors be held
/// liable for any damages arising from
/// the use of this software.
///
///          AC - Anax Creations
/// Copyright (C) 2012. All rights reserved.
///

#include "Client.h"

#include <boost/bind.hpp>

namespace im
{
	namespace client
	{
		Client::Client(IoService& io_service)
		: _io_service(&io_service), _isConnected(false), _buffer(32)
		{
		}
		
		
		Client::Client(IoService& io_service, Iterator& endpoint_iterator)
		: _io_service(&io_service), _isConnected(false)
		{
			connect(endpoint_iterator);
		}
		
		
		Client::IoService& Client::getIoService() const
		{
			return *_io_service;
		}
		
		
		
		void Client::write(const Data& data)
		{
			// tell the io service object to call the forceClose function at a later
			// time, just incase we're writing or reading from the server already
			// basically, so we don't "clog" the CPU
			getIoService().post(boost::bind(&Client::writeToServer, this, data));
		}
		
		
		void Client::read()
		{
			using namespace boost::asio;
			
			// async read the data
			async_read(*_socket, buffer(_buffer), boost::bind(&Client::handleRead, this, placeholders::error));
		}
		
		void Client::setBufferSize(size_t size)
		{
			// resize the buffer
			_buffer.resize(size);
		}
		
		size_t Client::getBufferSize() const
		{
			return _buffer.size();
		}
		
		void Client::connect(const std::string& ip, const std::string& port)
		{
			using namespace boost::asio::ip;
			tcp::resolver resolver(getIoService());
			tcp::resolver::query query(ip, port);
			tcp::resolver::iterator iterator = resolver.resolve(query);
			
			connect(iterator);
		}
		
		void Client::connect(Iterator& endpoint_iterator)
		{
			using namespace boost::asio;
			using namespace boost::asio::ip;
			tcp::endpoint endpoint = *endpoint_iterator++;
			
			// reset out socket
			// i.e. create a new one
			// reason for doing so:
			// http://stackoverflow.com/questions/3062803/how-do-i-cleanly-reconnect-a-boostsocket-following-a-disconnect
			_socket.reset(new TcpSocket(getIoService()));
			
			// asyncronously connect to the server; through the socket
			// let the handler handle our darn connection.
			_socket->async_connect(endpoint,
								   boost::bind(&Client::handleConnect,
											   this,
											   placeholders::error,
											   endpoint_iterator)
								   );
		}
		
		
		void Client::close()
		{
			// tell the io service object to call the forceClose function at a later
			// time, just incase we're writing or reading from the server already
			// basically, so we don't "clog" the CPU
			getIoService().post(boost::bind(&Client::forceClose, this));
		}
		
		
		bool Client::isConnected() const
		{
			return _isConnected;
		}
		
		
		void Client::doOnDataRecieved(const OnDataReceivedSignal::slot_type& slot)
		{
			_onDataRecievedSignal.connect(slot);
		}
		
		void Client::doOnErrorOccured(const OnErrorOccuredSignal::slot_type& slot)
		{
			_onErrorOccuredSignal.connect(slot);
		}
		
		void Client::doOnConnectionEstablished(const OnConnectionSignal::slot_type& slot)
		{
			_onConnectionEstablished.connect(slot);
		}
		
		void Client::doOnConnectionAttempt(const OnConnectionWithErrorSignal::slot_type& slot)
		{
			_onConnectionAttempt.connect(slot);
		}
		
		
		
		// utility methods
		
		
		void Client::handleWrite(const ErrorCode& errorCode)
		{
			// if there is no errors
			if(!errorCode)
			{
				// pop off the message (data) that was sent previously
				_dataQueue.pop();
				
				// if we still have some data that we need to write,
				// we'll write again.
				// Since it is possible, as we may push data without actually
				// writing to the server (refer to the writeToServer function)
				if(!_dataQueue.empty())
				{
					// asyncronously write to the server
					doAsyncWrite();
				}
			}
			// else if there is...
			else
			{
				// we'll just force close the Client's socket
				forceClose();
				
				// notify everyone that we have an error
				_onErrorOccuredSignal("Failed to write to server", errorCode);
			}
		}
		
		void Client::writeToServer(const Data& data)
		{
			// this bool determines if there is writing that is already occuring
			bool isWriteInProgress = !_dataQueue.empty();
			
			// push the data on the data queue
			_dataQueue.push(data);
			
			// if there is no write in progress
			if(!isWriteInProgress)
			{
				// asyncronously write to the server
				doAsyncWrite();
			}
		}
		
		void Client::doAsyncWrite()
		{
			boost::asio::async_write(*_socket,
									 ::boost::asio::buffer(_dataQueue.front()),
									 ::boost::bind(&Client::handleWrite, this, boost::asio::placeholders::error));
		}
		
		
		void Client::handleRead(const ErrorCode &errorCode)
		{
			// if there's no errors
			if(!errorCode)
			{
				// notify everyone
				_onDataRecievedSignal(_buffer);
				
				// re-check for any incoming data
				read();
			}
			else
			{
				if(_isConnected)
				{
					// close the socket, since we got an error
					forceClose();
					
					// notify everyone
					_onErrorOccuredSignal("Failed to read from Server", errorCode);
				}
			}
		}
		
		
		
		void Client::handleConnect(const ErrorCode& errorCode, Iterator& iterator)
		{
			using namespace ::boost::asio;
			using namespace ::boost::asio::ip;
			
			// if there's no error
			if(!errorCode)
			{
				// well, then we shall
				// 1. set the flag to true, to resemble that we are connected
				_isConnected = true;
				
				// 2. notify everyone that we connected :)
				_onConnectionEstablished(iterator);
				
				// read data
				read();
			}
			// else if we still have possible adresses to connect to...
			else if (iterator != tcp::resolver::iterator())
			{
				_onConnectionAttempt(errorCode, iterator); // notify everyone we're trying to reattempt
				
				// and we shall re-try to connect!
				connect(iterator);
			}
			else
			{
				// we failed to connect :(
				
				// let's tell everyone
				_onErrorOccuredSignal("Failed to connect", errorCode);
				
				// force close our socket
				forceClose();
			}
		}
		
		
		// force closes
		void Client::forceClose()
		{
			// set this flag to false,
			// since we are no longer connected
			_isConnected = false;
			
			// delete our socket,
			// close will be called automatically, through the descrutor
			_socket.reset();
		}
	}
}