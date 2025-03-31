#include "pch.hpp"
#include <brose/codegen.hpp>

using data_segment = std::unordered_map<int, double>;
using register_file = std::array<double, 2>;

namespace brose {
    
class VirtualMachine {
public:
    std::optional<double> endvalue;
    
    enum reg {
        r0 = 0,
        r1 = 1,
    };

    data_segment data;
    register_file file;
    
    void initialize();
    void feedScript(VMInstructions);
    void execute();
    double RetrieveValue();
private:
    // Reg = register
    // Lit = literal
    // Add = address
    void moveRegFromReg(reg ra, reg rb);
    void moveRegFromMem(reg r, size_t addr);
    void moveRegFromLit(reg r, double val);

    void moveMemFromLit(size_t addr, double val);
    void moveMemFromReg(size_t addr, reg r);
};

void VirtualMachine::initialize() {
    // allocate the variables and run the instructions
}

void VirtualMachine::feedScript(VMInstructions) {

}

void VirtualMachine::execute() {
    // run the instructions array
}

double VirtualMachine::RetrieveValue() {
    if (!endvalue) {
        throw std::runtime_error("Error: Must initialize and execute the vm before getting value.");
    } else {
        return *endvalue;
    }
}

void VirtualMachine::moveRegFromReg(reg ra, reg rb) {
    
}

void VirtualMachine::moveRegFromMem(reg r, size_t ad) {
    
}

void VirtualMachine::moveRegFromLit(reg r, double val) {
    
}

void VirtualMachine::moveMemFromLit(size_t addr, double val) {
    
}

void VirtualMachine::moveMemFromReg(size_t addr, reg r) {
    
}

};