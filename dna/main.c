/*
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

#include "../src/db.h"
#include "dna.h"

int main(int argc, char *argv[])
{
    __db_table genbank = genbank_constructor();
    __db_cursor cursor = db_create_cursor(genbank, GENBANK_PRIMARY_KEY);
    __genbank_s genbank_s;

    genbank_s.seq_from = 1;
    genbank_s.seq1 = db_string_create("ACGTACGTAT");
    genbank_s.seq2 = db_string_create("ACGTACGTAT");
    genbank_s.seq3 = db_string_create("ACGTACGTAT");
    genbank_s.seq4 = db_string_create("ACGTACGTAT");
    genbank_s.seq5 = db_string_create("ACGTACGTAT");
    genbank_s.seq6 = db_string_create("ACGTACGTAT");

    genbank_insert(cursor, &genbank_s);

    genbank_print(cursor);

    db_drop_cursor(cursor);
    db_drop_table(genbank);

    return 0;
}
