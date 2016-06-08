package twitchplays.irc.bot;

import java.io.IOException;

import twitchplays.irc.bot.conf.Config;
import twitchplays.irc.bot.socket.ChatServerDaemon;

/**
 * TwitchPlays IRC Bot's main.
 *
 * @author Kevin Buisson
 */
public class Main {

    /**
     * The entry point of application.
     *
     * @param args
     *            no args
     * @throws IOException
     *             if I/O exceptions occurs
     */
    public static void main(String[] args) throws IOException
    {
        // Initialize configuration
        Config.init();

        System.out.println("Starting server ...");

        // Start server
        new ChatServerDaemon().serve(true);
    }
}
