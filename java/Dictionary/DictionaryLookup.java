import java.util.*;

public class DictionaryLookup {
    public enum DictEntry {
        ARROW("arrow", "noun", "Here is one arrow: <IMG> -=>> </IMG>"),
        BOOK_NOUN_1("book", "noun", "A set of pages."),
        BOOK_NOUN_2("book", "noun", "A written work published in printed or electronic form."),
        BOOK_VERB_1("book", "verb", "To arrange for someone to have a seat on a plane."),
        BOOK_VERB_2("book", "verb", "To arrange something on a particular date."),
        DISTINCT_ADJ_1("distinct", "adjective", "Familiar. Worked in Java."),
        DISTINCT_ADJ_2("distinct", "adjective", "Unique. No duplicates. Clearly different or of a different kind."),
        DISTINCT_ADV("distinct", "adverb", "Uniquely. Written \"distinctly\"."),
        DISTINCT_NOUN_1("distinct", "noun", "A keyword in this assignment."),
        DISTINCT_NOUN_2("distinct", "noun", "A keyword in this assignment."),
        DISTINCT_NOUN_3("distinct", "noun", "A keyword in this assignment."),
        DISTINCT_NOUN_4("distinct", "noun", "An advanced search option."),
        DISTINCT_NOUN_5("distinct", "noun", "Distinct is a parameter in this assignment."),
        PLACEHOLDER_ADJ_1("placeholder", "adjective", "To be updated..."),
        PLACEHOLDER_ADJ_2("placeholder", "adjective", "To be updated..."),
        PLACEHOLDER_ADV("placeholder", "adverb", "To be updated..."),
        PLACEHOLDER_CONJ("placeholder", "conjunction", "To be updated..."),
        PLACEHOLDER_INTJ("placeholder", "interjection", "To be updated..."),
        PLACEHOLDER_NOUN_1("placeholder", "noun", "To be updated..."),
        PLACEHOLDER_NOUN_2("placeholder", "noun", "To be updated..."),
        PLACEHOLDER_NOUN_3("placeholder", "noun", "To be updated..."),
        PLACEHOLDER_PREP("placeholder", "preposition", "To be updated..."),
        PLACEHOLDER_PRON("placeholder", "pronoun", "To be updated..."),
        PLACEHOLDER_VERB("placeholder", "verb", "To be updated..."),
        REVERSE_ADJ_1("reverse", "adjective", "On back side."),
        REVERSE_ADJ_2("reverse", "adjective", "Opposite to usual or previous arrangement."),
        REVERSE_NOUN_1("reverse", "noun", "A dictionary program's parameter."),
        REVERSE_NOUN_2("reverse", "noun", "Change to opposite direction."),
        REVERSE_NOUN_3("reverse", "noun", "The opposite."),
        REVERSE_NOUN_4("reverse", "noun", "To be updated..."),
        REVERSE_NOUN_5("reverse", "noun", "To be updated..."),
        REVERSE_NOUN_6("reverse", "noun", "To be updated..."),
        REVERSE_NOUN_7("reverse", "noun", "To be updated..."),
        REVERSE_VERB_1("reverse", "verb", "Change something to opposite."),
        REVERSE_VERB_2("reverse", "verb", "Go back"),
        REVERSE_VERB_3("reverse", "verb", "Revoke ruling."),
        REVERSE_VERB_4("reverse", "verb", "To be updated..."),
        REVERSE_VERB_5("reverse", "verb", "To be updated..."),
        REVERSE_VERB_6("reverse", "verb", "Turn something inside out.");

        private final String keyword;
        private final String partOfSpeech;
        private final String definition;

        // Constructs a dictionary entry.
        DictEntry(String keyword, String partOfSpeech, String definition) {
            this.keyword = keyword;
            this.partOfSpeech = partOfSpeech;
            this.definition = definition;
        }

        // Retrieves the keyword for the entry.
        public String getKeyword() {
            return keyword;
        }
        // Retrieves the part of speech for the entry.
        public String getPartOfSpeech() {
            return partOfSpeech;
        }
        // Retrieves the definition of the entry.
        public String getDefinition() {
            return definition;
        }
    }

    // Loads the dictionary from the enum into a Map.
    private static Map<String, List<DictEntry>> loadDict() {
        Map<String, List<DictEntry>> newDict = new HashMap<>();
        for (DictEntry entry : DictEntry.values()) {
            newDict.putIfAbsent(entry.getKeyword().toLowerCase(), new ArrayList<>());
            newDict.get(entry.getKeyword().toLowerCase()).add(entry);
        }
        return newDict;
    }

    // --- Constants for Messages and Parts of Speech ---
    private static final String PARAMETER_HOW_TO_MESSAGE =
            "\t|\n" +
                    "\t PARAMETER HOW-TO, please enter:\n" +
                    "\t 1. A search key -then 2. An optional part of speech -then\n" +
                    "\t 3. An optional 'distinct' -then 4. An optional 'reverse'\n" +
                    "\t|";

    private static final String PARAMETER_NOT_FOUND_MESSAGE =
            "\t|\n" +
                    "\t <NOT FOUND> To be considered for the next release. Thank you.\n" +
                    "\t|";

    // Parses user input and searches the dictionary.
    private static void processQuery(String input, Map<String, List<DictEntry>> queryDict) {
        if (input.equalsIgnoreCase("!help") || input.trim().isEmpty()) {
            System.out.println(PARAMETER_HOW_TO_MESSAGE);
            return;
        }

        String[] tokens = input.trim().split("\\s+");
        if (tokens.length == 0) return;
        if (tokens.length > 4) {
            System.out.println(PARAMETER_HOW_TO_MESSAGE);
            return;
        }

        String keyword = tokens[0].toLowerCase();
        String partOfSpeech = null;
        boolean distinct = false;
        boolean reverse = false;

        List<String> errors = new ArrayList<>();
        if (tokens.length >= 2) {
            String second = tokens[1].toLowerCase();
            if (isPartOfSpeech(second)) {
                partOfSpeech = second;
            } else if (second.equals("distinct")) {
                distinct = true;
            } else if (second.equals("reverse")) {
                reverse = true;
            } else {
                errors.add("\t|");
                errors.add("\t <The entered 2nd parameter '" + tokens[1] + "' is NOT a part of speech.>");
                errors.add("\t <The entered 2nd parameter '" + tokens[1] + "' is NOT 'distinct'.>");
                errors.add("\t <The entered 2nd parameter '" + tokens[1] + "' is NOT 'reverse'.>");
                errors.add("\t <The entered 2nd parameter '" + tokens[1] + "' was disregarded.>");
                errors.add("\t <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>");
                errors.add("\t|");
            }
        }
        if (tokens.length >= 3) {
            String third = tokens[2].toLowerCase();
            if (third.equals("distinct")) {
                distinct = true;
            } else if (third.equals("reverse")) {
                reverse = true;
            } else {
                errors.add("\t|");
                errors.add("\t <The entered 3rd parameter '" + tokens[2] + "' is NOT 'distinct'.>");
                errors.add("\t <The entered 3rd parameter '" + tokens[2] + "' is NOT 'reverse'.>");
                errors.add("\t <The entered 3rd parameter '" + tokens[2] + "' was disregarded.>");
                errors.add("\t <The 3rd parameter should be 'distinct' or 'reverse'.>");
                errors.add("\t|");
            }
        }
        if (tokens.length >= 4) {
            String fourth = tokens[3].toLowerCase();
            if (fourth.equals("reverse")) {
                reverse = true;
            } else {
                errors.add("\t|");
                errors.add("\t <The entered 4th parameter '" + tokens[3] + "' is NOT 'reverse'.>");
                errors.add("\t <The entered 4th parameter '" + tokens[3] + "' was disregarded.>");
                errors.add("\t <The 4th parameter should be 'reverse'.>");
                errors.add("\t|");
            }
        }

        List<DictEntry> entries = queryDict.get(keyword);
        if (entries == null) {
            System.out.println(PARAMETER_NOT_FOUND_MESSAGE);
            System.out.println(PARAMETER_HOW_TO_MESSAGE);
            return;
        }

        List<String> results = new ArrayList<>();
        for (DictEntry entry : entries) {
            if (partOfSpeech == null || entry.getPartOfSpeech().equalsIgnoreCase(partOfSpeech)) {
                String result = capitalize(entry.getKeyword()) + " [" +
                        entry.getPartOfSpeech() + "] : " + entry.getDefinition();
                if (!distinct || !results.contains(result)) {
                    results.add(result);
                }
            }
        }
        if (reverse) {
            Collections.reverse(results);
        }
        for (String error : errors) {
            System.out.println(error);
        }
        if (results.isEmpty()) {
            System.out.println("\t|");
            System.out.println("\t <NOT FOUND> To be considered for the next release. Thank you.");
            System.out.println("\t|");
            System.out.println("\t|");
            System.out.println("\t PARAMETER HOW-TO, please enter:");
            System.out.println("\t 1. A search key -then 2. An optional part of speech -then");
            System.out.println("\t 3. An optional 'distinct' -then 4. An optional 'reverse'");
            System.out.println("\t|");
        }
        else {
            System.out.println("\t|");
            for (String res : results) {
                System.out.println("\t " + res);
            }
            System.out.println("\t|");
        }
    }

    // Checks if a word is a valid part of speech.
    private static boolean isPartOfSpeech(String word) {
        return Arrays.asList("noun", "verb", "adjective", "adverb", "conjunction",
                "interjection", "preposition", "pronoun").contains(word.toLowerCase());
    }

    // Capitalizes the first letter of a string.
    private static String capitalize(String word) {
        if (word == null || word.isEmpty()) return word;
        return word.substring(0,1).toUpperCase() + word.substring(1);
    }

    // Prints the number of keywords and definitions in the dictionary.
    private static void printDictStats(Map<String, List<DictEntry>> dictionary) {
        int keywordCount = dictionary.size();
        int defCount = 0;
        for (List<DictEntry> def : dictionary.values()) {
            defCount += def.size();
        }
        System.out.println("----- Keywords: " + keywordCount);
        System.out.println("----- Definitions: " + defCount + "\n");
    }

    // Main method to run the dictionary application.
    public static void main(String[] args) {
        System.out.println("! Loading data...");
        Map<String, List<DictEntry>> dict = loadDict();
        System.out.println("! Loading completed...\n");
        System.out.println("===== DICTIONARY 340 JAVA =====");
        printDictStats(dict);
        int count = 1;
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.print("Search [" + count + "]:\n");
            String wordInput = scanner.nextLine().trim();
            if (wordInput.equalsIgnoreCase("!q")) {
                System.out.println("\n-----THANK YOU-----");
                break;
            }
            processQuery(wordInput, dict);
            ++count;
        }
        scanner.close();
    }
}
