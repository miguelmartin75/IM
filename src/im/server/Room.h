/// ChatRoom.h
///
/// Declares the ChatRoom class,
/// which is used to define people in a chat.
///
/// LAST UPDATED:
/// 7/11/12 8:06PM
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

#ifndef __IM_CLIENT_ROOM_H__
#define __IM_CLIENT_ROOM_H__

#include <string>
#include <vector>

#include <boost/signals2.hpp>
#include <boost/noncopyable.hpp>


#include "Participant.h"
#include "Message.h"

namespace im
{
	namespace client
	{
		class Room
			: boost::noncopyable /* what's the point of copying a ChatRoom? It'd be quite inefficent to do so */
		{
		private:
			
			typedef boost::signals2::signal<void (const Message&)> MessageSignal;
			typedef boost::signals2::signal<void (const Participant&)> ParticipantSignal;
			
		public:
			
			/// The default amount of messages that the ChatRoom will store
			static const int DEFAULT_MAX_RECENT_MESSAGE_AMOUNT = 100;
			
			
			Room(int maxRecentMessageAmount = DEFAULT_MAX_RECENT_MESSAGE_AMOUNT);
			
			
			/// Adds a Participant to the ChatRoom
			/// \param pariticipant The Participant you wish to add to the room
			void add(const Participant& participant);
			
			/// Removes a Participant from the ChatRoom
			/// \param participant The Participant you wish to remove from the room
			void remove(const Participant& participant);
			
			/// Determines whether the room contains a Participant
			/// \param participant The Participant you wish to test for
			/// \return true if the room does contain the Participant
			bool doesContain(const Participant& participant) const;
			
		private:
			
			typedef std::vector<Message> MessageArray;
			typedef std::vector<Participant*> ParticipantArray;
			
			/// The paricipants in the ChatRoom
			ParticipantArray _participants;
			
			unsigned int _maxRecentMessageAmount;
		};
	}
}

#endif // __IM_CLIENT_ROOM_H__