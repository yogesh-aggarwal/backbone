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
   auto _ = buf->seek_read(0);
   if (buf->get_read_remaining() < 12) {
      return Error({ OUT_OF_BOUNDS, "Buffer overflowed while reading the header" });
   }

   PacketHeader header =
       PacketHeader(0, false, 0, false, false, false, false, 0, ResultCode::NO_ERROR, 0, 0, 0, 0);

   // 16 bits
   auto _id = buf->read_uint16()
                  //
                  .with_catch(OUT_OF_BOUNDS, "Failed to read the ID field from buffer");
   RETURN_IF_ERROR(_id)
   header.id = _id.get_value();

   // 16 bits
   auto _flags = buf->read_uint16()
                     //
                     .with_catch(OUT_OF_BOUNDS, "Failed to read the _flags field from buffer");
   RETURN_IF_ERROR(_flags);
   uint16_t flags = _flags.get_value();

   header.query_response       = (flags & 0b1000000000000000);                            // 1 bit
   header.op_code              = (flags & 0b0111100000000000);                            // 4 bits
   header.authoritative_answer = (flags & 0b0000010000000000);                            // 1 bit
   header.truncated_message    = (flags & 0b0000001000000000);                            // 1 bit
   header.recursion_desired    = (flags & 0b0000000100000000);                            // 1 bit
   header.recursion_available  = (flags & 0b0000000010000000);                            // 1 bit
   header.reserved             = (flags & 0b0000000001110000);                            // 3 bits
   header.response_code        = static_cast<ResultCode>((flags & 0b0000000000001111));   // 4 bits

   // 16 bits
   auto _question_count = buf->read_uint16()
                              //
                              .with_catch(OUT_OF_BOUNDS, "Failed to read the question count");
   RETURN_IF_ERROR(_question_count);
   header.question_count = _question_count.get_value();

   // 16 bits
   auto _answer_count = buf->read_uint16()
                            //
                            .with_catch(OUT_OF_BOUNDS, "Failed to read the answer count");
   RETURN_IF_ERROR(_answer_count);
   header.answer_count = _answer_count.get_value();

   // 16 bits
   auto _authority_count = buf->read_uint16()
                               //
                               .with_catch(OUT_OF_BOUNDS, "Failed to read the authority count");
   RETURN_IF_ERROR(_authority_count);
   header.authority_count = _authority_count.get_value();

   // 16 bits
   auto _additional_count = buf->read_uint16()
                                //
                                .with_catch(OUT_OF_BOUNDS, "Failed to read the additional count");
   RETURN_IF_ERROR(_additional_count);
   header.additional_count = _additional_count.get_value();

   return header;
}

/* ------------------------------------------------------------------------------------------------------- */

Result<void>
PacketHeader::write_to_buffer(Ref<PacketBuffer> buf) const {
   auto res = Ok();

   // Seek to the beginning of the buffer
   res = buf->seek_write(0)
             //
             .with_catch(OUT_OF_BOUNDS, "Failed to write the header to buffer");
   RETURN_IF_ERROR(res)

   /* ID */
   res = buf->write_uint16(id)
             //
             .with_catch(OUT_OF_BOUNDS, "Failed to write the ID field to buffer");
   RETURN_IF_ERROR(res)

   /* Flags */
   uint16_t flags = (query_response << 15) | (op_code << 11) | (authoritative_answer << 10) |
                    (truncated_message << 9) | (recursion_desired << 8) | (recursion_available << 7) |
                    (reserved << 4) | response_code;
   res = buf->write_uint16(flags)
             //
             .with_catch(OUT_OF_BOUNDS, "Failed to write the flags field to buffer");
   RETURN_IF_ERROR(res)

   /* Question count */
   res = buf->write_uint16(question_count)
             //
             .with_catch(OUT_OF_BOUNDS, "Failed to write the question count");
   RETURN_IF_ERROR(res)

   /* Answer count */
   res = buf->write_uint16(answer_count)
             //
             .with_catch(OUT_OF_BOUNDS, "Failed to write the answer count");
   RETURN_IF_ERROR(res)

   /* Authority count */
   res = buf->write_uint16(authority_count)
             //
             .with_catch(OUT_OF_BOUNDS, "Failed to write the authority count");
   RETURN_IF_ERROR(res)

   /* Additional count */
   res = buf->write_uint16(additional_count)
             //
             .with_catch(OUT_OF_BOUNDS, "Failed to write the additional count");
   RETURN_IF_ERROR(res)

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

void
PacketHeader::print(const std::string &name) const {
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
