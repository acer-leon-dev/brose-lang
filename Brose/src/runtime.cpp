#include "pch.hpp"
#include <brose/codegen.hpp>

using symbol_table = std::unordered_map<int, double>;
using register_file = std::array<double, 2>;

namespace brose {
    
class VirtualMachine {
public:
    enum reg {
        r0 = 0,
        r1 = 1,
    };
    
    symbol_table vartable;
    register_file regfile;
    std::optional<double> endvalue;
    
    void Initialize();
    void FeedScript(VMInstructions);
    void Execute();
    double RetrieveValue();
private:
    void Move_Reg_Reg(reg ra, reg rb);
    void Move_Reg_Literal(reg r, double lit);
    void Move_Reg_Address(reg r, int ad);
    void Move_Address_Reg();
};
    
void VirtualMachine::Move_Reg_Reg(reg ra, reg rb) {
    regfile[ra] = regfile[rb];    
}

void VirtualMachine::Move_Reg_Literal(reg r, double lit) {
    regfile[r] = lit;
}

void VirtualMachine::Move_Reg_Address(reg r, int ad) {
    regfile[r] = vartable[ad];
}

void VirtualMachine::Move_Address_Reg() {
    // assign some value source to a variable
}

void VirtualMachine::Initialize() {
    // allocate the variables and run the instructions
}

void VirtualMachine::FeedScript(VMInstructions) {

}

void VirtualMachine::Execute() {
    // run the instructions array
}

double VirtualMachine::RetrieveValue() {
    if (!endvalue) {
        throw std::runtime_error("Error: Must initialize and execute the vm before getting value.")
    } else {
        return *end_value;
    }
}

};