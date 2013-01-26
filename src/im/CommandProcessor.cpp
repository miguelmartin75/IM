/// CommandProcessor.cpp
///
/// Implements the CommandProcessor class.
///
/// LAST UPDATED:
/// 22/11/12 11:16AM
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

#include "CommandProcessor.h"

#include "../ac/util/ACString.h"


namespace im
{
	CommandProcessor::CommandProcessor()
		: _commandPrefix("/")
	{
	}

	CommandProcessor::CommandProcessor(const CommandIdentifier& prefix, bool isCaseSensitive)
	{
		setCommandPrefix(prefix);
	}
	

	void CommandProcessor::add(const CommandIdentifier& id, CommandFunction function)
	{
		// remove any whitespace
		// AND convert to lower case
		std::string temp = ac::util::StringToLower(ac::util::EraseWhitespaceFromString(id));

		// now add it
		_commands[temp] = function;
	}

	void CommandProcessor::remove(const CommandIdentifier& id)
	{
		// erase the command 
		_commands.erase(id);
	}

	bool CommandProcessor::doesContain(const CommandIdentifier& id) const
	{
		// if the id isn't contained in the map then map::find will return 
		// the map's end iterator, which is obtained by end()
		return (_commands.find(id) != _commands.end());
	}

	bool CommandProcessor::process(const CommandIdentifier& line)
	{
		CommandIdentifier identifier = extractCommandIdFromLine(line);
		// if there is not a command in the line
		if(!doesContain(identifier))
		{
			return false; // tell the caller that we failed :(
		}

		CommandArgs arguments = extractArgumentsFromLine(line);

		_commands[identifier](arguments);
		return true; // yay we succeded
	}

	void CommandProcessor::setCommandPrefix(const CommandIdentifier& prefix)
	{
		// remove any whitespace that may have been caught up
		_commandPrefix = ac::util::EraseWhitespaceFromString(prefix);
	}

	const CommandProcessor::CommandIdentifier& CommandProcessor::getCommandPrefix() const
	{
		return _commandPrefix;
	}

	bool CommandProcessor::isCommand(const std::string& line)
	{
		std::string extractedCommandPrefix = line.substr(0, _commandPrefix.length());
		return (extractedCommandPrefix == _commandPrefix);
	}


	// PRIVATE METHODS

	std::string CommandProcessor::extractCommandIdFromLine(const std::string& line)
	{
		std::string commandId;

		// is the line actually a command?
		if(isCommand(line))
		{
			// extract the ID from the command
			// we want everything from the first character to just before whitespace
			commandId = line.substr(_commandPrefix.length(), line.find(' ') - 1);
		}

		return ac::util::StringToLower(commandId);
	}


	CommandProcessor::CommandArgs CommandProcessor::extractArgumentsFromLine(const std::string& line)
	{
		size_t lengthOfPrefixAndCommand = _commandPrefix.length() + line.find(' ');
		if(lengthOfPrefixAndCommand == line.length())
		{
			return CommandArgs();
		}
		
		std::string rawArguments = line.substr(lengthOfPrefixAndCommand,
												line.length() - lengthOfPrefixAndCommand);
		CommandArgs temp;
		std::string buffer;
		for(size_t i = 0; i < rawArguments.length(); ++i)
		{
			// if we found white space or we're on the last character..
			if(rawArguments[i] == ' ')
			{
				temp.push_back(buffer); // add the buffer to the dynamic array
				buffer = ""; // clear the buffer
			}
			// last character
			else if(i == rawArguments.length() - 1)
			{
				buffer += rawArguments[i]; // add on the character
				temp.push_back(buffer); // add the buffer to the dynamic array
			}
			else
			{
				// add on the character, as we're continuing to loop through the string
				buffer += rawArguments[i];
			}
		}

		return temp;
	}
}