/// Application.h
///
/// Declares the Application class, designed for the client side.
///
/// LAST UPDATED:
/// 13/11/12 3:00PM
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

#ifndef __IM_SERVER_APPLICATION_H__
#define __IM_SERVER_APPLICATION_H__

#include "../CommandProcessor.h"

namespace im
{
	namespace server
	{
		// this class is not finished, as the Server class has not been completed...
		class Application
		{
		public:
			
			//Application(Client::IoService& io_service, int argc, char** argv);
			
			/// Runs the application
			/// \return Any error codes that could occur
			int run();
			
			
		private:
			/*
			
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
			
			*/
			/****************************************************
			 * COMMAND CALL BACKS								*
			 *													*
			 * Here is a list of the commands that	            *
			 * we require - only for the client:                *
			 * - host <ip> <port>								*
			 * - disconnect										*
			 * - help <command-name>							*
			 * - quit											*
			 ****************************************************/
			/*
			
			/// The command processors
			CommandProcessor _commandProcessor;
			
			/// Tells when we are running our ClientApplication
			bool _isRunning;
			
			/// Determines whether we should gather user input
			bool _shouldGatherUserInput;
			 */
		};
	}
}

#endif // __IM_CLIENT_APPLICATION_H__