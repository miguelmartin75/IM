/// Participant.h
///
/// Implements the Participant class.
///
/// LAST UPDATED:
/// 7/11/12 8:04PM
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

#include "Participant.h"

namespace im
{
	namespace client
	{
		Participant::Participant(const std::string& nickname)
		: _id(0), _nickname(nickname)
		{
			/* do nothing */
		}
		
		Participant::Participant(Id id, const std::string& nickname)
		: _id(id), _nickname(nickname)
		{
			/* do nothing */
		}
		
		
		void Participant::setNickname(const std::string &nickname)
		{
			_nickname = nickname;
		}
		
		const std::string& Participant::getNickname() const
		{
			return _nickname;
		}
		
		
		void Participant::setId(Id id)
		{
			_id = id;
		}
		
		Participant::Id Participant::getId() const
		{
			return _id;
		}
	}
}