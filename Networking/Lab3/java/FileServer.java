import java.net.*;
import java.io.*;

public class FileServer 
{
    public static void main(String[] args) throws IOException 
    {
    	// Assign parameters
    	int port = Integer.parseInt(args[0]);
    	String dir = args[1];
    	
    	// Create the Directory
    	File f = new File(dir);
    	if(!f.exists())
    		f.mkdir();
    	
    	// Create the Server Socket
        ServerSocket serverSocket = null;
        try 
        {
            serverSocket = new ServerSocket(port);
        } 
        catch (IOException e) 
        {
            System.err.println("Could not listen on port: " + port);
            System.exit(1);
        }
        
        //Create the Socket for the Client
        Socket clientSocket = null;
        BufferedReader in = null;
        try 
        {
            clientSocket = serverSocket.accept();
            in = new BufferedReader(new InputStreamReader(
            		clientSocket.getInputStream()));
        }
        catch (IOException e) 
        {
            System.err.println("Accept failed.");
            System.exit(1);
        }
        
        // Get the filename
        String name = in.readLine();

        //Create the file stream
        FileOutputStream out = new FileOutputStream(name);

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
