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
    public static String CHAT_FILE = "./res/chat/ballslow.chat";

    /**
     * Chat private message format.
     */
    public static String PRIVMSG_FORMAT = ":$NICK$!$NICK$@$NICK$.tmi.twitch.tv PRIVMSG $CHANNEL$ :$MESSAGE$";

    /**
     * Chat channel.
     */
    public static String CHANNEL = "#drymfr";

    /**
     * Initialize configuration (from system properties).
     */
    public static void init()
    {
        // Read configuration from system properties (-Dconfig=X)
        Config.SERVER_PORT = Integer
                .parseInt(System.getProperty("serverPort", String.valueOf(SERVER_PORT)));
        Config.WAIT_FOR_PASS = Boolean
                .parseBoolean(System.getProperty("waitForPass", String.valueOf(WAIT_FOR_PASS)));
        Config.MESSAGES_DELAY = Long
                .parseLong(System.getProperty("messagesDelay", String.valueOf(MESSAGES_DELAY)));
        Config.CHAT_FILE = System.getProperty("chatFile", CHAT_FILE);
        Config.PRIVMSG_FORMAT = System.getProperty("privmsgFormat", PRIVMSG_FORMAT);
        Config.CHANNEL = System.getProperty("channel", CHANNEL);
    }
}
