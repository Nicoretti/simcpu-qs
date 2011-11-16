#!/usr/bin/python
# -*- coding: utf-8 -*-
'''
This module provides test for the simcpu assembler.

@author: Nicola Coretti
@contact: nico.coretti@googlemail.com
@version: 0.1.0
'''
import unittest
from assembler import Assembler, INSTRUCTIONS, INSTRUCTION_MAPPING
from assembler import LDAA, LDAV, STA, ADDV, ADDA, SUBV, SUBA, JMP, BRZ, BRC, BRN, END, NOP


class Test(unittest.TestCase):


    def setUp(self):
        self.asm = Assembler(None)

    def tearDown(self):
        pass

# Tests NOP -------------------------------------------

    def test_nop(self):
        instr_line = "NOP"
        expected = NOP
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_nop_fail1(self):
        instr_line = "NOPP"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_nop_fail2(self):
        instr_line = "NOP #10"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

# Tests END -------------------------------------------

    def test_end(self):
        instr_line = "END"
        expected = END
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_end_fail1(self):
        instr_line = "END #"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_nop_fail2(self):
        instr_line = "END #10"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

# Tests JMP -------------------------------------------

    def test_jmp_fail1(self):
        instr_line = "JMP #-1"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_jmp_fail2(self):
        instr_line = "JMP #"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)
    
    def test_jmp_fail3(self):
        instr_line = "JMP #2544"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_jmp_sucess(self):
        instr_line = "JMP 10"
        expected = JMP
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

# Tests BRN -------------------------------------------

    def test_brn_val_negative(self):
        instr_line = "BRN #-1"
        expected = BRN
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_brn_val_positive(self):
        instr_line = "BRN #10"
        expected = BRN
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_brn_val_positive_fail1(self):
        instr_line = "BRN #2333"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_brn_val_negative_fail1(self):
        instr_line = "BRN #-2232"
        expected = None 
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

# Tests BRZ -------------------------------------------

    def test_brz_val_negative(self):
        instr_line = "BRZ #-1"
        expected = BRZ
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_brz_val_positive(self):
        instr_line = "BRZ #10"
        expected = BRZ
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_brz_val_positive_fail1(self):
        instr_line = "BRZ #2333"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_brz_val_negative_fail1(self):
        instr_line = "BRZ #-2232"
        expected = None 
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

# Tests BRC -------------------------------------------

    def test_brc_val_negative(self):
        instr_line = "BRC #-1"
        expected = BRC
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_brc_val_positive(self):
        instr_line = "BRC #10"
        expected = BRC
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_brc_val_positive_fail1(self):
        instr_line = "BRC #2333"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_brc_val_negative_fail1(self):
        instr_line = "BRC #-2232"
        expected = None 
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

# Tests LDAV -------------------------------------------

    def test_lda_val_negative(self):
        instr_line = "LDA #-1"
        expected = LDAV
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_lda_val_positive(self):
        instr_line = "LDA #10"
        expected = LDAV
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_lda_val_positive_fail1(self):
        instr_line = "LDA #2333"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_lda_val_negative_fail1(self):
        instr_line = "LDA #-2232"
        expected = None 
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

# Tests LDAA -------------------------------------------

    def test_lda_adr_fail1(self):
        instr_line = "LDA (-1)"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_lda_adr_fail2(self):
        instr_line = "LDAd (1)"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_lda_adr_positive(self):
        instr_line = "LDA (10)"
        expected = LDAA
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_lda_adr_positive_fail1(self):
        instr_line = "LDA (2333)"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

# Tests ADDA -------------------------------------------

    def test_add_adr_fail1(self):
        instr_line = "ADD (-1)"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_lda_adr_succces(self):
        instr_line = "ADD (1)"
        expected = ADDA
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_lda_adr_positive_fail1(self):
        instr_line = "ADD (2333)"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

# Tests ADDV -------------------------------------------

    def test_add_val_negative(self):
        instr_line = "ADD #-128"
        expected = ADDV
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_add_val_positive(self):
        instr_line = "ADD #10"
        expected = ADDV
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_add_val_positive_fail1(self):
        instr_line = "ADD #2333"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_add_val_negative_fail1(self):
        instr_line = "ADD #-2232"
        expected = None 
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

# Tests SUBA -------------------------------------------

    def test_sub_adr_fail1(self):
        instr_line = "SUB (-1)"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_sub_adr_succces(self):
        instr_line = "SUB (1)"
        expected = SUBA
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_sub_adr_positive_fail1(self):
        instr_line = "SUB (2333)"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

# Tests SUBV -------------------------------------------

    def test_sub_val_negative(self):
        instr_line = "SUB #-128"
        expected = SUBV
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_lda_val_positive(self):
        instr_line = "SUB #10"
        expected = SUBV
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_lda_val_positive_fail1(self):
        instr_line = "SUB #2333"
        expected = None
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

    def test_lda_val_negative_fail1(self):
        instr_line = "SUB #-2232"
        expected = None 
        actual = self.asm.get_instruction(instr_line)
        self.assertEqual(expected, actual)

# Tests values ------------------------------------------

    def test_val1(self):
        instr = LDAA
        instr_line = "LDA #-1"
        value = (instr << 8) | 255
        expected = "{0}".format(value)
        actual = self.asm.create_output_line(instr, instr_line)
        self.assertEqual(expected, actual)

    def test_val2(self):
        instr = LDAA
        instr_line = "LDA #1"
        value = (instr << 8) | 1
        expected = "{0}".format(value)
        actual = self.asm.create_output_line(instr, instr_line)
        self.assertEqual(expected, actual)

    def test_val3(self):
        instr = LDAV
        instr_line = "LDA (1)"
        value = (instr << 8) | 1
        expected = "{0}".format(value)
        actual = self.asm.create_output_line(instr, instr_line)
        self.assertEqual(expected, actual)

    def test_val4(self):
        instr = LDAV
        instr_line = "LDA #256"
        value = (LDAA << 8) | 256
        expected = "{0}".format(value)
        self.assertRaises(ValueError,self.asm.create_output_line, instr, instr_line)

    def test_val5(self):
        instr = LDAV
        instr_line = "LDA (-1)"
        value = (LDAV << 8) | 255
        expected = "{0}".format(value)
        actual = self.asm.create_output_line(instr, instr_line)
        self.assertEqual(expected, actual)


if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
