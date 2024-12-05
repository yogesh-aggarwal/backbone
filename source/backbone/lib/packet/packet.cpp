#include "packet.hpp"

/* ------------------------------------------------------------------------------------------------------- */

Packet::Packet() = default;

/* ------------------------------------------------------------------------------------------------------- */

Packet::Packet(const Packet &other)
    : header(other.header), questions(other.questions), answers(other.answers),
      authorities(other.authorities), additionals(other.additionals)
{
}

/* ------------------------------------------------------------------------------------------------------- */

Packet::Packet(Packet &&other)
    : header(std::move(other.header)), questions(std::move(other.questions)),
      answers(std::move(other.answers)), authorities(std::move(other.authorities)),
      additionals(std::move(other.additionals))
{
}

/* ------------------------------------------------------------------------------------------------------- */

Packet &
Packet::operator=(const Packet &other)
{
   if (this != &other)
   {
      header      = other.header;
      questions   = other.questions;
      answers     = other.answers;
      authorities = other.authorities;
      additionals = other.additionals;
   }
   return *this;
}

/* ------------------------------------------------------------------------------------------------------- */

Packet &
Packet::operator=(Packet &&other)
{
   if (this != &other)
   {
      header      = std::move(other.header);
      questions   = std::move(other.questions);
      answers     = std::move(other.answers);
      authorities = std::move(other.authorities);
      additionals = std::move(other.additionals);
   }
   return *this;
}

/* ------------------------------------------------------------------------------------------------------- */

Packet
Packet::from_buffer(PacketBuffer &buffer)
{
   return Packet();
}

/* ------------------------------------------------------------------------------------------------------- */
