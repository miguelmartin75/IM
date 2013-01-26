/// CommandProcessor.h
///
/// Defines the CommandProcessor class.
///
/// LAST UPDATED:
/// 22/11/12 11:17AM
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

#ifndef __IM_COMMANDPROCESSOR_H__
#define __IM_COMMANDPROCESSOR_H__

#include <vector>
#include <map>
#include <string>
#include <algorithm>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>


namespace im
{
	/// \class CommandProcessor
	/// \brief Processes commands
	/// 
	/// This class can have multiple commands added to it, and it will
	/// process the commands.
	/// 
	/// \author Miguel Martin
	class CommandProcessor
		: boost::noncopyable
	{
	public:
		
		/// Identifies a Command
		typedef std::string CommandIdentifier;
		/// The arguments for a command
		typedef std::vector<std::string> CommandArgs;
		/// Defines a function object that we will use for commands
		typedef boost::function<void (const CommandArgs& arguments)> CommandFunction;
		
		
		/// Default constructor
		CommandProcessor();

		/// \param prefix The prefix that begins a command
		/// \param isCaseSensitive A flag to tell whether commands should be case sensitive or not 
		CommandProcessor(const CommandIdentifier& prefix, bool isCaseSensitive);


		
		/// Adds a command
		/// \param id The ID of the command you wish the command to have
		/// \param function The function you wish to add
		/// \note
		/// If the name already exists, then it will add the slot to process the command
		void add(const CommandIdentifier& id, CommandFunction function);
		
		/// Removes a command
		/// \param id The ID of the command that you wish to remove
		void remove(const CommandIdentifier& id);
		
		/// Determines whether this CommandProcessor object contains a command
		/// \param name The ID of the command
		/// \return true if this CommandProcessor object does contain the command
		bool doesContain(const CommandIdentifier& id) const;

		/// Processes a command
		/// \param line The line you wish to process
		/// \return false if this function did not process the command properly, i.e. the command does not exist
		bool process(const CommandIdentifier& line);
		
		/// Sets the command prefix
		/// i.e. The part of the string that identifies a command
		/// \param prefix The prefix you wish to use
		/// \note THIS PREFIX CANNOT BE OF LENGTH 0, IT MUST HAVE SOME CHARACTERS
		/// If you pass in a prefix with nothing in it, it will simply be ignored.
		void setCommandPrefix(const CommandIdentifier& prefix);

		/// \return The command prefix
		const CommandIdentifier& getCommandPrefix() const;
		
		/// Determines whether a line is a command
		/// \note
		/// This does not check if the command actually exists
		/// \param line The line you wish to determine whether it is a command
		/// \return true if the line is a command
		bool isCommand(const std::string& line);
		
	private:
		
		/// Extracts a Command ID from a line
		/// \param line The line you wish to extract the command ID from
		/// \return The command id (name) that was in the line
		std::string extractCommandIdFromLine(const std::string& line);

		/// Extracts arguments from a line
		/// \param line The line you wish to extract the arguments from
		CommandArgs extractArgumentsFromLine(const std::string& line);


		// MAY HAVE TO USE POINTERS IN ORDER FOR THIS TO WORK
		
		/// A dictionary of commands in the command processor
		typedef std::map<CommandIdentifier, CommandFunction> CommandDictionary;
		/// A pair of objects that is used to pair a command identifier with a command signal
		/// This is used so we can add and iterate to/through a CommandDictionary
		typedef std::pair<CommandIdentifier, CommandFunction> CommandDiciontaryPair;


		/// The commands in the command processor
		CommandDictionary _commands;
		
		/// The prefix for a command
		/// this is the prefix for a command, by default it is a backslash ('/')
		CommandIdentifier _commandPrefix;
	};
}

#endif // __IM_COMMANDPROCESSOR_H__