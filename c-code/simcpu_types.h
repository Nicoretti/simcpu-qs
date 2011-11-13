#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#define MAX_LENGTH 256

#ifndef SIMCPU_TYPES_H
#define SIMCPU_TYPES_H

static const char* symtable []= { 
		"NOP", "LDA #n", "LDA (n)", "STA n", "ADD #n" , "ADD (n)"
    "SUB #n", "SUB (n)", "JMP n", "BRZ #n", "BRC #n", "BRN #", "END" };

enum {
        NOP  = 0x00,
        // loads the accumulator with the specified value
        LDAV = 0x01,
        // loads the accumulator with the value contained at the specified memory address
        LDAA = 0x02,
        // stores the content of the accumulator at the specified memory address
        STA  = 0x03,
        // increases the value of the accumulator by the specified value
        ADDV = 0x04,
        // increases the value of the the accumulator by the value at the given memory address
        ADDA = 0x05,
        // decreases the value of the accumulator by the specified value
        SUBV = 0x6,
        // decreases the value of the accumulator by the value at the specified memory address
        SUBA = 0x07,
        // loads the instruction pointer with the specified value
        JMP  = 0x08,
        // adds the specified value to the instruction pointer if the ZERO-Falg is set
        BRZ  = 0x09,
        // adds the specified value to the instruction pointer if the CARRY-Falg is set
        BRC  = 0x0A,
        // adds the specified value to the instruction pointer if the NEGATION-Fag is set
        BRN  = 0x0B,
        // indicates the end of the programm
        END  = 0x0C
};

typedef struct {

    // instruction pointer
    uint8_t ips;
    uint8_t accu;
    // status bits / flags ("psw")
    uint8_t zero_bit;
    uint8_t carry_bit;
    uint8_t negation_bit;
} CpuStatus;

typedef struct {

    uint8_t opcode;
    uint8_t param;
} TextSegment;

typedef struct {

    TextSegment text[256];
    uint8_t data [256];
} Memory;

/**
 * Outputs a debug message to stdout for the specified text segment.
 * @param text_segment: which will be used for the debug output.
 */
void debug_output(TextSegment* text_segment);

/*
 * Prints the contents of the data segment.
 * @param start: address for the dump.
 * @param end: address for the dump.
 */
extern void print_data_segment(uint8_t* data_segment, uint8_t start, uint8_t end);

/*
 * Prints the contents of the text segment.
 * @param start: address for the dump.
 * @param end: address for the dump.
 */
extern void print_text_segment(Memory* memory, uint8_t start, uint8_t end);

/**
 * Checks the result and sets the flags (carry, zero, negation) appropriate.
 */
extern void set_flags_by_result(CpuStatus* cpu_status, uint16_t result);

/**
 * As expected nop = no operation => it does nothing.
 */
extern void nop();

/*
 * Loads the accumulator with the specified value.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be loaded into the accumulator. 
 */
extern void load_value(CpuStatus* cpu_status, uint8_t value); 


/*
 * Loads the accumulator with the value contained at the specified memory address.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param data_segemnt:
 * @param address: where the value can be found.
 */
extern void load_value_by_address(CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address);


/*
 * Stores the content of the accumulator at the specified memory address
 * @param cpu_status: of the cpu which is calling this operation.
 * @param data_segemnt:
 * @param address: where the value shall be stored.
 */
extern void store_value(CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address);

/**
 * Increases the value of the accumulator by the specified value. 
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be added to the accumulator.
 */
extern void add_value(CpuStatus* cpu_status, uint8_t value);


/**
 * Increases the value of the the accumulator by the value at the given memory address
 * @param cpu_status: of the cpu which is calling this operation.
 * @param data_segemnt:
 * @param address: where the value can be found which will be added to the accumulator.
 */
extern void add_value_by_address(CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address);


/**
 * Decreases the value of the accumulator by the specified value.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will subtracted from the accumulator.
 */
extern void sub_value(CpuStatus* cpu_status, uint8_t value);


/**
 * Decreases the value of the accumulator by the value at the specified memory address
 * @param cpu_status: of the cpu which is calling this operation.
 * @param data_segemnt:
 * @param address: where the value can be found which will be subtracted from the accumulator.
 */
extern void sub_value_by_address(CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address);


/**
 * Loads the instruction pointer with the specified value.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be loaded into the instruction pointer.
 */
extern void jump(CpuStatus* cpu_status, uint8_t value);


/*
 * Adds the specified value to the instruction pointer if the ZERO-Falg is set
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be added to the instruction pointer.
 */
extern void brz(CpuStatus* cpu_status, uint8_t value);


/*
 * Adds the specified value to the instruction pointer if the CARRY-Falg is set.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be added to the instruction pointer.
 */
extern void brc(CpuStatus* cpu_status, uint8_t value);


/*
 * Adds the specified value to the instruction pointer if the NEGATION-Fag is set.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param value: which will be added to the instruction pointer.
 */
extern void brn(CpuStatus* cpu_status, uint8_t value);


/*
 * Not Specified yet.
 * @param cpu_status: of the cpu which is calling this operation.
 */
extern void end(CpuStatus* cpu_status);

/**
 * Checks if it is ok to jump with the given offset.
 * @param cpu_status: of the cpu which is calling this operation.
 * @param offset: to jump.
 * @return: 1 if it is ok to jump, otherwise 0.
 */
uint8_t is_jump_valid(CpuStatus* cpu_status, uint8_t offset);

#endif /* SIMCPU_TYPES_H */
