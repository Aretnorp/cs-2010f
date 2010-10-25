import java.io.*;
import java.net.*;

public class FileClient 
{
    public static void main(String[] args) throws IOException 
    {
        Socket fileSocket = null;

        //Open the Socket
        try 
        {
            fileSocket = new Socket("127.0.0.1", 1024);
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

        //Print the file
        byte[] buf = new byte[1024];
        int length = 0;

        FileInputStream in = new FileInputStream("/usr/bin/vim");
        while((length = in.read(buf)) >= 0)
        {
        	fileSocket.getOutputStream().write(buf, 0, length);
        }
        
        //Close streams
        in.close();
		fileSocket.close();
    }
}
