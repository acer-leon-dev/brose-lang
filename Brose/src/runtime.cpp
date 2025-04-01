#include "pch.hpp"
#include <brose/codegen.hpp>

namespace brose {

using instruction_args = std::span<std::variant<size_t, double>>;

class VirtualMachine {
public:
    using data_segment = std::unordered_map<int, double>;
    using register_file = std::array<double, 4>;
    
    enum reg : size_t {
        pc = 0,
        r0,
        r1,
        r2,
    };
    
    data_segment data;
    register_file file;
    std::optional<double> endvalue;
    
    void initialize();
    void feed(program);
    void execute();
    double value();
private:
    void switch_instruction(instruction i);
    void moverr(reg, reg);
    void moverm(reg, size_t);
    void moverc(reg, double);
    void movemc(reg, double);
    void movemr(reg, size_t);
    void addrr(reg, reg);
    void subrr(reg, reg);
    void mulrr(reg, reg);
    void negrr(reg, reg);
    void divrr(reg, reg);
    void modrr(reg, reg);
    void exprr(reg, reg);
    void absrr(reg, reg);
    void facrr(reg, reg);
    void sinrr(reg, reg);
    void cosrr(reg, reg);
    void tanrr(reg, reg);
    void logrr(reg, reg);
    void lnrr(reg, reg);
    void floorrr(reg, reg);
    void ceilrr(reg, reg);
};


void VirtualMachine::switch_instruction(instruction i) {
    switch (i.op) {
        case MOVrr: moverReg(i); return;
        case MOVrc: moverMem(i); return;
        case MOVrm: moverCon(i); return;
        case MOVmr: moveMemFromCon(i); return;
        case MOVmc: moveMemFromReg(i); return;
        case ADDrr: add(i); return;
        case SUBrr: sub(i); return;
        case MULrr: mul(i); return;
        case NEGrr: neg(i); return;
        case DIVrr: div(i); return;
        case MODrr: mod(i); return;
        case EXPrr: exp(i); return;
        case ABSrr: abs(i); return;
        case FACrr: fac(i); return;
        case SINrr: sin(i); return;
        case COSrr: cos(i); return;
        case TANrr: tan(i); return;
        case LOGrr: log(i); return;
        case LNrr: ln(i); return;
        case FLOORrr: floor(i); return;
        case CEILrr: ceil(i); return;
    }
}

void VirtualMachine::initialize() {
    // allocate the variables and run the instructions
}

void VirtualMachine::feed(program) {

}

void VirtualMachine::execute() {
    // run the instructions array
}

double VirtualMachine::value() {
    if (!endvalue) {
        throw std::runtime_error("Error: Must initialize and execute the vm before getting value.");
    } else {
        return *endvalue;
    }
}

};