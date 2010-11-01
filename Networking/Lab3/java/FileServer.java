import java.net.*;
import java.io.*;

public class FileServer 
{
    public static void main(String[] args) throws IOException 
    {
    	// Create the Server Socket
        ServerSocket serverSocket = null;
        try 
        {
            serverSocket = new ServerSocket(1024);
        } 
        catch (IOException e) 
        {
            System.err.println("Could not listen on port: 1024.");
            System.exit(1);
        }
        
        //Create the Socket for the Client
        Socket clientSocket = null;
        try 
        {
            clientSocket = serverSocket.accept();
        }
        catch (IOException e) 
        {
            System.err.println("Accept failed.");
            System.exit(1);
        }

        
        //Create the file stream
        FileOutputStream out = new FileOutputStream("testfile");

        //Read from the socket	
        byte[] buf = new byte[1024];
        int length;
        while ((length = clientSocket.getInputStream().read(buf)) >= 0) 
        {
             out.write(buf, 0, length);
        }

        //Clean-up
        clientSocket.close();
        serverSocket.close();
    }
}
