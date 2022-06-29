#include "header.h"

/*
 * You are required to implement the parser functions below.
 *
 * int validateHeader(uint32_t header); function validates the header. A header is valid if all the conditions below evaluate true.
 *  - SYNC field is equal to 0x2a
 *  - if ACK bit is set V bit is also
 *  - if ACK bit is reset TYPE is non-zero.
 *  - SOURCE ADDRESS and DESTINATION ADDRESS are non-zero and different than each other.
 *
 *  If the header is valid, the function returns 1 otherwise it returns 0.
 *
 * int getFrameId(uint32_t header); function returns FRAME ID field if the header is valid, possibly checked using validateHeader function above.
 *  - If the header is not valid, it returns -1.
 *  - Otherwise, it returns non-negative integer corresponding to FRAME ID field.
 *
 * int getFrameType(uint32_t header); function returns TYPE field if the header is valid, possibly checked using validateHeader function above, and ACK bit is reset.
 *  - If the header is not valid, it returns -1.
 *  - If ACK bit is set, it returns 0.
 *  - Otherwise, it returns non-negative integer corresponding to TYPE field.
 *
 * int getSourceAddress(uint32_t header); function returns SOURCE ADDRESS field if the header is valid, possibly checked using validateHeader function above.
 *  - If the header is not valid, it returns -1.
 *  - Otherwise, it returns non-negative integer corresponding to SOURCE ADDRESS field.
 */

#define SYN_MASK ((1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5))
#define ACK_MASK ((1<<6))
#define V_MASK ((1<<7))
#define TYPE_MASK ((1<<8) | (1<<9) | (1<<10))
#define FRAMEID_MASK ((1<<11) | (1<<12) | (1<<13) | (1<<14) | (1<<15))
#define SOURCEADDRESS_MASK ((1<<16) | (1<<17) | (1<<18) | (1<<19) | (1<<20) | (1<<21) | (1<<22) | (1<<23))
#define DESTINATIONADDRESS_MASK ((1<<24) | (1<<25) | (1<<26) | (1<<27) | (1<<28) | (1<<29) | (1<<30) | (1<<31))

int validateHeader(uint32_t header) {
  if((header & SYN_MASK) != 0x2a)
    return 0;

  if((((header & ACK_MASK) == (1 << 6))) && (header & V_MASK) == 0)
    return 0;

  if((header & ACK_MASK) == 0 && (header & TYPE_MASK) == 0)
    return 0;

  if((header & SOURCEADDRESS_MASK) == 0)
    return 0;

  if((header & DESTINATIONADDRESS_MASK) == 0)
    return 0;

  return (
      ((header & SOURCEADDRESS_MASK) << 8) != (header & DESTINATIONADDRESS_MASK) 
      ) ? 1 : 0;
}

int getFrameId(uint32_t header) {
  if(validateHeader(header) == 0)
    return -1;

  return ((header & FRAMEID_MASK) >> 11);
}

int getFrameType(uint32_t header)
{
  if(validateHeader(header) == 0)
    return -1;

  if ((header & ACK_MASK) == (1 << 6))
    return 0;

  return ((header & TYPE_MASK) >> 8);
}

int getSourceAddress(uint32_t header)
{
  if(validateHeader(header) == 0)
    return -1;

  return ((header & SOURCEADDRESS_MASK) >> 16);
}

uint32_t createAckHeader(int destAddress, int sourceAddress, uint8_t frameId, char valid)
{
  uint32_t result = 0;
  result = result | (42);
  result = result | (1 << 6);
  result = result | (sourceAddress << 16);
  result = result | (destAddress << 24);
  result = result | (frameId << 11);
  result = (valid == 0) ? result | (0 << 7) : result | (1 << 7);
  return result;
}

uint32_t createHeader(int destAddress, int sourceAddress, uint8_t frameId, uint8_t type)
{
  uint32_t result = 0;
  result = result | (42);
  result = result | (sourceAddress << 16);
  result = result | (destAddress << 24);
  result = result | (frameId << 11);
  result = result | (type << 8);
  return result;
}
