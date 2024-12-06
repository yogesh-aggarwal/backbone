#include "buffer.hpp"

/* ------------------------------------------------------------------------------------------------------- */

PacketBuffer::PacketBuffer() : BasicBuffer<uint8_t, 512>(0) {}

/* ------------------------------------------------------------------------------------------------------- */

PacketBuffer::PacketBuffer(const PacketBuffer &other) : BasicBuffer<uint8_t, 512>(other) {}

/* ------------------------------------------------------------------------------------------------------- */

PacketBuffer::PacketBuffer(PacketBuffer &&other) : BasicBuffer<uint8_t, 512>(std::move(other)) {}

/* ------------------------------------------------------------------------------------------------------- */

PacketBuffer &
PacketBuffer::operator=(const PacketBuffer &other) {
   BasicBuffer<uint8_t, 512>::operator=(other);
   return *this;
}

/* ------------------------------------------------------------------------------------------------------- */

PacketBuffer &
PacketBuffer::operator=(PacketBuffer &&other) {
   BasicBuffer<uint8_t, 512>::operator=(std::move(other));
   return *this;
}

/* ------------------------------------------------------------------------------------------------------- */
