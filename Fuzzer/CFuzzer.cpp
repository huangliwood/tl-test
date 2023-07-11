//
// Created by wkf on 2021/10/29.
//

#include "Fuzzer.h"

CFuzzer::CFuzzer(tl_agent::CAgent *cAgent) {
    this->cAgent = cAgent;
}

void CFuzzer::randomTest(bool do_alias) {
    paddr_t addr = (rand() % 0x8) * (rand() % 0x80) * 0x40;  // Tag + Set + Offset
    int alias = (do_alias) ? (rand() % 4) : 0;
    if (rand() % 2) {
        if (rand() % 3) {
            if (rand() % 2) {
                cAgent->do_acquireBlock(addr, tl_agent::NtoT, alias); // AcquireBlock NtoT
                printf("addr 0x%lx\n",addr);
            } else {
                cAgent->do_acquireBlock(addr, tl_agent::NtoT, alias); // AcquireBlock NtoB
            }
        } else {
            cAgent->do_acquirePerm(addr, tl_agent::NtoT, alias); // AcquirePerm
        }
    } else {
        /*
        uint8_t* putdata = new uint8_t[DATASIZE];
        for (int i = 0; i < DATASIZE; i++) {
            putdata[i] = (uint8_t)rand();
        }
        cAgent->do_releaseData(addr, tl_agent::TtoN, putdata); // ReleaseData
        */
        cAgent->do_releaseDataAuto(addr, alias); // feel free to releaseData according to its priv
    }
}

void CFuzzer::caseTest() {
    if (*cycles == 100) {
        this->cAgent->do_acquireBlock(0x1040, tl_agent::NtoT, 0);
    }
    if (*cycles == 300) {
        uint8_t* putdata = new uint8_t[DATASIZE];
        for (int i = 0; i < DATASIZE; i++) {
            putdata[i] = (uint8_t)rand();
        }
        this->cAgent->do_releaseData(0x1040, tl_agent::TtoN, putdata, 0);
    }
    if (*cycles == 400) {
      this->cAgent->do_acquireBlock(0x1040, tl_agent::NtoT, 0);
    }
}

void CFuzzer::pfTest(){
    paddr_t addr = (paddr_t)100;//this->cycles ;//& ((36<<1)-1);  // Tag + Set + Offset

    int alias = 0;
    if (rand() % 2) {
        if (rand() % 3) {
            if (rand() % 2) {
                cAgent->do_acquireBlock(addr, tl_agent::NtoT, alias); // AcquireBlock NtoT
                printf("addr 0x%lx\n",addr);
            } else {
                cAgent->do_acquireBlock(addr, tl_agent::NtoT, alias); // AcquireBlock NtoB
            }
        } else {
            cAgent->do_acquirePerm(addr, tl_agent::NtoT, alias); // AcquirePerm
        }
    } else {
        /*
        uint8_t* putdata = new uint8_t[DATASIZE];
        for (int i = 0; i < DATASIZE; i++) {
            putdata[i] = (uint8_t)rand();
        }
        cAgent->do_releaseData(addr, tl_agent::TtoN, putdata); // ReleaseData
        */
        cAgent->do_releaseDataAuto(addr, alias); // feel free to releaseData according to its priv
    } 
}

void CFuzzer::tick() {
     this->randomTest(false);
    // this->caseTest();
//    this->pfTest();
}