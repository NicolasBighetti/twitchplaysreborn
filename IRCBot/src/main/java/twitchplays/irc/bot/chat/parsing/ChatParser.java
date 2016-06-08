package twitchplays.irc.bot.chat.parsing;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.stream.Stream;

import twitchplays.irc.bot.chat.Chat;

/**
 * Chat parser.
 *
 * @author Kevin Buisson
 */
public class ChatParser {

    /**
     * Parses the chat from specified file.
     *
     * @param file
     *            file to parse
     * @return parsed chat
     */
    public static Chat parse(String file)
    {
        return parse(Paths.get(file));
    }

    /**
     * Parses the chat from specified file.
     *
     * @param file
     *            file to parse
     * @return parsed chat (null if error occurs)
     */
    public static Chat parse(Path file)
    {
        Chat chat = new Chat();

        // Parse every line
        try (Stream<String> stream = Files.lines(file))
        {
            // Parse messages from this line
            stream.forEach((m) -> parseMessages(m, chat));
        }
        catch (IOException e)
        {
            e.printStackTrace();
            return null;
        }

        return chat;
    }

    /**
     * Parses messages from specified line.
     *
     * @param line
     *            line to parse
     * @param chat
     *            chat to add parsed messages
     * @return true if success, false otherwise (parsing error)
     */
    private static boolean parseMessages(String line, Chat chat)
    {
        // Ignore comments
        line = line.replaceAll("\\s*#.*", "");

        // Ignore empty lines
        if (line.matches("^\\s*$"))
            return true;

        try
        {
            // Split message
            String[] values = line.split("\\s+");

            // Add messages to chat
            chat.addMessages( // Parse message
                    (values[0].substring(0, values[0].indexOf(':'))), // Nickname
                    (values[0].substring(values[0].indexOf(':') + 1, values[0].length())), // Message
                    (values.length > 1 ? Long.parseLong(values[1]) : 0), // Delay
                    (values.length > 2 ? Integer.parseInt(values[2]) : 1) // Count
            );
        }
        catch (Exception e)
        {
            // Parsing error
            System.err.println("ChatParser: Chat parsing error for line: " + line);
            return false;
        }

        return true;
    }
}
