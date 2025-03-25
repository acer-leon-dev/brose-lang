#include "pch.hpp"
#include "util.hpp"
#include <brose/lexer.hpp>

std::string decontrol(std::string str) {   
    // static boost::regex r_sqte { R"(\')" };
    // static boost::regex r_dqte { R"(\")" };
    // static boost::regex r_ques { R"(\?)" };
    // static boost::regex r_bsla { R"(\\)" };
    // static boost::regex r_bell { R"(\a)" };
    // static boost::regex r_back { R"(\b)" };
    // static boost::regex r_fmfd { R"(\f)" };
    // static boost::regex r_vtab { R"(\v)" };
    static boost::regex r_lnfd { R"(\n)" };
    static boost::regex r_cret { R"(\r)" };
    static boost::regex r_htab { R"(\t)" };
    
    // str = boost::regex_replace(str, r_sqte, R"(\\')");
    // str = boost::regex_replace(str, r_dqte, R"(\\")");
    // str = boost::regex_replace(str, r_ques, R"(\\?)");
    // str = boost::regex_replace(str, r_bsla, R"(\\\)");
    // str = boost::regex_replace(str, r_bell, R"(\\a)");
    // str = boost::regex_replace(str, r_back, R"(\\t)");
    // str = boost::regex_replace(str, r_fmfd, R"(\\b)");
    // str = boost::regex_replace(str, r_vtab, R"(\\v)");
    str = boost::regex_replace(str, r_lnfd, R"(\\n)");
    str = boost::regex_replace(str, r_cret, R"(\\r)");
    str = boost::regex_replace(str, r_htab, R"(\\t)");

    return str;
}
    
std::string token_to_string(const brose::Token& token) {
    return "{" + token.value + ", " + brose::token_type_to_string(token.type) + "}";
}

std::string tokenlist_to_string(const TokenList& vector) {
    if (vector.empty()) {
        return "";
    }
    
    std::string str;
    for (int i = 0; i < vector.size() - 1; i++) {
        str += vector.at(i).value + " ";
    }

    return decontrol(str + vector.back().value);
}

void assertTokenListsAreEqual(const TokenList& actual_output, const TokenList& expected_output) {
    total_tests++;
    
    std::cout << "!------------------------------------------------!\n";
    if (actual_output == expected_output) {
        successful_tests++;
        std::cout << "Test " << total_tests << ": SUCCESS!\n";
        std::cout << "Output:\n\t" << tokenlist_to_string(actual_output) << "\n";
    }
    else {
        std::cerr << "Test " << total_tests << ": FAIL!\n";
        std::cerr << "Expected output:\n\t" << tokenlist_to_string(expected_output) << "\n";
        std::cerr << "Incorrect output:\n\t" << tokenlist_to_string(actual_output) << "\n";
    }

    std::cout << "!------------------------------------------------!\n\n";
}
