/// main.cpp
///
/// Defines the main function for the IM application.
/// This file has the ability to be compiled for either the client application
/// or the server application.
///
/// LAST UPDATED:
/// 22/11/12 9:13PM
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

#include <boost/thread.hpp> // for multi-threading

#define SERVER_BUILD 0 // used to determine if we'd like a server build of the program
#define CLIENT_BUILD 1 // used to determine if we'd like a client build of the program

// Used to determine what type of build this is...
//#define BUILD_TYPE SERVER_BUILD // uncomment this and comment out the below line for a server build
#define BUILD_TYPE CLIENT_BUILD // uncomment this and comment out the above line for a client build


// This is used to determine what type of Application object we're wanting to create
#if (BUILD_TYPE == SERVER_BUILD)
	// include the server application
#	include "im/server/Application.h"
	using namespace im::server; // this is for a server Application
#elif (BUILD_TYPE == CLIENT_BUILD)
	// include the client Application
#	include "im/client/Application.h"
	using namespace im::client; // this is for a client Application
#endif


// main starting point of the application
int main(int argc, char** argv)
{
	// Just for less typing...
	using namespace im;
	using namespace boost::asio;
	
	io_service service; // The I/O service object used, so we can connect to the internet
	io_service::work work(service); // used so that the run function in the below thread keeps going
	// we require another thread,
	// so that we can run the function run for the io_service the whole time the application is open
	boost::thread t(boost::bind(&boost::asio::io_service::run, &service));
	
	// now let's create an application
	Application app(service, argc, argv);
	
	// run the application
	int returnValue = app.run(); // store the return value of the application in a variable
	return returnValue; // return the return value from the application
}