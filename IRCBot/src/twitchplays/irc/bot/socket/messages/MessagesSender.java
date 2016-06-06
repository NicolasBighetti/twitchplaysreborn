package twitchplays.irc.bot.socket.messages;

import twitchplays.irc.bot.chat.Chat;
import twitchplays.irc.bot.conf.Config;

/**
 * Message sender.
 *
 * @author Kevin Buisson
 */
public class MessagesSender implements Runnable {

    /**
     * Chat.
     */
    private Chat chat;

    /**
     * Current time.
     */
    private long currentTime;

    /**
     * Listener.
     */
    private IMessagesSenderListener listener;

    /**
     * Output.
     */
    private IMessagesOutput output;

    /**
     * Instantiates a new Messages sender.
     *
     * @param chat
     * 		the chat
     * @param listener
     * 		the listener
     * @param output
     * 		the output
     */
    public MessagesSender(Chat chat, IMessagesSenderListener listener, IMessagesOutput output)
    {
        this.chat = chat;
        this.listener = listener;
        this.output = output;
    }

    @Override
    public void run()
    {
        // Send all messages for the delay
        chat.getMessagesBetween(this.currentTime, this.currentTime += Config.MESSAGES_DELAY)
                .forEach(output::sendMessage);

        // Check if there is more messages
        if (!chat.hasMessagesAfter(this.currentTime))
            // Notify sending is done
            listener.sendingDone();
    }
}
