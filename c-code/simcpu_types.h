#include <stdlib.h>

#ifndef SIMCPU_TYPES_H
#define SIMCPU_TYPES_H

struct CpuStatus {

    // instruction pointer
    uint8_t ips = 0;
    uint8_t accu = 0;
    // status bits / flags ("psw")
    uint8_t zero_bit  = 1;
    uint8_t carry_bit = 0;
    uint8_t negation_bit = 0;
};

struct TextSegment {

    uint8_t opcode = 0;
    uint8_t param  = 0;
}

struct DataSegment {

    uint8_t value;
}

struct Memory {

    TextSegment text[256];
    DataSegment data[256];
}

/**
 * As expected nop = no operation => it does nothing.
 */
bool nop();

/*
 * Loads the accumulator with the specified value.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be loaded into the accumulator. 
 */
bool load_value(CpuStatus& cpu_status, uint8_t value);

/*
 * Loads the accumulator with the value contained at the specified memory address.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param data_segemnt:
 * @param address: where the value can be found.
 */
bool load_value_by_address(CpuStatus& cpu_status, DataSegment& data_segment, uint8_t address);

/*
 * Stores the content of the accumulator at the specified memory address
 * @param cpu_status: of the cpu which is calling this operation.
 * @param data_segemnt:
 * @param address: where the value shall be stored.
 */
bool store_value(CpuStatus& cpu_status, DataSegment& data_segment, uint8_t address);

/**
 * Increases the value of the accumulator by the specified value. 
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be added to the accumulator.
 */
bool add_value(CpuStatus& cpu_status, uint8_t value);

/**
 * Increases the value of the the accumulator by the value at the given memory address
 * @param cpu_status: of the cpu which is calling this operation.
 * @param data_segemnt:
 * @param address: where the value can be found which will be added to the accumulator.
 */
bool add_value_by_address(CpuStatus& cpu_status, DataSegment& data_segment, uint8_t address);

/**
 * Decreases the value of the accumulator by the specified value.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will subtracted from the accumulator.
 */
bool sub_value(CpuStatus& cpu_status, uint8_t value);

/**
 * Decreases the value of the accumulator by the value at the specified memory address
 * @param cpu_status: of the cpu which is calling this operation.
 * @param data_segemnt:
 * @param address: where the value can be found which will be subtracted from the accumulator.
 */
bool sub_value_by_address(CpuStatus& cpu_status, DataSegment& data_segment, uint8_t address);

/**
 * Loads the instruction pointer with the specified value.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be loaded into the instruction pointer.
 */
bool jump(CpuStatus& cpu_status, uint8_t value);

/*
 * Adds the specified value to the instruction pointer if the ZERO-Falg is set
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be added to the instruction pointer.
 */
bool brz(CpuStatus& cpu_status, uint8_t value);

/*
 * Adds the specified value to the instruction pointer if the CARRY-Falg is set.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be added to the instruction pointer.
 */
bool brc(CpuStatus& cpu_status, uint8_t value);

/*
 * Adds the specified value to the instruction pointer if the NEGATION-Fag is set.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be added to the instruction pointer.
 */
bool brz(CpuStatus& cpu_status, uint8_t value);

/*
 * Not Specified yet.
 * @param cpu_status: of the cpu which is calling this operation.
 */
bool end(CpuStatus& cpu_status);
#endif /* SIMCPU_TYPES_H */
