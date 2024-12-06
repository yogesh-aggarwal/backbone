#include "packet.hpp"

/* ------------------------------------------------------------------------------------------------------- */

Packet::Packet(PacketHeader                header,
               std::vector<PacketQuestion> questions,
               std::vector<PacketRecord>   answers,
               std::vector<PacketRecord>   authorities,
               std::vector<PacketRecord>   additionals)
    : header(header), questions(questions), answers(answers), authorities(authorities),
      additionals(additionals) {}

/* ------------------------------------------------------------------------------------------------------- */

Packet::Packet(const Packet &other)
    : header(other.header), questions(other.questions), answers(other.answers),
      authorities(other.authorities), additionals(other.additionals) {}

/* ------------------------------------------------------------------------------------------------------- */

Packet::Packet(Packet &&other)
    : header(std::move(other.header)), questions(std::move(other.questions)),
      answers(std::move(other.answers)), authorities(std::move(other.authorities)),
      additionals(std::move(other.additionals)) {}

/* ------------------------------------------------------------------------------------------------------- */

Packet &
Packet::operator=(const Packet &other) {
   if (this != &other) {
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
Packet::operator=(Packet &&other) {
   if (this != &other) {
      header      = std::move(other.header);
      questions   = std::move(other.questions);
      answers     = std::move(other.answers);
      authorities = std::move(other.authorities);
      additionals = std::move(other.additionals);
   }
   return *this;
}

/* ------------------------------------------------------------------------------------------------------- */

Result<Packet>
Packet::from_buffer(Ref<PacketBuffer> buffer) {
   /* Parse header */
   auto header = PacketHeader::from_buffer(buffer)
                     //
                     .with_catch({ FAILED_TO_PARSE_HEADER, "Failed to parse packet header" });
   if (header.is_error()) {
      return header.get_error();
   }

   /* Parse questions */

   /* Parse answers */

   /* Parse authorities */

   /* Parse additionals */

   return Packet(header.get_value(), {}, {}, {}, {});
}

/* ------------------------------------------------------------------------------------------------------- */
