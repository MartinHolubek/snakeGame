/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   maxValue.c
 * Author: Martin
 *
 * Created on Piatok, 2017, decembra 29, 15:54
 */

#include "maxValue.h"

/*
 * 
 */
static int valueHeight = 0;
static int valueWidth = 0;

int getMaxHeight(void){
    return valueHeight;
}

void setMaxHeight(int new_value){
    valueHeight = new_value;
}

int getMaxWidth(void){
    return valueWidth;
}

void setMaxWidth(int new_value){
    valueWidth= new_value;
}