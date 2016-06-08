package twitchplays.irc.bot.socket;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;

import twitchplays.irc.bot.conf.Config;

/**
 * Chat server daemon.
 *
 * @author Kevin Buisson
 */
public class ChatServerDaemon {

    /**
     * Task scheduler for servers.
     */
    private ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);

    /**
     * Serve.
     */
    public void serve(boolean multiClients) throws IOException
    {
        // Create socket
        ServerSocket serverSocket = new ServerSocket(Config.SERVER_PORT);
        System.out.println("Server started on port " + Config.SERVER_PORT);

        // Never stop handle clients
        do
        {
            // Accept client
            Socket clientSocket = serverSocket.accept();
            System.out.println("Accepted connection from client");

            // Create chat server and start
            ChatServer server = new ChatServer(clientSocket, scheduler);

            // Multi clients = multi threads
            if (multiClients)
                server.start();
            // Single thread
            else
                server.run();

            // Loop on clients
        } while (multiClients);
    }
}
