char* g_RecBuffer;
static int g_MAX_FRAME_SIZE = 16777216; //16 MB

class WebSocketRequestHandler: public HTTPRequestHandler
	/// Handle a WebSocket connection.
{
public:

	



	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{

		JSONValue *value;



		Application& app = Application::instance();

		
		
		try
		{


			WebSocket ws(request, response);
			app.logger().information("WebSocket connection established.");
			//char buffer[1024];
			int flags;
			int n;
			
			
			do
			{
				n = ws.receiveFrame(g_RecBuffer, g_MAX_FRAME_SIZE, flags);
				app.logger().information(Poco::format("Frame received (length=%d, flags=0x%x).", n, unsigned(flags)));
				ws.sendFrame(g_RecBuffer, n, flags);


				if (n > 0) {

					g_RecBuffer[n+1] = '\0';


					value = JSON::Parse(g_RecBuffer);
					if (value == NULL)
					{
						app.logger().information("Invalid JSON\n\n");
					}
					else {
						app.logger().information("Valid JSON\n\n");
						
						doTrace( "JSON VAL", f__s(value->Child(L"x")->number_value) , "\n\n" );

						delete value;
						value = NULL;

					}

				}

			}
			while ( (n > 0 || (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE) && PROG_ACTIVE );
			app.logger().information("WebSocket connection closed.");

			

			


		}
		catch (WebSocketException& exc)
		{
			app.logger().log(exc);
			switch (exc.code())
			{
			case WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
				response.set("Sec-WebSocket-Version", WebSocket::WEBSOCKET_VERSION);
				// fallthrough
			case WebSocket::WS_ERR_NO_HANDSHAKE:
			case WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
			case WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
				response.setStatusAndReason(HTTPResponse::HTTP_BAD_REQUEST);
				response.setContentLength(0);
				response.send();
				break;
			}
		}

		


		

	}
};


class RequestHandlerFactory: public HTTPRequestHandlerFactory
{
public:
	HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
	{
		Application& app = Application::instance();
		app.logger().information("Request from " 
			+ request.clientAddress().toString()
			+ ": "
			+ request.getMethod()
			+ " "
			+ request.getURI()
			+ " "
			+ request.getVersion());
			
		for (HTTPServerRequest::ConstIterator it = request.begin(); it != request.end(); ++it)
		{
			app.logger().information(it->first + ": " + it->second);
		}

		return new WebSocketRequestHandler;
	}
};


class WebSocketServer: public Poco::Util::ServerApplication
	/// The main application class.
	///
	/// This class handles command-line arguments and
	/// configuration files.
	/// Start the WebSocketServer executable with the help
	/// option (/help on Windows, --help on Unix) for
	/// the available command line options.
	///
	/// To use the sample configuration file (WebSocketServer.properties),
	/// copy the file to the directory where the WebSocketServer executable
	/// resides. If you start the debug version of the WebSocketServer
	/// (WebSocketServerd[.exe]), you must also create a copy of the configuration
	/// file named WebSocketServerd.properties. In the configuration file, you
	/// can specify the port on which the server is listening (default
	/// 9980) and the format of the date/time string sent back to the client.
	///
	/// To test the WebSocketServer you can use any web browser (http://localhost:9980/).
{
public:

	bool dataReady;

	WebSocketServer(): _helpRequested(false)
	{
		dataReady = false;
	}
	
	~WebSocketServer()
	{
	}

	//int main(const std::vector<std::string>& args);

protected:
	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
		ServerApplication::initialize(self);
	}
		
	void uninitialize()
	{
		ServerApplication::uninitialize();
	}

	void defineOptions(OptionSet& options)
	{
		ServerApplication::defineOptions(options);
		
		options.addOption(
			Option("help", "h", "display help information on command line arguments")
				.required(false)
				.repeatable(false));
	}

	void handleOption(const std::string& name, const std::string& value)
	{
		ServerApplication::handleOption(name, value);

		if (name == "help")
			_helpRequested = true;
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("A sample HTTP server supporting the WebSocket protocol.");
		helpFormatter.format(std::cout);
	}


	int main(const std::vector<std::string>& args)
	{

		g_RecBuffer = new char[g_MAX_FRAME_SIZE];

		// get parameters from configuration file
		unsigned short port = (unsigned short) config().getInt("WebSocketServer.port", 9980);
		
		// set-up a server socket
		ServerSocket svs(port);
		// set-up a HTTPServer instance
		HTTPServer srv(new RequestHandlerFactory, svs, new HTTPServerParams);
		// start the HTTPServer
		srv.start();
		// wait for CTRL-C or kill
		//waitForTerminationRequest();
		// Stop the HTTPServer

		glutMainLoop();
		
		srv.stop();

		delete[] g_RecBuffer;

		return Application::EXIT_OK;

		/*
		if (_helpRequested)
		{
			displayHelp();
		}
		else
		{
			// get parameters from configuration file
			unsigned short port = (unsigned short) config().getInt("WebSocketServer.port", 9980);
			
			// set-up a server socket
			ServerSocket svs(port);
			// set-up a HTTPServer instance
			HTTPServer srv(new RequestHandlerFactory, svs, new HTTPServerParams);
			// start the HTTPServer
			srv.start();
			// wait for CTRL-C or kill
			waitForTerminationRequest();
			// Stop the HTTPServer
			srv.stop();
		}
		return Application::EXIT_OK;

		return 0;
		*/
	}
	
	
private:
	bool _helpRequested;
};




 
