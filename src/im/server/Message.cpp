/// Message.h
///
/// Implements the Message class
///
/// LAST UPDATED:
/// 7/11/12 7:28PM
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

#include "Message.h"

// required to convert to a string and operator<< overload for the ostream
#include "Participant.h"

namespace im
{
	namespace client
	{
		Message::Message()
		: _sender(NULL) // use default constructors for every other object
		{
		}
		
		Message::Message(const Participant* sender, const std::string& body, const TimeValue& timeSent)
		: _sender(sender), _body(body), _timeSent(timeSent)
		{
		}
		
		
		Message::Message(const Message& message)
		: _sender(message._sender), _body(message._body), _timeSent(message._timeSent)
		{
		}
		
		
		void Message::setBody(const std::string& body)
		{
			_body = body;
		}
		
		const std::string& Message::getBody() const
		{
			return _body;
		}
		
		
		void Message::setTimeSent(const Message::TimeValue &timeSent)
		{
			_timeSent = timeSent;
		}
		
		const Message::TimeValue& Message::getTimeSent() const
		{
			return _timeSent;
		}
		
		
		void Message::setSender(const Participant *sender)
		{
			_sender = sender;
		}
		
		const Participant* Message::getSender() const
		{
			return _sender;
		}
		
		
		std::string Message::toString() const
		{
			std::string result;
			
			return result;
		}
		
		
		const Message& Message::operator=(const Message& message)
		{
			if(this != &message)
			{
				_sender = message._sender;
				_body = message._body;
				_timeSent = message._timeSent;
			}
			
			return *this;
		}
		
		
		std::ostream& operator<<(std::ostream& ostream, const Message& message)
		{
			return ostream << message.toString();
		}
	}
}