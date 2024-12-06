#include "header.hpp"

/* ------------------------------------------------------------------------------------------------------- */

PacketHeader::PacketHeader(uint16_t   id,
                           bool       query_response,
                           uint8_t    op_code,
                           bool       authoritative_answer,
                           bool       truncated_message,
                           bool       recursion_desired,
                           bool       recursion_available,
                           uint8_t    reserved,
                           ResultCode response_code,
                           uint16_t   question_count,
                           uint16_t   answer_count,
                           uint16_t   authority_count,
                           uint16_t   additional_count)
    : id(id), query_response(query_response), op_code(op_code), authoritative_answer(authoritative_answer),
      truncated_message(truncated_message), recursion_desired(recursion_desired),
      recursion_available(recursion_available), reserved(reserved), response_code(response_code),
      question_count(question_count), answer_count(answer_count), authority_count(authority_count),
      additional_count(additional_count) {}

/* ------------------------------------------------------------------------------------------------------- */

PacketHeader::PacketHeader(const PacketHeader &other)
    : id(other.id), query_response(other.query_response), op_code(other.op_code),
      authoritative_answer(other.authoritative_answer), truncated_message(other.truncated_message),
      recursion_desired(other.recursion_desired), recursion_available(other.recursion_available),
      reserved(other.reserved), response_code(other.response_code), question_count(other.question_count),
      answer_count(other.answer_count), authority_count(other.authority_count),
      additional_count(other.additional_count) {}

/* ------------------------------------------------------------------------------------------------------- */

PacketHeader::PacketHeader(PacketHeader &&other) noexcept
    : id(other.id), query_response(other.query_response), op_code(other.op_code),
      authoritative_answer(other.authoritative_answer), truncated_message(other.truncated_message),
      recursion_desired(other.recursion_desired), recursion_available(other.recursion_available),
      reserved(other.reserved), response_code(other.response_code), question_count(other.question_count),
      answer_count(other.answer_count), authority_count(other.authority_count),
      additional_count(other.additional_count) {}

/* ------------------------------------------------------------------------------------------------------- */

/**
 * @brief
 * Parse a packet header from a buffer. The buffer must be at least 12 bytes long.
 *
 * @details
 * Use the following bit masking to extract the individual bits from the 16-bit flags field:
 *     1000000000000000 = 1 bit  = 0x8000 = Query/Response
 *     0111100000000000 = 4 bits = 0x7800 = Operation code
 *     0000010000000000 = 1 bit  = 0x0400 = Authoritative answer
 *     0000001000000000 = 1 bit  = 0x0200 = Truncated message
 *     0000000100000000 = 1 bit  = 0x0100 = Recursion desired
 *     0000000010000000 = 1 bit  = 0x0080 = Recursion available
 *     0000000001110000 = 3 bits = 0x0078 = Reserved
 *     0000000000001111 = 4 bits = 0x000F = Response code
 */
Result<PacketHeader>
PacketHeader::from_buffer(Ref<PacketBuffer> buf) {
   auto _ = buf->SeekRead(0);
   if (buf->GetReadRemaining() < 12) {
      return Error({ OUT_OF_BOUNDS, "Buffer overflowed while reading the header" });
   }

   PacketHeader header =
       PacketHeader(0, false, 0, false, false, false, false, 0, ResultCode::NO_ERROR, 0, 0, 0, 0);

   // 16 bits
   auto _id = buf->ReadUInt16().with_catch({ OUT_OF_BOUNDS, "Failed to read the ID field from buffer" });
   RETURN_IF_ERROR(_id);
   header.id = _id.get_value();

   // 16 bits
   auto _flags =
       buf->ReadUInt16().with_catch({ OUT_OF_BOUNDS, "Failed to read the _flags field from buffer" });
   RETURN_IF_ERROR(_flags);
   int flags = _flags.get_value();

   header.query_response       = (flags & 0b1000000000000000);   // 1 bit
   header.op_code              = (flags & 0b0111100000000000);   // 4 bits
   header.authoritative_answer = (flags & 0b0000010000000000);   // 1 bit
   header.truncated_message    = (flags & 0b0000001000000000);   // 1 bit
   header.recursion_desired    = (flags & 0b0000000100000000);   // 1 bit
   header.recursion_available  = (flags & 0b0000000010000000);   // 1 bit
   header.reserved             = (flags & 0b0000000001110000);   // 3 bits
   header.response_code        = static_cast<ResultCode>((flags & 0b0000000000001111));

   // 16 bits
   auto _question_count =
       buf->ReadUInt16().with_catch({ OUT_OF_BOUNDS, "Failed to read the question count" });
   RETURN_IF_ERROR(_question_count);
   header.question_count = _question_count.get_value();

   // 16 bits
   auto _answer_count = buf->ReadUInt16().with_catch({ OUT_OF_BOUNDS, "Failed to read the answer count" });
   RETURN_IF_ERROR(_answer_count);
   header.answer_count = _answer_count.get_value();

   // 16 bits
   auto _authority_count =
       buf->ReadUInt16().with_catch({ OUT_OF_BOUNDS, "Failed to read the authority count" });
   RETURN_IF_ERROR(_authority_count);
   header.authority_count = _authority_count.get_value();

   // 16 bits
   auto _additional_count =
       buf->ReadUInt16().with_catch({ OUT_OF_BOUNDS, "Failed to read the additional count" });
   RETURN_IF_ERROR(_additional_count);
   header.additional_count = _additional_count.get_value();

   return header;
}

/* ------------------------------------------------------------------------------------------------------- */

PacketHeader &
PacketHeader::operator=(const PacketHeader &other) {
   if (this != &other) {
      id                   = other.id;
      query_response       = other.query_response;
      op_code              = other.op_code;
      authoritative_answer = other.authoritative_answer;
      truncated_message    = other.truncated_message;
      recursion_desired    = other.recursion_desired;
      recursion_available  = other.recursion_available;
      reserved             = other.reserved;
      response_code        = other.response_code;
      question_count       = other.question_count;
      answer_count         = other.answer_count;
      authority_count      = other.authority_count;
      additional_count     = other.additional_count;
   }
   return *this;
}

/* ------------------------------------------------------------------------------------------------------- */

PacketHeader &
PacketHeader::operator=(PacketHeader &&other) noexcept {
   if (this != &other) {
      id                   = other.id;
      query_response       = other.query_response;
      op_code              = other.op_code;
      authoritative_answer = other.authoritative_answer;
      truncated_message    = other.truncated_message;
      recursion_desired    = other.recursion_desired;
      recursion_available  = other.recursion_available;
      reserved             = other.reserved;
      response_code        = other.response_code;
      question_count       = other.question_count;
      answer_count         = other.answer_count;
      authority_count      = other.authority_count;
      additional_count     = other.additional_count;
   }
   return *this;
}

/* ------------------------------------------------------------------------------------------------------- */

void
PacketHeader::Print(const std::string &name) const {
   /* Print title */
   char title[100];
   sprintf(title, "%s Packet Header", name.c_str());
   PrintAtCenter(title, "[", "]", true, true);

   /* Print data */
   printf("ID: %d\n", id);
   printf("Query/Response: %d\n", query_response);
   printf("Operation Code: %d\n", op_code);
   printf("Authoritative Answer: %d\n", authoritative_answer);
   printf("Truncated Message: %d\n", truncated_message);
   printf("Recursion Desired: %d\n", recursion_desired);
   printf("Recursion Available: %d\n", recursion_available);
   printf("Reserved: %d\n", reserved);
   printf("Response Code: %d\n", response_code);
   printf("Question Count: %d\n", question_count);
   printf("Answer Count: %d\n", answer_count);
   printf("Authority Count: %d\n", authority_count);
   printf("Additional Count: %d\n", additional_count);

   /* Print separator */
   // PrintSeparator();
}

/* ------------------------------------------------------------------------------------------------------- */
