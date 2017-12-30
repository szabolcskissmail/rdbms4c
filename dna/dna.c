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

#include "dna.h"

#include <time.h>
#include <stdlib.h>

__db_string random_dna(int length)
{
    char random_array[4] = {DNA_T, DNA_A, DNA_C, DNA_G};
    __db_string result = NULL;
    char* sequence = malloc((sizeof(char) * length) + 1);
    int random_int;
    srand(time(NULL));
    int i = 0;
    for(i = 0; i < length; i++) {
        random_int = rand() % 4;
        sequence[i] = random_array[random_int];
    }
    sequence[length] = 0;
    result = db_string_create(sequence);
    return result;
}

__db_table genbank_constructor()
{
    __db_primary_key primary_key;
    __db_record_definition record_definition = db_create_record_definition(7);

    db_set_record_definition_field(record_definition, GENBANK_seq_from, "seq_from", __NOT_NULL, __unsigned_int);
    db_set_record_definition_field(record_definition, GENBANK_seq1, "seq1", __NOT_NULL, __char_array);
    db_set_record_definition_field(record_definition, GENBANK_seq2, "seq2", __NOT_NULL, __char_array);
    db_set_record_definition_field(record_definition, GENBANK_seq3, "seq3", __NOT_NULL, __char_array);
    db_set_record_definition_field(record_definition, GENBANK_seq4, "seq4", __NOT_NULL, __char_array);
    db_set_record_definition_field(record_definition, GENBANK_seq5, "seq5", __NOT_NULL, __char_array);
    db_set_record_definition_field(record_definition, GENBANK_seq6, "seq6", __NOT_NULL, __char_array);

    primary_key = db_create_pk(1);
    db_set_index_field(primary_key, GENBANK_seq_from, GENBANK_PRIMARY_KEY, __asc);

    return db_create_table(record_definition, primary_key);
}

__db_table genbank_from_dna(__db_string dna)
{
    __db_table result = genbank_constructor();
    __db_cursor cursor = db_create_cursor(result, GENBANK_PRIMARY_KEY);
    __genbank_s genbank_s;
    char end = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    char* seq = NULL;
    int seq_from = 1;
    genbank_s.seq1 = NULL;
    genbank_s.seq2 = NULL;
    genbank_s.seq3 = NULL;
    genbank_s.seq4 = NULL;
    genbank_s.seq5 = NULL;
    genbank_s.seq6 = NULL;
    genbank_clear(&genbank_s);
    while(!end) {
        if(dna->str[i] == 0) {
            end = 1;
        } else {
            if(j == 61) {
                j = 0;
                k = 0;
            }
            if(j == 0 || j == 11 || j == 21 || j == 31 || j == 41 || j == 51) {
                if(seq != NULL) {
                    free(seq);
                }
                k = 0;
                seq = malloc(sizeof(char) * 11);
            }
            seq[k] = dna->str[i];
            if(j == 10) {
                seq[k + 1] = 0;
                genbank_s.seq1 = db_string_create(seq);
            } else if(j == 20) {
                seq[k + 1] = 0;
                genbank_s.seq2 = db_string_create(seq);
            } else if(j == 30) {
                seq[k + 1] = 0;
                genbank_s.seq3 = db_string_create(seq);
            } else if(j == 40) {
                seq[k + 1] = 0;
                genbank_s.seq4 = db_string_create(seq);
            } else if(j == 50) {
                seq[k + 1] = 0;
                genbank_s.seq5 = db_string_create(seq);
            } else if(j == 60) {
                seq[k + 1] = 0;
                genbank_s.seq6 = db_string_create(seq);
                genbank_s.seq_from = seq_from;
                genbank_insert(cursor, &genbank_s);
                seq_from += 60;
            }
            i++;
            j++;
            k++;
        }
    }
    if(j > 0 && j < 61) {
        if(j <= 10) {
            seq[k] = 0;
            genbank_s.seq1 = db_string_create(seq);
        } else if(j > 10 && j <= 20) {
            seq[k] = 0;
            genbank_s.seq2 = db_string_create(seq);
        } else if(j > 20 && j <= 30) {
            seq[k] = 0;
            genbank_s.seq3 = db_string_create(seq);
        } else if(j > 30 && j <= 40) {
            seq[k] = 0;
            genbank_s.seq4 = db_string_create(seq);
        } else if(j > 40 && j <= 50) {
            seq[k] = 0;
            genbank_s.seq5 = db_string_create(seq);
        } else if(j > 50 && j <= 60) {
            seq[k] = 0;
            genbank_s.seq6 = db_string_create(seq);
        }
        genbank_s.seq_from = seq_from;
        genbank_insert(cursor, &genbank_s);
    }
    db_drop_cursor(cursor);
    return result;
}

__db_cursor genbank_insert(__db_cursor cursor, __genbank_s* genbank)
{
    __db_field db_field = db_insert_preparation(7);
    db_insert_set_field(cursor, db_field, GENBANK_seq_from, &genbank->seq_from);
    db_insert_set_field(cursor, db_field, GENBANK_seq1, genbank->seq1->str);
    db_insert_set_field(cursor, db_field, GENBANK_seq2, genbank->seq2->str);
    db_insert_set_field(cursor, db_field, GENBANK_seq3, genbank->seq3->str);
    db_insert_set_field(cursor, db_field, GENBANK_seq4, genbank->seq4->str);
    db_insert_set_field(cursor, db_field, GENBANK_seq5, genbank->seq5->str);
    db_insert_set_field(cursor, db_field, GENBANK_seq6, genbank->seq6->str);

    db_insert_into(cursor, db_field);
    genbank_clear(genbank);
    return cursor;
}

__db_cursor genbank_find(__db_cursor cursor, unsigned int seq_from)
{
    __db_key key = db_create_key(cursor);
    db_set_key_field(key, GENBANK_seq_from, &seq_from);
    db_find_by_key(key);
    db_drop_key(key);
    return cursor;
}

void genbank_clear(__genbank_s* genbank)
{
    genbank->seq_from = 0;
    db_string_drop(genbank->seq1);
    genbank->seq1 = db_string_create("");
    db_string_drop(genbank->seq2);
    genbank->seq2 = db_string_create("");
    db_string_drop(genbank->seq3);
    genbank->seq3 = db_string_create("");
    db_string_drop(genbank->seq4);
    genbank->seq4 = db_string_create("");
    db_string_drop(genbank->seq5);
    genbank->seq5 = db_string_create("");
    db_string_drop(genbank->seq6);
    genbank->seq6 = db_string_create("");
}

void genbank_print(__db_cursor cursor)
{
    __db_record record;
    __for_cursor_loop(record, cursor)
    printf("%.10i %s %s %s %s %s %s \n",
           get_GENBANK_seq_from(record),
           get_GENBANK_seq1(record),
           get_GENBANK_seq2(record),
           get_GENBANK_seq3(record),
           get_GENBANK_seq4(record),
           get_GENBANK_seq5(record),
           get_GENBANK_seq6(record));
    __end_loop(record, cursor)
}


