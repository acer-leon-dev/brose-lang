#ifndef CAE0E821_D3FB_4E99_97CC_340B972AB4C2
#define CAE0E821_D3FB_4E99_97CC_340B972AB4C2

namespace mathl
{

class Script
{
private:
    // Some data structure (probably a sequence or tree) that holds the instructions
    // AbstractDataStructure instructions;
public:
    double invoke(double x);
};

Script compile(std::string_view source);

}

#endif /* CAE0E821_D3FB_4E99_97CC_340B972AB4C2 */
