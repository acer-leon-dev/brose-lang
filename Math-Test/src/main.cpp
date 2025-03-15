#include "mathcompiler/Mathcompiler.hpp"

namespace 
{

std::string script_1 = "// EXAMPLE1.math\na = 2^3 - floor(3.50)\nb = 0.333 * a(5 - 1.2)\nc = 4 / 3 + .5x\nd = c mod 4 - 2\ny = d ^ ( 1/3 ) * b";
std::string script_2 = "// EXAMPLE2.math\nf = log10.254(x^2)\np = (3.14159)^2\nm = fp\nc = 54.23/11.96\ny = m + -x / 10 * c";
std::string script_3 = "// EXAMPLE3.math\nA = ceil(.5*x) * 0.2\na = x * (1 / 3)\nB = sin(A * 66.666)\nb = aB\ny = b";

std::string readFile(std::filesystem::path path)
{
    std::ifstream in { path };
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

std::string tokenTypeToString(TokenType t)
{
    using enum TokenType;
    
    switch (t) {
        case NOT_A_TOKEN: return "NOT_A_TOKEN";
        case NEWLINE: return "NEWLINE";
        case VARIABLE: return "VARIABLE";
        case NUMBER: return "NUMBER";
        case OPEN_PAREN: return "OPEN_PAREN";
        case CLOSE_PAREN: return "CLOSE_PAREN";
        case OPEN_ABS: return "OPEN_ABS";
        case CLOSE_ABS: return "CLOSE_ABS";
        case EQUAL: return "EQUAL";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case MULTIPLY: return "MULTIPLY";
        case DIVIDE: return "DIVIDE";
        case EXPONENT: return "EXPONENT";
        case MOD: return "MOD";
        case GENERIC_FUNC: return "GENERIC_FUNC";
        case LOG: return "LOG";
    }   

    return "";
}

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

bool isNum(const std::string& str)
{
    if (str.length() == 0) {
        return false;
    }

    for (char c : str)
    {
        if (!std::isdigit(c) && c != '.') {
            return false;
        }
    }

    return true;
}

};

int main(int argc, char** argv)
{
    // std::string src0 = readFile(argv[1]);
    
    std::vector<Token> tokens;
    while (true) {
        std::string* p_src;

        std::cout << "\nType 1, 2, or 3 to test tokens for a script\n";
        std::cout << "> ";
        std::string s_n;
        std::getline(std::cin, s_n);
        int i_n = (isNum(s_n)) ? std::stoi(s_n) : -1;
        switch (i_n)
        {
            default: std::cout << "Invalid Input"; continue;
            case 1: p_src = &script_1; break;
            case 2: p_src = &script_2; break;
            case 3: p_src = &script_3; break;
        }
        
        std::cout << "```\n" << *p_src << "\n```\n\n";
        tokens = tokenizeSource(*p_src);
        for (auto tok : tokens) {
            std::cout << controlToString(tok.value) << "\t " << tokenTypeToString(tok.type) << "\n";
        }
    }
    
}
