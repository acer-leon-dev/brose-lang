#include "Brose/Lexer.hpp"

namespace 
{

std::string controlToString(char c)
{
    switch (c) {
        case '\'': return "\\'";
        case '\"': return "\\\"";
        case '\?': return "\\?";
        case '\\': return "\\\\";
        case '\a': return "\\a";
        case '\b': return "\\b";
        case '\f': return "\\f";
        case '\n': return "\\n";
        case '\r': return "\\r";
        case '\t': return "\\t";
        case '\v': return "\\v";
    }

    return std::string(1, c);
}

std::string controlToString(std::string str)
{
    for (int i = 0; i < str.size(); i++) {
        str.replace(i, 1, controlToString(str[i]));
    }

    return str;
}

std::string readFile(std::filesystem::path path, bool* result = nullptr)
{
    std::ifstream in { path };

    if (!in.is_open()) {
        if (result) {
            *result = false;
        }
        return "";
    }

    std::stringstream buffer;
    buffer << in.rdbuf();
    if (result) {
        *result = true;
    }
    return buffer.str();
}

int run(const std::vector<std::string>& args) {
    // Validate path
    if (!std::filesystem::exists(args[1]))
    {
        std::cerr << std::quoted(args[1]) << " is not a real path.\n";
        return EXIT_FAILURE;
    }
    
    // Load source file
    bool read_success;
    std::string source = readFile(args[1], &read_success);
    if (!read_success) {
        std::cerr << "Failed to open file " << std::quoted(args[1]) << ".\n";
        return EXIT_FAILURE;
    }

    // Tokenize source file
    std::vector<Token> tokens = Lexer::tokenize(source);

    // Print token values and types
    std::cout << "Tokens:\n";
    for (auto tok : tokens) {
        std::cout << "  "<< controlToString(tok.value) << "\t " << Token::typeToString(tok.type) << "\n";
    }

    return EXIT_SUCCESS;
}

int read(std::string& dest) {
    std::cout << ">>> ";
    std::getline(std::cin, dest);
    return 0;
}

int eval(const std::string& src, std::vector<Token>& dest) {
    std::vector<Token> tokens;

    try {
        tokens = Lexer::tokenize(src);
    }
    catch (std::logic_error e) {
        return 1;
    }

    for (const Token& t : tokens)
    {
        if (t.type == TokenType::NOT_A_TOKEN) {
            return 1;
        }
    }
    
    dest = tokens;
    return 0;
}

int print(const std::vector<Token>& tokens) {
    for (auto tok : tokens) {
        std::cout << controlToString(tok.value) << "\t " << Token::typeToString(tok.type) << "\n";
    }

    return 0;
}

int runREPL() {
    while (true) {
        std::string line;
        std::vector<Token> tokens;

        if (read(line)) {
            std::cerr << "Fatal Error: Could not read input\n";
            return EXIT_FAILURE;
        }

        if (eval(line, tokens)) {
            std::cerr << "Error: Invalid Input\n";
            continue;
        }
        
        if (print(tokens)) {
            std::cerr << "Fatal Error: Could not print results\n";
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

};

int main(int argc, char** argv)
{
    std::vector<std::string> args;
    args.reserve(argc); 
    for (int i = 0; i < argc; i++) {
        args.emplace_back(argv[i]);
    }   

    if (argc > 2 || *std::find(args.begin(), args.end(), "--help") == "--help") {
        std::cerr << "Usage: " << std::filesystem::path(args[0]).stem().string() << " [--help] [<source_file>]\n";
        return EXIT_SUCCESS;
    }

    if (argc == 2) {
        run(args);
    }

    if (argc == 1) {
        runREPL();
    }

    return EXIT_SUCCESS;
}