#!/bin/sh
echo "----starting build bdf----"
# build bdf
rm bdf/*

w3_pts=(9 12 14 16 18)
w6_pts=(20 90)

for pt in "${w3_pts[@]}"; do
    ./otf2bdf -r 100 -p $pt dqhtjw3.otf -o bdf/dqhtjw3_${pt}pt.bdf
    echo "build dqhtjw3_${pt}pt.bdf"
done

for pt in "${w6_pts[@]}"; do
    echo "building dqhtjw6_${pt}pt.bdf"
    ./otf2bdf -r 100 -p $pt dqhtjw6.otf -o bdf/dqhtjw6_${pt}pt.bdf
    
done

echo "bdf build finished."

echo "----starting generate fonts c file----"
# generater fonts c file
rm release/*
cat header.txt >> release/u8g2_font_dqhtj.h

for pt in "${w3_pts[@]}"; do
    echo "extern const uint8_t u8g2_font_dqhtjw3_${pt}pt[] U8G2_FONT_SECTION("u8g2_font_dqhtjw3_${pt}pt");" >> release/u8g2_font_dqhtj.h
    ./bdfconv bdf/dqhtjw3_${pt}pt.bdf -b 0 -f 1 -M maps/gb2312.map -n u8g2_font_dqhtjw3_${pt}pt -o release/u8g2_font_dqhtjw3_${pt}pt.c
    echo '#include "u8g2_font_dqhtj.h"' >> release/temp.c
    cat release/u8g2_font_dqhtjw3_${pt}pt.c >> release/temp.c
    cat release/temp.c > u8g2_font_dqhtjw3_${pt}pt.c
    rm release/temp.c
    echo "generate w3 fonts ${pt}pt c file."

done

for pt in "${w6_pts[@]}"; do
    echo "extern const uint8_t u8g2_font_dqhtjw6_${pt}pt[] U8G2_FONT_SECTION("u8g2_font_dqhtjw6_${pt}pt");" >> release/u8g2_font_dqhtj.h
    ./bdfconv bdf/dqhtjw6_${pt}pt.bdf -b 0 -f 1 -M maps/gb2312.map -n u8g2_font_dqhtjw6_${pt}pt -o release/u8g2_font_dqhtjw6_${pt}pt.c
    echo '#include "u8g2_font_dqhtj.h"' >> release/temp.c
    cat release/u8g2_font_dqhtjw6_${pt}pt.c >> release/temp.c
    cat release/temp.c > u8g2_font_dqhtjw6_${pt}pt.c
    echo "generate w6 fonts ${pt}pt c file."

done

cat header2.txt >> release/u8g2_font_dqhtj.h
echo "finished all."