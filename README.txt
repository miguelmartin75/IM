				   Anax IM Application
			       	      Version 1.0
			      	Anax Creations © 2012

			Author(s):
				Miguel Martin - Programmer and Designer

NOTES:
-----

*.h files contain INTERFACES of a class, or functions.
*.cpp files contain the IMPLEMENTATION of a class or functions.

To look at how the program is RUN from start to end, look at the main.cpp file.
The Client application is in the directory: im/client/Application.h
Similarly the Server application is in the directory: im/server/Application.h

P.S.
I didn't get to finishing what I wanted to start
So most of the commands I wanted in there are not actually implemented all there, but the basic ones are there.


> CONTENTS
==========
	1. Brief 
		- A brief description of what the Anax IM Application is about
	2. Tutorial
		- A simple tutorial to help get you started
	3. Appendices 
		a. Appendix A - Commands
		b. Appendix B - Command Line Arguments


> BRIEF
=======
	The Anax IM application is designed to be VERY similar to IRC chats, however it is quite smaller.
	Maybe sooner or later it will transition to into making this into an IRC client, but for this time 
	being it is just a simple IM application. Before using this IM application, you may wish to understand
	what a server is, and also what the differences between a server and a chat room is.

	WHAT'S A SERVER?
	----------------
		Server - Noun
		1. A person or thing that provides a service or commodity, in particular.
		2. A computer or computer program that manages access to a centralised 
		   resource or service in a network.

		For this application's case, a server is a program that contains various chat rooms* 
		that allows users (clients*) to chat through.

		*this will be discussed later on


	WHAT'S A CHAT ROOM?
	-------------------
		A chat room is a virtual room, where you can talk to other people.
		The people inside of this chat room may be administrators, or simply guests.
		Administrators may kick/ban other people inside a chat room.

		WARNING:
		Administrators CAN kick/ban other Administrators.


> TUTORIAL:
===========
	Now you're probably thinking: "Okay so you taught me the differences between a server 
	and a chat room, but all I really want to do is chat to my friends!". The notation that
	is used in this tutorial to resemble input in the application is a separate line with 
	the '>' character preceding the text.

	e.g. 
	>Hello World

	Before you do anything you must first understand what a command is. A command is simply a
	statement, that is occupied by one line, which you type. A command performs a particular 
	function, depending on what a command is implemented to do. The syntax of a command is as follows:

	>/command_name <optional arguments>

	All commands start with a back slash (/). "command_name" is the name of the command, and
	<optional arguments> is arguments that you may specify for the command.

	For example, if you wish to change your name to "George", so that the people you are talking
	to may recognise you, the command is as follows:

	>/nick George

	Where nick is the name of the command, and George is the proceeding argument that goes along
	with the nick command. 



	1. CONNECTING/DISCONNECTING FROM A SERVER
		To connect to a server you must use the "connect" command. The connect command takes two arguments, 
		first is the server's IP address OR host name. The second argument is the port number.

		e.g.

		>/connect localhost 6660

		This command connects to the localhost (your local machine) on port 6660.

		To disconnect from a connected server, simply use the command "disconnect".

		NOTE:
			You must be connected to a server before you perform this command to take any effect.

		e.g.
		>/disconnect

	2. JOINING/LEAVING A CHAT ROOM
		To join a chat room, you simply use the "join" command along with the chat room's name. 

		e.g.
		>/join ExampleChatRoom

		NOTE:
			If the name of the chat room you have specified to join is not registered, 
			you will automatically create your own chat room, in which case you will be 
		administrator of the chat room.
		
		And similarly with the disconnect command, you use the leave command to leave a chat room.

		e.g.
		>/leave

		NOTE:
			You must be in a chat room to leave a chat room.

		You're probably wondering, how the heck do I know what the chat room's name is? 
		Well there is a command to list all the chat rooms in a server. To do this use the command "list".

		e.g.
		>/list

	3. CHANGING YOUR NICKNAME
		As discussed previously, to change your nickname inside the chat room that you are in,
		you use the "nick" command, along with the nickname you wish to have.

		e.g.
		>/nick George

		Your nickname is technically not case sensitive, but it will be displayed as whatever case(s) 
		you typed it with.

		e.g.
		>/nick George
		>Hello
		>[5/11/12 10:07PM] George: Hello


	3. SENDING MESSAGES

		Once you are connected to a server and joined in the chat room that you wish to talk in, 
		you may send messages. To send a message you simply type your message and press return/enter 
		on your keyboard. This will send your message to everyone in the chat room you are connected in.

		e.g.
		>Hello
		[5/11/12 8:03PM] miguel: Hello

	4. KICKING/BANNING PARTICIPANTS IN CHAT ROOMS

		To kick/ban a person out the chat room, you simply use the "kick" or "ban" command, 
		along with the nickname of the person you wish to kick. As discussed before, the nickname
		that you supply is not case sensitive.

		e.g.
		>/kick George

		^ that command is the same as this command:

		/kick george

		Kicking someone out from a chat room is very different from banning someone. 
		Kicking someone simply "kicks" them out of the chat room, but the person MAY join back 
		in the chat room immediately. 
		
		Banning someone from a chat room KICKS them out of the chat room AND disallows them from 
		joining the chat room, until the server is reset or they are unbanned. To ban someone,
		simple use the "ban" command along with the nickname of the person you wish to ban.
		e.g.
		>/ban George
		
		To unban someone, simply use the "unban" command along with the nickname of the person you wish to unbar.
		e.g.
		>/unban George



	5. RETRIEVING THE NAMES OF EVERYONE INSIDE OF THE CHAT ROOM

		To retrieve a list of the names of everyone that is inside the room that you are in, you simply 

		e.g.
		>/names

		By now you should have the absolute minimum understanding of how this IM application works, 
		and what some various different commands are to go along with the application. There are more
		commands, and if you wish to know more commands or in greater depth see Appendix A.


APPENDICES
---------


	APPENDIX A - COMMANDS:
	----------------------

		>/connect <host> <port>
			Connects to a server with a specified host and port number

				EXCEPTIONS:
					1. Not connected to internet
					2. Invalid host/port number

		>/disconnect
			Disconnects from a server

			EXCEPTIONS:
				1. Not connected to a server

		>/join <chat room name>
			Joins to a chat room on the currently connected server
				
				EXCEPTIONS:
					1. Chat room does not exist
					2. Chat room requires a pass word

		>/leave
			Leaves the currently connected chat room
			
				EXCEPTIONS:
					1. Not currently inside a chat room


		>/list
			Lists all chat rooms on a server, showing whether they are password protected or not

			EXCEPTIONS:
				1. Not connected to a server
				2. No available chat rooms	
			e.g.
			>/list
			_________________________________________
			|NAME 		  | PASSWORD PROTECTED?  |
			|------------------|---------------------|
			|Awesome Chat Room | NO			 |
			|Cheese Factory    | YES		 |
			------------------------------------------
			>/op <nickname>

			Makes a person inside the chatroom an administrator.

			EXCEPTIONS:
				1. Nickname does not exist
				2. Person is already administrator

		>/deop <nickname>

			Makes a person not an administrator.
				
				EXCEPTIONS:
					1. Nickname does not exist
					2. Person is not administrator

			>/nick <name>
			Sets your nickname. This is what you're known as to other people.
			Valid Characters:
			A-Z
			a-z
			0-9
			!@#$%^&*()-=_+[]{}\|;':",.<>/?
			NO SPACES

				EXCEPTIONS:
					1. Nickname is already taken
					2. Invalid characters

			e.g.

			>/nick miguel
			Attempting the change name from "guest123" to "miguel"...
			Successfully set name to "miguel", from "guest123".


	Appendix B - COMMAND LINE ARGUMENTS
	==================================

		-connect <host> <port>
		Connects to a server
		-join <chat room name>
		Joints a chat room
		-nick <name>
		Sets your nickname


		e.g.
		>IM -c localhost 30 -j myRoom -n miguel
		Connecting to localhost on port 30...
		Successfully connected to localhost.
		Attempting to join chatroom "myRoom"...
		Successfully joined chatroom "myRoom".
		Attempting the change name from "guest123" to "miguel"...
		Successfully set name to "miguel", from "guest123".