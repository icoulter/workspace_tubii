/* tubiiUtil.h
 *
 *  Created on: Apr 9, 2014
 *      Author: Ian Coulter (help from various sources)
 */
#include "sys/mman.h"
#include <fcntl.h>

#ifndef TUBIIUTIL_H_
#define TUBIIUTIL_H_

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct {
    client *c;
    uint32_t key;
} load_db_args;

#define REG0_OFFSET 0
#define REG1_OFFSET 4
#define REG2_OFFSET 8
#define REG3_OFFSET 12
#define REG4_OFFSET 16
#define REG5_OFFSET 20
#define REG6_OFFSET 24
#define REG7_OFFSET 28
#define REG8_OFFSET 32
#define REG9_OFFSET 36
#define REG10_OFFSET 40
#define REG11_OFFSET 44
#define REG12_OFFSET 48
#define REG13_OFFSET 52
#define REG14_OFFSET 56
#define REG15_OFFSET 60

#define SOCKET_ERROR        -1
#define BUFFER_SIZE         100
#define QUEUE_SIZE          5

// Register offsets
u32 RegOffset0= REG0_OFFSET;
u32 RegOffset1= REG1_OFFSET;
u32 RegOffset2= REG2_OFFSET;
u32 RegOffset3= REG3_OFFSET;
u32 RegOffset4= REG4_OFFSET;
u32 RegOffset5= REG5_OFFSET;
u32 RegOffset6= REG6_OFFSET;
u32 RegOffset7= REG7_OFFSET;
u32 RegOffset8= REG8_OFFSET;
u32 RegOffset9= REG9_OFFSET;
u32 RegOffset10= REG10_OFFSET;
u32 RegOffset11= REG11_OFFSET;
u32 RegOffset12= REG12_OFFSET;
u32 RegOffset13= REG13_OFFSET;
u32 RegOffset14= REG14_OFFSET;
u32 RegOffset15= REG15_OFFSET;

// Write a value to a register. A 32 bit write is performed.
#define mWriteReg(BaseAddress, RegOffset, Data) \
  	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

// Read a value from a register. A 32 bit read is performed.
#define mReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))

// Read to and from addresses
u32 Xil_In32(u32 Addr)
{
  return *(volatile u32 *) Addr;
}

void Xil_Out32(u32 OutAddress, u32 Value)
{
  *(volatile u32 *) OutAddress = Value;
}

// Memory Mapping Method
void* MemoryMapping(u32 BaseAddress, u32 HighAddress)
{
  //Begin memory mapping
  int memfd;
  void *MappedBaseAddress;
  off_t dev_base = BaseAddress;

  // Open Memory location
  memfd = open("/dev/mem", O_RDWR | O_SYNC);
  if (memfd == -1){
	Log(WARNING, "TUBii: Can't open memory location.");
   	exit(0);
  }

  // Map into user space the area of memory containing the device
  MappedBaseAddress = mmap(0, (HighAddress-BaseAddress), PROT_READ | PROT_WRITE, MAP_SHARED, memfd, dev_base & ~(HighAddress-BaseAddress-1));
  if (MappedBaseAddress == (void *) -1){
	Log(WARNING, "TUBii: Can't map the memory to user space");
    exit(0);
  }

  close(memfd);
  return MappedBaseAddress;
}

void InitialiseRegs(void* MappedBaseAddress)
{
  // Set all regs to zero...
  mWriteReg((u32) MappedBaseAddress, RegOffset0, 0);
  mWriteReg((u32) MappedBaseAddress, RegOffset1, 0);
  mWriteReg((u32) MappedBaseAddress, RegOffset2, 0);
  mWriteReg((u32) MappedBaseAddress, RegOffset3, 0);
}

// For error messages
char tubii_err[256];

// Constants
float HunMHz = 100000000;
float ns=0.1;

// Dead man switch
int dont_die = 0;

#endif /* TUBIIUTIL_H_ */
