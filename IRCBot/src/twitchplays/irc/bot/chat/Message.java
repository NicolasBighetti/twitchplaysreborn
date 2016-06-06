package twitchplays.irc.bot.chat;

/**
 * Chat message.
 *
 * @author Kevin Buisson
 */
public class Message {

    /** Message text */
    private String message;

    /** Message time */
    private long time;

    /**
     * Creates a new message.
     *
     * @param message
     *            message text
     * @param time
     *            message time
     */
    public Message(String message, long time)
    {
        this.message = message;
        this.time = time;
    }

    /**
     * Gets message.
     *
     * @return the message
     */
    public String getMessage()
    {
        return message;
    }

    /**
     * Gets time.
     *
     * @return the time
     */
    public long getTime()
    {
        return time;
    }

    @Override
    public String toString()
    {
        return message;
    }
}
