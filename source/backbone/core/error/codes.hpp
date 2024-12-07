#pragma once

/* ------------------------------------------------------------------------------------------------------- */

enum ErrorCode {
   /* Generic Error Codes */

   UNDEFINED = -1,
   UNKNOWN   = 0x0,

   /* Buffer Codes */
   OUT_OF_BOUNDS = 0x1,
   FAILED_TO_READ_QNAME,
   FAILED_TO_READ_LABEL,

   /* Packet Error Codes */
   PACKET_BUFFER_UNKNOWN = 0x2,

   PACKET_READ_CORRUPTED_BUFFER,
   PACKET_WRITE_CORRUPTED_BUFFER,

   PACKET_READ_CORRUPTED_HEADER,
   PACKET_READ_CORRUPTED_QUESTION,
   PACKET_READ_CORRUPTED_RECORD,
};

/* ------------------------------------------------------------------------------------------------------- */
