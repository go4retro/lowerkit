cp new.fnt.bin new.fnt.trunc.bin
truncate -s 2048 new.fnt.trunc.bin

cat chgapl2.fnt.bin new.fnt.trunc.bin small.fnt.bin little2.fnt.bin chgmath.fnt.bin chgkata.fnt.bin chgapl.fnt.bin chgeuro.fnt.bin chggreek.fnt.bin chgkata.fnt.bin chgkata2.fnt.bin chgmath.fnt.bin chgscrip.fnt.bin little2.fnt.bin small.fnt.bin new.fnt.trunc.bin > allfonts.bin
