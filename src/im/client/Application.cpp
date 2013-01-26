/// Application.h
///
/// Implements the Application class.
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

#include "Application.h"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

namespace im
{
	namespace client
	{
		Application::Application(Client::IoService& io_service, int argc, char** argv)
			: _io_service(io_service),
			  _client(io_service),
			  _isRunning(true),
			  _shouldGatherUserInput(true)
		{
			// initalize the applicatoin
			init();
			
			// process the command line arguments
			processCommandLine(argc, argv);
		}
		
		
		int Application::run()
		{
			showWelcomeMessage();
			_client.setBufferSize(1);
			
			std::string buffer;
			while(_isRunning)
			{
				// if we should gather input from the user
				if(_shouldGatherUserInput)
				{
					// Get input from the user
					std::getline(std::cin, buffer);
					
					// process the inputted line
					this->process(buffer);
				}
			}
			
			return 0;
		}
		
		
		void Application::process(const std::string& line)
		{
			// if the line is a commmand
			if(!_commandProcessor.process(line))
			{
				// are we connected to a server?
				if(_client.isConnected())
				{
					// if so, we will send the line to the server
					_client.write(Client::Data(line.begin(), line.end()));
				}
			}
		}
		
		void Application::setShouldGatherUserInput(bool flag)
		{
			_shouldGatherUserInput = flag;
		}
		
		bool Application::shouldGatherUserInput() const
		{
			return _shouldGatherUserInput;
		}
		
		// private methods
		
		void Application::init()
		{
			// set the command processor prefix to a colon ( : ), this way we may not confuse
			// IRC related commands with the actual application commands, e.g. help
			_commandProcessor.setCommandPrefix(":");
			
			// link up call backs for the client
			_client.doOnConnectionAttempt(boost::bind(&Application::onConnectionAttempt, this, _1, _2));
			_client.doOnConnectionEstablished(boost::bind(&Application::onConnectionEstablished, this, _1));
			_client.doOnErrorOccured(boost::bind(&Application::onErrorOccured, this, _1, _2));
			_client.doOnDataRecieved(boost::bind(&Application::onDataRecieved, this, _1));
			
			// link up commands for the command processor
			
			// The connect command
			_commandProcessor.add("connect", boost::bind(&Application::connectCommandCallback, this, _1));
			// The disconnect command
			_commandProcessor.add("disconnect", boost::bind(&Application::disconnectCommandCallback, this, _1));
			// The quit command
			_commandProcessor.add("quit", boost::bind(&Application::quitCommandCallback, this, _1));
			// The held command
			_commandProcessor.add("help", boost::bind(&Application::helpCommandCallback, this, _1));
			// The set command prefix command
			_commandProcessor.add("setPrefix", boost::bind(&Application::setPrefixCommandCallback, this, _1));
		}
		
		
		void Application::processCommandLine(int argc, char **argv)
		{
			/* do nothing */
		}
		
		
		void Application::showWelcomeMessage()
		{
			std::cout << "Welcome to Miguel's IM Application.\n";
			std::cout << "To enter a command, please type \"" << _commandProcessor.getCommandPrefix() << "\" before the command name, and provide arguments (if the command requires commands).\n";
			std::cout << "To get information about some valid commands, type in the \"help\" command.\n\n";
		}
		
		void Application::showGeneralHelp()
		{
			std::cout << "To enter a command, please type \"" << _commandProcessor.getCommandPrefix() << "\" before the command name, and provide arguments (if the command requires commands).\n";
			std::cout << "COMMANDS:\n";
			std::cout << "<name> <optional-arguments> - <description>\n";
			std::cout << "help <command-name> - gathers help\n";
			std::cout << "quit - quits the application\n";
			std::cout << "connect <ip> <port> - connects to a server\n";
			std::cout << "disconnect - disconnects from the connected server\n";
		}
		
		void Application::printIteratorInfo(const Client::Iterator& iterator)
		{
			std::cout << iterator->endpoint().address() << " port: " << iterator->endpoint().port();
		}
		
		
		// COMMAND CALL BACKS
		
		void Application::connectCommandCallback(const CommandProcessor::CommandArgs& args)
		{
			// this command requires 2 arguments
			if(args.size() < 2)
			{
				// show a message to show how to use the command
				return;
			}
			
			_client.connect(args[0], args[1]);
			setShouldGatherUserInput(false); // disable user input...
		}
		
		void Application::disconnectCommandCallback(const CommandProcessor::CommandArgs& args)
		{
			// no point in being here, we're not connected
			if(!_client.isConnected())
			{
				std::cerr << "[NOTICE]: You must be connected to a server to disconnect from one!\n";
				return;
			}
			
			std::cout << "Disconnecting from connected server...\n";
			_client.close();
		}
		
		void Application::helpCommandCallback(const CommandProcessor::CommandArgs& args)
		{
			showGeneralHelp();
		}
		
		void Application::setPrefixCommandCallback(const CommandProcessor::CommandArgs& args)
		{
			// this command requires 1 argument
			if(args.size() < 1)
			{
				// show a message
				return;
			}
			
			// set the prefix
			_commandProcessor.setCommandPrefix(args[0]);
		}
		
		void Application::quitCommandCallback(const CommandProcessor::CommandArgs& args)
		{
			std::cout << "Quiting...\n";
			_isRunning = false;
			_client.close();
		}
		
		
		// CLIENT CALL BACKS
		
		void Application::onDataRecieved(const Client::Data& data)
		{
			std::string text(data.begin(), data.end());
			std::cout << text;
		}
		
		void Application::onErrorOccured(const std::string& desc, const Client::ErrorCode& errorCode)
		{
			std::cout << "[ERROR]: " << desc << " " << errorCode << '\n';
			setShouldGatherUserInput(true);
		}
		
		void Application::onConnectionEstablished(const Client::Iterator& iterator)
		{
			std::cout << "[NOTICE]: Successfully connected to server: ";
			printIteratorInfo(iterator);
			std::cout << '\n';
			setShouldGatherUserInput(true);
		}
		
		void Application::onConnectionFailed(const Client::Iterator& iterator)
		{
			std::cout << "[ERROR]: Connection to server failed: ";
			printIteratorInfo(iterator);
			std::cout << '\n';
			setShouldGatherUserInput(true);
		}
		
		void Application::onConnectionAttempt(const Client::ErrorCode& errorCode, const Client::Iterator& iterator)
		{
			std::cout << "[NOTICE]: Attempting Connection to server: ";
			printIteratorInfo(iterator);
			std::cout << '\n';
			setShouldGatherUserInput(false);
		}
	}
}