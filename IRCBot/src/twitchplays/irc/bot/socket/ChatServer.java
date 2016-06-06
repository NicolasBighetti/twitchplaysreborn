package twitchplays.irc.bot.socket;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

import twitchplays.irc.bot.chat.Chat;
import twitchplays.irc.bot.chat.Message;
import twitchplays.irc.bot.chat.parsing.ChatParser;
import twitchplays.irc.bot.conf.Config;
import twitchplays.irc.bot.socket.messages.IMessagesOutput;
import twitchplays.irc.bot.socket.messages.IMessagesSenderListener;
import twitchplays.irc.bot.socket.messages.MessagesSender;

/**
 * Chat server.
 *
 * @author Kevin Buisson
 */
public class ChatServer extends Thread implements IMessagesSenderListener, IMessagesOutput {

    /** Client socket */
    private Socket clientSocket;

    /** Socket input. */
    private BufferedReader input;

    /** Socket output. */
    private PrintWriter output;

    /**
     * Tasks scheduler.
     */
    private ScheduledExecutorService scheduler;

    /**
     * Server chat task.
     */
    private ScheduledFuture task;

    /**
     * Instantiates a new Chat server.
     *
     * @param clientSocket
     *            the client socket
     */
    public ChatServer(Socket clientSocket, ScheduledExecutorService scheduler) throws IOException
    {
        this.clientSocket = clientSocket;
        this.scheduler = scheduler;

        // Create streams
        this.input = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        this.output = new PrintWriter(clientSocket.getOutputStream(), true);
    }

    @Override
    public void run()
    {
        // Parse the chat
        Chat chat = ChatParser.parse(Config.CHAT_FILE);
        if (chat == null)
            return;
        System.out.println("Chat file to send successfully parsed.");

        // Wait for the "PASS" authentication message
        String line;
        while (Config.WAIT_FOR_PASS)
        {
            try
            {
                // Read the line
                line = input.readLine();
                if (line == null)
                    break;

                // Pass received, send messages
                if (line.startsWith("PASS"))
                {
                    System.out.println("PASS received, start sending messages...");
                    break;
                }
            }
            catch (IOException e)
            {
                e.printStackTrace();
            }
        }

        // Start messages sender
        MessagesSender sender = new MessagesSender(chat, this, this);
        this.task = scheduler.scheduleWithFixedDelay(sender, 0, Config.MESSAGES_DELAY,
                TimeUnit.MILLISECONDS);

        // Wait for the task to end
        try
        {
            // Use wait to synchronize
            synchronized (this)
            {
                this.wait();
            }
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
        }
    }

    @Override
    public void sendMessage(Message message)
    {
        System.out.println("Sending message : " + message);

        // Send message
        output.println("PRIVMSG " + message + "\r\n");
    }

    @Override
    public void sendingDone()
    {
        // Stop task and notify
        this.task.cancel(true);

        // Use notify to synchronize
        synchronized (this)
        {
            this.notify();
        }

        System.out.println("Closing connection with client");

        // Close sockets input/output
        try
        {
            output.close();
            input.close();
            clientSocket.close();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}
