#!/usr/bin/python
# -*- coding: utf-8 -*-
'''
This module provides a basic assembler for a simcpu.

@author: Nicola Coretti
@contact: nico.coretti@gmail.com
@version: 0.1.0
'''

import re
import sys
import argparse

# Instructions -----------------------------------------------------------------
# does nothing
NOP  = 0x00
# loads the accumulator with the specified value
LDAV = 0x01
# loads the accumulator with the value contained at the specified memory address
LDAA = 0x02
# stores the content of the accumulator at the specified memory address
STA  = 0x03
# increases the value of the accumulator by the specified value
ADDV = 0x04
# increases the value of the the accumulator by the value at the given memory address
ADDA = 0x05
# decreases the value of the accumulator by the specified value
SUBV = 0x6
# decreases the value of the accumulator by the value at the specified memory address
SUBA = 0x07
# loads the instruction pointer with the specified value
JMP  = 0x08
# adds the specified value to the instruction pointer if the ZERO-Falg is set
BRZ  = 0x09
# adds the specified value to the instruction pointer if the CARRY-Falg is set
BRC  = 0x0A
# adds the specified value to the instruction pointer if the NEGATION-Fag is set
BRN  = 0x0B
# indicates the end of the programm
END  = 0x0C

# a list of all instructions
INSTRUCTIONS = [NOP, LDAV, LDAA, STA, ADDV, ADDA, 
                SUBV, SUBA, JMP, BRZ, BRC, BRN, END]
# Default-Mapping
INSTRUCTION_MAPPING = {
                           NOP:  re.compile("NOP$"),
                           LDAV: re.compile("LDA #(([0-9]{1,3})|(-[0-9]{1,3}))$"),
                           LDAA: re.compile("LDA \([0-9]{1,3}\)$"),
                           STA:  re.compile("STA [0-9]{1,3}$"),
                           ADDV: re.compile("ADD #(([0-9]{1,3})|(-[0-9]{1,3}))$"),
                           ADDA: re.compile("ADD \([0-9]{1,3}\)$"),
                           SUBV: re.compile("SUB #(([0-9]{1,3})|(-[0-9]{1,3}))$"),
                           SUBA: re.compile("SUB \([0-9]{1,3}\)$"),
                           JMP:  re.compile("JMP [0-9]{1,3}$"),
                           BRZ:  re.compile("BRZ #(([0-9]{1,3})|(-[0-9]{1,3}))$"),
                           BRC:  re.compile("BRC #(([0-9]{1,3})|(-[0-9]{1,3}))$"),
                           BRN:  re.compile("BRN #(([0-9]{1,3})|(-[0-9]{1,3}))$"),
                           END:  re.compile("END$")
                       }
# mapping opcode instruction string
INSTRUCTION_STRINGS = {
                           NOP:  "NOP",
                           LDAV: "LDA #n",
                           LDAA: "LDA (n)",
                           STA:  "STA n",
                           ADDV: "ADD #n",
                           ADDA: "ADD (n)",
                           SUBV: "SUB #n",
                           SUBA: "SUB (n)",
                           JMP:  "JMP n",
                           BRZ:  "BRZ #n",
                           BRC:  "BRC #n",
                           BRN:  "BRN #n",
                           END:  "END"
                       }

class Assembler(object):
    """
    This class provides minimalistic assembler for the simcpu.
    """
    
    def __init__(self, in_file, out_file=None):
        """
        Creates a new Assembler.
        """
        self.in_file = in_file
        self.out_file = out_file
        self.output_lines = []
        self._line_no = 1
        self.parse_error = False
    
    
    def _check_file_length(self):
        """
        Checks whether the in file hasn't more than 255 lines.
        
        @raise exception: if the input file has to many lines.
        """
        asm_file = open(self.in_file, "r")
        line_no = 0
        for line in asm_file:
            line_no = line_no + 1
            if line_no > 255: 
                raise Exception("FileError: File has more than 255 lines")
    
    
    def get_instruction(self, line):
        """
        Gets the instruction from the given line.
            
        @param line: of a asm code file.
            
        @return: returns the instruction of this line, if no instruction
                 was found None will be returned.
        @rtype: instruction constant.
        """    
        instruction = None
        for current_instruction in INSTRUCTIONS:   
            if INSTRUCTION_MAPPING[current_instruction].match(line):
                instruction = current_instruction
                break
            
        return instruction
  
        
    def get_value(self, digit_str):
        """
        Gets the numeric value of the given string.
            
        @param digit_str: whose value will be determined.
        @type digit_str: string
             
        @return: the numeric value for the given string.
        @rtype: int
            
        @raise ValueError:  If the value it isn't  contained in [0, 255].
        """
        value = int(digit_str)
        if (value >= 0 and value <= 255) or (value >= -128 and value <= 127): return value
        else:
            err_msg = "ValueError: In line {0} a value != [0,255] or value != [-128, 127] was used."
            raise ValueError(err_msg.format(self._line_no))
    
        
    def create_output_line(self, instruction, line):
        """
        Adds an output line to the ou
        """
        out_line = "{0}"
        parameter = 0
        
        if instruction == NOP or instruction == END:
            parameter = 0
        else:
            results = re.findall("(([0-9]{1,3})|(-[0-9]{1,3}))", line)
            if len(results) == 1:
                digit_str = results[0][0]
                if digit_str.isdigit() or digit_str[1:].isdigit():
                    parameter = self.get_value(digit_str)
                    if parameter < 0: parameter = 256 + parameter
                else:
                    err_msg = "SyntaxError, line {0}: Parameter isn't a int value"
                    raise Exception(err_msg.format(self._line_no))
            else:
                # if this exception is raised there is an error in the regex
                raise NotImplementedError()
        
        out_value = instruction << 8
        out_value = out_value | parameter
        return out_line.format(out_value)

        
    def write_output(self):
        """
        Writes the compiled output to file or to the std.
        """
        if self.out_file:
            out_file = None
            try:
                out_file = open(self.out_file, "w")
                out_file
                for line in self.output_lines:
                    out_file.write(line)
                    out_file.write("\n")
            except IOError as ex:
                err_msg = "IOError, details: {0}"
                print(err_msg.format(ex))
            finally:
                if out_file: out_file.close()
        else:
            for line in self.output_lines:
                print(line)
        
        
    def compile(self):
        """
        Compiles the input file.
        """
        asm_file = None
        try:
            self._check_file_length()
            self._line_no = 1
            asm_file = open(self.in_file, "r")
            for line in asm_file:
                line = line.strip()
                instruction = self.get_instruction(line)
                if instruction != None:
                    output_line = self.create_output_line(instruction, line)
                    self.output_lines.append(output_line)
                    self._line_no = self._line_no + 1
                else:
                    err_msg = "Syntax error in line: {0}"
                    raise Exception(err_msg.format(self._line_no))
        except Exception as ex:
            self.parse_error = True
            print("{0}".format(ex))
        finally:
            if asm_file: asm_file.close() 
  

def print_mappings():
    """
    Prints all the instruction mappings.
    """
    print("{0:<15}   {1}    {2}".format("Instruction", "Opcode", "Matching-Pattern"))
    for instruction in INSTRUCTIONS:
        line = "{0:<17} {1:#x}       {2}"
        print(line.format(INSTRUCTION_STRINGS[instruction],instruction,
                          INSTRUCTION_MAPPING[instruction].pattern))
    
if __name__ == "__main__":
    
    DESCRIPTION = "Compiles assembler code for the simcpu"
    arg_parser = argparse.ArgumentParser(description=DESCRIPTION)
    arg_parser.add_argument("-i", metavar="input-file", dest="in_file",
                            help="a file with assembler instructions")
    arg_parser.add_argument("-o", metavar="out-file", dest="out_file",
                            help="file to which the compiled output will be written")
    arg_parser.add_argument("-m", dest="mappings", nargs="?", const=True,
                            help="show out the instruction mappings")
  
    if len(sys.argv) == 1:
        arg_parser.print_help()
        sys.exit(0)
    else:
        args = arg_parser.parse_args()
        args = vars(args)
    
    assembler = None
    if args["in_file"]:
        if args["out_file"]:
            assembler = Assembler(args["in_file"], args["out_file"])
        else:
            assembler = Assembler(args["in_file"])
        assembler.compile()
        if not assembler.parse_error:
            assembler.write_output()
            sys.exit(0)
        sys.exit(1)
    elif args["mappings"]:
        print_mappings()
        sys.exit(0)
    else:
        arg_parser.print_help()
        sys.exit(0)
