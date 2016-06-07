package twitchplays.irc.bot.chat;

import java.util.LinkedList;
import java.util.List;
import java.util.stream.Collectors;

/**
 * Chat.
 *
 * @author Kevin Buisson
 */
public class Chat {

    /** Chat messages. */
    private LinkedList<Message> messages = new LinkedList<>();

    /** Current chat time. */
    private long nextMessageTime;

    /**
     * Adds a message.
     *
     * @param nickname
     *            the nickname
     * @param message
     *            message to add
     * @param delay
     *            delay between messages
     */
    public void addMessage(String nickname, String message, long delay)
    {
        // Add message to list
        this.messages.add(new Message(nickname, message, this.nextMessageTime));

        // Increase messages delay
        this.nextMessageTime += delay;
    }

    /**
     * Adds a message N times.
     *
     * @param nickname
     *            the nickname
     * @param message
     *            message to add
     * @param delay
     *            delay between messages
     * @param count
     *            number of messages to add
     */
    public void addMessages(String nickname, String message, long delay, int count)
    {
        // Add the message N times
        while (count-- > 0)
            this.addMessage(nickname, message, delay);
    }

    /**
     * Gets all messages between the specified time.
     *
     * @param beginTime
     *            begin time
     * @param endTime
     *            end time
     * @return messages between the times
     */
    public List<Message> getMessagesBetween(long beginTime, long endTime)
    {
        // Get messages between the specified time
        return this.messages.stream()
                .filter(
                        // Times filtering
                        (m) -> m.getTime() >= beginTime && m.getTime() < endTime)
                .collect(Collectors.toList());
    }

    /**
     * Checks if there is more messages after specified time.
     *
     * @param time
     *            time to check
     * @return true if there is more messages, false otherwise
     */
    public boolean hasMessagesAfter(long time)
    {
        return !messages.isEmpty() && messages.getLast().getTime() >= time;
    }

    /**
     * Gets messages.
     *
     * @return messages messages
     */
    public List<Message> getMessages()
    {
        return messages;
    }
}
