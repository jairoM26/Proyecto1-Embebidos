package com.example.david.smarth;

/**
 * Created by david on 04/04/18.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;


public class Client {
    private String hostname;
    private int port;
    Socket socketClient;

    public Client(String hostname, int port) {
        this.hostname = hostname;
        this.port = port;
    }

    public void connect() throws UnknownHostException, IOException {
        System.out.println("Attempting to connect to " + hostname + ":" + port);
        socketClient = new Socket(hostname, port);
        System.out.println("\nConnection Established.");
    }

    public String readResponse() throws IOException {
        String userInput;
        System.out.print("Response from server: ");
        BufferedReader reader = new BufferedReader(new InputStreamReader(socketClient.getInputStream()), 1024);
        return reader.readLine();


    }




    public void sendDataForImage() throws IOException {
        PrintWriter writer = new PrintWriter(socketClient.getOutputStream(), true);
        writer.println("0");
    }
    public void sendDataForSignals() throws IOException {
        PrintWriter writer = new PrintWriter(socketClient.getOutputStream(), true);
        writer.println("6");
    }
    public void sendDataForLights(String light) throws IOException {
        PrintWriter writer = new PrintWriter(socketClient.getOutputStream(), true);
        writer.println(light);
    }
    public  void sendDataForLogin() throws IOException {
        PrintWriter writer = new PrintWriter(socketClient.getOutputStream(), true);
        writer.println("7");
    }
}
