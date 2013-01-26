/// Application.h
///
/// Declares the Application class, designed for the client side.
///
/// LAST UPDATED:
/// 23/11/12 9:24PM
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

#ifndef __IM_CLIENT_APPLICATION_H__
#define __IM_CLIENT_APPLICATION_H__

#include "../CommandProcessor.h"
#include "Client.h"

namespace im
{
	namespace client
	{
		/// \class Application
		/// \brief A class that defines an Application
		///
		/// This Application class is designed for the client side of instant messaging.
		/// It uses the CONSOLE, however I'm thinking of generalizing it a bit more, so in future I may
		/// create a GUI in Qt, without rewriting code.
		///
		/// \author Miguel Martin
		class Application
		{
		public:
			
			/// Constructor
			Application(Client::IoService& io_service, int argc, char** argv);
			
			
			/// Runs the application
			/// \return Any error codes that could occur
			int run();
			
		private:
			
			/// Enables or disables user input
			/// \param flag The value you wish to set it to
			void setShouldGatherUserInput(bool flag);
			
			/// \return true if the Application should gather user input
			bool shouldGatherUserInput() const;
			
			/// Processes a line of text
			/// \param line The line of text you wish to process
			void process(const std::string& line);
			
			/// initializes the application
			void init();
			
			/// Processes command line arguments
			void processCommandLine(int argc, char** argv);
			
			/// Shows a welcome message
			void showWelcomeMessage();
			
			/// Shows general help
			void showGeneralHelp();
			
			/// prints iterator information
			void printIteratorInfo(const Client::Iterator& iterator);
			
			
			/****************************************************
			 * COMMAND CALL BACKS								*
			 *													*
			 * Here is a list of the commands that	            *
			 * we require - only for the client:                *
			 * - connect <ip> <port>							*
			 * - disconnect										*
			 * - help <command-name>							*
			 * - quit											*
			 ****************************************************/
			
			/// Handles connecting to a server
			void connectCommandCallback(const CommandProcessor::CommandArgs& args);
			/// Handles disconnecting from a server
			void disconnectCommandCallback(const CommandProcessor::CommandArgs& args);
			/// Handles the help command
			void helpCommandCallback(const CommandProcessor::CommandArgs& args);
			/// Handles the set prefix command callback
			void setPrefixCommandCallback(const CommandProcessor::CommandArgs& args);
			/// Handles when the user wishes to quit
			void quitCommandCallback(const CommandProcessor::CommandArgs& args);
			
			
			// CLIENT CALL BACKS
			
			/// Occurs when we recieve data
			void onDataRecieved(const Client::Data& data);
			/// Occurs when there was an error
			void onErrorOccured(const std::string& desc, const Client::ErrorCode& errorCode);
			/// Occurs when connection is established
			void onConnectionEstablished(const Client::Iterator& iterator);
			/// Occurs when connection has failed
			void onConnectionFailed(const Client::Iterator& iterator);
			/// Occurs when an attempt to connect has occured
			void onConnectionAttempt(const Client::ErrorCode& errorCode, const Client::Iterator& iterator);
			
			
			
			/// The command processor
			CommandProcessor _commandProcessor;
			
			/// Defines the client class
			Client _client;
			
			/// The io_serivce object that is with the client application
			Client::IoService& _io_service;
			
			/// Tells when we are running our ClientApplication
			bool _isRunning;
			
			/// Determines whether we should gather user input
			bool _shouldGatherUserInput;
		};
	}
}

#endif // __IM_CLIENT_APPLICATION_H__