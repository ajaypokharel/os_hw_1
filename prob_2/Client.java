package prob_2;

import java.io.*;
import java.net.*;

class Client {

	public static void main(String args[])	{
        try {
            // Create client socket
            Socket s = new Socket("127.0.0.1", 6013);

            // send data to the server
            DataOutputStream dos = new DataOutputStream(s.getOutputStream());

            // to read data coming from the server
            BufferedReader server_data = new BufferedReader(new InputStreamReader(s.getInputStream()));

            // to read data from the keyboard
            BufferedReader inp = new BufferedReader(new InputStreamReader(System.in));
            
            String str, str1;

            // repeat as long as exit
            // is not typed at client
            while (!(str = inp.readLine()).equals("FINISH")) {

                // send to the server
                dos.writeBytes(str + "\n");

                // receive from the server
                str1 = server_data.readLine();

                System.out.println(str1);
            }

            // close connection.
            dos.close();
            server_data.close();
            inp.close();
            s.close();

        } catch (IOException ioe) {
            System.err.println(ioe);
        }
		
	}
}
