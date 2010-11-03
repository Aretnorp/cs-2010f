import java.io.*;
import java.net.*;

public class FileClient 
{
    public static void main(String[] args) throws IOException 
    {
        //Assign parameters
        String address = args[0];
        int port = Integer.parseInt(args[1]);
        String file = args[2];

        //Open the Socket
        PrintWriter out = null;
        Socket fileSocket = null;
        try 
        {
            fileSocket = new Socket(address, port);
            out = new PrintWriter(fileSocket.getOutputStream(), true);
        } 
        catch (UnknownHostException e) 
        {
            System.err.println("Unable to determine host");
            System.exit(1);
        } 
        catch (IOException e) 
        {
            System.err.println("Unable to connect");
            System.exit(1);
        }

        //Send the file
        out.write(file);
        
        //Print the file
        byte[] buf = new byte[1024];
        int length = 0;

        FileInputStream in = new FileInputStream(file);
        while((length = in.read(buf)) >= 0)
        {
        	fileSocket.getOutputStream().write(buf, 0, length);
        }
        
        //Close streams
        in.close();
		fileSocket.close();
    }
}
