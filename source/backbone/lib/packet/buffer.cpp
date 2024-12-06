#include "buffer.hpp"

/* ------------------------------------------------------------------------------------------------------- */

PacketBuffer::PacketBuffer() : BasicBuffer<uint8_t, 512>(0) {}

/* ------------------------------------------------------------------------------------------------------- */

Result<std::string>
PacketBuffer::read_qname() {
   return Result<std::string>("");
}

/* ------------------------------------------------------------------------------------------------------- */

Result<void>
PacketBuffer::write_qname(std::string qname) {
   return Result<void>();
}

/* ------------------------------------------------------------------------------------------------------- */
