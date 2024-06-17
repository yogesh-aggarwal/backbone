use crate::utility::packet_buffer::PacketBuffer;
use crate::utility::result::Result;

#[derive(Clone, Debug)]
pub struct DNSHeader {
    /**
     * 16-bits
     *
     * - A random identifier is assigned to query packets.
     * - Response packets must reply with the same id.
     * - This is needed to differentiate responses due to the stateless nature of UDP.
     */
    pub id: u16,
    /**
     * 1-bit
     *
     * - 0: Query
     * - 1: Response
     */
    pub query_response: bool,
    /**
     * 4-bits
     *
     * Typically always 0.
     * - 0: Standard query
     * - 1: Inverse query
     * - 2: Server status request
     * - 3-15: Reserved
     */
    pub op_code: u8,

    /**
     * 1-bit
     *
     * Whether the server is authoritative for the domain name in the query i.e. owns it.
     */
    pub authoritative_answer: bool,
    /**
     * 1-bit
     *
     * - Whether the message length exceeds 512 bytes or not.
     * - Traditionally a hint that the query can be reissued using TCP, for which the
     *   length limitation doesn't apply.
     */
    pub truncated_message: bool,

    /**
     * 1-bit
     *
     * Set by the sender of the request if the server should attempt to resolve the query
     * recursively if it does not have an answer readily available.
     */
    pub recursion_desired: bool,
    /**
     * 1-bit
     *
     * Set by the server to indicate whether or not recursive queries are allowed.
     */
    pub recursion_available: bool,

    /**
     * 3-bits
     *
     * Originally reserved for later use, but now used for DNSSEC queries.
     */
    pub reserved: u8,

    /**
     * 4-bits
     *
     * Set by the server to indicate the status of the response, i.e. whether or not it
     * was successful or failed, and in the latter case providing details about the cause
     * of the failure.
     *
     * - 0: No error
     * - 1: Format error
     * - 2: Server failure
     * - 3: Name error
     * - 4: Not implemented
     * - 5: Refused
     * - 6-15: Reserved
     */
    pub response_code: u8,

    /**
     * 16-bits
     *
     * The number of entries in the question section.
     */
    pub question_count: u16,
    /**
     * 16-bits
     *
     * The number of entries in the answer section.
     */
    pub answer_count: u16,
    /**
     * 16-bits
     *
     * The number of entries in the authority section.
     */
    pub authority_count: u16,
    /**
     * 16-bits
     *
     * The number of entries in the additional section.
     */
    pub additional_count: u16,
}

impl DNSHeader {
    pub fn new() -> DNSHeader {
        DNSHeader {
            id: 0,
            query_response: false,
            op_code: 0,
            authoritative_answer: false,
            truncated_message: false,
            recursion_desired: false,
            recursion_available: false,
            reserved: 0,
            response_code: 0,
            question_count: 0,
            answer_count: 0,
            authority_count: 0,
            additional_count: 0,
        }
    }

    pub fn from_buffer(buffer: &mut PacketBuffer) -> Result<DNSHeader> {
        let mut result = DNSHeader::new();

        result.id = buffer.read_as_u16()?;

        /*
        Use the following bit masking to extract the individual bits from the 16-bit flags field:
        * 0b1000000000000000 = 1 bit  = 0x8000 = Query/Response
        * 0b0111100000000000 = 4 bits = 0x7800 = Operation code
        * 0b0000010000000000 = 1 bit  = 0x0400 = Authoritative answer
        * 0b0000001000000000 = 1 bit  = 0x0200 = Truncated message
        * 0b0000000100000000 = 1 bit  = 0x0100 = Recursion desired
        * 0b0000000010000000 = 1 bit  = 0x0080 = Recursion available
        * 0b0000000001111000 = 3 bits = 0x0078 = Reserved
        * 0b0000000000001111 = 4 bits = 0x000F = Response code
        */
        let flags = buffer.read_as_u16()?;
        /* 1st bit */
        result.query_response = (flags & 0b1000000000000000) == 1;
        /* 2nd to 5th bit = 4 bits */
        result.op_code = (flags & 0b0111100000000000) as u8;
        /* 6th bit */
        result.authoritative_answer = (flags & 0b0000010000000000) == 1;
        /* 7th bit */
        result.truncated_message = (flags & 0b0000001000000000) == 1;
        /* 8th bit */
        result.recursion_desired = (flags & 0b0000000100000000) == 1;
        /* 9th bit */
        result.recursion_available = (flags & 0b0000000010000000) == 1;
        /* 10th to 12th bit = 3 bits */
        result.reserved = ((flags & 0b0000000001111000) >> 4) as u8;
        /* 13th to 16th bit = 4 bits */
        result.response_code = (flags & 0b0000000000001111) as u8;

        result.question_count = buffer.read_as_u16()?;
        result.answer_count = buffer.read_as_u16()?;
        result.authority_count = buffer.read_as_u16()?;
        result.additional_count = buffer.read_as_u16()?;

        Ok(result)
    }
}
