//
//  siavm.c
//  Assignment3
//
//  Created by 秦玮蔚 on 2020/5/23.
//  Copyright © 2020 Qin Weiwei. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//const int MEMORY = 1024;
//unsigned char memory[1024];
unsigned char *memory;
int registers[16];
unsigned int PC = 0;

int OP1,OP2;
int result;
unsigned char *currentInstruction;

void fetch() {
    currentInstruction = calloc(4,sizeof(unsigned char));

    for(int i = 0;i < 2;i ++) {
      currentInstruction[i] = memory[PC + i];
    }
    if(currentInstruction[0] == 0){
      free(currentInstruction);
      currentInstruction = NULL;
    }
    /*
    switch(Op) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            currentInstruction[1] = memory[PC + 1];
            PC += 2;
        case 10:
        case 11:
        case 12:
        case 13:
            currentInstruction[1] = memory[PC + 1];
            currentInstruction[2] = memory[PC + 2];
            currentInstruction[3] = memory[PC + 3];
            PC += 4;
        case 14:
        case 15:
            currentInstruction[1] = memory[PC + 1];
            PC += 2;
    }
     */
}

void decode() {
    printf("DECODE: Read only from the array of bytes from fetch.\n");
    if(currentInstruction == NULL) {
      return;
    }
    int op = currentInstruction[0] >> 4;
    if(op == 0xA | op == 0xB | op == 0xC | op == 0xD) {
      unsigned int temp = PC + 2;
      for(int i = 2;i < 4;i ++) {
        currentInstruction[i] = memory[temp];
        temp += 1;
      }
    }
    switch(op) {
      case 0x7:
            OP1 = (currentInstruction[1] & 0x20) >> 5;
            OP2 = currentInstruction[1] & 0x1F;
            break;
      case 0x8:
            OP1 = ((currentInstruction[0] & 0x0F) << 8) | currentInstruction[1];
            break;
      case 0x9:
            OP1 = (signed char) currentInstruction[1];
            break;
      case 0xA:
      case 0xB:
            OP1 = (signed int)((((currentInstruction[1] & 0x0F) << 8) | currentInstruction[2]) << 8) | currentInstruction[3];
            break;
      case 0xC:
            OP1 = ((((((currentInstruction[0] & 0x0F) << 8) | currentInstruction[1]) << 8) | currentInstruction[2]) << 8) | currentInstruction[3];
            break;
      case 0xD:
            OP1 = currentInstruction[1];
            OP2 = (currentInstruction[2] << 8) | currentInstruction[3];
            break;
      case 0xE:
      case 0xF:
            OP1 = (signed char) currentInstruction[1] & 0x0F;
            break;
      default:
            break;
    }
    /*
    if(isFetch != true) {
        return;
    }
    switch(currentOp) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            OP1Decode = (int)currentInstruction[0];
            OP1Decode %= 16;
            OP2Decode = (int)currentInstruction[1];
        case 7:
            OP1Decode = (int)currentInstruction[0];
            OP1Decode %= 16;
            OP2Decode = (int)currentInstruction[1];
            OP2Decode = OP2Decode >> 6;
        case 8:
            OP1Decode = (int)currentInstruction[1];
        case 9:
            OP1Decode = (int)currentInstruction[0];
            OP1Decode %= 16;
            OP2Decode = (int)currentInstruction[1];
            if(OP2Decode > 127) {
                OP2Decode -= 256;
            }
        case 10:
            OP1Decode = (int)currentInstruction[0] % 16;
            OP1Decode = OP1Decode << 4;
            OP1Decode |= (int)currentInstruction[1] / 16;
            if((int)currentInstruction[1] % 16 >= 8) {
     
     }
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
    }
     */
}

void execute() {
    printf("EXECUTE: Switch statement that “does the work” and stores the work into Result.\n");
    int a;
    
    if(currentInstruction == NULL) {
      return;
    }
    int op = currentInstruction[0] >> 4;
    switch(op) {
      case 0x0:
            break;
      case 0x1:
            result = registers[currentInstruction[0] & 0x0F] + registers[currentInstruction[1] >> 4];
            break;
      case 0x2:
            result = registers[currentInstruction[0] & 0x0F] & registers[currentInstruction[1] >> 4];
            break;
      case 0x3:
            result = registers[currentInstruction[0] & 0x0F] / registers[currentInstruction[1] >> 4];
            break;
      case 0x4:
            result = registers[currentInstruction[0] & 0x0F] * registers[currentInstruction[1] >> 4];
            break;
      case 0x5:
            result = registers[currentInstruction[0] & 0x0F] - registers[currentInstruction[1] >> 4];
            break;
      case 0x6:
            result = registers[currentInstruction[0] & 0x0F] |     registers[currentInstruction[1] >> 4];
            break;
      case 0x7:
            if(OP1 == 0) {
                result = registers[currentInstruction[0] & 0x0F] << OP2;
            }else if(OP1 == 1) {
                result = registers[currentInstruction[0] & 0x0F] >> OP2;
            }
            break;
      case 0x8:
            if(OP1 == 0){
                for(int i = 0;i < 16;i ++) {
                  printf("r%d == %d\n",i,registers[i]);
                }
            }else if(OP1 == 1) {
                for(int i = 0;i < 100;i ++) {
                    if(i % 10 == 0){
                        printf("\n%08d ",i);
                    }
                    if(i % 2 == 0){
                       printf("%02x ",memory[i]);
                    }else {
                        printf("%02x ",memory[i]);
                    }
                }
            }
            break;
      case 0x9:
            result = registers[currentInstruction[0] & 0x0F] + OP1;
            break;
      case 0xA:
            if(registers[currentInstruction[0] & 0x0F] == registers[currentInstruction[1] >> 4]) {
                PC += OP1;
                break;
            }else {
                PC += 4;
                break;
            }
      case 0xB:
            if(registers[currentInstruction[0] & 0x0F] < registers[currentInstruction[1] >> 4]) {
                PC += OP1;
                break;
            }else {
                PC += 4;
                break;
            }
      case 0xC:
            PC = OP1;
            break;
      case 0xD:
            if(memory[registers[currentInstruction[0] & 0x0F] + OP1] != 0) {
                result = memory[registers[currentInstruction[0] & 0x0F] + OP1];
                PC -= OP2;
            }else {
                PC += 4;
            }
            break;
      case 0xE:
            a = registers[currentInstruction[1] >> 4] + OP1;
            result = (((((memory[a] << 8) | memory[a + 1]) << 8) | memory[a + 2]) << 8) | memory[a + 3];
            break;
      case 0xF:
            break;
      default:
            break;
    }
}

void store() {
    printf("STORE: Write result into final register or memory address. Update PC.\n");
    int a;
    int value;
    
    if(currentInstruction == NULL){
      return;
    }
    int op = currentInstruction[0] >> 4;
    switch(op) {
      case 0x0:
            PC += 2;
            break;
      case 0x1:
      case 0x2:
      case 0x3:
      case 0x4:
      case 0x5:
      case 0x6:
            registers[currentInstruction[1] & 0x0F] = result;
            PC += 2;
            break;
      case 0x7:
            registers[currentInstruction[0] & 0x0F] = result;
            PC += 2;
            break;
      case 0x8:
            PC += 2;
            break;
      case 0x9:
            registers[currentInstruction[0] & 0x0F] = result;
            PC += 2;
            break;
      case 0xA:
      case 0xB:
            break;
      case 0xC:
            break;
      case 0xD:
            registers[currentInstruction[0] & 0x0F] = result;
            break;
      case 0xE:
            registers[currentInstruction[0] & 0x0F] = result;
            PC += 2;
            break;
      case 0xF:
            value = registers[currentInstruction[0] & 0x0F];
            a = registers[currentInstruction[1] >> 4] + OP1;

            memory[a] = value >> 24;
            memory[a + 1] = (value >> 16) & 0x00FF;
            memory[a + 2] = (value >> 8) & 0x0000FF;
            memory[a + 3] = value & 0x000000FF;
            PC += 2;
            break;
      default:
            break;
    }
}

int main(int argc,char *argv[]) {
    /*
    FILE *src = fopen(argv[1],"r");
    char line[2];
    int i,size = 0;
    while (NULL != fgets(line, sizeof(line), src)) {
            unsigned char temp;
            for(i=0;i<1;i++){
            temp = line[i];
            mem[instructionSize]=temp;
            instructionSize++;
        }
    }
    fclose(src);
     */
    
    memory = (unsigned char *) malloc(1024 * sizeof(unsigned char));
    /*
    if(argc < 2) {
        puts("ERROR: not enough element");
        free(memory);
        return -1;
    }else if(argc > 2) {
        puts("ERROR: more argument");
        free(memory);
        return -1;
    }
     */
    if(argc > 2) {
        puts("ERROR: more argument");
        free(memory);
        return -1;
    }
    char * filename = argv[1];
    FILE *fptr;
    fptr = fopen(filename,"rb");
    if(fptr == NULL) {
        fclose(fptr);
        puts("ERROR: can not read file");
    }
    fseek(fptr,0,SEEK_END);
    size_t fileSize = ftell(fptr);
    fseek(fptr,0,SEEK_SET);
    if(fread(memory, sizeof *memory,fileSize,fptr) != fileSize) {
        fclose(fptr);
        puts("ERROR: can not read file");
    }
    
    int halt = 0;
    while(halt != 1) {
        fetch();
        decode();
        execute();
        store();
      if(currentInstruction == NULL){
        halt = 1;
      }
    }
     
    free(memory);
    return 0;
}
