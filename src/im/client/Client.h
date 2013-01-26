/// Client.h
///
/// Declares the Client class.
///
/// LAST UPDATED:
/// 23/11/12 9:25PM
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

#ifndef __IM_CLIENT_CLIENT_H__
#define __IM_CLIENT_CLIENT_H__

#include <queue>
#include <vector>
#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

namespace im
{
	namespace client
	{	
		/// \class Client
		/// \brief Describes a Client which writes/recieves information to and from a server
		///
		/// This class is generalized so that it has various call backs when it
		/// receives data out from a server. This class can also write data out to a server.
		///
		/// \author Miguel Martin
		class Client
			: boost::noncopyable /* There is no need for objects of this class to be copied */
		{
		public:
			
			/// Describes an error code
			typedef ::boost::system::error_code ErrorCode;
			
			// Describes data
			typedef ::std::vector<char> Data;
			
			// an io service object, this is used for boost
			// I just type def'd it for less writing
			typedef ::boost::asio::io_service IoService;
			
			// same as above, except for an iterator, it iterate through IP addresses
			typedef ::boost::asio::ip::tcp::resolver::iterator Iterator;
			
		private:
			
			// a signal that is used for error detection
			typedef ::boost::signals2::signal<void (const std::string&, const ErrorCode&)> OnErrorOccuredSignal;
			// a signal that is used when data is recieved
			typedef ::boost::signals2::signal<void (const Data&)> OnDataReceivedSignal;
			// a signal that is used when a connection occurs
			typedef ::boost::signals2::signal<void (const Iterator&)> OnConnectionSignal;
			// a signal that is used when a connection occurs
			// which also includes an error
			typedef ::boost::signals2::signal<void (const ErrorCode& errorCode, const Iterator&)> OnConnectionWithErrorSignal;
			
		public:
			
			/// Creates a Client
			/// \param io_service The network I/O object used for asyncronous functions
			Client(IoService& io_service);
			
			/// Creates a client, and connects to a server.
			/// \param io_service The network I/O object used for asyncronous functions
			/// \param endpoint_iterator The iterator used to connect to a server, this basically holds IP addresses; since hosts may have multiple addresses
			Client(IoService& io_service, Iterator& endpoint_iterator);
			
			
			
			/// \return The io_service object that the client uses to communicate with the server
			IoService& getIoService() const;
			
			
			/// Writes data to the server
			/// \param data The data you wish to send
			void write(const Data& data);
			
			/// Reads some data from the server
			/// \note
			/// Call this once the server is connected
			/// and then call it once again when you recieve data,
			/// This way the application will constantly read data from the server.
			void read();
			
			/// Sets the buffer size
			/// \param size The size of the buffer, in bytes.
			void setBufferSize(size_t size);
			
			/// \return The size of the buffer, in bytes.
			size_t getBufferSize() const;
			
			/// Connects to a server
			/// \param ip The IP address of the server
			/// \param port The port number of the server
			void connect(const std::string& ip, const std::string& port);
			
			/// Connects to a server
			/// \param endpoint_iterator The iterator used to connect to a server, this basically holds IP addresses; since hosts may have multiple addresses
			void connect(Iterator& endpoint_iterator);
			
			/// Closes the client;
			/// as in it closes the Client's socket
			void close();
			
			/// \return true if the Client is connected to a server
			bool isConnected() const;
			
			/// Adds a slot to the signal that is called whenever there is data that is recieved.
			/// \param slot The slot you wish to add
			void doOnDataRecieved(const OnDataReceivedSignal::slot_type& slot);
			
			/// Adds a slot to the signal that is called whenever there is an error.
			/// \param slot The slot you wish to add
			void doOnErrorOccured(const OnErrorOccuredSignal::slot_type& slot);
			
			/// Adds a slot to the signal that is called when a connection is established
			/// \param slot The slot you wish to add
			void doOnConnectionEstablished(const OnConnectionSignal::slot_type& slot);
			
			/// Adds a slot to the signal which is called when the Client object
			/// is attempting to connect
			/// \param slot The slot you wish to add
			void doOnConnectionAttempt(const OnConnectionWithErrorSignal::slot_type& slot);
			
		private:
			
			// Call back handlers
			
			/***********
			 * Writing *
			 ***********/
			
			/// Handles writing data to a server
			void handleWrite(const ErrorCode& errorCode);
			
			/// Writes information to the connected server
			/// \param data The data you wish to write
			void writeToServer(const Data& data);
			
			// does an async write; this is used to reduce bugs...
			void doAsyncWrite();
			
			
			
			/***********
			 * Reading *
			 ***********/
			
			/// Handles reading data from a server
			void handleRead(const ErrorCode& errorCode);
			
			
			
			/**********************
			 * Connecting/Closing *
			 **********************/
			
			/// Handles connecting to a server
			void handleConnect(const ErrorCode& errorCode, Iterator& iterator);
			
			/// Closes the actual socket
			void forceClose();
			
			
			
			/// Defines a TcpSocket
			typedef ::boost::asio::ip::tcp::socket TcpSocket;
			/// Defines a Queue of data
			typedef std::queue<Data> DataQueue;
			
			
			/// The socket that is used to receive data from a server
			/// This is a scoped pointer so I can easily delete/create a new socket
			/// The reason for this is because I require to connect and disconnect
			/// from a server, without any difficulties
			boost::scoped_ptr<TcpSocket> _socket;
			
			/// A pointer to the io_service object, that will be used to contact the server
			IoService* _io_service;
			
			/// A flag that tells whether the Client is connected to the server
			bool _isConnected;
			
			/// The queue of data that is required to be sent to the server
			/// This is a queue because FIFO (first in first out)
			DataQueue _dataQueue;
			
			/// This holds any data that is currently being read
			Data _buffer;
			
			/// A signal which occurs when data is recieved to the Client object
			OnDataReceivedSignal _onDataRecievedSignal;
			
			/// A signal which occurs when an error has occured
			OnErrorOccuredSignal _onErrorOccuredSignal;
			
			/// A signal which occurs when a connection is established
			OnConnectionSignal _onConnectionEstablished;
			
			/// A signal which occurs when a connection is attempted
			OnConnectionWithErrorSignal _onConnectionAttempt;
		};
	}
}


#endif // __IM_CLIENT_H__