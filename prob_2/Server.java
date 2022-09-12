package prob_2;

import java.io.*;
import java.net.*;

class Server {

	public static void main(String args[]) {

        try (ServerSocket sock = new ServerSocket(6013)){

            while (true){
                // connect it to client socket
                Socket s = sock.accept();
                // We have a connection

                // to send data to the client
                // PrintStream ps = new PrintStream(s.getOutputStream());
                DataOutputStream dos = new DataOutputStream(s.getOutputStream());

                // to read data coming from the client
                BufferedReader client_data = new BufferedReader( new InputStreamReader(s.getInputStream()));

                // to read input data
                BufferedReader inp = new BufferedReader(new InputStreamReader(System.in));

                String str, str1;

                // read from User
                while (!(str1 = inp.readLine()).equals("FINISH")) {
                    
                    str = client_data.readLine();
                    System.out.println(str);

                    // send to client
                    dos.writeBytes(str1 + "\n");
                }

                // close connection
                dos.close();
                client_data.close();
                inp.close();
                sock.close();
                s.close();

                // terminate application
                System.exit(0);

            }
        }
        catch (IOException ioe) {
            System.err.println(ioe);
        }
		
	}
}