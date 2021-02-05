#!/bin/sh


# 定义字体大小
regular_pts=(9 12 16 18)
heavy_pts=(14 20)
bigger_pt=120

# build maps
function build_maps() {
    rm maps/numeral.map
    echo '32-128,' > maps/numeral.map
    cat source/numeral.txt | iconv -f utf-8 -t c99 | sed 's/\\u\([0-9a-f]\{4\}\)/\$\1,\'$'\n/g' | sort | uniq | sed '/^$/d' | tr '/a-f/' '/A-F/' >> maps/numeral.map

}
# build bdfs
function build_bdfs() {

    rm bdf/*

    # start build
    for pt in "${regular_pts[@]}"; do
        echo "building pingfang_regular_${pt}pt.bdf"
        ./otf2bdf -r 100 -p $pt source/PingFangRegular.ttf -o bdf/pingfang_regular_${pt}pt.bdf
        
    done

    for pt in "${heavy_pts[@]}"; do
        echo "building pingfang_heavy_${pt}pt.bdf"
        ./otf2bdf -r 100 -p $pt source/PingFangHeavy.ttf -o bdf/pingfang_heavy_${pt}pt.bdf
        
    done

    # echo "building dongqingheiti_bigger_${bigger_pt}pt.bdf"
    # ./otf2bdf -r 80 -p $bigger_pt source/dqhtjw6.otf -o bdf/dongqingheiti_bigger_${bigger_pt}pt.bdf
}

function build_c_file() {
    # generater fonts c file
    rm release/*
    cat source/header.txt > release/u8g2_font_pingfang.h

    # regular pingfang use gb2312
    for pt in "${regular_pts[@]}"; do
        echo "extern const uint8_t u8g2_font_pingfang_regular_${pt}pt[] U8G2_FONT_SECTION("u8g2_font_pingfang_regular_${pt}pt");" >> release/u8g2_font_pingfang.h
        ./bdfconv bdf/pingfang_regular_${pt}pt.bdf -b 0 -f 1 -M maps/gb2312.map -n u8g2_font_pingfang_regular_${pt}pt -o release/u8g2_font_pingfang_regular_${pt}pt.c
        echo '#include "u8g2_font_pingfang.h"' >> release/temp.c
        cat release/u8g2_font_pingfang_regular_${pt}pt.c >> release/temp.c
        cat release/temp.c > release/u8g2_font_pingfang_regular_${pt}pt.c
        rm release/temp.c
        echo "generate PingFang regular fonts ${pt}pt c file."

    done

    # 粗体都使用 numeral map，减小体积
    for pt in "${heavy_pts[@]}"; do
        echo "extern const uint8_t u8g2_font_pingfang_heavy_${pt}pt[] U8G2_FONT_SECTION("u8g2_font_pingfang_heavy_${pt}pt");" >> release/u8g2_font_pingfang.h
        ./bdfconv bdf/pingfang_heavy_${pt}pt.bdf -b 0 -f 1 -M maps/numeral.map -n u8g2_font_pingfang_heavy_${pt}pt -o release/u8g2_font_pingfang_heavy_${pt}pt.c
        echo '#include "u8g2_font_pingfang.h"' >> release/temp.c
        cat release/u8g2_font_pingfang_heavy_${pt}pt.c >> release/temp.c
        cat release/temp.c > release/u8g2_font_pingfang_heavy_${pt}pt.c
        rm release/temp.c
        echo "generate PingFang heavy fonts ${pt}pt c file."

    done

    cat source/header2.txt >> release/u8g2_font_pingfang.h

    # cat source/header.txt > release/u8g2_font_dongqingheiti_bigger.h

    # # bigger use numeral-map
    # echo "extern const uint8_t u8g2_font_dongqingheiti_bigger_${bigger_pt}pt[] U8G2_FONT_SECTION("u8g2_font_dongqingheiti_bigger_${bigger_pt}pt");" >> release/u8g2_font_dongqingheiti_bigger.h
    # ./bdfconv bdf/dongqingheiti_bigger_${bigger_pt}pt.bdf -b 0 -f 1 -M maps/numeral.map -n u8g2_font_dongqingheiti_bigger_${bigger_pt}pt -o release/u8g2_font_dongqingheiti_bigger_${bigger_pt}pt.c
    # echo '#include "u8g2_font_pingfang.h"' > release/temp.c
    # cat release/u8g2_font_dongqingheiti_bigger_${bigger_pt}pt.c >> release/temp.c
    # cat release/temp.c > release/u8g2_font_dongqingheiti_bigger_${bigger_pt}pt.c
    # rm release/temp.c

    # cat source/header2.txt >> release/u8g2_font_dongqingheiti_bigger.h
}




if [[ $1 = "map" ]]; then
    build_maps
    echo "build maps ok."
elif [[ $1 = "bdf" ]]; then
    build_bdfs
    echo "build bdfs ok."
elif [[ $1 = "c" ]]; then
    build_c_file
    echo "build fonts c file ok."
else
    echo "error: use 'map' or 'bdf' or 'c' to build"
    exit 1
fi

