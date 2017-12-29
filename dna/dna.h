/*
    dna
    Copyright (C) 2017  Szabolcs Kiss

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DNA_H_INCLUDED
#define DNA_H_INCLUDED

#include "../src/db.h"

#define GENBANK_PRIMARY_KEY 0

#define GENBANK_seq_from 0
#define GENBANK_seq1 1
#define GENBANK_seq2 2
#define GENBANK_seq3 3
#define GENBANK_seq4 4
#define GENBANK_seq5 5
#define GENBANK_seq6 6

#define get_GENBANK_seq_from(p_record) db_get_field_as_unsigned_int(p_record, GENBANK_seq_from)
#define get_GENBANK_seq1(p_record) db_get_field_as_char_array(p_record, GENBANK_seq1)
#define get_GENBANK_seq2(p_record) db_get_field_as_char_array(p_record, GENBANK_seq2)
#define get_GENBANK_seq3(p_record) db_get_field_as_char_array(p_record, GENBANK_seq3)
#define get_GENBANK_seq4(p_record) db_get_field_as_char_array(p_record, GENBANK_seq4)
#define get_GENBANK_seq5(p_record) db_get_field_as_char_array(p_record, GENBANK_seq5)
#define get_GENBANK_seq6(p_record) db_get_field_as_char_array(p_record, GENBANK_seq6)

typedef struct __genbank_ss {
    unsigned int seq_from;
    __db_string seq1;
    __db_string seq2;
    __db_string seq3;
    __db_string seq4;
    __db_string seq5;
    __db_string seq6;
} __genbank_s;


__db_table genbank_constructor();

__db_cursor genbank_insert(__db_cursor cursor, __genbank_s* genbank);

__db_cursor genbank_find(__db_cursor cursor, unsigned int seq_from);

void genbank_clear(__genbank_s* genbank);

#endif
