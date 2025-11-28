#include <string>

std::string runCaesarCipher(const std::string& inputText, const size_t key,
                            const bool encrypt)
{
    // Create the alphabet container and output string
    // Loop over the input text
    // For each character find the corresponding position in the alphabet
    // Apply the shift (+ve or –ve depending on encrypt/decrypt)
    // to the position, handling correctly potential wrap-around
    // Determine the new character and add it to the output string
    // Finally (after the loop), return the output string
    std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    size_t alphabet_size = alphabet.size();

    std::string outputText;
    for (const auto& c : inputText) {
        // determine shift
        int shift = static_cast<int>(key);
        if (not encrypt) {
            // Decrypting, use negative shift
            shift = -shift;
        }
        // compute shifted character with wrap-around using modulo
        size_t initial_position = alphabet.find(c);
        size_t shifted_position = (initial_position + alphabet_size + shift) % alphabet_size;
        char newChar = alphabet[shifted_position];

        outputText += newChar;
    }
    return outputText;
}