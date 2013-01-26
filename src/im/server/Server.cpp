/// Server.cpp
///
/// Implement the Server class.
///
/// LAST UPDATED:
/// 20/11/12 12:06PM
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

#include "Server.h"

namespace im
{
	namespace client
	{
		
		Server::Server(boost::asio::io_service& service)
			: _io_service(&service)
		{
			// Start accepting connections
			startAccept();
		}
		
		/*
		void Server::addRoom(const std::string& name)
		{
			Room* roomToInsert = new Room;
			_rooms.insert(RoomDictionaryPair(name, roomToInsert));
		}
		
		
		void Server::removeRoom(const std::string& name)
		{
			// if we don't have the room in the server
			if(!doesContainRoom(name))
			{
				return; // get out of the function
			}
			
			Room* roomToDelete = _rooms[name];
			delete roomToDelete; // delete the room
			
			// and now we can actually remove it from the array
			_rooms.erase(name);
		}
		
		bool Server::doesContainRoom(const std::string& name)
		{
			for(auto i = _rooms.begin(); i != _rooms.end(); ++i)
			{
				if(i->first == name)
				{
					return true;
				}
			}
			
			return false;
		}*/
		
		
		// PRIVATE METHODS
		
		void Server::startAccept()
		{
			
		}
		
		void Server::handleAccept(ParticipantPtr participant, const ErrorCode& errorCode)
		{
			if(!errorCode)
			{
				
			}
			else
			{
				
			}
		}
	}
}