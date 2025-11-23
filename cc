Aim: A client server based program using TCP to find if the number entered is prime

import java.io.*;
import java.net.*;

public class TCPServer {

    public static void main(String[] args) {

        try {

            ServerSocket serverSocket = new ServerSocket(8888);
            System.out.println("Server started. Waiting for client....");

            Socket socket = serverSocket.accept();
            System.out.println("Client connected.");

            DataInputStream dis = new DataInputStream(socket.getInputStream());
            DataOutputStream dos = new DataOutputStream(socket.getOutputStream());

            int number = dis.readInt();
            System.out.println("Received number:" + number);

            boolean isPrime = checkPrime(number);
            String result = number + (isPrime ? " is a Prime Number" : "is not a prime number");
            dos.writeUTF(result);

            dis.close();
            dos.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static boolean checkPrime(int num) {
        if (num <= 1) {
            return false;
        }
        for (int i = 2; i <= Math.sqrt(num); i++) {
            if (num % i == 0) {
                return false;

            }
        }
        return true;
    }
}

#code for TCPClient

import java.io.*;
import java.net.*;
import java.util.Scanner;

public class TCPClient {

    public static void main(String[] args) {
        try {
            Socket socket = new Socket("localhost", 8888);
            DataInputStream dis = new DataInputStream(socket.getInputStream());
            DataOutputStream dos = new DataOutputStream(socket.getOutputStream());

            Scanner scanner = new Scanner(System.in);
            System.err.println("Enter a number to check for a prime:");
            int number = scanner.nextInt();

            dos.writeInt(number);

            String result = dis.readUTF();
            System.err.println("Server says:" + result);

            dis.close();
            dos.close();
            socket.close();
            scanner.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}

Aim:  A client server TCP based chatting  application
import java.io.*;
import java.net.*;

public class ChatServer {
     public static void main(String[] args) {
         try {
             ServerSocket serverSocket = new ServerSocket( 5000);
             System.out.println("Server started. Waiting for client...");


             Socket socket = serverSocket.accept();
             System.out.println("Client connected....");
            
             
             DataInputStream dis  = new DataInputStream(socket.getInputStream());
             DataOutputStream dos  = new DataOutputStream(socket.getOutputStream());
             BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
             
             String clientMessage = "" ,serverMessage = "";
 

             while(!clientMessage.equals("bye")) {
                 clientMessage = dis.readUTF();
                 System.out.print("Client:" + clientMessage);
                 
 
                System.out.print("Server:");
                serverMessage = reader.readLine();
                dos.writeUTF (serverMessage);
                dos.flush(); 
             }
            dis.close();
            dos.close();
            socket.close();
            serverSocket.close();
            } catch(Exception e){
               System.out.println("Error:" +e);
            }
         }
       }

code for ChatClient
import java.io.*;
import java.net.*;

public class ChatClient {
     public static void main(String[] args ){
         try {
             Socket socket  = new Socket("localhost", 5000);
             System.out.println("Connected to Server..")
             
             DataInputStream dis  = new DataInputStream(socket.getInputStream());
             DataOutputStream dos  = new DataOutputStream(socket.getOutputStream());
             BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
             
             String clientMessage = "" ,serverMessage = "";
 

             while(!clientMessage.equals("bye")) {
                 System.out.print("Client:");
                 clientMessage = reader.readLine();
                 dos.writeUTF(clientMessage);
                 dos.flush();


                serverMessage = dis.readUTF();
                System.out.println("Server:" +serverMessage);
            }
            dis.close();
            dos.close();
            socket.close();
           } catch(Exception e){
               System.out.println("Error:" +e);
            }
         }
       }

Aim : A client server based program using  UDP to find if the number entered is  even or odd.
import java.io.*;
import java.net.*;

public class EvenOddServer{
  public static void main(String[] args){
    DatagramSocket serverSocket = null;
    try{
        serverSocket = new DatagramSocket(9876);
        byte[] receiveData = new byte [1024];
        byte[] sendData = new byte[1024];

        System.out.println("UDP Server listening on port 9876....");
        
        while(true){
         DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
         serverSocket.receive(receivePacket);

         String clientMessage = new String(receivePacket.getData(),0,receivePacket.getLength());
         int number = Integer.parseInt(clientMessage.trim());
         InetAddress clientAddress = receivePacket.getAddress();
         int clientPort = receivePacket.getPort();

         String response;
         if(number%2 ==0){
            response = number+" is Even";
         } else {
            response = number+" is Odd";
         }
         
         sendData = response.getBytes();
         DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, clientAddress, clientPort);

         serverSocket.send(sendPacket);
         }
      } catch (IOException e){
         e.printStackTrace();
     } finally {
        if (serverSocket != null){
           serverSocket.close();
        }
      }
   }
}

Code for EvenOddClient
import java.io.*;
import java.net.*;
import java.util.Scanner;

public class EvenOddClient{
  public static void main(String[] args){
    DatagramSocket clientSocket = null;
    try{
        clientSocket = new DatagramSocket();
        InetAddress serverAddress = InetAddress.getByName("localhost");
        int serverPort = 9876;
        
        Scanner scanner = new Scanner(System.in);
        byte[] sendData = new byte [1024];
        byte[] receiveData = new byte[1024];

        System.out.println("Enter a number....");
        String numberString = scanner.nextLine();

        sendData =  numberString.getBytes();
        DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, serverAddress , serverPort);
        clientSocket.send(sendPacket);

        
        DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
        clientSocket.receive(receivePacket);

        String serverResponse = new String(receivePacket.getData(),0,receivePacket.getLength());
        System.out.println("Server response :" +serverResponse);
        
       
      } catch (IOException e){
         e.printStackTrace();
     } finally {
        if (clientSocket != null){
           clientSocket.close();
        }
      }
   }
}

Aim :  A client server based program using  UDP to find the factorial of the entered number. 
import java.net.*;
import java.io.*;

public class UDPFactorialServer {
    public static void main(String[] args) {
        int port = 1234;

        try {
            DatagramSocket socket = new DatagramSocket(port);
            System.out.println("Server is running on port " + port + "...");

            while (true) {
                // Receive number from client
                byte[] buffer = new byte[1024];
                DatagramPacket receivedPacket = new DatagramPacket(buffer, buffer.length);
                socket.receive(receivedPacket);

                String message = new String(receivedPacket.getData(), 0, receivedPacket.getLength()).trim();
                int number = Integer.parseInt(message);

                // Calculate factorial
                int result = 1;
                for (int i = 1; i <= number; i++) {
                    result *= i;
                }

                String response = "Factorial of " + number + " is " + result;

                // Send result back to client
                byte[] responseData = response.getBytes();
                InetAddress clientAddress = receivedPacket.getAddress();
                int clientPort = receivedPacket.getPort();

                DatagramPacket responsePacket = new DatagramPacket(responseData, responseData.length, clientAddress, clientPort);
                socket.send(responsePacket);

                System.out.println("Processed request for number: " + number);
            }
        } catch (Exception e) {
            System.out.println("Server error: " + e.getMessage());
            e.printStackTrace();
        }
    }
}

Code for FactorialClient
import java.io.*;
import java.net.*;
import java.util.Scanner;

public class UDPFactorialClient {
  private final static String SERVER_IP ="localhost";
  private final static int SERVER_PORT =9876;
  
  public static void main(String[] args) throws IOException {
     DatagramSocket clientSocket = new DatagramSocket();
     InetAddress serverAddress = InetAddress.getByName(SERVER_IP);
     byte[] sendData;
     byte[] receiveData = new byte[1024];
     Scanner scanner=new Scanner(System.in);

    System.out.println("Enter a number to calculate its factorial:");
    int number=scanner.nextInt();

    sendData=String.valueOf(number).getBytes();
    DatagramPacket sendPacket =  new DatagramPacket(sendData,Data.length,serverAddress,SERVE_PORT);
    clientSocket.send(sendPacket);

   DatagramPacket receivePacket =  new DatagramPacket(receiveData,receiveData.length);
   clientSocket.receive(sendreceive);

   String FactorialStr = new String(receivePacket.getData(), 0 ,receivePacket.getLength());
   
  }
}

Aim: A program that finds the square, square root, cube and cube root of the entered number.
import java.io.*;
import java.net.*;
public class Server {     
public static void main(String[] args) { 
        try { 
            ServerSocket serverSocket = new ServerSocket(5000); 
            System.out.println("Server started. Waiting for client..."); 
            Socket socket = serverSocket.accept(); 
            System.out.println("Client connected."); 
            BufferedReader in = new BufferedReader(new 
InputStreamReader(socket.getInputStream())); 
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true); 
            // Read number from client 
            String input = in.readLine();
            double num = Double.parseDouble(input); 
            // Calculations             
            double square = num * num;             
            double sqrt = Math.sqrt(num);            
            double cube = num * num * num;             
            double cbrt = Math.cbrt(num); 
            // Sending results back to client             
            out.println("Square: " + square);             
            out.println("Square Root: " + sqrt);             
            out.println("Cube: " + cube);             
            out.println("Cube Root: " + cbrt);             
            socket.close();             
            serverSocket.close();         
      } catch (Exception e) { 
            e.printStackTrace(); 
        } 
    } 
} 

Code for ClientSquare
import java.io.*;
import java.net.*;

public class sauareClient {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("localhost", 5000);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader userInput = new BufferedReader(new InputStreamReader(System.in));

            System.out.print("Enter a number: ");
            String number = userInput.readLine();

            // Send number to server
            out.println(number);  // FIXED ↑

            // Read results from server
            System.out.println("\nResults from Server:");
            System.out.println(in.readLine());
            System.out.println(in.readLine());
            System.out.println(in.readLine());
            System.out.println(in.readLine());

            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
Aim : A RMI based application program to  display current date and time. 
RemoteDate.java
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Date;

public interface RemoteDate extends Remote {
    Date getRemoteDate() throws RemoteException;
    String LOOKUPNAME = "RemoteDateService"; // Name for RMI registry
}

#RemoteDateImpl.java (2nd java file)
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Date;

public class RemoteDateImpl extends UnicastRemoteObject implements RemoteDate {
    protected RemoteDateImpl() throws RemoteException {
        super();
    }

    @Override
    public Date getRemoteDate() throws RemoteException {
        return new Date(); // Returns current date and time on the server
    }

    public static void main(String[] args) {
        try {
            RemoteDateImpl server = new RemoteDateImpl();
            java.rmi.registry.LocateRegistry.createRegistry(1099); // Start RMI registry
            java.rmi.Naming.rebind(RemoteDate.LOOKUPNAME, server);
            System.out.println("Remote Date Server ready.");
        } catch (Exception e) {
            System.err.println("Remote Date Server exception: " + e.toString());
            e.printStackTrace();
        }
    }
}

#RemoteDateClient.java(3rd file)
import java.rmi.Naming;
import java.util.Date;

public class RemoteDateClient {
    public static void main(String[] args) {
        try {
            RemoteDate remoteDateService = (RemoteDate) Naming.lookup("rmi://localhost/" + RemoteDate.LOOKUPNAME);
            Date remoteDateTime = remoteDateService.getRemoteDate();
            System.out.println("Current date and time from remote server: " + remoteDateTime);
        } catch (Exception e) {
            System.err.println("Remote Date Client exception: " + e.toString());
            e.printStackTrace();
        }
    }
}

Aim: - A RMI based application program that converts digits to words, e.g 123 will be converted to one two three
InterConvert.java
import java.rmi.*;
public interface InterConvert extends Remote 
{ public String convertDigit(String no) throws Exception; 
} 

ServerConvert.java
import java.rmi.*;
import java.rmi.server.*;

public class ServerConvert extends UnicastRemoteObject implements InterConvert {

    public ServerConvert() throws Exception {
        super();
    }

    public String convertDigit(String no) throws Exception {
        String str = "";

        for (int i = 0; i < no.length(); i++) {
            int p = no.charAt(i);

            if (p == 48) {
                str += "zero ";
            }
            if (p == 49) {
                str += "one ";
            }
            if (p == 50) {
                str += "two ";
            }
            if (p == 51) {
                str += "three ";
            }
            if (p == 52) {
                str += "four ";
            }
            if (p == 53) {
                str += "five ";
            }
            if (p == 54) {
                str += "six ";
            }
            if (p == 55) {
                str += "seven ";
            }
            if (p == 56) {
                str += "eight ";
            }
            if (p == 57) {
                str += "nine ";
            }
        }
        return str;
    }

    public static void main(String args[]) throws Exception {
        ServerConvert s1 = new ServerConvert();
        Naming.bind("Wrd", s1);
        System.out.println("Object registered....");
    }
}

ClientConvert.java 
import java.rmi.*;
import java.io.*;

public class ClientConvert {

    public static void main(String args[]) throws Exception {

        InterConvert h1 = (InterConvert) Naming.lookup("Wrd");

        BufferedReader br = new BufferedReader(
                new InputStreamReader(System.in));

        System.out.print("Enter a number: ");
        String no = br.readLine();

        String ans = h1.convertDigit(no);

        System.out.println("The word representation of the entered digit is: " + ans);
    }
}

 
 
 

             









































