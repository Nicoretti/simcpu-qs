#include <stdlib.h>
#include <inttypes.h>

#ifndef SIMCPU_TYPES_H
#define SIMCPU_TYPES_H

struct CpuStatus {

    // instruction pointer
    uint8_t ips;
    uint8_t accu;
    // status bits / flags ("psw")
    uint8_t zero_bit;
    uint8_t carry_bit;
    uint8_t negation_bit;
};

struct TextSegment {

    uint8_t opcode;
    uint8_t param;
};

struct Memory {

    struct TextSegment text[256];
    uint8_t data [256];
};


/**
 * Sets the zero bit if necessary.
 */
void zero_bit_check(struct CpuStatus* cpu_status) {

    if (cpu_status->accu == 0) { 
        cpu_status->zero_bit = 1; 
    }
    else { 
        cpu_status->zero_bit = 0; 
    }
}

/**
 * As expected nop = no operation => it does nothing.
 */
void nop() {}

/*
 * Loads the accumulator with the specified value.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be loaded into the accumulator. 
 */
void load_value(struct CpuStatus* cpu_status, uint8_t value) {
    
    cpu_status->accu = value;
    zero_bit_check(cpu_status);
}

/*
 * Loads the accumulator with the value contained at the specified memory address.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param data_segemnt:
 * @param address: where the value can be found.
 */
void load_value_by_address(struct CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address) {

}

/*
 * Stores the content of the accumulator at the specified memory address
 * @param cpu_status: of the cpu which is calling this operation.
 * @param data_segemnt:
 * @param address: where the value shall be stored.
 */
void store_value(struct CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address) {

}

/**
 * Increases the value of the accumulator by the specified value. 
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be added to the accumulator.
 */
void add_value(struct CpuStatus* cpu_status, uint8_t value) {
    
    
}

/**
 * Increases the value of the the accumulator by the value at the given memory address
 * @param cpu_status: of the cpu which is calling this operation.
 * @param data_segemnt:
 * @param address: where the value can be found which will be added to the accumulator.
 */
void add_value_by_address(struct CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address) {

}

/**
 * Decreases the value of the accumulator by the specified value.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will subtracted from the accumulator.
 */
void sub_value(struct CpuStatus* cpu_status, uint8_t value) {

}

/**
 * Decreases the value of the accumulator by the value at the specified memory address
 * @param cpu_status: of the cpu which is calling this operation.
 * @param data_segemnt:
 * @param address: where the value can be found which will be subtracted from the accumulator.
 */
void sub_value_by_address(struct CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address) {

}

/**
 * Loads the instruction pointer with the specified value.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be loaded into the instruction pointer.
 */
void jump(struct CpuStatus* cpu_status, uint8_t value) {

}

/*
 * Adds the specified value to the instruction pointer if the ZERO-Falg is set
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be added to the instruction pointer.
 */
void brz(struct CpuStatus* cpu_status, uint8_t value) {

}

/*
 * Adds the specified value to the instruction pointer if the CARRY-Falg is set.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be added to the instruction pointer.
 */
void brc(struct CpuStatus* cpu_status, uint8_t value) {

}

/*
 * Adds the specified value to the instruction pointer if the NEGATION-Fag is set.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be added to the instruction pointer.
 */
void brn(struct CpuStatus* cpu_status, uint8_t value) {

}

/*
 * Not Specified yet.
 * @param cpu_status: of the cpu which is calling this operation.
 */
void end(struct CpuStatus* cpu_status) {

}
#endif /* SIMCPU_TYPES_H */
