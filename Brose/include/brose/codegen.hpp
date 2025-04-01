#include <span>
#include <variant>

namespace brose {

using instruction_args = std::span<std::variant<size_t, double>>;

enum opcode : size_t {
    MOVrr,
    MOVrc,
    MOVrm, 
    MOVmr,
    MOVmc,
    ADDrr,
    SUBrr,
    MULrr,
    NEGrr,
    DIVrr,
    MODrr,
    EXPrr,
    ABSrr,
    FACrr,
    SINrr,
    COSrr,
    TANrr,
    LOGrr,
    LNrr,
    FLOORrr,
    CEILrr,
};

struct instruction {
    opcode op;
    instruction_args argv;
};

struct program {
    
};

};