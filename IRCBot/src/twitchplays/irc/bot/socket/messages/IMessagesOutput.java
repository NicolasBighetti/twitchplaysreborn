package twitchplays.irc.bot.socket.messages;

import twitchplays.irc.bot.chat.Message;

/**
 * Created by Kevin on 06/06/2016.
 */
public interface IMessagesOutput {

	/**
	 * Send message.
	 *
	 * @param message
	 * 		the message
	 */
	void sendMessage(Message message);
}
