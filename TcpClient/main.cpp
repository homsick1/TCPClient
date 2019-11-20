#using <System.dll>

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;


void Connect(String^ server,Int32 port, String^ message)
{
	try
	{
		TcpClient^ client = gcnew TcpClient(server, port);

		// Translate the passed message into Unicode and store it as a Byte array.
		array<Byte>^ data = Text::Encoding::Unicode->GetBytes(message);

		// Get a client stream for reading and writing.
		NetworkStream^ stream = client->GetStream();

		// Send the message to the connected TcpServer. 
		stream->Write(data, 0, data->Length);

		Console::WriteLine("Sent: {0}", message);

		// Buffer to store the response bytes.
		data = gcnew array<Byte>(256);

		// String to store the response Unicode representation.
		String^ responseData = String::Empty;

		// Read the first batch of the TcpServer response bytes.
		Int32 bytes = stream->Read(data, 0, data->Length);
		responseData = Text::Encoding::Unicode->GetString(data, 0, bytes);
		Console::WriteLine("Received: {0}", responseData);

		// Shutdown and end connection
		client->Close();
	}
	catch (ArgumentNullException ^ e)
	{
		Console::WriteLine("ArgumentNullException: {0}", e);
	}
	catch (SocketException ^ e)
	{
		Console::WriteLine("SocketException: {0}", e);
	}
}

void main()
{
	try
	{
		while (true)
		{
			Console::WriteLine("Type a message and press Enter to send...");
			String^ message = Console::ReadLine();
			Connect("127.0.0.1", 13000, message);
		}
	}
	catch (SocketException ^ e)
	{
		Console::WriteLine("SocketException: {0}", e);
	}
}