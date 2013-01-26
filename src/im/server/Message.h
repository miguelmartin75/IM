/// Message.h
///
/// Declares the Message class.
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

#ifndef __IM_MESSAGE_H__
#define __IM_MESSAGE_H__

#include <iostream>
#include <string>

// for ptime (standing for posix time),
// which basically encapsulates a time and a date into an
// object... thank you boost ;D
#include <boost/date_time/posix_time/posix_time.hpp>


namespace im
{
	namespace client
	{
		class Participant;
		
		/// \class Message
		/// \brief Defines a Message that is sent
		///
		/// This class simply describes a message,
		/// it has the date it was sent and who it was sent by.
		///
		/// \author Miguel Martin
		class Message
		{
		public:
			
			// a typedef for the ptime object; less typing required
			typedef ::boost::posix_time::ptime TimeValue;
			
			
			/// Default constructor
			Message();
			
			/// Constructs a Message object
			/// \param sender The Participant who sent the message
			/// \param body The body of text that the message contains
			/// \param timeSent The time that the message is sent
			Message(const Participant* sender, const std::string& body, const TimeValue& timeSent = ::boost::posix_time::second_clock::local_time());
			
			/// Copy constructor
			/// \param message The message object you wish to copy from
			Message(const Message& message);
			
			
			/// Sets the body text of the Message
			/// \param body The text of the body you wish the message to have
			void setBody(const std::string& body);
			
			/// \return The body text of the Message
			const std::string& getBody() const;
			
			
			/// Sets the Time the message is sent
			/// \param timeSent The time that the message is sent
			void setTimeSent(const TimeValue& timeSent);
			
			/// \return The time that the message was sent
			const TimeValue& getTimeSent() const;
			
			
			/// Sets the sender of the Message
			/// \param sender The Participant who has sent this message
			void setSender(const Participant* sender);
			
			/// \return The chat participant who has sent this message
			const Participant* getSender() const;
			
			
			/// \return The Message converted to a string
			std::string toString() const;
			
			
			/// Assignment operator
			/// \param message The message you wish to assign to
			/// \return The current object being assigned to
			const Message& operator=(const Message& message);
			
		private:
			
			/// The body of text
			std::string _body;
			
			/// The sender that sent the message
			const Participant* _sender;
			
			/// The time that this message was sent
			TimeValue _timeSent;
		};
		
		
		// stream operator, for use with streams
		std::ostream& operator<<(std::ostream&, const Message&);
		
	}
}

#endif // __IM_MESSAGE_H__