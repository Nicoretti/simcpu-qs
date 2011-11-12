#include <stdlib.h>
#include <inttypes.h>

#ifndef SIMCPU_TYPES_H
#define SIMCPU_TYPES_H

typedef struct {

    // instruction pointer
    uint8_t ips;
    uint8_t accu;
    // status bits / flags ("psw")
    uint8_t zero_bit;
    uint8_t carry_bit;
    uint8_t negation_bit;
} CpuStatus;

typedef struct  {

    uint8_t opcode;
    uint8_t param;
} TextSegment;

typedef struct {

    TextSegment text[256];
    uint8_t data [256];
} Memory;

/**
 * Checks the result and sets the flags (carry, zero, negation) appropriate.
 */
void set_flags_by_result(CpuStatus* cpu_status, uint16_t result) {

    if (result == 0) { 
        cpu_status->zero_bit = 1; 
    }
    else { 
        cpu_status->zero_bit = 0; 
    }
    cpu_status->carry_bit = (result & 0xff00) >> 8;
    cpu_status->negation_bit = (result & 0x0080) >> 7;
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
void load_value(CpuStatus* cpu_status, uint8_t value) {
    
    cpu_status->accu = value;
    set_flags_by_result(cpu_status, value);
}

/*
 * Loads the accumulator with the value contained at the specified memory address.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param data_segemnt:
 * @param address: where the value can be found.
 */
void load_value_by_address(CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address) {
    
    cpu_status->accu = data_segment[address];
    set_flags_by_result(cpu_status, data_segment[address]);
}

/*
 * Stores the content of the accumulator at the specified memory address
 * @param cpu_status: of the cpu which is calling this operation.
 * @param data_segemnt:
 * @param address: where the value shall be stored.
 */
void store_value(CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address) {
    
    data_segemnt[address] = cpu_status->accu;
    set_flags_by_result(cpu_status, cpu_status
}

/**
 * Increases the value of the accumulator by the specified value. 
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be added to the accumulator.
 */
void add_value(CpuStatus* cpu_status, uint8_t value) {
    
    uint16_t result = cpu_status->accu;
    result += value; 
    set_flags_by_result(cpu_status, result);
    cpu_status->accu = (uint8_t) result;
}

/**
 * Increases the value of the the accumulator by the value at the given memory address
 * @param cpu_status: of the cpu which is calling this operation.
 * @param data_segemnt:
 * @param address: where the value can be found which will be added to the accumulator.
 */
void add_value_by_address(CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address) {

}

/**
 * Decreases the value of the accumulator by the specified value.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will subtracted from the accumulator.
 */
void sub_value(CpuStatus* cpu_status, uint8_t value) {

}

/**
 * Decreases the value of the accumulator by the value at the specified memory address
 * @param cpu_status: of the cpu which is calling this operation.
 * @param data_segemnt:
 * @param address: where the value can be found which will be subtracted from the accumulator.
 */
void sub_value_by_address(CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address) {

}

/**
 * Loads the instruction pointer with the specified value.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be loaded into the instruction pointer.
 */
void jump(CpuStatus* cpu_status, uint8_t value) {

}

/*
 * Adds the specified value to the instruction pointer if the ZERO-Falg is set
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be added to the instruction pointer.
 */
void brz(CpuStatus* cpu_status, uint8_t value) {

}

/*
 * Adds the specified value to the instruction pointer if the CARRY-Falg is set.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be added to the instruction pointer.
 */
void brc(CpuStatus* cpu_status, uint8_t value) {

}

/*
 * Adds the specified value to the instruction pointer if the NEGATION-Fag is set.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be added to the instruction pointer.
 */
void brn(CpuStatus* cpu_status, uint8_t value) {

}

/*
 * Not Specified yet.
 * @param cpu_status: of the cpu which is calling this operation.
 */
void end(CpuStatus* cpu_status) {

}
#endif /* SIMCPU_TYPES_H */
