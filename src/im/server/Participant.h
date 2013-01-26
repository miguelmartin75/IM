/// Participant.h
///
/// Declares the Participant class,
/// which is used to define people in a chat.
///
/// LAST UPDATED:
/// 7/11/12 8:08PM
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

#ifndef __IM_CLIENT_PARTICIPANT_H__
#define __IM_CLIENT_PARTICIPANT_H__

#include <string>
#include <boost/noncopyable.hpp>

namespace im
{
	namespace client
	{
		/// \class ChatParticipant
		/// \brief A particpant in a chat, i.e. A person in a chat
		///
		/// This class defines a particpant in a chat. Typically,
		/// a particpant has a name.
		///
		/// \author Miguel Martin
		class Participant
		: boost::noncopyable /* I don't want chat particpants to be copied; there is no point */
		{
		public:
			
			/// The default nickname that is given to a ChatParticipant
			static std::string DefaultNickname;
			
			/// An identifier that the chat participant has
			typedef unsigned int Id;
			
			
			/// Constructs a ChatParticiapnt object with a nickname
			/// \param nickname The nickname of the chat participant
			Participant(const std::string& nickname = DefaultNickname);
			
			/// Constructs a ChatParticipant object with an ID
			/// \param id The identifier of the ChatParticipant
			/// \param nickname The nickname of the chat participant
			Participant(Id id, const std::string& nickname = DefaultNickname);
			
			
			/// Sets the nickname of the ChatParticipant
			/// \param nickname The nickname of the ChatParticipant
			void setNickname(const std::string& nickname);
			
			/// \return The nickname of the ChatParticipant
			const std::string& getNickname() const;
			
			
			/// Sets the ID of the ChatParticipant
			/// \param id The identifier of the ChatParticipant, a.k.a index/element
			void setId(Id id);
			
			/// \return The identifier of the ChatParticipant, a.k.a index/element
			Id getId() const;
			
		private:
			
			/// The Identifier of the ChatParticipant
			/// This is used for quick access for the stored ChatParticipants on the server
			/// This basically should store the index of where the ChatParticipant is located
			/// In the array of ChatParticipants in a server.
			Id _id;
			
			/// the nick name of the ChatParticipant
			std::string _nickname;
		};
	}
}

#endif // __IM_CLIENT_PARTICIPANT_H__