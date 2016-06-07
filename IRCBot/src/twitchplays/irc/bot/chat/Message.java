package twitchplays.irc.bot.chat;

/**
 * Chat message.
 *
 * @author Kevin Buisson
 */
public class Message {

    /** Message nickname */
    private String nickname;

    /** Message text */
    private String message;

    /** Message time */
    private long time;

    /**
     * Creates a new message.
     *
     * @param nickname
     *            message nickname
     * @param message
     *            message text
     * @param time
     *            message time
     */
    public Message(String nickname, String message, long time)
    {
        this.nickname = nickname;
        this.message = message;
        this.time = time;
    }

    /**
     * Gets nickname.
     *
     * @return the nickname
     */
    public String getNickname()
    {
        return nickname;
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
        return nickname + ":" + message;
    }
}
