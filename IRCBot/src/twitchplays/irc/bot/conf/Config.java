package twitchplays.irc.bot.conf;

/**
 * Configuration.
 *
 * @author Kevin Buisson
 */
public class Config {

    /**
     * Server port.
     */
    public static int SERVER_PORT = 6667;

    /**
     * Wait for pass on connection.
     */
    public static boolean WAIT_FOR_PASS = true;

    /**
     * Messages delay in milliseconds.
     */
    public static long MESSAGES_DELAY = 100;

    /**
     * Chat file to parse.
     */
    public static String CHAT_FILE = "./res/chat/bilboquet.chat";

    /**
     * Initialize configuration (from system properties).
     */
    public static void init()
    {
        // Server port
        Config.SERVER_PORT = Integer
                .parseInt(System.getProperty("serverPort", String.valueOf(SERVER_PORT)));

        // Wait for pass
        Config.WAIT_FOR_PASS = Boolean
                .parseBoolean(System.getProperty("waitForPass", String.valueOf(WAIT_FOR_PASS)));

        // Messages delay
        Config.MESSAGES_DELAY = Long
                .parseLong(System.getProperty("messagesDelay", String.valueOf(MESSAGES_DELAY)));

        // Chat file
        Config.CHAT_FILE = System.getProperty("chatFile", CHAT_FILE);
    }
}
