#include <string>
#include <vector>

namespace brose {
    struct Token;
};

using TokenList = std::vector<brose::Token>;

std::string decontrol(std::string str);
std::string token_to_string(const brose::Token& token);
std::string tokenlist_to_string(const TokenList& vector);
inline std::size_t successful_tests = 0;
inline std::size_t total_tests = 0;
void assertTokenListsAreEqual(const TokenList& actual_output, 
    const TokenList& expected_output);