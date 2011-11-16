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



if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
