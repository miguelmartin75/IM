/// Server.h
///
/// Declares the Server class.
///
/// LAST UPDATED:
/// 19/11/12 3:06PM
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

#ifndef __IM_SERVER_SERVER_H__
#define __IM_SERVER_SERVER_H__

#include <vector>
#include <map>
#include <string>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include "Room.h"
#include "Participant.h"

// This class is not finished,
// was hoping to get it finished...
// even a simple server with just one room, but it hasn't been done yet..

namespace im
{
	namespace client
	{
		/// \class Server
		/// \brief
		class Server
			: boost::noncopyable /* no point in objects of this class to be copied */
		{
		public:
			
			/// resembles an error code
			typedef boost::system::error_code ErrorCode;
			
			/// resembles a TCP socket
			typedef boost::asio::ip::tcp::socket TcpSocket;
			
			/// Defines data
			typedef std::vector<char> Data;
			
		private:
			
			// SIGNALS
			
			/// A signal that is used for error detection
			//typedef boost::signals2::signal<void (const ErrorCode&)> OnErrorOccuredSignal;
			
			/// A signal that occurs when data is received
			//typedef
			
		public:
			
			
			/// A TCP acceptor object which accepts incoming connections
			typedef boost::asio::ip::tcp::acceptor TcpAcceptor;
			
			/// Default constructor
			Server(boost::asio::io_service& service);
			
			/// Hosts a server on an IP address and pot
			/// \param ip The IP address you wish to use
			/// \param port The port number you wish to use
			void host(const std::string& ip, const std::string& port);
			
			/// Closes the server
			void close();
			
			/// writes to the server
			/// \param data The data you wish to write to
			void write(const Data& data);
			
			void write(const std::string& data)
			{
				write(Data(data.begin(), data.end()));
			}
			
			/*
			/// Adds a Room
			/// \param name The name of the Room
			void addRoom(const std::string& name);
			
			/// Removes a Room
			/// \param name The name of the Room
			void removeRoom(const std::string& name);
			
			/// Determines whether a Room exsists in the Server
			/// \param name The name of the Room
			bool doesContainRoom(const std::string& name);
			*/
			/// adds a paricipant to a room
			//void addParticpantToRoom(const std::string& roomName, Participant& particpant);
			
			/// Removes a particpant from a room
			//void removeParticpantFromRoom(const std::string& roomName, Participant& particpant);
			
			/// Sends a message to a room
			void sendToRoom(const std::string& roomName);
			
			
			
		private:
			
			typedef boost::shared_ptr<Participant> ParticipantPtr;
			
			
			
			// ACCEPTING CONNECTION
			
			/// Starts to accept any connections that wish to join the server
			void startAccept();
			
			/// Handles to accept any connections that wish to join the server
			void handleAccept(ParticipantPtr participant, const ErrorCode& errorCode);
			
			// WRITING
			
			/// Handles writing
			void handleWrite(const Room& room, const ErrorCode& errorCode);
			
			// READING
			
			void handleRead(const ErrorCode& errorCode);
			
			/// Defines a dictionay for a room
			typedef std::map<std::string, Room*> RoomDictionary;
			typedef std::pair<std::string, Room*> RoomDictionaryPair;
			typedef std::pair<Participant*, Room*> ParcipantRoomPair;
			typedef std::vector<ParcipantRoomPair> ParticipantArray;
			
			/// The rooms which are in the server
			//RoomDictionary _rooms;
					  
					  
			boost::asio::io_service* _io_service;
			
			/// The room that's in the server
			Room _room;
			
			/// The object that accepts connections
			boost::scoped_ptr<TcpAcceptor> _acceptor;
			
			/// The socket
			boost::scoped_ptr<TcpSocket> _socket;
		};
	}
}

#endif // __IM_SERVER_SERVER_H__