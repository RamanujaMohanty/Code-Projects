/*
 * Objective:
 *     1. Parse a line like: arrow|noun -=>> Here is one arrow: <IMG> -=>> </IMG>..
 *     2. The queries look like this:
 *        a. !help<enter> or just <enter>
 *        b. word [part_of_speech] [distinct] [reverse]
 *
 *
 * In memory DB:
 *      map of: keyword:string -> vector of dict_entry
 *          dict_entry is a pair: { part_of_speech:enum, definition: string}
 */

#include <iostream>
#include <pthread.h>
#include <random>
#include <string>
#include <utility>              // for pair<>
#include <unordered_map>
#include <vector>

enum PartsOfSpeech
{
    NOUN_PART_OF_SPEECH         = 0,
    VERB_PART_OF_SPEECH         = 1,
    ADJECTIVE_PART_OF_SPEECH    = 2,
    ADVERB_PART_OF_SPEECH       = 3
};

using std::cout;
using std::string;
using std::pair, std::unordered_map, std::vector;

using DictEntry = pair<PartsOfSpeech, string>;
using DictEntries = vector<DictEntry>;
using Dictionary = unordered_map<string, DictEntries>;
// example:
// dictionary["arrow"].push_back({NOUN_PART_OF_SPEECH, "Here is one arrow: <IMG> -=>> </IMG>.."});

// TODO: implement this
bool readDictionary(const string &dictionaryFile, Dictionary &dictionary)
{
    return false;
}

// TODO: implement this
string showMenu(void)
{
    return "command";
}

bool actOnCommand(const string &command, const Dictionary &dictionary)
{
    return false;
}

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        cout << "Usage: " << argv[0] << "Dictionary file\n";
    }

    Dictionary dictionary;
    // TODO: handle errors
    readDictionary(argv[1], dictionary);

    while (true) {
        string command = showMenu();

        // TODO: implement actOnCommand(). It takes a string and returns a bool
        bool rc = actOnCommand(command, dictionary);

        if (rc) continue;
        // TODO: handle errors in parsing
    }

    return 0;
}
