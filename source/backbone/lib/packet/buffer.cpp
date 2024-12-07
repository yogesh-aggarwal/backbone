#include "buffer.hpp"

/* ------------------------------------------------------------------------------------------------------- */

PacketBuffer::PacketBuffer() : BasicBuffer<uint8_t, 512>(0) {}

/* ------------------------------------------------------------------------------------------------------- */

Result<std::string>
PacketBuffer::read_qname() {
   const int max_jumps = 5;

   size_t      pos             = get_read_index();
   bool        jumped          = false;
   int         jumps_performed = 0;
   std::string delim           = "";

   std::string result;
   while (true) {
      if (jumps_performed > max_jumps) {
         return Error(FAILED_TO_READ_QNAME, "Limit of 5 jumps in a DNS name exceeded.");
      }

      uint8_t len = get_at(pos).with_fallback(0).get_value();

      if ((len & 0xC0) == 0xC0) {
         if (!jumped) {
            auto res = seek_read(pos + 2);
            RETURN_IF_ERROR(res);
         }

         uint8_t b2     = get_at(pos + 1).with_fallback(0).get_value();
         size_t  offset = (((len ^ 0xC0) << 8) | b2);
         pos            = offset;

         jumped = true;
         jumps_performed += 1;

         continue;
      } else {
         pos += 1;

         if (len == 0) {
            break;
         }

         result += delim;

         auto str_buffer = get_range(pos, pos + len)
                               //
                               .with_catch(FAILED_TO_READ_LABEL, "Failed to read label from buffer.");
         RETURN_IF_ERROR(str_buffer);

         result += std::string(str_buffer.get_value().begin(), str_buffer.get_value().end());

         delim = ".";
         pos += len;
      }
   }

   if (!jumped) {
      auto res = seek_read(pos);
      RETURN_IF_ERROR(res);
   }

   return result;
}

/* ------------------------------------------------------------------------------------------------------- */

Result<void>
PacketBuffer::write_qname(std::string qname) {
   return Result<void>();
}

/* ------------------------------------------------------------------------------------------------------- */
